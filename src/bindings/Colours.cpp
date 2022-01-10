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

#include <Engine/Colours.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <sstream>
namespace py = pybind11;
void initColours(py::module_ & module) {

  py::class_<ASGE::Colour>(
    module, "Colour",
    R"(
    Used to represent the RGB values of a colour.

    Example
    -------
      >>> self.colour = pyasge.COLOURS.AQUA      # predefined
      >>> self.colour = pyasge.Colour(1, 0, 0)   # red
      >>> self.colour = [0, 1, 0]                # green
      >>> self.colour = (1, 0, 1)                # purple

  )")

    .def(py::init<float, float, float>(), py::arg("red") = 0, py::arg("green") = 0, py::arg("blue") = 0)
    .def(py::init<std::array<float,3>>(), py::arg("rgb"))
    .def(py::init<ASGE::Colour>())
    .def_readwrite("r", &ASGE::Colour::r, "The red component of the colour.")
    .def_readwrite("g", &ASGE::Colour::g, "The green component of the colour.")
    .def_readwrite("b", &ASGE::Colour::b, "The blue component of the colour.")

  .def("__repr__",
       [](const ASGE::Colour& colour)
       {
         //nolint
         std::stringstream ss;
         ss << "pyasge.Colour(";
         ss << "r=" + std::to_string(colour.r) << ",";
         ss << "g=" + std::to_string(colour.g) << ",";
         ss << "b=" + std::to_string(colour.b);
         ss << ")";

         return ss.str();
       })

  .def("__str__",
       [](const ASGE::Colour& colour) {

         //nolint
         std::stringstream ss;
         ss << "ASGE RGB Colour: (";
         ss << "r:"        << std::to_string(colour.r) << "  ";
         ss << "g:"        << std::to_string(colour.g) << "  ";
         ss << "b:"        << std::to_string(colour.b) << ")";

         return ss.str();
       });

  py::module_ submodule  = module.def_submodule(
    "COLOURS",
    R"(
    A collection of predefined RGB values.

    Example
    -------
    >>> self.colour = pyasge.COLOURS.MAGENTA
    >>> self.text.colour = pyasge.COLOURS.AQUA
    >>> self.sprite.colour = pyasge.COLOURS.PINK
  )");

  submodule.attr("ALICEBLUE") = ASGE::COLOURS::ALICEBLUE;
  submodule.attr("ANTIQUEWHITE") = ASGE::COLOURS::ANTIQUEWHITE;
  submodule.attr("AQUA") = ASGE::COLOURS::AQUA;
  submodule.attr("AQUAMARINE") = ASGE::COLOURS::AQUAMARINE;
  submodule.attr("AZURE") = ASGE::COLOURS::AZURE;
  submodule.attr("BEIGE") = ASGE::COLOURS::BEIGE;
  submodule.attr("BISQUE") = ASGE::COLOURS::BISQUE;
  submodule.attr("BLACK") = ASGE::COLOURS::BLACK;
  submodule.attr("BLANCHEDALMOND") = ASGE::COLOURS::BLANCHEDALMOND;
  submodule.attr("BLUE") = ASGE::COLOURS::BLUE;
  submodule.attr("BLUEVIOLET") = ASGE::COLOURS::BLUEVIOLET;
  submodule.attr("BROWN") = ASGE::COLOURS::BROWN;
  submodule.attr("BURLYWOOD") = ASGE::COLOURS::BURLYWOOD;
  submodule.attr("CADETBLUE") = ASGE::COLOURS::CADETBLUE;
  submodule.attr("CHARTREUSE") = ASGE::COLOURS::CHARTREUSE;
  submodule.attr("CHOCOLATE") = ASGE::COLOURS::CHOCOLATE;
  submodule.attr("CORAL") = ASGE::COLOURS::CORAL;
  submodule.attr("CORNFLOWER") = ASGE::COLOURS::CORNFLOWERBLUE;
  submodule.attr("CORNSILK") = ASGE::COLOURS::CORNSILK;
  submodule.attr("CRIMSON") = ASGE::COLOURS::CRIMSON;
  submodule.attr("CYAN") = ASGE::COLOURS::CYAN;
  submodule.attr("DARKBLUE") = ASGE::COLOURS::DARKBLUE;
  submodule.attr("DARKCYAN") = ASGE::COLOURS::DARKCYAN;
  submodule.attr("DARKGOLDENROD") = ASGE::COLOURS::DARKGOLDENROD;
  submodule.attr("DARKGRAY") = ASGE::COLOURS::DARKGRAY;
  submodule.attr("DARKGREEN") = ASGE::COLOURS::DARKGREEN;
  submodule.attr("DARKGREY") = ASGE::COLOURS::DARKGREY;
  submodule.attr("DARKKHAKI") = ASGE::COLOURS::DARKKHAKI;
  submodule.attr("DARKMAGENTA") = ASGE::COLOURS::DARKMAGENTA;
  submodule.attr("DARKOLIVEGREEN") = ASGE::COLOURS::DARKOLIVEGREEN;
  submodule.attr("DARKORANGE") = ASGE::COLOURS::DARKORANGE;
  submodule.attr("DARKORCHID") = ASGE::COLOURS::DARKORCHID;
  submodule.attr("DARKRED") = ASGE::COLOURS::DARKRED;
  submodule.attr("DARKSALMON") = ASGE::COLOURS::DARKSALMON;
  submodule.attr("DARKSEAGREEN") = ASGE::COLOURS::DARKSEAGREEN;
  submodule.attr("DARKSLATEBLUE") = ASGE::COLOURS::DARKSLATEBLUE;
  submodule.attr("DARKSLATEGRAY") = ASGE::COLOURS::DARKSLATEGRAY;
  submodule.attr("DARKTURQUOISE") = ASGE::COLOURS::DARKTURQUOISE;
  submodule.attr("DARKVIOLET") = ASGE::COLOURS::DARKVIOLET;
  submodule.attr("DEEPPINK") = ASGE::COLOURS::DEEPPINK;
  submodule.attr("DEEPSKYBLUE") = ASGE::COLOURS::DEEPSKYBLUE;
  submodule.attr("DIMGRAY") = ASGE::COLOURS::DIMGRAY;
  submodule.attr("DIMGREY") = ASGE::COLOURS::DIMGREY;
  submodule.attr("DODGERBLUE") = ASGE::COLOURS::DODGERBLUE;
  submodule.attr("FIREBRICK") = ASGE::COLOURS::FIREBRICK;
  submodule.attr("FLORALWHITE") = ASGE::COLOURS::FLORALWHITE;
  submodule.attr("FORESTGREEN") = ASGE::COLOURS::FORESTGREEN;
  submodule.attr("FUCHSIA") = ASGE::COLOURS::FUCHSIA;
  submodule.attr("GAINSBORO") = ASGE::COLOURS::GAINSBORO;
  submodule.attr("GHOSTWHITE") = ASGE::COLOURS::GHOSTWHITE;
  submodule.attr("GOLD") = ASGE::COLOURS::GOLD;
  submodule.attr("GOLDENROD") = ASGE::COLOURS::GOLDENROD;
  submodule.attr("GRAY") = ASGE::COLOURS::GRAY;
  submodule.attr("GRAYBLACK") = ASGE::COLOURS::GRAYBLACK;
  submodule.attr("GREEN") = ASGE::COLOURS::GREEN;
  submodule.attr("GREENYELLOW") = ASGE::COLOURS::GREENYELLOW;
  submodule.attr("GREY") = ASGE::COLOURS::GREY;
  submodule.attr("GREYBLACK") = ASGE::COLOURS::GREYBLACK;
  submodule.attr("HONEYDEW") = ASGE::COLOURS::HONEYDEW;
  submodule.attr("HOTPINK") = ASGE::COLOURS::HOTPINK;
  submodule.attr("INDIANRED") = ASGE::COLOURS::INDIANRED;
  submodule.attr("INDIGO") = ASGE::COLOURS::INDIGO;
  submodule.attr("IVORY") = ASGE::COLOURS::IVORY;
  submodule.attr("KHAKI") = ASGE::COLOURS::KHAKI;
  submodule.attr("LAVENDER") = ASGE::COLOURS::LAVENDER;
  submodule.attr("LAVENDERBLUSH") = ASGE::COLOURS::LAVENDERBLUSH;
  submodule.attr("LAWNGREEN") = ASGE::COLOURS::LAWNGREEN;
  submodule.attr("LEMONCHIFFON") = ASGE::COLOURS::LEMONCHIFFON;
  submodule.attr("LIGHTBLUE") = ASGE::COLOURS::LIGHTBLUE;
  submodule.attr("LIGHTCORAL") = ASGE::COLOURS::LIGHTCORAL;
  submodule.attr("LIGHTCYAN") = ASGE::COLOURS::LIGHTCYAN;
  submodule.attr("LIGHTGOLDENRODYELLOW") = ASGE::COLOURS::LIGHTGOLDENRODYELLOW;
  submodule.attr("LIGHTGRAY") = ASGE::COLOURS::LIGHTGRAY;
  submodule.attr("LIGHTGREEN") = ASGE::COLOURS::LIGHTGREEN;
  submodule.attr("LIGHTGREY") = ASGE::COLOURS::LIGHTGREY;
  submodule.attr("LIGHTPINK") = ASGE::COLOURS::LIGHTPINK;
  submodule.attr("LIGHTSALMON") = ASGE::COLOURS::LIGHTSALMON;
  submodule.attr("LIGHTSEAGREEN") = ASGE::COLOURS::LIGHTSEAGREEN;
  submodule.attr("LIGHTSKYBLUE") = ASGE::COLOURS::LIGHTSKYBLUE;
  submodule.attr("LIGHTSLATEGRAY") = ASGE::COLOURS::LIGHTSLATEGRAY;
  submodule.attr("LIGHTSLATEGREY") = ASGE::COLOURS::LIGHTSLATEGREY;
  submodule.attr("LIGHTSTEELBLUE") = ASGE::COLOURS::LIGHTSTEELBLUE;
  submodule.attr("LIGHTYELLOW") = ASGE::COLOURS::LIGHTYELLOW;
  submodule.attr("LIME") = ASGE::COLOURS::LIME;
  submodule.attr("LIMEGREEN") = ASGE::COLOURS::LIMEGREEN;
  submodule.attr("LINEN") = ASGE::COLOURS::LINEN;
  submodule.attr("MAGENTA") = ASGE::COLOURS::MAGENTA;
  submodule.attr("MAROON") = ASGE::COLOURS::MAROON;
  submodule.attr("MEDIUMAQUAMARINE") = ASGE::COLOURS::MEDIUMAQUAMARINE;
  submodule.attr("MEDIUMBLUE") = ASGE::COLOURS::MEDIUMBLUE;
  submodule.attr("MEDIUMORCHID") = ASGE::COLOURS::MEDIUMORCHID;
  submodule.attr("MEDIUMPURPLE") = ASGE::COLOURS::MEDIUMPURPLE;
  submodule.attr("MEDIUMSEAGREEN") = ASGE::COLOURS::MEDIUMSEAGREEN;
  submodule.attr("MEDIUMSLATEBLUE") = ASGE::COLOURS::MEDIUMSLATEBLUE;
  submodule.attr("MEDIUMSPRINGGREEN") = ASGE::COLOURS::MEDIUMSPRINGGREEN;
  submodule.attr("MEDIUMTURQUOISE") = ASGE::COLOURS::MEDIUMTURQUOISE;
  submodule.attr("MEDIUMVIOLETRED") = ASGE::COLOURS::MEDIUMVIOLETRED;
  submodule.attr("MIDNIGHTBLUE") = ASGE::COLOURS::MIDNIGHTBLUE;
  submodule.attr("MINTCREAM") = ASGE::COLOURS::MINTCREAM;
  submodule.attr("MISTYROSE") = ASGE::COLOURS::MISTYROSE;
  submodule.attr("MOCCASIN") = ASGE::COLOURS::MOCCASIN;
  submodule.attr("NAVAJOWHITE") = ASGE::COLOURS::NAVAJOWHITE;
  submodule.attr("NAVY") = ASGE::COLOURS::NAVY;
  submodule.attr("OLDLACE") = ASGE::COLOURS::OLDLACE;
  submodule.attr("OLIVE") = ASGE::COLOURS::OLIVE;
  submodule.attr("OLIVEDRAB") = ASGE::COLOURS::OLIVEDRAB;
  submodule.attr("OLIVEDRAB") = ASGE::COLOURS::OLIVEDRAB;
  submodule.attr("ORANGE") = ASGE::COLOURS::ORANGE;
  submodule.attr("ORANGERED") = ASGE::COLOURS::ORANGERED;
  submodule.attr("ORCHID") = ASGE::COLOURS::ORCHID;
  submodule.attr("PALEGOLDENROD") = ASGE::COLOURS::PALEGOLDENROD;
  submodule.attr("PALEGREEN") = ASGE::COLOURS::PALEGREEN;
  submodule.attr("PALETURQUOISE") = ASGE::COLOURS::PALETURQUOISE;
  submodule.attr("PALEVIOLETRED") = ASGE::COLOURS::PALEVIOLETRED;
  submodule.attr("PAPAYAWHIP") = ASGE::COLOURS::PAPAYAWHIP;
  submodule.attr("PEACHPUFF") = ASGE::COLOURS::PEACHPUFF;
  submodule.attr("PERU") = ASGE::COLOURS::PERU;
  submodule.attr("PINK") = ASGE::COLOURS::PINK;
  submodule.attr("PLUM") = ASGE::COLOURS::PLUM;
  submodule.attr("POWDERBLUE") = ASGE::COLOURS::POWDERBLUE;
  submodule.attr("PURPLE") = ASGE::COLOURS::PURPLE;
  submodule.attr("RED") = ASGE::COLOURS::RED;
  submodule.attr("ROSYBROWN") = ASGE::COLOURS::ROSYBROWN;
  submodule.attr("ROYALBLUE") = ASGE::COLOURS::ROYALBLUE;
  submodule.attr("SADDLEBROWN") = ASGE::COLOURS::SADDLEBROWN;
  submodule.attr("SALMON") = ASGE::COLOURS::SALMON;
  submodule.attr("SANDYBROWN") = ASGE::COLOURS::SANDYBROWN;
  submodule.attr("SEAGREEN") = ASGE::COLOURS::SEAGREEN;
  submodule.attr("SEASHELL") = ASGE::COLOURS::SEASHELL;
  submodule.attr("SIENNA") = ASGE::COLOURS::SIENNA;
  submodule.attr("SILVER") = ASGE::COLOURS::SILVER;
  submodule.attr("SKYBLUE") = ASGE::COLOURS::SKYBLUE;
  submodule.attr("SKYBLUE") = ASGE::COLOURS::SKYBLUE;
  submodule.attr("SLATEBLUE") = ASGE::COLOURS::SLATEBLUE;
  submodule.attr("SLATEGRAY") = ASGE::COLOURS::SLATEGRAY;
  submodule.attr("SLATEGREY") = ASGE::COLOURS::SLATEGREY;
  submodule.attr("SNOW") = ASGE::COLOURS::SNOW;
  submodule.attr("SPRINGGREEN") = ASGE::COLOURS::SPRINGGREEN;
  submodule.attr("STEELBLUE") = ASGE::COLOURS::STEELBLUE;
  submodule.attr("TAN") = ASGE::COLOURS::TAN;
  submodule.attr("TEAL") = ASGE::COLOURS::TEAL;
  submodule.attr("THISTLE") = ASGE::COLOURS::THISTLE;
  submodule.attr("TOMATO") = ASGE::COLOURS::TOMATO;
  submodule.attr("TURQUOISE") = ASGE::COLOURS::TURQUOISE;
  submodule.attr("VIOLET") = ASGE::COLOURS::VIOLET;
  submodule.attr("WHEAT") = ASGE::COLOURS::WHEAT;
  submodule.attr("WHITE") = ASGE::COLOURS::WHITE;
  submodule.attr("WHITESMOKE") = ASGE::COLOURS::WHITESMOKE;
  submodule.attr("YELLOW") = ASGE::COLOURS::YELLOW;
  submodule.attr("YELLOWGREEN") = ASGE::COLOURS::YELLOWGREEN;

  py::implicitly_convertible<py::tuple, ASGE::Colour>();
  py::implicitly_convertible<py::list, ASGE::Colour>();
}
