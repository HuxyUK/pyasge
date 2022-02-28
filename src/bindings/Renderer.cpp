#include <Engine/FileIO.hpp>
#include <Engine/OpenGL/GLFontSet.hpp>
#include <Engine/OpenGL/GLRenderTarget.hpp>
#include <Engine/OpenGL/GLRenderer.hpp>
#include <Engine/OpenGL/GLSprite.hpp>
#include <Engine/Renderer.hpp>
#include <filesystem>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
namespace py = pybind11;

void initRenderer(py::module_ &module) {
  py::class_<ASGE::GLRenderer>(
    module,
    "Renderer",
    py::is_final(),
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
    >>> self.renderer.setViewport(pyasge.ViewPort(0, 0, 1024, 768))
    >>> self.renderer.setProjectionMatrix(self.camera.view)
    >>> self.renderer.render(self.sprite)
    >>>
    >>> ''' render texture to screen '''
    >>> self.renderer.setRenderTarget(None)
    >>> self.renderer.setViewport(pyasge.ViewPort(0, 0, 1024, 768))
    >>> self.renderer.render(self.sprite)
    >>>
  )")

    .def(
      "createNonCachedTexture",
      [](ASGE::GLRenderer& self, const std::string& path)
      { return dynamic_cast<ASGE::GLTexture*>(self.createNonCachedTexture(path)); },
      py::return_value_policy::automatic,
      py::arg("file"),
      "Attempts to create a non-cached texture file by loading a local "
      "file.")

    .def(
      "createNonCachedTexture",
      [](ASGE::GLRenderer& self, int width, int height, ASGE::Texture2D::Format format, void* data)
      {
        return dynamic_cast<ASGE::GLTexture*>(
          self.createNonCachedTexture(width, height, format, data));
      },
      py::return_value_policy::automatic,
      py::arg("width"),
      py::arg("height"),
      py::arg("format"),
      py::arg("data"),
      R"(Creates a non-cached texture of a given size and format.)")

    .def(
        "createCachedTexture",
        py::overload_cast<const std::string&>(&ASGE::GLRenderer::createCachedTexture),
        py::arg("id"),py::return_value_policy::automatic_reference,
        "Loads a texture using the rendering cache subsystem.")

    .def(
        "loadTexture",
        py::overload_cast<const std::string&>(&ASGE::GLRenderer::createCachedTexture),
        py::arg("path"), py::return_value_policy::automatic_reference,
        "Loads a texture using the rendering cache subsystem.")

    .def(
      "getDefaultFont",
      [](const ASGE::GLRenderer& self)
      { return std::ref(dynamic_cast<const ASGE::GLFontSet&>(self.getDefaultFont())); },
      py::return_value_policy::reference,
      "Returns the Engine's default font.")

    .def(
      "render",
      [](ASGE::GLRenderer& self, const ASGE::GLSprite& sprite) { self.render(sprite); },
      py::arg("sprite"))

    .def(
      "render",
      [](ASGE::GLRenderer& self, const ASGE::Tile& tile, float x, float y) { self.render(tile, {x, y}); },
      py::arg("tile"),
      py::arg("x"),
      py::arg("y"))

    .def(
      "render",
      [](ASGE::GLRenderer& self, const ASGE::Text& text) { self.render(text); },
      py::arg("text"))

    .def(
      "render",
      [](ASGE::GLRenderer& self, ASGE::GLTexture& texture, int x, int y, int16_t z)
      {
          self.ASGE::Renderer::render(
          texture, {static_cast<float>(x),static_cast<float>(y)}, z);
      },
      py::arg("texture"),
      py::arg("x"),
      py::arg("y"),
      py::arg("z") = 0)

    .def(
      "render",
      [](ASGE::GLRenderer& self, ASGE::GLTexture& texture, int x, int y, int width, int height, int16_t z)
      {
        self.render(
        texture,
        {0, 0, static_cast<float>(texture.getWidth()), static_cast<float>(texture.getHeight())},
        ASGE::Point2D{static_cast<float>(x),static_cast<float>(y)}, width, height, z);
      },
      py::arg("texture"),
      py::arg("x"),
      py::arg("y"),
      py::arg("width"),
      py::arg("height"),
      py::arg("z") = 0)

    .def(
      "render",
      [](ASGE::GLRenderer& self, ASGE::GLTexture& texture, const py::list& rect, int x, int y, int width, int height, int16_t z)
      {
        self.render(
        texture,
        {rect[0].cast<float>(), rect[1].cast<float>(), rect[2].cast<float>(), rect[3].cast<float>()},
        ASGE::Point2D{static_cast<float>(x),static_cast<float>(y)}, width, height, z);
      },
      py::arg("texture"),
      py::arg("rect"),
      py::arg("x"),
      py::arg("y"),
      py::arg("width"),
      py::arg("height"),
      py::arg("z") = 0)

    .def(
      "setProjectionMatrix",
      py::overload_cast<float, float, float, float>(&ASGE::GLRenderer::setProjectionMatrix),
      py::arg("x"),
      py::arg("y"),
      py::arg("width"),
      py::arg("height"))

    .def(
      "setProjectionMatrix",
      py::overload_cast<const ASGE::Camera::CameraView&>(&ASGE::GLRenderer::setProjectionMatrix),
      py::arg("camera_view"))

    .def(
      "setProjectionMatrix",
      [](ASGE::GLRenderer& self, py::array_t<float, py::array::c_style | py::array::forcecast> array){
        py::buffer_info info = array.request();

        if (info.format != py::format_descriptor<float>::format())
          throw std::runtime_error("Incompatible format: expected a float array!");

        if (info.ndim != 1)
          throw std::runtime_error("Incompatible array dimension!");

        if (info.size != 4)
          throw std::runtime_error("Incompatible number of elements!");

        ASGE::Camera::CameraView view{};
        memcpy(&view, array.data(), sizeof(float) * 4);
        self.setProjectionMatrix(view);
        },
      py::arg("camera_view"))

    .def(
      "setRenderTarget",
      [](ASGE::GLRenderer& self, ASGE::GLRenderTarget* target)
      { self.setRenderTarget(target); },
      "Sets a render target to use for rendering.")

    .def(
      "initPixelShader",
      [](ASGE::GLRenderer& self, const std::string& source)
      { return dynamic_cast<ASGE::SHADER_LIB::GLShader*>(self.initPixelShader(source)); },
      py::return_value_policy::reference_internal,
      py::arg("shader_source"),
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
      [](ASGE::GLRenderer& self, const std::string& path)
      { return dynamic_cast<ASGE::SHADER_LIB::GLShader*>(self.initPixelShaderFromFile(path)); },
      py::return_value_policy::reference_internal,
      "Loads and initialises a pixel shader from a local file.")

    .def_property(
      "shader",
      [](ASGE::GLRenderer& self) { return self.getActiveShader(); },
      [](ASGE::GLRenderer& self, ASGE::SHADER_LIB::GLShader* shader)
      { self.setActiveShader(shader); },
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

    .def(
      "setViewport",
      &ASGE::GLRenderer::setViewport,
      R"(
      The viewport that maps to the rendered window.

      :setter: Updates the renderer's viewport used for mapping to the window.
      :type: :class:`Viewport`

      Example
      -------
      >>> self.renderer.setViewport(pyasge.Viewport(0, 0, 1024, 768))
    )")

    .def_property_readonly(
      "resolution_info",
      &ASGE::GLRenderer::getResolutionInfo,
      R"(
      The renderer's resolution information.

      The renderer is responsible for overseeing the current window and
      desktop resolutions as well as the most recently applied viewport
      and camera views. All of this information can easily be retrieved
      using this function. For example, it's simple to obtain the window's
      width and height or the currently set viewport.

      .. note::
        When the user requests a new viewport or camera view, the renderer
        stores this request in a render state. This state is then attached
        to the rendering batches and they will apply these settings when it
        comes time to dispatch the draw counts.

      :getter: Returns the resolution and current render view settings.
      :type: pyasge.Resolution
    )")

    .def("setClearColour",
    [](ASGE::GLRenderer& self, const ASGE::Colour colour)
    {
      self.setClearColour(colour);
    }, py::arg("colour"),
      R"(
      The colour used to clear the buffer each frame.

      When clearing the window's content each tick, the colour to use can
      easily be adjusted by using this function. Calling it means the
      an empty non-rendered area of the window will know be the colour
      passed through to this function.

      :setter: Sets the clear colour for the Window.
      :type: pyasge.Colour

      Example
      -------
      >>> self.renderer.setClearColour(pyasge.COLOURS.BLACK)
    )")

    .def(
        "setBaseResolution",
        &ASGE::GLRenderer::setBaseResolution,
        py::arg("width"), py::arg("height"), py::arg("policy"), R"(
        The base design resolution of the game.

        When designing the game this resolution is used to control how the screen is
        mapped when using a different resolution, whether that be smaller or larger.
        When used correctly sprites positioned on the screen will remain in their
        relative location (depending on the chosen resolution policy).)")

    .def(
        "setResolutionPolicy",
        &ASGE::GLRenderer::setResolutionPolicy, py::arg("policy"), R"(
        Sets the resolution policy to use.

        The resolution policy controls how the game's view will be mapped to the window
        or to any attached render target. Depending on the policy applied, the view may
        be centered, bordered, stretched or even maintain it's aspect ration. This is
        used when the game view does not directly map to the viewport.

        .. code-block::
           :caption: Example

           >>> self.renderer.setResolutionPolicy(pyasge.ResolutionPolicy.CENTER)

        .. note::
          If using a custom viewport, it's recommended to set it after this function
          call, to ensure its size is correct.

        .. seealso::
          pyasge.ResolutionPolicy )")

    .def(
      "loadFont",
      [](ASGE::GLRenderer& self, const std::string_view path, int size, double range) -> const ASGE::GLFontSet*
      {
        const std::filesystem::path FS_PATH(path);
        if (std::filesystem::exists(FS_PATH))
        {
          return dynamic_cast<const ASGE::GLFontSet*>(self.loadFont(path.data(), size, range));
        }

        // try asge IO now
        ASGE::FILEIO::File file;
        if (file.open(path.data()))
        {
          ASGE::FILEIO::IOBuffer buffer = file.read();
          return dynamic_cast<const ASGE::GLFontSet*>(
                  self.loadFontFromMem(path.data(), buffer.as_unsigned_char(), buffer.length, size, range));
        }

        return nullptr;
      },
      py::return_value_policy::reference,
      py::arg("path"),
      py::arg("size"),
      py::arg("range") = 2.0,
      R"(
      Loads a font from the file system.

      In order to render fonts the renderer needs to generate a texture atlas.
      This atlas stores each glyph that might need to be rendered along with
      its respective UV co-ordinates. Once loaded a font can be assigned to
      any text that needs rendering.

      Note
      ----
      If the font file can not be loaded successfully, None will be returned.
    )")

    .def(
      "loadFontAtlas",
       [](ASGE::GLRenderer &self, ASGE::Font::AtlasMetrics metrics, const std::string &img_path,
          const std::string &csv_path) -> const ASGE::GLFontSet *
      {
         return dynamic_cast<const ASGE::GLFontSet *>(self.loadFontAtlas(std::move(metrics), img_path, csv_path));
       },
       py::return_value_policy::reference,
       py::arg("metrics"),
       py::arg("img_path"),
       py::arg("csv_path"),
      R"(
      Loads a font atlas from the file system.

      Use msdf-atlas-gen to create a font atlas, which can then be imported
      in to the game. In order to successfully map the glyph information it
      needs additional data on both the font face metrics but also the glyph
      positioning. The metrics are provided using a `AtlasMetric` data structure
      and the UV positioning and unicode information via a CSV file. Using these
      a font can be loaded without having to rely on runtime generation.

      Note
      ----
      If the font file can not be loaded successfully, None will be returned.
    )");
}
