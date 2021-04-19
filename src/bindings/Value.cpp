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

#include <Engine/Value.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;
namespace {
  template<typename T>
  void declare_value(py::module_ &m, std::string &&type) {
    using Class = ASGE::Value<T>;
    std::string pyclass_name = std::string("Value") + type;
    py::class_<Class>(m, pyclass_name.c_str(), py::buffer_protocol(), py::is_final())
      .def(py::init<>())
      .def("get", [](ASGE::Value<T>& self) { return std::any_cast<T*>(self.get()); })
      .def("set", [](ASGE::Value<T>& self, T value) { self.set(value); })
      .def("value", [](ASGE::Value<T>& self) { return std::any_cast<T*>(self.get()); });
  }
}  // namespace

void initValue(py::module_ & module) {
  py::class_<ASGE::ValueBase>(module, "Value", py::buffer_protocol(), py::is_final(),
    R"(A generic value storing class.

       The value class uses std::any to store an object of any type. By using
       this templated version the data can be stored internally and access to
       it is controlled safely via the std::any wrapper. If an incorrect type is
       used an exception is thrown. In python this of less interest, but is used
       in ASGE for storing things like uniform mappings.

       Example
       -------
         >>> self.alpha_shader = self.renderer.loadPixelShader("/data/shaders/alpha.frag")
         >>> print(self.alpha_shader.uniform("alpha").value)
         >>> self.alpha_shader.uniform("alpha").set(0.2)
  )")

    .def("set",  [](ASGE::ValueBase& self, bool  v)  { self.set(v); }, py::arg("value"))
    .def("set",  [](ASGE::ValueBase& self, int   v)  { self.set(v); }, py::arg("value"))
    .def("set",  [](ASGE::ValueBase& self, float v)  { self.set(v); }, py::arg("value"))
    .def("set",  [](ASGE::ValueBase& self, std::array<bool, 2> v)  { self.set(v); }, py::arg("value"))
    .def("set",  [](ASGE::ValueBase& self, std::array<float,2> v)  { self.set(v); }, py::arg("value"))
    .def("set",  [](ASGE::ValueBase& self, std::array<float,3> v)  { self.set(v); }, py::arg("value"))
    .def("set",  [](ASGE::ValueBase& self, std::array<float,4> v)  { self.set(v); }, py::arg("value"))
    .def("set",  [](ASGE::ValueBase& self, std::array<std::array<float, 2>, 2> v)  { self.set(v); }, py::arg("value"))
    .def("set",  [](ASGE::ValueBase& self, std::array<std::array<float, 4>, 4> v)  { self.set(v); }, py::arg("value"))

    .def_property_readonly(
      "value",
      [](ASGE::ValueBase& self) {
        if (auto* cast = dynamic_cast<ASGE::Value<float>*>(&self); cast != nullptr)
        {
          return py::cast(std::any_cast<float*>(self.get()));
        }
        if (auto* cast = dynamic_cast<ASGE::Value<int>*>(&self); cast != nullptr)
        {
          return py::cast(std::any_cast<int*>(self.get()));
        }
        if (auto* cast = dynamic_cast<ASGE::Value<bool>*>(&self); cast != nullptr)
        {
          return py::cast(std::any_cast<bool*>(self.get()));
        }
        if (auto* cast = dynamic_cast<ASGE::Value<std::array<bool, 2>>*>(&self); cast != nullptr)
        {
          return py::cast(std::any_cast<std::array<bool, 2>*>(self.get()));
        }
        if (auto* cast = dynamic_cast<ASGE::Value<std::array<float, 2>>*>(&self); cast != nullptr)
        {
          return py::cast(std::any_cast<std::array<float, 2>*>(self.get()));
        }
        if (auto* cast = dynamic_cast<ASGE::Value<std::array<float, 3>>*>(&self); cast != nullptr)
        {
          return py::cast(std::any_cast<std::array<float, 3>*>(self.get()));
        }
        if (auto* cast = dynamic_cast<ASGE::Value<std::array<float, 4>>*>(&self); cast != nullptr)
        {
          return py::cast(std::any_cast<std::array<float, 4>*>(self.get()));
        }
        if (auto* cast = dynamic_cast<ASGE::Value<std::array<std::array<float, 2>, 2>>*>(&self); cast != nullptr)
        {
          return py::cast(std::any_cast<std::array<std::array<float, 2>, 2>*>(self.get()));
        }
        if (auto* cast = dynamic_cast<ASGE::Value<std::array<std::array<float, 4>, 4>>*>(&self); cast != nullptr)
        {
          return py::cast(std::any_cast<std::array<std::array<float, 4>, 4>*>(self.get()));
        }
        return py::cast(0);
      });
}
