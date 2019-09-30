#include <vector>
#include <cstdint>
#include <tuple>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
#include <pybind11/eigen.h>

//typedef Eigen::Array<float_t, Eigen::Dynamic, 4, Eigen::RowMajor> Event_t;
typedef Eigen::Array<float_t, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> Event_t;
//typedef Eigen::Array<float_t, Eigen::Dynamic, Eigen::Dynamic> Event_t;
typedef Eigen::Matrix<uint64_t, Eigen::Dynamic, 1> VectorXull;

Event_t map_events(Eigen::Ref<Event_t> &in_events,
	 	std::tuple<int, int> in_shape,
	 	Eigen::Ref<VectorXull> &in_src,
	 	Eigen::Ref<VectorXull> &in_dst);
