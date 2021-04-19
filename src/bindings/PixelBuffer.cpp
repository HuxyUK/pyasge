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

#include <Engine/OpenGL/GLPixelBuffer.hpp>
#include <Engine/OpenGL/GLTexture.hpp>
#include <pybind11/attr.h>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;
void initPixelBuffer(py::module_ & module)
{
  // ----------------------------------------------------
  // ASGE GLPixelBuffer
  // ----------------------------------------------------
  py::class_<ASGE::GLPixelBuffer> pixelbuffer(
    module, "PixelBuffer", py::is_final(), py::buffer_protocol(),
    "A pixel buffer that resides on the GPU");

  pixelbuffer.def(
    py::init<ASGE::GLTexture&>(), py::arg("texture"),
    R"(
        Pixel buffers allow retrieval and updating of individual pixels stored on
        the GPU. This class acts as a proxy between the hosts memory and the GPU.
        It works by storing a local copy of the pixel data, which can then be read
        from or modified and uploaded back on to the GPU.

        Parameters
        ----------
        texture : Texture
            The texture this pixel buffer is assigned to.
    )");

  pixelbuffer.def_property_readonly(
    "width", [](const ASGE::GLPixelBuffer& self) {
      return self.getWidth();
    },
    R"(
      The buffers width in pixels.

      Returns
      ------
         int
            The width allocated for the pixel buffer.
    )");

  pixelbuffer.def_property_readonly(
    "height", [](const ASGE::GLPixelBuffer& self) {
      return self.getHeight();
    },
    R"(
      The buffers height in pixels.

      Returns
      ------
         int
            The height allocated for the pixel buffer.
    )");

  pixelbuffer.def(
    "stale",  [](const ASGE::GLPixelBuffer& self) {
      return self.isBufferStale();
    },
    R"(
      Is the local buffer out of date?

      Downloads from the GPU are asynchronous. When a download is requested it
      does not immediately update the contents of the local pixel buffer, instead
      it sets the stale flag to true. This flag is reset and the local buffer
      updated when the data is next retrieved.

      Return
      ------
         bool
            true if the local pixel data need updating
    )");

  pixelbuffer.def("download",  &ASGE::GLPixelBuffer::download, py::arg("mip_level") = 0,
    R"(
      Schedules a download from the GPU

      Use this function when you wish to retrieve a copy of the texture currently
      stored on the GPU. This can be used to overwrite the local buffer, for example
      if you want to restore it to the version currently in GPU memory.

      :Parameters:
        - **mip_level** - the mip level to download, defaults to 0
    )");

  pixelbuffer.def(
    "upload",
    py::overload_cast<unsigned int>(&ASGE::GLPixelBuffer::upload), py::arg("mip_level") = 0,
    R"(
      Uploads the data to the GPU

      Use this function to upload the CPU pixel buffer onto the GPU.
      When complete, the transfer will replace any existing texture data
      resident on the GPU. *Please note: you can not revert the data unless
      you have a backup of the pixel buffer array*.

      :Parameters:
        - **mip_level** (int) - the mip level to download, defaults to 0.
    )");

  pixelbuffer.def(
    "upload",
    [](ASGE::GLPixelBuffer& self,
       py::array_t<unsigned char, py::array::c_style | py::array::forcecast> &buffer,
       unsigned int mips) {
        auto  buf = buffer.request(); //NOLINTNEXTLINE
        auto* ptr = reinterpret_cast<std::byte*>(buf.ptr);
        self.upload(ptr, mips);
    },
    py::arg("buffer"), py::arg("mip_level") = 0,
    R"(
        Uploads the data to the GPU

        Use this function to take a copy of a pre-existing array of bytes,
        and then upload the resultant buffer to the GPU. The array passed
        in must be the same size or larger than the pixel buffer's width
        and height to prevent out of bounds access.

        :Parameters:
          - **buffer** (array_like) - An existing array of bytes to copy.
          - **mip_level** (int) - the mip level to download, defaults to 0.
    )");


  pixelbuffer.def_buffer([](ASGE::GLPixelBuffer &self) -> py::buffer_info {
    return py::buffer_info(
      self.getPixelData(),
      sizeof(std::byte),
      py::format_descriptor<unsigned char>::format(),
      2,
      { self.getHeight(), self.getWidth() * self.pixelFormat() },
      {
        sizeof(std::byte) * self.pixelFormat() * self.getWidth(),
        sizeof(std::byte)
      });
  });

  pixelbuffer.def_property(
    "data",
    [](ASGE::GLPixelBuffer& self) -> py::array {
    auto type = pybind11::dtype(pybind11::format_descriptor<unsigned char>::format());
    auto base  = pybind11::array(
      type,
      { self.getHeight(), self.getWidth() * self.pixelFormat() },
      { sizeof(std::byte) * self.pixelFormat() * self.getWidth(), sizeof(std::byte) });

    return pybind11::array(
      type,
      { self.getHeight(), self.getWidth() * self.pixelFormat() },
      { sizeof(std::byte) * self.pixelFormat() * self.getWidth(), sizeof(std::byte) },
      self.getPixelData(),
      base);
    },

    [](ASGE::GLPixelBuffer& self) {},
    R"(
        The pixel data

        This is the CPU copy of the pixel data used to represent a texture. The
        data itself is stored as a range of bytes and is treated as a numpy array in order
        to allow it to be accessed without copying. Adjusting the pixel data will not
        automatically update the GPU. To do this an `upload` function call is required.

        Example
        -------
          >>> '''Upload pixel data directly'''
          >>> blocks = numpy.full((200, 600), 65, dtype='B')
          >>> self.sprite = pyasge.Sprite()
          >>> self.sprite.width = 200
          >>> self.sprite.height = 200
          >>> self.texture = self.renderer.createNonCachedTexture(200, 200, pyasge.Texture.Format.RGB, None)
          >>> self.sprite.attach(self.texture)
          >>> self.texture.buffer.upload(blocks, 0)
          >>>
          >>> '''Edit an existing texture'''
          >>> def update(self, game_time):
          >>>   with numpy.nditer(self.texture.buffer.data, op_flags=['readwrite'], order='C') as it:
          >>>     for x in it:
          >>>       x[...] = numpy.random.randint(0, 256)
          >>>   self.texture.buffer.upload()

          .. figure:: ../_static/images/pixelbuffer.png
      )");

  pixelbuffer.def(
    "__str__",
   [](const ASGE::GLPixelBuffer& self) {
     return
        "pixel buffer (width=" +
        std::to_string(self.getWidth()) +
        ";height=" +
        std::to_string(self.getHeight())+")";
   });

  pixelbuffer.def(
    "__repr__",
    [](const ASGE::GLPixelBuffer& self) {
      //nolint
      std::stringstream ss;
      ss << "pyasge.PixelBuffer(";
      ss << "width=:\t\t"              << std::to_string(self.getWidth()) << std::endl;
      ss << "height=:\t\t"             << std::to_string(self.getHeight()) << std::endl;
      ss << "stale=:\t\t"              << std::boolalpha << self.isBufferStale() << std::endl;
      ss << "pixel_fmt=:\t\t"          << std::to_string(self.pixelFormat()) << std::endl;
      return ss.str();
    });
}
