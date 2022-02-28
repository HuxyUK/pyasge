#include <Engine/OpenGL/GLShader.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

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
    supported. Provided below is a working fragment shader that can be loaded
    and used to render a custom alpha channel effect.

    Example
    -------

    .. code-block:: c

      #version 330 core
      #define FRAG_COLOUR     0
      in VertexData
      {
          vec2    uvs;
          vec4    rgba;
      } fs_in;

      // user defined
      uniform float alpha;

      // engine related
      uniform sampler2D image;
      layout  (location = FRAG_COLOUR, index = 0) out vec4 fragColor;

      void main()
      {
          fragColor = vec4(fs_in.rgba.rgb, alpha) * texture(image, fs_in.uvs);
      }

    >>> self.renderer.shader = self.alpha_shader  # activates a shader globally
    >>> self.renderer.render(self.sprite)         # renders a sprite using it
    >>> self.renderer.shader = None               # resets and uses the default shader
    >>> self.renderer.render(self.sprite)         # renders a sprite using the default shader

  )")

    .def(py::init<>(), "Default constructor.")

    .def_property_readonly(
        "id",
         &ASGE::SHADER_LIB::GLShader::getShaderID,
         R"(Retrieves the shaders unique ID.)")

    .def(
        "uniform", &ASGE::SHADER_LIB::GLShader::getUniform,
        R"(
        Retrieves a uniform by its str name. This can be used to update the
        value of the global shader data. The name and type must match the
        variable defined inside the shader i.e. a uniform named alpha of
        type float must be addressed as such.

        Example
        -------
        >>> self.shader.uniform("alpha").set(float(1)) )",
        py::return_value_policy::reference)

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
