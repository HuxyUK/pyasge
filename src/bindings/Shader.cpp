#include <Engine/OpenGL/GLShader.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>

PYBIND11_MAKE_OPAQUE(std::map<std::string, ASGE::SHADER_LIB::uniform_ptr>);

namespace py = pybind11;
void initShader(py::module_ & module)
{
  py::class_<ASGE::SHADER_LIB::GLShader>(
    module,
    "Shader",
    R"(
    A shader in the context of ASGE is a pixel shader.

    Due to the nature of the 2D game engine and for ease of use, the vertex
    shader is fixed and not easily adjustable, which means the inputs in to the
    fragment shaders remain consistent. At present only uniform mapping is
    provided, the addition of extra samplers within the pixel shader is not
    supported.
  )")

    .def(py::init<>(), "Default constructor.")

    .def_property_readonly(
      "id", &ASGE::SHADER_LIB::GLShader::getShaderID, R"(Retrieves the shaders unique ID.)")

    .def("uniform", &ASGE::SHADER_LIB::GLShader::getUniform, "Retrieves a uniform by its str name.")

    .def_property_readonly(
      "uniforms",
      [](ASGE::SHADER_LIB::GLShader& self) {
        py::list list;
        for (auto& iter : self.getUniforms())
        {
          list.append(iter.first.c_str());
        }
        return list;
      },
      R"(List of all mapped and available uniforms.)");
}
