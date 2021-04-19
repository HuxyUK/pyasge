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

#include <Engine/OpenGL/GLRenderTarget.hpp>
#include <Engine/OpenGL/GLRenderer.hpp>
#include <Engine/OpenGL/GLTexture.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
namespace py = pybind11;

void initRenderTarget(py::module_& module)
{
  py::class_<ASGE::GLRenderTarget>(
    module, "RenderTarget", py::is_final(),
    R"(
    An offscreen render target.

    Offscreen render targets can be used to create complex rendering scenes
    and special effects. By rendering to the texture, it is easy to apply
    multi-passes with different shaders or even to render the scene within a
    a scene.

    Note
    ----
    In order to use a render target a renderer is needed. This is because the
    setup of such targets is GPU and framework dependent.
  )")

    .def(
      py::init<ASGE::GLRenderer*, float, float, ASGE::Texture2D::Format, int>(),
      py::arg("renderer"),
      py::arg("width"),
      py::arg("height"),
      py::arg("format"),
      py::arg("count"))

    .def_property(
      "buffers",
      &ASGE::GLRenderTarget::getBuffers,
      &ASGE::GLRenderTarget::setBuffers,
      "Access to the textures associated with this render target.");
}
