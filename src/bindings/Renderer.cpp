#include <Engine/FileIO.hpp>
#include <Engine/OpenGL/GLFontSet.hpp>
#include <Engine/OpenGL/GLRenderTarget.hpp>
#include <Engine/OpenGL/GLRenderer.hpp>
#include <Engine/OpenGL/GLSprite.hpp>
#include <Engine/Renderer.hpp>
#include <filesystem>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
namespace py = pybind11;

void initRenderer(py::module_ &module) {
  py::class_<ASGE::GLRenderer>(module, "Renderer", py::is_final(),
    R"(
    An OpenGL renderer.

    The renderer is the heart and sole of the engine. It's responsible for
    managing rendering, shaders, input initialisation, the window etc. ASGE
    currently only supports OpenGL but utilises two different renderers based
    on the supported OpenGL version available. The modern renderer which targets
    4.5+, will make use of features such as SSBOs and named bindings. The legacy
    renderer is retained to allow support on Mac OSX and older GPU drivers and
    requires OpenGL 3.3, but not maintain feature parity going forwards.

    A copy of the renderer is attached to each ASGEGame and can be used for
    rendering, managing textures, updating pixel buffers and basic window
    management.

    Example
    -------
    >>> '''load font and create text instance'''
    >>> font = self.renderer.loadFont("/data/fonts/font.ttf", 40)
    >>> text = pyasge.Text(self.font, "Hello World")
    >>>
    >>> ''' render to texture '''
    >>> self.renderer.setRenderTarget(self.rt)
    >>> self.renderer.viewport = pyasge.ViewPort(0, 0, 1024, 768)
    >>> self.renderer.setProjectionMatrix(self.camera.view)
    >>> self.renderer.render(self.sprite)
    >>>
    >>> ''' render texture to screen '''
    >>> self.renderer.setRenderTarget(None)
    >>> self.renderer.viewport = pyasge.ViewPort(0, 0, 1024, 768)
    >>> self.renderer.render(self.sprite)
    >>>
  )")

      .def(
          "createNonCachedTexture",
          [](ASGE::GLRenderer &self, const std::string &path) {
            return dynamic_cast<ASGE::GLTexture *>(
                self.createNonCachedTexture(path));
          },
          py::return_value_policy::automatic, py::arg("file"),
          "Attempts to create a non-cached texture file by loading a local "
          "file.")

      .def(
          "createNonCachedTexture",
          [](ASGE::GLRenderer &self, int width, int height,
             ASGE::Texture2D::Format format, void *data) {
            return dynamic_cast<ASGE::GLTexture *>(
                self.createNonCachedTexture(width, height, format, data));
          },
          py::return_value_policy::automatic, py::arg("width"),
          py::arg("height"), py::arg("format"), py::arg("data"),
          R"(Creates a non-cached texture of a given size and format.)")

      .def(
          "getDefaultFont",
          [](const ASGE::GLRenderer &self) {
            return std::ref(
                dynamic_cast<const ASGE::GLFontSet &>(self.getDefaultFont()));
          },
          py::return_value_policy::reference,
          "Returns the Engine's default font.")

      .def(
          "render",
          [](ASGE::GLRenderer &self, const ASGE::GLSprite &sprite) {
            self.renderSprite(sprite);
          },
          py::arg("sprite"))

      .def(
          "render",
          [](ASGE::GLRenderer &self, const ASGE::Text &text) {
            self.renderText(text);
          },
          py::arg("text"))

      .def(
          "render",
          [](ASGE::GLRenderer &self, ASGE::GLTexture &texture, int x, int y) {
            self.render(texture, x, y);
          },
          py::arg("texture"), py::arg("x"), py::arg("y"))

      .def("setProjectionMatrix",
           py::overload_cast<float, float, float, float>(
               &ASGE::GLRenderer::setProjectionMatrix),
           py::arg("x"), py::arg("y"), py::arg("width"), py::arg("height"))

      .def("setProjectionMatrix",
           py::overload_cast<const ASGE::Camera::CameraView &>(
               &ASGE::GLRenderer::setProjectionMatrix),
           py::arg("camera_view"))

      .def(
          "setRenderTarget",
          [](ASGE::GLRenderer &self, const ASGE::GLRenderTarget *target) {
            self.setRenderTarget(target);
          },
          "Sets a render target to use for rendering.")

      .def(
          "initPixelShader",
          [](ASGE::GLRenderer &self, const std::string &source) {
            return dynamic_cast<ASGE::SHADER_LIB::GLShader *>(
                self.initPixelShader(source));
          },
          py::return_value_policy::reference_internal, py::arg("shader_source"),
      R"(
      Initialises a pixel shader from a str.

      :returns: The initialised pixel shader.
      :type: pyasge.Shader

      Example
      -------
      >>> frag_shader = """
      >>> #version 330 core
      >>> #define FRAG_COLOUR     0
      >>> in VertexData
      >>> {
      >>>   vec2    uvs;
      >>>   vec4    rgba;
      >>> } fs_in;
      >>> uniform float alpha;
      >>> uniform sampler2D image;
      >>> layout  (location = FRAG_COLOUR, index = 0) out vec4 FragColor;
      >>> void main()
      >>> {
      >>>    FragColor = vec4(fs_in.rgba.rgb, alpha) * texture(image, fs_in.uvs);
      >>> }
      >>> """
      >>>
      >>> inline_shader = self.renderer.initPixelShader(frag_shader)
    )")

      .def(
          "loadPixelShader",
          [](ASGE::GLRenderer &self, const std::string &path) {
            return dynamic_cast<ASGE::SHADER_LIB::GLShader *>(
                self.initPixelShaderFromFile(path));
          },
          py::return_value_policy::reference_internal,
          "Loads and initialises a pixel shader from a local file.")

      .def_property(
          "shader",
          [](ASGE::GLRenderer &self) { return self.getActiveShader(); },
          [](ASGE::GLRenderer &self, ASGE::SHADER_LIB::GLShader *shader) {
            self.setActiveShader(shader);
          },
      R"(
      The renderer's currently assigned shader.

      :getter: Returns the renderer's current shader.
      :setter: Changes the currently active shader used for rendering.
      :type: pyasge.Shader

      Example
      -------
      >>> self.alpha_shader.uniform("alpha").set(0.2)
      >>> self.renderer.shader = self.alpha_shader
      >>> self.renderer.render(self.sprite)
    )")

      .def_property("viewport", &ASGE::GLRenderer::getViewport,
                    &ASGE::GLRenderer::setViewport,
      R"(
      The viewport that maps to the rendered window.

      :getter: Returns the renderer's current viewport.
      :setter: Updates the renderer's viewport used for mapping to the window.
      :type: pyasge.ViewPort

      Example
      -------
      >>> self.renderer.viewport = pyasge.Viewport(0, 0, 1024, 768)
    )")

      .def(
          "loadFont",
          [](ASGE::GLRenderer &self, const std::string_view path,
             int size) -> const ASGE::GLFontSet & {
            const std::filesystem::path FS_PATH(path);
            if (std::filesystem::exists(FS_PATH)) {
              return dynamic_cast<const ASGE::GLFontSet &>(
                  self.getFont(self.loadFont(path.data(), size)));
            }

            // try asge IO now
            ASGE::FILEIO::File file;
            if (file.open(path.data())) {
              ASGE::FILEIO::IOBuffer buffer = file.read();
              return dynamic_cast<const ASGE::GLFontSet &>(self.getFont(
                  self.loadFontFromMem(path.data(), buffer.as_unsigned_char(),
                                       buffer.length, size)));
            }

            return dynamic_cast<const ASGE::GLFontSet &>(self.getDefaultFont());
          },
          py::return_value_policy::reference, py::arg("path"), py::arg("size"),
      R"(
      Loads a font from the file system.

      In order to render fonts the renderer needs to generate a texture atlas.
      This atlas stores each glyph that might need to be rendered along with
      its respective UV co-ordinates. Once loaded a font can be assigned to
      any text that needs rendering.

      Note
      ----
      If the font file can not be loaded successfully, the renderer's inbuilt
      font used for debugging will be returned.
  )");
}
