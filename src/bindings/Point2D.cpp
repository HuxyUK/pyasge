/*
  Copyright (c) 2021 James Huxtable. All rights reserved.

  This work is licensed under the terms of the MIT license.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#include "Engine/Point2D.hpp"
#include <pybind11/operators.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
namespace py = pybind11;
using namespace pybind11::literals;

void initPoint2D(py::module_ &m)
{
  py::class_<ASGE::Point2D>(m, "Point2D", "Represents a point in 2D.")
    .def(py::init())
    .def(py::init<float, float>(), "x"_a=0, "y"_a=0)
    .def(py::init<const ASGE::Point2D&>())
    .def(py::init([](std::array<float, 2> point) { return ASGE::Point2D(point[0], point[1]); }))
    .def(py::self == py::self)
    .def(py::self != py::self)
    .def(py::self += py::self)
    .def(py::self *= float())
    .def(py::self *  float())
    .def(float()  *  py::self)
    .def("distance", &ASGE::Point2D::distance, "Given two points, calculate the distance between them.")
    .def("midpoint", &ASGE::Point2D::midpoint, "Calculates the midpoint between two different points.")
    .def_readwrite("x", &ASGE::Point2D::x, "x coordinate")
    .def_readwrite("y", &ASGE::Point2D::y, "y coordinate")
    .def("__repr__", &ASGE::Point2D::toString, py::return_value_policy::move)
    .def("__str__",  &ASGE::Point2D::toString, py::return_value_policy::move);

    py::implicitly_convertible<py::tuple, ASGE::Point2D>();
    py::implicitly_convertible<py::list, ASGE::Point2D>();
}
