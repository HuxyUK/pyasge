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

#include <Engine/SpriteBounds.hpp>
#include <pybind11/pybind11.h>
#include <sstream>
namespace py = pybind11;

void initSpritebounds(py::module& module)
{
  py::class_<ASGE::SpriteBounds>(
    module, "SpriteBounds", "A simple helper class for describing a sprite's boundaries.")

    .def_readwrite("v1", &ASGE::SpriteBounds::v1, "Top left")
    .def_readwrite("v2", &ASGE::SpriteBounds::v2, "Top right")
    .def_readwrite("v3", &ASGE::SpriteBounds::v3, "Bottom right")
    .def_readwrite("v4", &ASGE::SpriteBounds::v4, "Bottom left")

    .def("__repr__",
     [](const ASGE::SpriteBounds& bounds) {
       std::stringstream ss;
       ss << "ASGE SpriteBounds: (";
       ss << "v1: " << bounds.v1.toString() << ", ";
       ss << "v2: " << bounds.v2.toString() << ", ";
       ss << "v3: " << bounds.v3.toString() << ", ";
       ss << "v4: " << bounds.v4.toString() << ") ";

       return ss.str();
     });
}
