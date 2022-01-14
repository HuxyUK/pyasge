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

#include <Engine/OpenGL/GLTexture.hpp>
#include <Engine/OpenGL/GLTextureCache.hpp>
#include <Engine/Texture.hpp>
#include <Tile.hpp>
#include <pybind11/numpy.h>

namespace py = pybind11;

namespace {
  void setTexture(ASGE::Tile& tile, ASGE::GLTexture* texture)
  {
    tile.texture = texture;
  }

  auto getTexture(const ASGE::Tile& tile)
  {
    return dynamic_cast<ASGE::GLTexture*>(tile.texture);
  }

  auto loadTexture(ASGE::Tile& tile, std::string_view file)
  {
    auto* texture = ASGE::GLTextureCache::getInstance().createCached(
        file.data(), 0, 0, ASGE::Texture2D::MONOCHROME_ALPHA, nullptr);

    if (texture != nullptr)
    {
      tile.texture = texture;
      return true;
    }
    return false;
  }

  py::array_t<float> srcRect(ASGE::Tile &tile) {
    auto length = 4;
    py::capsule free_when_done(&tile.src_rect[0], [](void * /*data*/) {
      Logging::TRACE("destroying capsule");
    });

    py::array_t<float> out{
            {length},
            {sizeof(float)},
            &tile.src_rect[0],
            free_when_done};
    return out;
  }

  void setSrcRect(ASGE::Tile &tile, const py::array_t<float, 4> &array) {
    tile.src_rect[0] = array.at(0);
    tile.src_rect[1] = array.at(1);
    tile.src_rect[2] = array.at(2);
    tile.src_rect[3] = array.at(3);
  }
}

void initTile(py::module_& module)
{
  py::class_<ASGE::Tile> tile(module, "Tile", py::dynamic_attr(),
  R"(
  An PyASGE supported tile.

  Tiles, whilst sharing much of the same functionality as the Sprites
  are conceptually quite different. Instead they are used to build more
  complex scenes and game maps. Because of this their position is
  normally dictated by the map itself and typically consists of using rows,
  columns and tile sizes to determine their exact positioning.

  The aim of this class is to easily allow this kind of functionality to
  exist within PyASGE. Instead of having to construct instances of Sprites
  with their own positional data, you can use a Tile instead.

  When rendering a Tile you will need to provide the XY position that it's
  to appear in World Space. Remember that by default origins in PyASGE
  for positions (not rotations) are calculated from the top-left.

  Mozilla's developer documentation (https://developer.mozilla.org/en-US/docs/Games/Techniques/Tilemaps)
  does a great job of introducing tile maps and how conceptually they
  operate. This might help if you're unsure about when you would use a
  Tile instead of a Sprite.

  .. figure:: https://developer.mozilla.org/en-US/docs/Games/Techniques/Tilemaps/tile_atlas.png
   :alt: https://developer.mozilla.org/en-US/docs/Games/Techniques/Tilemaps

   Mozilla Developer Documentation: Tilemaps

  Example
  -------

  >>> # create a tile
  >>> pyasge_tile = pyasge.Tile()
  >>> pyasge_tile.texture = renderer.loadTexture(filename)
  >>> pyasge_tile.texture.setMagFilter(pyasge.MagFilter.NEAREST)
  >>> pyasge_tile.width = 32
  >>> pyasge_tile.height = 32
  >>> pyasge_tile.src_rect = [0,0,32,32]
  >>> pyasge_tile.visible = True

  >>> # render a tile map by looping through layers of tiles
  >>> for layer in self.map:
  >>>   for row_index, row in enumerate(layer[1]):
  >>>     for col_index, tile in enumerate(row):
  >>>       if tile:
  >>>          renderer.render(tile,
  >>>                          col_index * self.tile_size[0],
  >>>                          row_index * self.tile_size[1])

  See Also
  --------
  Sprite

  )");

  tile.def(py::init());
  tile.def(py::init<const ASGE::Tile&>());
  tile.def_readwrite("tint",     &ASGE::Tile::tint,     "Rotation for the tile" );
  tile.def_readwrite("rotation", &ASGE::Tile::rotation, "Rotation for the tile" );
  tile.def_readwrite("opacity",  &ASGE::Tile::opacity,  "Controls alpha for the rendered tile" );
  tile.def_readwrite("width",    &ASGE::Tile::width,    "Controls alpha for the rendered tile" );
  tile.def_readwrite("height",   &ASGE::Tile::height,   "Controls alpha for the rendered tile" );
  tile.def_readwrite("z",        &ASGE::Tile::z,        "Controls alpha for the rendered tile" );
  tile.def_property("texture",   &getTexture,  &setTexture, py::return_value_policy::reference, R"(
  The texture attached to the tile.

  When tiles are rendered they sample images or textures to colour the
  pixels. You can use this property to replace the texture that's being
  used during the rendering phase or to retrieve the currently attached
  one.

  :getter: Will return a reference to the currently active texture
           assigned to to the tile. It's possible that a tile may
           have no texture, so it contents should be checked to make
           sure it is not ``None`` to prevent undefined behaviour.
  :setter: Attaches a ``Texture`` object to the sprite. This will replace
           the texture that's being used during the rendering phase.
  :type: Texture

  Warning
  -------
  As a reference is being returned, the texture is only safe to access whilst
  it has not been destroyed. Once the texture's  memory is freed, this reference
  will no longer be valid.

  See Also
  --------
  Texture
  )");

  tile.def_property("src_rect",  &srcRect,     &setSrcRect, R"(
  Source rectangle for the texture.

  The source rectangle allows the developer to specify what part of
  a texture should be sampled during rendering. This allows the
  use of sprite sheets, where for example each cell might represent
  an animation. By changing the source rectangle, a single cell
  of animation could be selected, ignoring the others.

  Return
  ------
   numpy.ndarray[numpy.float]
      Direct access to the source rectangle used for texture mapping.

  Example
  -----
  Selecting a specific tile on a sprite sheet requires setting the
  source rectangle's starting position and its length. In the
  example that follows, a sprite sheet is loaded and then a single cell
  is used for rendering by modifying the source rectangle's starting x
  position and its length.

  >>> pyasge_tile = pyasge.Tile()
  >>> pyasge_tile.texture = renderer.loadTexture(filename)
  >>> pyasge_tile.src_rect = [0, 0, 44, 227]
  >>> pyasge_tile.width = 44

  )");

  tile.def("load", &loadTexture);
}
