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

#include <Engine/Viewport.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

namespace py = pybind11;
void initViewPort(py::module_ &module)
{
  py::class_<ASGE::Viewport> viewport(
      module, "Viewport",
      R"(
      Viewports are a way of framing the rendering and control the mapping to
      the destination target, be that a pyasge.RenderTarget or a window.

      For example you could create a viewport that only consumed half the render
      window and render a camera's view in to it. This could allow for more
      complex solutions such as split screen support.

      Example
      -------
      In the following example, the game screen is split into half (vertically)
      with one viewport on the left and the other on the right. A camera is then
      used to frame the action, before one sprite is rendered and then another.

      >>> def __init__(self, settings):
      >>>   pyasge.ASGEGame.__init__(self, settings)
      >>>
      >>>   '''game window is 384x256 pixels, so reduce half camera width'''
      >>>   self.camera = pyasge.Camera((-(384 * 0.25), -256 / 2), 384 / 2, 256)
      >>>
      >>>   '''load two sprites, one for each viewport'''
      >>>   self.sprite1 = pyasge.Sprite()
      >>>   self.sprite1.loadTexture("/data/character_zombie_idle.png")
      >>>   self.sprite2 = pyasge.Sprite()
      >>>   self.sprite2.loadTexture("/data/character_robot_idle.png")
      >>>
      >>> def render(self) -> None:
      >>>   self.renderer.setProjectionMatrix(self.camera.view)
      >>>   self.renderer.setViewport(pyasge.Viewport(0, 0, 384 / 2, 256))
      >>>   self.renderer.render(self.sprite)
      >>>   self.renderer.setViewport(pyasge.Viewport(384 / 2, 0, 384 / 2, 256))
      >>>   self.renderer.render(self.sprite2)

      .. image:: ../_static/images/viewports.png

      |

      Note
      ----
      Changing the size of the viewport will directly impact how the rendered
      sprites are mapped to the screen. This can result in distortion when
      your viewport has a different aspect ratio compared to the camera.

      .. image:: ../_static/images/viewports2.png

 )");

  viewport.def(py::init());
  viewport.def(py::init<float, float, float, float>());
  viewport.def(py::init<const ASGE::Viewport&>());
  viewport.def_readwrite("x", &ASGE::Viewport::x, "The viewports starting x position.");
  viewport.def_readwrite("y", &ASGE::Viewport::y, "The viewports starting y position.");
  viewport.def_readwrite("w", &ASGE::Viewport::w, "The viewports width.");
  viewport.def_readwrite("h", &ASGE::Viewport::h, "The viewports height.");

  PYBIND11_NUMPY_DTYPE(ASGE::Viewport, x, y, w, h);
}
