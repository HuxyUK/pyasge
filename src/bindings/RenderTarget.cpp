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

    Example
    -------
      >>> # Render Function
      >>> """ render to texture """
      >>> self.renderer.setRenderTarget(self.rt)
      >>> self.renderer.setViewport(pyasge.Viewport(0, 0, 1024 / 2, 768 / 2))
      >>> self.renderer.render(self.sprite)
      >>>
      >>> """ render the resultant texture """
      >>> self.renderer.setRenderTarget(None)
      >>> self.rt.resolve(0)
      >>> self.renderer.setViewport(pyasge.Viewport(0, 0, 1024, 768))
      >>> self.renderer.render(self.rt_texture)
  )")

    .def(
      py::init<ASGE::GLRenderer*, float, float, ASGE::Texture2D::Format, int>(),
      py::arg("renderer"),
      py::arg("width"),
      py::arg("height"),
      py::arg("format"),
      py::arg("count"))

      .def_property_readonly(
          "buffers",
          [](const ASGE::GLRenderTarget &self) {
            auto &buffers = self.getResolved();

            std::vector<ASGE::GLTexture *> list;
            list.reserve(buffers.size());
            for (auto &ptr : buffers) {
              list.emplace_back(ptr.get());
            }
            return list;
          },
          py::return_value_policy::reference_internal, R"(
          Returns the most recently resolved textures.

          Once a MSAA texture has been resolved, it will be stored in a list
          of resolved textures. This function returns them. If the MSAA
          textures have been updated then these will be stale and a resolve
          function call will be required to update them.

          :returns: A list of all the currently resolved textures.
          :type: list[Texture]

          Warning
          -------
          You need to call resolve to sample the buffers correctly.

          Example
          -------
            >>> """create a new render target and sprite to store the render texture"""
            >>> self.rt = pyasge.RenderTarget(self.renderer, 1024 / 2, 768 / 2, pyasge.Texture.Format.RGB, 1)
            >>> self.rt_texture = pyasge.Sprite()
            >>> self.rt_texture.x = 1024 / 2
            >>> self.rt_texture.y = 768 / 2
            >>> self.rt_texture.width = 1024 / 2
            >>> self.rt_texture.height = 768 / 2
            >>> self.rt_texture.attach(self.rt.buffers[0])

          See Also
          --------
          Texture
      )")

      .def(
          "resolve",
          [](ASGE::GLRenderTarget &self, int index) {
            return self.resolve(static_cast<unsigned int>(index));
          },
          py::return_value_policy::reference_internal, R"(
          Resolves the MSAA texture at specified index.

          Before sampling can take place, the multi-sampled images need to be
          "blited" in to a standard 2D texture. As render targets may have
          multiple color attachments, this function allows the user to specify
          which attachment to specifically update.

          :param index: The index of the attachment to resolve. A count of 1 is index 0.
          :returns: A handle to the resultant updated textures.
          :type: Texture

          .. warning:: You need to call resolve to sample the buffers correctly.

          .. seealso:: :class:`Texture`
      )")

      .def(
          "resolve",
          [](ASGE::GLRenderTarget &self) {
            auto &resolved = self.resolve();

            std::vector<ASGE::GLTexture *> list;
            list.reserve(resolved.size());
            for (auto &ptr : resolved) {
              list.emplace_back(ptr.get());
            }
            return list;
          },
          py::return_value_policy::reference_internal, R"(
          Resolves all MSAA textures attached to this frame buffer.

          Before sampling can take place, the multi-sampled images need to be
          "blited" in to a standard 2D texture. As render targets may have
          multiple color attachments, this function loops through all
          attachments and resolves them into textured that can then be used in
          normal samplers in the fragment shader.

          :returns: A list of all the resultant updated texture.
          :type: list[Texture]

          .. warning:: You need to call resolve to sample the buffers correctly.

          .. seealso:: :class:`Texture`
      )");
}
