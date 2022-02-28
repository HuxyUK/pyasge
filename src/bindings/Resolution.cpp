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

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <Engine/Resolution.hpp>

namespace py = pybind11;

void initResolution(py::module_& module) {

  py::enum_<ASGE::Resolution::Policy>(
      module, "ResolutionPolicy", R"(
      The resolution policy controls how the viewport will be scaled when the window
      size does not match the base resolution set for the game. This can be used to
      control scaling and any offsets applied to keep the content centered. For
      example using the option *SCALE* will keep the viewport the same size as the
      window and stretch any rendered content.)")

      .value("NONE", ASGE::Resolution::Policy::NONE, "Does not apply any offset or scaling to the game.")
      .value("MAINTAIN", ASGE::Resolution::Policy::MAINTAIN, "Maintains the aspect ratio and centers the view.")
      .value("CENTER", ASGE::Resolution::Policy::CENTER, "Centers but does not scale the viewport." )
      .value("SCALE", ASGE::Resolution::Policy::SCALE, "Fills the window which may lead to stretching or distortion.");

  py::class_<ASGE::Resolution> resolution(
      module, "Resolution", py::is_final(), R"(
      Resolution contains the display and render resolution information.

      This data structure contains a collection of useful values that can be used
      to determine both the game's design resolution but also the size of the
      window being rendered. This includes information regarding the viewport and
      the camera view currently assigned to the renderer. These types of information
      are often needed when moving between world and screen space. )");

  resolution.def_readonly("base_resolution", &ASGE::Resolution::base, R"(
      The base resolution of the game.

      The base resolution is simply the resolution the game was designed in. It's the
      coordinates used when drawing the game world or even checking for collisions.
      Depending on the resolution policy being used, the game will be scaled using
      this resolution. For example if the game resolution is 1280x720 and the window
      is 1920x1080 and a policy of MAINTAIN is requested; the game world will be scaled
      perfectly without any black borders. However, your bounds checks such as
      `if x > 1280:` remain valid.

      The idea behind the base resolution is to make the game independent of the window
      resolution. Instead the PyASGE will handle the scaling for you, where possible.)");

  resolution.def_readonly("window_resolution",
      &ASGE::Resolution::window,
      R"(
      The framebuffer size attached to the window.

      There is a slight but important distinction between the window size and the framebuffer
      size. This is due to the window being described in screen space, where as the
      framebuffer is in pixel space. Often the mapping is the same, but scaling of the
      window can result in a window having more units than the equivalent pixels. For the
      time being it's just easier to expose the width and height of the window in pixel space
      until a need to differ between the two arises.

      :getter: Returns the size of the framebuffer in pixels.
      :type: list[int,int]

      Example
      -------
      >>> window_size = self.renderer.resolution_info.window_resolution
      >>> print(f"Window Size: [{window_size[0]}, {window_size[1]}]")
    )");

  resolution.def_readonly("desktop_resolution", &ASGE::Resolution::desktop, R"(
      The resolution of the primary monitor.

      :getter: Returns the resolution and refresh rate of the primary display.
      :type: List[int, int, int]

      Example
      -------
      >>> resolution = self.renderer.resolution_info.desktop_resolution
      >>> print(f"Desktop Resolution: {resolution[0]}x{resolution[1]}@{resolution[2]}Hz")
  )");

  resolution.def_readonly("viewport", &ASGE::Resolution::viewport, R"(
      The viewport that maps to the rendered window.

      Whilst the projection matrix (camera view) controls what part of the game scene is being
      shown, the viewport looks after how it's view is mapped to the game window or to any
      attached render targets that are active.

      :getter: Returns the how the view will be mapped to the screen or to the :class:`RenderTarget`.
      :type: pyasge.Viewport

      .. note::
        It is the view port that controls the scaling properties when the window is resized. It
        is used to map the camera view to resultant area on the screen. A viewport does not have
        to necessarily fit the whole screen either, it can be used for concepts such as
        picture-in-picture.
  )");

  resolution.def_readonly("view", &ASGE::Resolution::view, R"(
      The view (camera) that frames the content drawn in the viewport.

      The camera view controls the orthogonal projection used to frame the game's action. To see
      more of the game world the view can be increased in size. It's not measured in pixels but
      rather world space.

      :getter: Returns the camera's view of the world.
      :type: pyasge.CameraView
  )");

  resolution.def_property_readonly("base_aspect_ratio", &ASGE::Resolution::getBaseAspectRatio, "The base resolution aspect ratio.");
  resolution.def_property_readonly("window_aspect_ratio", &ASGE::Resolution::getWindowAspectRatio, "The game window's resolution aspect ratio.");
  resolution.def_property_readonly("desktop_aspect_ratio", &ASGE::Resolution::getDesktopAspectRatio, "The desktop's resolution aspect ratio.");
}
