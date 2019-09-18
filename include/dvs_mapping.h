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

namespace py = pybind11;

Event_t map_events(py::EigenDRef<Event_t> &in_events,
	 	std::tuple<int, int> in_shape,
	 	py::EigenDRef<VectorXull> &in_src,
	 	py::EigenDRef<VectorXull> &in_dst);
