#include <map>
#include <utility>
#include <vector>
#include <iostream>
#include <stdexcept>

#include "dvs_mapping.h"

using std::vector;
using std::cerr;
using std::endl;
using std::max;
using std::min;
using std::invalid_argument;

namespace py = pybind11;

PYBIND11_MODULE(event_mapper, m) {
  m.doc() = "module to convert a sequence of images to an event stream";
  m.def("map", &map_events, py::call_guard<py::gil_scoped_release>(),
      "Updates events according to the input mapping: e[dst] <- e[src],\n"
      "where dst and src are raveled pixel coordinates.\n"
      "Note: src and dst can have duplicate values!\n\n"
      "Parameters\n"
      "----------\n"
      "events: 2D ndarray of floats\n"
      "\tevents before mapping. Shape is (N, 4). "
      "The first two elements represent (x,y) coordinates\n"
      "shape: tuple\n"
      "\t(height, width) is a sensor resolution\n"
      "src: 2D ndarray of integers\n"
      "\traveled indices of events before mapping\n"
      "dst: 2D ndarray of integers\n"
      "\traveled indices of events after mapping\n"
      "\n"
      "Returns\n"
      "-------\n"
      "events: 2D ndarray of floats\n"
      "\tevents after mapping"
      );
}
