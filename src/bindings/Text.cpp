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

#include <Engine/OpenGL/GLFontSet.hpp>
#include <Engine/Text.hpp>
#include <pybind11/pybind11.h>
namespace py = pybind11;
void initText(py::module_ &module) {
  py::class_<ASGE::Text> text(
      module, "Text",
      R"(
      Text is designed to allow rendering of text to the screen.

      Rendering text to a screen is not a simple process. There are lots of
      parameters involved, which can result in many different overloaded
      render functions. To resolve this, the pyasge.Text was created. All the
      information needed to successfully render text to the screen is stored
      within the struct. This includes positioning, colours, scaling, the text
      and even the font face to use.

      Advantages of using this class allow a single instance to be constructed
      and used repeatedly as well as the ability to add additional features to
      the Text class without having to modify the renderer API.

      **Positioning**

      There are always a lot of questions around positioning of text on the
      screen. The issue comes from the x and y actually controlling the position
      of the baseline. The baseline is the point at which all characters should
      lay along and allows consistent positioning of text irrespective of the
      strings context.

       .. figure:: https://www.freetype.org/freetype2/docs/glyphs/layout.png
          :alt: https://www.freetype.org/freetype2/docs/glyphs/glyphs-3.html

          The FreeType project

      Example
      -------
         >>> """load font and create text instance"""
         >>> self.font = self.renderer.loadFont("/data/fonts/font.ttf", 40)
         >>> self.text = pyasge.Text(self.font, "Hello World")
         >>> self.text.colour = pyasge.COLOURS.AQUA
         >>> self.text.opacity = 0.5
         >>> self.text.scale = 0.75
         >>> self.text.position = pyasge.Point2D(200, 200)
         >>> self.renderer.renderText(self.text)

      Warning
      -------
      In order for text to be rendered and for any width and height calculations
      to be performed a font face is required. If a font face is not provided the
      width and height functions will return 0 and the renderer will fallback on
      the engine's debug font for rendering.
)");

  // Constructors
  text.def(py::init<const ASGE::GLFontSet&>(), py::arg("Font"));
  text.def(py::init<const ASGE::GLFontSet&, const std::string&>(), py::arg("Font"), py::arg("string"));
  text.def(py::init<const ASGE::GLFontSet&, const std::string&, int, int>(), py::arg("Font"), py::arg("string"), py::arg("x"), py::arg("y"));
  text.def(py::init<const ASGE::GLFontSet&, const std::string&, int, int, const ASGE::Colour&>(), py::arg("Font"), py::arg("string"), py::arg("x"), py::arg("y"), py::arg("colour"));

  text.def(
      "validFont", &ASGE::Text::validFont,
      R"(
      Does the text instance have a valid font to render with?

      Checks to see if a valid font has been attached to the text object.
      An invalid font would be one where the value is None

      :returns: True if the font is not None
      :type: bool
  )");

  // Readonly Properties
  text.def_property_readonly(
      "height", &ASGE::Text::getHeight,
      R"(
      Returns the expected rendered height of the text.

      Attempts to calculate the output height of the text using the assigned
      font face. Scaling will also have an impact on the end result.

      :returns: The height of the rendered string.
      :type: float
  )");

  text.def_property_readonly(
      "width", &ASGE::Text::getWidth,
      R"(
      Returns the expected rendered width of the text.

      Attempts to calculate the output width of the text using the assigned
      font face. Scaling will also have an impact on the end result.

      :returns: The width of the rendered string.
      :type: float
  )");

  text.def_property_readonly(
      "line_spacing", &ASGE::Text::getLineSpacing,
      R"(
      Attempts to calculate the spacing between lines.

      :returns: The expected spacing between each line of text.
      :type: int
  )");

  text.def_property("opacity", &ASGE::Text::getOpacity, &ASGE::Text::setOpacity,
      R"(
      The opacity of the text.

      Controls the alpha channel used to render the text. Values closer to 0
      will make the text more transparent and values closer to 1 will make it
      more opaque.

      :getter: Returns the text's opacity.
      :setter: Sets the text's rendered opacity by adjusting the alpha channel.
      :type: float
  )");

  text.def_property(
      "scale", &ASGE::Text::getScale, &ASGE::Text::setScale,
      R"(
      The scale to apply to the text output.

      :getter: Returns the text's scale factor.
      :setter: Updates the scale factor to use.
      :type: float
  )");

  text.def_property(
      "z_order", &ASGE::Text::getZOrder, &ASGE::Text::setZOrder,
      R"(
      The z-order level to use.

      Z-ordering controls the rendering order. This is important to ensure
      certain elements of the game are rendered before others. For example, a
      text element may prevent itself from being blocked by other elements by
      increasing it's Z order, meaning it will be rendered last.

      :getter: Returns the text's scale factor.
      :setter: Updates the scale factor to use.
      :type: np.uint8
  )");

  text.def_property(
    "position",
    &ASGE::Text::getPosition,
    static_cast<ASGE::Text& (ASGE::Text::*)(const ASGE::Point2D&)>(&ASGE::Text::setPosition),
    R"(
    The baseline position to use.

    The position property controls the very starting point of the baseline. All
    glyphs (characters) rendered should align evenly on the baseline. This is
    important as it allows lines of text to follow a line evenly.

    :getter: The current baseline position.
    :setter: The new baseline position to use for rendering.
    :type: float
  )");

  text.def_property(
    "x",
    [](const ASGE::Text& self){ return self.getPosition().x; },
    [](ASGE::Text& self, float x){ self.setPositionX(x); },

    R"(
    The text's baseline position on the X axis.

    The property controls the very starting point of the baseline on the X
    axis. All glyphs (characters) rendered should align evenly on the baseline.
    This is important as it allows lines of text to follow a line evenly.

    :getter: The current baseline starting x position.
    :setter: The new baseline position on the x axis to use for rendering.
    :type: float
  )");

  text.def_property(
    "y",
    [](const ASGE::Text& self){ return self.getPosition().y; },
    [](ASGE::Text& self, float y){ self.setPositionY(y); },

    R"(
    The text's baseline position on the Y axis.

    The property controls the position of the baseline on the Y axis.
    All glyphs (characters) rendered will be positioned horizontally level
    and this property controls the vertical placement of the line.

    :getter: The current baseline starting y position.
    :setter: The new baseline position on the y axis to use for rendering.
    :type: float
  )");

  text.def_property(
    "colour", &ASGE::Text::getColour, &ASGE::Text::setColour,
    R"(
    The colour to use.

    Text rendering supports the full RGB range of colours. Adjusting this
    value will control the rendered output (assuming no custom pixel shaders
    are in use). Colours are described using three floats, ranging from [0,1],
    with 0 being an absence of colour (black) and 1.0 being fully lit (white).

    :getter: Returns the current colour being used for rendering.
    :setter: Updates the colour assigned to the text render.
    :type: float

    See Also
    --------
    pyasge.Colour

  )");

  text.def_property(
    "string",
    &ASGE::Text::getString,
    py::overload_cast<const std::string&>(&ASGE::Text::setString),
    R"(
    The contents of the text to render.

    :getter: Returns the current string.
    :setter: Sets a new string for calculating bounds and rendering output.
    :type: str
  )");

  text.def_property(
    "font", &ASGE::Text::getFont, &ASGE::Text::setFont,
    R"(
    The font face attached to the text.

    :getter: Returns the currently attached font face.
    :setter: Sets the font face to use for rendering.
    :type: pyasge.Font
  )");

  text.def_property_readonly(
    "local_bounds", &ASGE::Text::getLocalBounds,
    R"(
    The text object's 4 points in local space.

    Whilst this does not provide the absolute positioning of the text in the
    game world, it does allow an easy way to calculate the bounding box
    dimensions of the rendered text i.e. how wide and tall it is.

    :returns: The four vertex bounds of the text object.
    :type: pyasge.SpriteBounds

    Example
    -------
      >>> self.font = self.renderer.loadFont("/data/fonts/font.ttf", 40)
      >>> self.text = pyasge.Text(self.font, "Hello World")
      >>> print(self.text.getLocalBounds)

    See Also
    --------
    pyasge.SpriteBounds

  )");

  text.def_property_readonly(
      "world_bounds", &ASGE::Text::getWorldBounds,
      R"(
      The text object's 4 points in transformed world space.

      Calculates the width and height of the text in local space and then
      positions it within a bounding box that it is subsequently transformed
      in to world space.

      :returns: The four vertex bounds of the text in world space.
      :type: pyasge.SpriteBounds

      Example
      -------
        >>> self.font = self.renderer.loadFont("/data/fonts/font.ttf", 40)
        >>> self.text = pyasge.Text(self.font, "Hello World")
        >>> print(self.text.world_bounds)

      See Also
      --------
      pyasge.SpriteBounds
  )");
}
