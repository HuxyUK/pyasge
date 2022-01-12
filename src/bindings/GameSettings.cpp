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

#include <Engine/GameSettings.hpp>
#include <pybind11/pybind11.h>
namespace py = pybind11;
void initGamesettings(py::module_ & module){
  py::class_<ASGE::GameSettings>(
    module, "GameSettings",
    R"(GameSettings allows you to configure the game window and its initial
       state upon construction of the game. You could easily use a GUI to create
       an instance of GameSettings and then construct the game using it.

       Example
       -------
       >>> settings = pyasge.GameSettings()
       >>> settings.window_width = 608
       >>> settings.window_height = 1080
       >>> settings.window_mode = pyasge.WindowMode.BORDERLESS_FULLSCREEN
       >>> game = MyASGEGame(settings)
       >>> game.run()
    )")

    .def(py::init<>())

    .def_readwrite(
      "window_width", &ASGE::GameSettings::window_width,
      R"(
          The requested window width for the game.

          :getter: Returns requested window width
          :setter: Sets the requested window width
          :type: int
    )")

    .def_readwrite(
      "window_height", &ASGE::GameSettings::window_height,
      R"(
          The requested window height for the game.

          :getter: Returns requested window height
          :setter: Sets the requested window height
          :type: int
    )")

    .def_readwrite(
      "vsync", &ASGE::GameSettings::vsync,
      R"(
          The vsync mode to attempt to use.

          :getter: Returns the requested vsync mode
          :setter: Sets the requested vsync mode
          :type: pyasge.Vsync
    )")

    .def_readwrite(
      "window_mode", &ASGE::GameSettings::mode,
      R"(
          The window mode to use.

          :getter: Returns the window mode
          :setter: Sets the window mode to try and use
          :type: pyasge.WindowMode
    )")

    .def_readwrite(
      "window_title", &ASGE::GameSettings::game_title,
      R"(
          Each window has a title, customise yours.

          :getter: Returns the requested window title
          :setter: The window title to apply
          :type: str
    )")

    .def_readwrite(
      "write_dir", &ASGE::GameSettings::write_dir,
      R"(
          The directory to write files to.

          :getter: Returns the requested write directory
          :setter: Sets the requested write directory
          :type: str
    )")

    .def_readwrite(
      "fixed_ts", &ASGE::GameSettings::fixed_ts,
      R"(
          Controls the pacing of the fixed time-step update function.

          :getter: Returns the desired delta between update calls.
          :setter: Sets the desired fixed time-step delta.
          :type: int
    )")

    .def_readwrite(
      "msaa_level", &ASGE::GameSettings::msaa_level,
      R"(
          Controls the pacing of the fixed time-step update function.

          :getter: Returns the desired delta between update calls.
          :setter: Sets the desired fixed time-step delta.
          :type: int
    )")

    .def_readwrite(
        "fps_limit", &ASGE::GameSettings::fps_limit,
        R"(
        Attempts to limit the game's FPS

        :getter: Returns the FPS limit
        :setter: Sets desired FPS cap
        :type: int
    )")

    .def_readwrite(
      "mag_filter",
      &ASGE::GameSettings::mag_filter,
      R"(
      Sets the default magnification filter to use for the game.

      :getter: Returns the MagFilter to use by default
      :setter: Sets the default MagFilter to use when scaling upwards
      :type: pyasge.MagFilter
    )");

  py::enum_<ASGE::GameSettings::WindowMode>(
    module, "WindowMode",
  R"(Input Event.

       Input events are signalled when specific inputs are detected. These
       include key presses, mouse button clicks, mouse movements and mouse
       scrolling. When the framework receives one of these events, it forwards
       the data packaged in one of these EventType classes. They contain all
       the relevant information about the event itself. )")

    .value("FULLSCREEN", ASGE::GameSettings::WindowMode::EXCLUSIVE_FULLSCREEN,
           "Present the game in full-screen, changing resolution if necessary.")
    .value("WINDOWED", ASGE::GameSettings::WindowMode::WINDOWED,
           "Present the game in a window.")
    .value("BORDERLESS_WINDOW", ASGE::GameSettings::WindowMode::BORDERLESS_WINDOWED,
           "Present the game in a borderless window.")
    .value("BORDERLESS_FULLSCREEN", ASGE::GameSettings::WindowMode::BORDERLESS_FULLSCREEN,
           "Present the game in a fullscreen borderless window, maintaining the "
           "desktop resolution and settings");


  py::enum_<ASGE::GameSettings::MagFilter>(
    module, "MagFilter",
    R"(Magnification filter types.

    When zooming in on textures, the engine supports two methods of filtering.
    The type of filtering applied will control the sharpness of the image.
    Nearest neighbour filtering is popular for low-bit assets, as it doesn't
    blur the image, but it has a "chunky" appearance.")")

    .value("NEAREST", ASGE::GameSettings::MagFilter::NEAREST,
           "Takes the `nearest <https://en.wikipedia.org/wiki/Nearest-neighbor_interpolation>`_ pixel in manhattan distance.")
    .value("LINEAR", ASGE::GameSettings::MagFilter::LINEAR,
           "Takes the `weighted <https://en.wikipedia.org/wiki/Texture_filtering#Linear_mipmap_filtering>`_ average of all 4 pixels.");

  py::enum_<ASGE::GameSettings::Vsync>(
    module, "Vsync",
    R"(Vertical sync modes.

       **Not currently working when using Python bindings**.)")

    .value("ENABLED", ASGE::GameSettings::Vsync::ENABLED,
           "Forces vsync at all times. FPS will be controlled by monitors refresh.")
    .value("ADAPTIVE", ASGE::GameSettings::Vsync::ADAPTIVE,
           "Enables vsync when able to meet monitor's refresh, disables when below.")
    .value("DISABLED", ASGE::GameSettings::Vsync::DISABLED,
           "Allow the game to run unrestricted.");
}
