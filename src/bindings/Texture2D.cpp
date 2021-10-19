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

#include <Engine/OpenGL/GLTexture.hpp>
#include <Engine/Texture.hpp>
#include <magic_enum.hpp>
#include <pybind11/attr.h>
#include <pybind11/pybind11.h>
namespace py = pybind11;
void initTexture2D(py::module_& module)
{
  // ----------------------------------------------------
  // ASGE GLTexture
  // ----------------------------------------------------
  py::class_<ASGE::GLTexture> texture(
    module, "Texture", py::is_final(), "A texture which can attach to the GPU");

  py::enum_<ASGE::Texture2D::Format>(
    texture,
    "Format",
    R"(
    Pixel format of the texture.

    These types can be used to calculate the bit-depth of each pixel. This is important when
    manually iterating or updating the pixel buffers, as the stride between various pixels
    will depend on the format used.)")

    .value("MONOCHROME", ASGE::Texture2D::MONOCHROME, "The texture is monochromatic.")
    .value("MONOCHROME_ALPHA", ASGE::Texture2D::MONOCHROME_ALPHA, "The texture is monochromatic and has an alpha channel.")
    .value("RGB", ASGE::Texture2D::RGB, " There are Red, Green & Blue channels present.")
    .value("RGBA", ASGE::Texture2D::RGBA, "There are RGB plus alpha channels present.");

  py::enum_<ASGE::Texture2D::UVWrapMode>(
    texture,
    "UVWrapMode",
    R"(
    Modes that controlling the UV texture wrapping

    When sampling textures and using UV coordinates outside of the normalised
    range, wrapping modes can be used to control the resultant sampled pixel.
    For example, REPEAT will continuously wrap the texture. This is good for
    when you want to sample outside the normal [0,1] range but still obtain a
    resultant pixel. A use case for this is a scrolling background layer.

    .. figure:: https://learnopengl.com/img/getting-started/texture_wrapping.png
       :alt: https://learnopengl.com/Getting-started/Textures

       learnopengl.com
    )")

    .value("CLAMP", ASGE::Texture2D::UVWrapMode::CLAMP, "Clamps the texture to [0,1].")
    .value("REPEAT", ASGE::Texture2D::UVWrapMode::REPEAT, "Repeats the texture.")
    .value("MIRROR", ASGE::Texture2D::UVWrapMode::MIRRORED, "Mirrors the image with each repeat.");

  texture.def(
    "_test_texture_format_enum",
    [](ASGE::Texture2D::Format fmt)
    { return std::string("ASGE::Texture2D::Format::").append(magic_enum::enum_name(fmt)); });

  texture.def(
    py::init<float, float>(),
    py::arg("width")  = 0,
    py::arg("height") = 0,
    R"(
        Initially the texture is empty and does not get allocated on the GPU.
        On the first retrieval of the pixel buffer, the memory will be allocated
        and a handle to the pixel buffer's contents will be created. You are then
        free to manipulate this data locally, before re-uploading it to the GPU at
        a later point in time by signalling the pixel buffer ``upload`` function.

        Parameters
        ----------
        width : int
          the width of the texture.
        height: int
          the height of the texture.

        See Also
        --------
        pyasge.PixelBuffer
    )");

  texture.def_property_readonly(
    "width",
    [](const ASGE::GLTexture& self) { return self.getWidth(); },
    R"(
        The texture's width in pixels.

        Returns
        ------
           int
              The width of the texture.
    )");

  texture.def_property_readonly(
    "height",
    [](const ASGE::GLTexture& self) { return self.getHeight(); },
    R"(
        The texture's height in pixels.

        Returns
        ------
           int
              The height of the texture.
    )");

  texture.def_property(
    "format",
    &ASGE::GLTexture::getFormat,
    [](ASGE::GLTexture& self, ASGE::Texture2D::Format format) { self.setFormat(format); },
    R"(
        The texture's designated pixel format.

        Returns
        ------
           Format
              The pixel format for the texture.
    )");

  texture.def(
    "setMagFilter",
    [](ASGE::GLTexture& self, ASGE::Texture2D::MagFilter filter) { self.updateMagFilter(filter); },
    py::arg("filter"),
    R"(
        Updates the magnification filter.

        Magnification filters control how textures are scaled when rendered at
        a higher resolution. The default is ``linear`` filtering, but ``nearest
        neighbour`` is also available.

        Parameters
        ----------
        filter : MagFilter
          The filtering algorithm to apply when scaling

        See Also
        --------
        pyasge.MagFilter

        Note
        -----
        |filtering|
    )");

  texture.def_property_readonly(
    "id",
    static_cast<const unsigned int& (ASGE::GLTexture::*)(void) const>(&ASGE::GLTexture::getID),
    R"(
        Retrieves the GPU ID allocated to the texture

        When allocating space for the texture on the GPU, a handle is generated.
        This unique ID represents the handle. Textures that share the same handle
        use the same region of GPU memory. If the id is 0 then it is safe to the
        assume that the texture hasn't yet been allocated.

        Return
        ------
           unsigned int
              the unique id of the GPU data
  )");

  texture.def_property(
    "buffer",
    static_cast<const ASGE::PixelBuffer* (ASGE::GLTexture::*)(void) const>(
      &ASGE::GLTexture::getPixelBuffer),
    static_cast<ASGE::PixelBuffer* (ASGE::GLTexture::*)(void)>(&ASGE::GLTexture::getPixelBuffer),
    py::return_value_policy::reference,
    R"(
        The texture's pixel buffer.

        Each texture's data is uploaded and resident on the GPU. Using
        a ``PixelBuffer``, it is possible to download the data and manipulate
        it locally, before re-uploading the changes. Pixel buffers are allocated
        on first use and will download from the GPU automatically upon creation.

        Returns
        ------
           PixelBuffer
              The host copy of the texture's pixel data.
  )");

  texture.def("updateMips", &ASGE::Texture2D::updateMips, "Rebuilds the mip-maps used for minification.");

  texture.def(
    "setUVMode",
    &ASGE::Texture2D::updateUVWrapping,
    py::arg("s") = ASGE::Texture2D::UVWrapMode::CLAMP,
    py::arg("t") = ASGE::Texture2D::UVWrapMode::CLAMP,
    R"(
    Set the wrapping mode used for UV coordinates.

    When sampling the texture, UV coordinates outside of the range of [0,1]

    can either be clamped or repeated. It is also possible to clamp the UV range
    in one direction, and repeat in another as both directions (s,t) are
    controlled independently of each other. The repeating technique can be used
    to create simple animations such as scrolling backgrounds.

    Parameters
    ----------
    s : pyasge.Texture.UVWrapMode
        The wrapping mode to use when sampling outside the [0,1] range in the x axis.
    t : pyasge.Texture.UVWrapMode
        The wrapping mode to use when sampling outside the [0,1] range in the y axis.


    .. figure:: https://learnopengl.com/img/getting-started/texture_wrapping.png
       :alt: https://learnopengl.com/Getting-started/Textures

       learnopengl.com


    Example
    -------
    >>> sprite = pyasge.Sprite()
    >>> sprite.loadTexture("scrolling_bg.png")
    >>> sprite.texture.setUVMode(Texture.UVWrapMode.REPEAT, Texture.UVWrapMode.REPEAT)

    See Also
    --------
    pyasge.Texture.UVWrapMode

    )");

  texture.def(
    "__str__",
    [](const ASGE::GLTexture& texture)
    {
      // nolint
      std::stringstream ss;
      ss << "ASGE 2D Texture: (";
      ss << "id:" << std::to_string(texture.getID()) << "  ";
      ss << "width:" << std::to_string(texture.getWidth()) << "  ";
      ss << "height:" << std::to_string(texture.getHeight()) << ")";

      return ss.str();
    });
}
