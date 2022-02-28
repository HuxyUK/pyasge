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

#include <Engine/OpenGL/GLAtlas.hpp>
#include <Engine/OpenGL/GLFontSet.hpp>
#include <Engine/Text.hpp>
#include <pybind11/pybind11.h>
namespace py = pybind11;
void initFont(py::module_ &module) {

  py::class_<ASGE::Font::AtlasMetrics> metrics( module, "AtlasMetrics");
  metrics.def(py::init());
  metrics.def_readwrite("id", &ASGE::Font::AtlasMetrics::id);
  metrics.def_readwrite("ascender", &ASGE::Font::AtlasMetrics::ascender);
  metrics.def_readwrite("descender", &ASGE::Font::AtlasMetrics::descender);
  metrics.def_readwrite("em_size", &ASGE::Font::AtlasMetrics::em_size);
  metrics.def_readwrite("line_height", &ASGE::Font::AtlasMetrics::line_height);
  metrics.def_readwrite("range", &ASGE::Font::AtlasMetrics::range);
  metrics.def_readwrite("size", &ASGE::Font::AtlasMetrics::size);

  py::class_<ASGE::GLFontSet> font(
    module, "Font", py::is_final(),
    R"(A loaded instance of a Font.

       Before font's can be used in the rendering of text they need to be
       loaded by the renderer. On successful loading of a font this instance
       is returned which can then be attached to text for rendering use.

       Example
       -------
         >>> '''load font using renderer'''
         >>> self.font = self.renderer.loadFont("/data/fonts/kenvector_future.ttf", 40)
         >>>
         >>> '''attach font to a text object'''
         >>> self.text = pyasge.Text(self.font, "Hello World")
         >>>
         >>> '''pixel distance checks'''
         >>> print(self.font.pxWide('c', 1))
         >>> print(self.font.pxWide("cat", 1))

       Warning
       -------
       Without a font instance it is not possible to render using any other font
       than the default provided by the engine. This is due to the way the
       font's are converted into renderable glyphs and stored in the game
       engine.

  )");


  font.def(py::init());

  font.def("setMagFilter", (&ASGE::GLFontSet::setMagFilter), py::arg("mag_filter"));

  font.def(
    "pxWide",
    static_cast<float (ASGE::GLFontSet::*) (const std::string&, float) const>(&ASGE::GLFontSet::pxWide),
    py::arg("string"), py::arg("scale") = 1.0F, "How wide the string will be in pixels.");

  font.def(
    "pxWide",
    static_cast<float (ASGE::GLFontSet::*) (char, float) const>(&ASGE::GLFontSet::pxWide),
    py::arg("char"), py::arg("scale")= 1.0F, "How wide the character will be in pixels.");

  font.def(
    "pxHeight",
    &ASGE::GLFontSet::pxHeight, py::arg("string"), py::arg("scale"),
    "How tall the the bearing on the first line or text will be in pixels.");

  font.def(
      "boundsY",
      &ASGE::GLFontSet::boundsY, py::arg("string"), py::arg("scale"),
      R"(
      Calculates the bounding height for the string.

      Calculates the deviation in the Y axis from the top of the rendered
      string to the bottom. The function takes in to account the multiple lines
      by adding appropriate amounts of spacing and also the individual
      bearings of each character glpyh.

      Example
      -------
      >>> '''load font using renderer'''
      >>> self.font = self.renderer.loadFont("/data/fonts/kenvector_future.ttf", 40)
      >>>
      >>> '''attach font to a text object'''
      >>> print(self.font.boundsY("Where are you?", 2.0))
    )");
}
