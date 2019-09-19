#include <transformation.h>
#include <numeric>
#include <iostream>
#include <stdexcept>

using py::EigenDRef;

using namespace pybind11::literals; // to bring in the `_a` literal

using std::vector;
using std::pair;
using std::get;
using std::make_pair;
using std::unordered_map;
using std::invalid_argument;
using std::runtime_error;

typedef pair<int, int> mindex_t; // (y, x)
typedef pair<int, int> shape_t;	 // (height, width)

int ravel_multi_index(const mindex_t &mindex, const shape_t &shape) {
	return mindex.first * shape.second + mindex.second;
}

mindex_t unravel_index(int index, const shape_t &shape) {
	return make_pair<int, int>(index / shape.second, index % shape.second);
}

template<int I, int J, class... T>
auto to_pair(std::tuple<T...> t)
	-> decltype(std::make_pair(std::get<I>(t), std::get<J>(t))) {
	return std::make_pair(std::get<I>(t), std::get<J>(t));
}

Event_t map_events(EigenDRef<Event_t> &in_events,
	 	std::tuple<int, int> in_shape,
	 	EigenDRef<VectorXull> &in_src,
	 	EigenDRef<VectorXull> &in_dst) {

	long int mapping_size = in_src.rows();
	if (in_dst.rows() != mapping_size)
		throw invalid_argument("src and dst should have the same size!");

  if (!in_events.IsRowMajor)
		throw invalid_argument("Events should be a row-major matrix");

	shape_t shape = to_pair<0, 1>(in_shape);

	// compute list of dst indices for each src index
	unordered_map<int, vector<int>> mapping;
	auto src_ptr = in_src.data();
	auto dst_ptr = in_dst.data();
  for (auto idx = 0U; idx < mapping_size; ++idx)
		mapping[src_ptr[idx]].push_back(dst_ptr[idx]);

	// compute number of output events
	size_t num_output = 0;
	size_t num_events = in_events.rows();
	size_t event_size = in_events.cols();
	for (auto idx = 0U; idx < num_events; ++idx) {
		auto *event_ptr = in_events.row(idx).data();
		num_output += mapping[ravel_multi_index(make_pair<int, int>(event_ptr[1], event_ptr[0]), shape)].size();
	}
  
	// allocate memory for output events
	Event_t out_events = Event_t::Zero(num_output, event_size);
	if (!out_events.IsRowMajor)
		runtime_error("I want to make a row-major matrix for events, but made a column-major");

	// write output
	int j = 0;
	for (auto idx = 0U; idx < num_events; ++idx) {
		auto event_ptr = in_events.row(idx).data();
		auto pixel_mapping = mapping[ravel_multi_index(make_pair<int, int>(event_ptr[1], event_ptr[0]), shape)];

		for (auto out_idx: pixel_mapping) {
			auto mindex = unravel_index(out_idx, shape);
			auto out_ptr = out_events.row(j++).data();
			out_ptr[0] = mindex.second;
			out_ptr[1] = mindex.first;
			memcpy(out_ptr+2, event_ptr+2, (event_size - 2) * sizeof(float));
		}
	}
	return out_events;
}
