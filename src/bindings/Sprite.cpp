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

#include <Engine/OpenGL/GLSprite.hpp>
#include <Engine/Sprite.hpp>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

namespace py = pybind11;
using namespace pybind11::literals;

namespace {
  py::array_t<float> srcRect(ASGE::GLSprite &sprite) {
    auto length = 4;
    py::capsule free_when_done(sprite.srcRect(), [](void * /*data*/) {
      Logging::TRACE("destroying capsule");
    });

    py::array_t<float> out{
        {length}, {sizeof(float)}, sprite.srcRect(), free_when_done};
    return out;
  }

  void setSrcRect(ASGE::GLSprite &sprite, const py::array_t<float, 4> &array) {
    sprite.srcRect()[0] = array.at(0);
    sprite.srcRect()[1] = array.at(1);
    sprite.srcRect()[2] = array.at(2);
    sprite.srcRect()[3] = array.at(3);
  }
}

void initSprite(py::module_ &module) {
  // ----------------------------------------------------
  // ASGE GLSprite (Concrete Class)
  // ----------------------------------------------------
  py::class_<ASGE::GLSprite> asge_sprite(
      module, "Sprite", py::is_final(),
      R"(A sprite is the simplest renderable primitive in the game.

       Flip flags are an easy to control the rendering of
       the texture's UV coordinates. In default state, the texture
       is rendered from top left. When flipped the UV positions
       are inverted.
  )");

  asge_sprite.def(py::init());

  py::enum_<ASGE::Sprite::FlipFlags>(
      asge_sprite, "FlipFlags",
      R"(Texture flipping flags.

       Flip flags are an easy to control the rendering of
       the texture's UV coordinates. In default state, the texture
       is rendered from top left. When flipped the UV positions
       are inverted. )")

      .value("NORMAL", ASGE::Sprite::FlipFlags::NORMAL,
             "Texture is not flipped.")
      .value("FLIP_X", ASGE::Sprite::FlipFlags::FLIP_X,
             "Texture is flipped on the x axis.")
      .value("FLIP_Y", ASGE::Sprite::FlipFlags::FLIP_Y,
             "Texture is flipped on the y axis.")
      .value("FLIP_XY", ASGE::Sprite::FlipFlags::FLIP_XY,
             "Texture is flipped diagonally.")
      .value("FLIP_BOTH", ASGE::Sprite::FlipFlags::FLIP_BOTH,
             "Texture is flipped on both axis.");

  py::enum_<ASGE::Sprite::SourceRectIndex>(
      asge_sprite, "SourceRectIndex",
      R"(Source rectangle helper.

       The source rectangle indices can be accessed using these enum
       values to prevent the use of magic numbers. It aids with clarity
       when the individual UV indices are being accessed. )")

      .value("START_X", ASGE::Sprite::SourceRectIndex::SRC_START_X,
             "Starting point on the x axis")
      .value("START_Y", ASGE::Sprite::SourceRectIndex::SRC_START_Y,
             "Starting point on the y axis")
      .value("LENGTH_X", ASGE::Sprite::SourceRectIndex::SRC_LENGTH_X,
             "The length on the x axis")
      .value("LENGTH_Y", ASGE::Sprite::SourceRectIndex::SRC_LENGTH_Y,
             "The length on the y axis");

  py::enum_<ASGE::Sprite::AttachMode>(
      asge_sprite, "AttachFlags", py::arithmetic(),
      R"(Attach mode flags.

      When attaching a texture to the sprite, by default the sprite's
      settings will be reset to match the newly attached texture. These
      flags allow the user to prevent certain resets from occurs. )")

      .value("DEFAULT", ASGE::Sprite::AttachMode::DEFAULT,
             "Clobbers the existing sprite's settings")
      .value("KEEP_DIMS", ASGE::Sprite::AttachMode::KEEP_DIMS,
             "Retain the sprite's dimensions")
      .value("KEEP_UVS", ASGE::Sprite::AttachMode::KEEP_UVS,
             "Retain the sprite's UV settings")
      .value("KEEP_TINT", ASGE::Sprite::AttachMode::KEEP_TINT,
             "Retain the sprite's tint")
      .value("KEEP_ROTATION", ASGE::Sprite::AttachMode::KEEP_ROTATION,
             "Retain the sprite's rotation")
      .value("GENERATE_MIPS", ASGE::Sprite::AttachMode::GENERATE_MIPS,
             "Generate a new set of MipMaps for the texture")

      .def(py::self | py::self)
      .def(py::self & py::self);

  asge_sprite.def_property(
      "src_rect", &srcRect, &setSrcRect, R"(
      Source rectangle for the texture.

      The source rectangle allows the developer to specify what part of
      a texture should be sampled during rendering. This allows the
      use of sprite sheets, where for example each cell might represent
      an animation. By changing the source rectangle, a single cell
      of animation could be selected, ignoring the others.

      Return
      ------
       numpy.ndarray[numpy.float]
          Direct access to the sprite's source rectangle.

      Example
      -----
      Selecting a specific sprite on a sprite sheet requires setting the
      source rectangle's starting position and its length. In the
      example that follows, a sprite sheet is loaded and then a single cell
      is used for rendering by modifying the source rectangle's starting x
      position and its length.

      Note
      -------
      Notice how the width of the sprite itself is altered. If we don't
      change the width of the sprite to match, it will render the
      source rectangle stretched, which in some situations may actually
      be desirable i.e. when stretching a background image.


      |playerspritesheet1|

      >>> import pyasge
      >>> '''selecting a sprite within a sprite sheet'''
      >>> sprite_sheet = pyasge.Sprite()
      >>> sprite_sheet.loadTexture("/data/spritesheet.png")
      >>> sprite_sheet.src_rect[pyasge.Sprite.SourceRectIndex.START_X] = 227
      >>> sprite_sheet.src_rect[pyasge.Sprite.SourceRectIndex.LENGTH_X] = 44
      >>> sprite_sheet.width = 44

      |playerspritesheet2|

      .. |playerspritesheet1| image:: ../_static/images/spritesheet_walk.png
      .. |playerspritesheet2| image:: ../_static/images/spritesheet_walk_cell.png

      See Also
      --------
      SourceRectIndex
  )");

  asge_sprite.def_property(
      "z_order",
      [](const ASGE::GLSprite &self) { return self.getGlobalZOrder(); },
      [](ASGE::GLSprite &self, int8_t z_order) {
        self.setGlobalZOrder(z_order);
      }, R"(
      The rendering order (layer) of the sprite.

      When rendering it is often necessary to control the order in which sprites,
      text or even UI elements are rendered. For example, if parts of the UI were
      rendered before the background they would end up hidden. Z-ordering is a
      common approach to controlling this behaviour and is essential when using
      batch rendering.

      :getter: The currently assigned z-order value.
      :setter: Replaces the z-ordering of the sprite.
      :type: np.uint8

      Tip
      ---
      Typically, an object with a lower z-order will be rendered
      before one with a higher z-order. In PyASGE you can use the z_order property
      to control the render ordering.

      Example
      -------
      In this image you can see an example of when the z-order for a sprite is
      not set correctly. The blocks below the player should have a lower z-order
      than the player's sprite, to ensure they are rendered first.

      .. figure:: https://i.stack.imgur.com/8aGig.png
         :alt: https://gamedev.stackexchange.com/questions/130703/2d-voxel-isometric-rendering-with-non-grid-aligned-objects

         GameDev @ StackExchange
  )");

  asge_sprite.def_property(
      "opacity",
      static_cast<float (ASGE::GLSprite::*)(void) const>(&ASGE::GLSprite::opacity),
      static_cast<void (ASGE::GLSprite::*)(float)>(&ASGE::GLSprite::opacity), R"(
      Sets the opacity of the sprite.

      This field let's you control the opacity of the sprite by modifying the
      alpha channel during the render cycle. 1.0F is opaque and 0.0F is completely
      transparent.

      :getter: Returns value for the alpha channel.
      :setter: Sets the new value for the alpha channel.
      :type: float
  )");

  asge_sprite.def_property(
      "alpha",
      static_cast<float (ASGE::GLSprite::*)(void) const>(&ASGE::GLSprite::opacity),
      static_cast<void (ASGE::GLSprite::*)(float)>(&ASGE::GLSprite::opacity), R"(
      Alpha channel to control the opacity of the sprite.

      This field let's you control the opacity of the sprite by modifying the
      alpha channel during the render cycle. 1.0F is opaque and 0.0F is completely
      transparent.

      :getter: Returns value for the alpha channel.
      :setter: Sets the new value for the alpha channel.
      :type: float
  )");

  asge_sprite.def_property(
      "x",
      static_cast<float (ASGE::GLSprite::*)(void) const>(&ASGE::GLSprite::xPos),
      static_cast<void (ASGE::GLSprite::*)(float)>(&ASGE::GLSprite::xPos), R"(
      Sprite's position on the x axis

      Used to position the sprite in world space, which in turn is used for
      rendering the sprite on the orthographic viewport. The x axis refers
      to the horizontal positioning of the sprite and is based on the top-left
      of the sprite.

      :getter: Returns the sprite's x position.
      :setter: Sets the sprite's x position.
      :type: float

      Example
      -------
      >>> import pyasge
      >>> sprite = pyasge.Sprite()
      >>> print(sprite.x)
      >>> sprite.x = 250
  )");

  asge_sprite.def_property(
      "y",
      static_cast<float (ASGE::GLSprite::*)(void) const>(&ASGE::GLSprite::yPos),
      static_cast<void (ASGE::GLSprite::*)(float)>(&ASGE::GLSprite::yPos), R"(
      Sprite's position on the y axis

      Used to position the sprite in world space, which in turn is used for
      rendering the sprite on the orthographic viewport. The y axis refers
      to the vertical positioning of the sprite and is based on the top-left
      of the sprite.

      :getter: Returns the sprite's y position.
      :setter: Sets the sprite's y position.
      :type: float

      Example
      -------
      >>> import pyasge
      >>> sprite = pyasge.Sprite()
      >>> print(sprite.y)
      >>> sprite.y = 250
  )");

  asge_sprite.def_property(
      "width",
      static_cast<float (ASGE::GLSprite::*)(void) const>(&ASGE::GLSprite::width),
      static_cast<void (ASGE::GLSprite::*)(float)>(&ASGE::GLSprite::width), R"(
      The width to render the sprite.

      The width controls how wide the sprite will be rendered. It does
      not directly control the source rectangle and will stretch the
      texture attached to it, to ensure it meets the requested width.

      :getter: Returns the requested width of the sprite.
      :setter: Sets the requested width of the sprite.
      :type: float

      Example
      -------
      >>> import pyasge
      >>> sprite = pyasge.Sprite()
      >>> print(sprite.width)
      >>> sprite.width = 500
  )");

  asge_sprite.def_property(
      "height",
      static_cast<float (ASGE::GLSprite::*)(void) const>(&ASGE::GLSprite::height),
      static_cast<void (ASGE::GLSprite::*)(float)>(&ASGE::GLSprite::height), R"(
      The height to render the sprite.

      The height controls how tall the sprite will be rendered. It does
      not directly control the source rectangle and will stretch the
      texture attached to it, to ensure it meets the requested height.

      :getter: Returns the requested height of the sprite.
      :setter: Sets the requested height of the sprite.
      :type: float

      Example
      -------
      >>> import pyasge
      >>> sprite = pyasge.Sprite()
      >>> print(sprite.width)
      >>> sprite.height = 500
  )");

  asge_sprite.def_property(
      "scale",
      static_cast<float (ASGE::GLSprite::*)(void) const>(&ASGE::GLSprite::scale),
      static_cast<void (ASGE::GLSprite::*)(float)>(&ASGE::GLSprite::scale), R"(
      Scale to apply to the sprite.

      The scale can be adjusted to automatically make the sprite render
      larger or smaller than it's original size. This allows for on the fly
      alterations without having to edit the sprite's width and height. The
      scaling operation is performed uniformly in both axis.

      :getter: Returns the scale factor.
      :setter: Sets the scale factor.
      :type: float

      Example
      -------
      >>> import pyasge
      >>> sprite = pyasge.Sprite()
      >>> sprite.scale = 5
  )");

  asge_sprite.def_property(
      "shader",
      [](const ASGE::GLSprite &self) {
        return dynamic_cast<const ASGE::SHADER_LIB::GLShader*>(
            self.getPixelShader());
      },
      [](ASGE::GLSprite &self, ASGE::SHADER_LIB::GLShader *shader) {
        self.setPixelShader(shader);
      }, R"(
      Example
      -------
      >>> self.sprite = pyasge.Sprite()
      >>> self.shader = self.renderer.loadPixelShader("/data/shaders/red.frag")
      >>> self.sprite.shader = shader
  )");

  asge_sprite.def_property(
      "flip_flags",
      static_cast<ASGE::GLSprite::FlipFlags (ASGE::GLSprite::*)(void) const>
      (&ASGE::GLSprite::flipFlags),
      static_cast<void (ASGE::GLSprite::*)(ASGE::GLSprite::FlipFlags)>
      (&ASGE::GLSprite::setFlipFlags), R"(
      Controls the flipping of the attached texture.

      Flipping the sprite will simply swap the sampled UV coordinates. Meaning
      the inverse textures pixels will be sampled. Flipping the axis will mean
      samples from the [1,0] domain instead of [0,1].

      :getter: Returns the current flip state of the sprite.
      :setter: Sets the sprites flip flags.
      :type: FlipFlags

      Example
      -------
      >>> sprite.flip_flags = pyasge.Sprite.FlipFlags.FLIP_X
      >>> sprite.flip_flags = pyasge.Sprite.FlipFlags.FLIP_Y

      See Also
      --------
      FlipFlags
  )");

  asge_sprite.def_property(
      "rotation",
      static_cast<float (ASGE::GLSprite::*)(void) const>(&ASGE::GLSprite::rotationInRadians),
      static_cast<void (ASGE::GLSprite::*)(float)>(&ASGE::GLSprite::rotationInRadians),
      R"(
      Rotation (in radians) to apply to the rendered sprite.

      The angle of rotation is used to rotate the sprite around it's origin.
      The origin defaults to the mid-point of the sprite. The angle of rotation
      is expressed in radians.

      :getter: Returns the sprites angle of rotation in radians.
      :setter: Sets the rotation of the sprite in radians.
      :type: float

      Note
      -------
      :math:`degrees = radians * 180^\theta\ / pi`
  )");

  asge_sprite.def_property(
      "colour",
      static_cast<ASGE::Colour (ASGE::GLSprite::*)(void) const>(&ASGE::GLSprite::colour),
      static_cast<void (ASGE::GLSprite::*)(ASGE::Colour)>(&ASGE::GLSprite::colour), R"(
      Controls the tinting of the sprite.

      :getter: The sprite's colour.
      :setter: Sets the sprite's colour.
      :type: pyasge.Colour

  )");

  asge_sprite.def(
      "dimensions",
      [](ASGE::GLSprite &sprite) {
        float width = 0;
        float height = 0;
        sprite.dimensions(width, height);
        return std::make_tuple(width, height);
      }, R"(
      Gets the height and the width of the sprite.

      Retrieves the requested width and height to render the sprite.
      This does not relate to the texture attached to the sprite, rather
      the size and shape the texture will appear on the screen.
      the inverse textures pixels will be sampled.

      Returns
      ----------
      tuple[float,float]
        the width of the texture.
  )");

  asge_sprite.def(
      "isFlippedOnX",
      [](const ASGE::GLSprite &self) { return self.isFlippedOnX(); }, R"(
      Checks to see if the texture is flipped on the X axis.

      It is possible to flip the UV coordinates used on the sprite's texture.
      This will check to see if the X axis is flipped.

      Returns
      ----------
      bool
        If the texture is flipped on the X axis.
  )");

  asge_sprite.def(
      "isFlippedOnY",
      [](const ASGE::GLSprite &self) { return self.isFlippedOnY(); }, R"(
      Checks to see if the texture is flipped on the Y axis.

      It is possible to flip the UV coordinates used on the sprite's texture.
      This will check to see if the Y axis is flipped.

      Returns
      ----------
      bool
        If the texture is flipped on the Y axis.
  )");

  asge_sprite.def(
      "isFlippedOnXY",
      [](const ASGE::GLSprite &self) { return self.isFlippedOnXY(); }, R"(
      Checks to see if the texture is flipped  diagonally.

      It is possible to flip the UV coordinates used on the sprite's texture.
      This will check to see if the XY axis are flipped with each other.

      Returns
      ----------
      bool
        If the texture is flipped diagonally.
  )");

  asge_sprite.def(
      "getLocalBounds",
      [](ASGE::GLSprite &self) { return self.getLocalBounds(); }, R"(
      Retrieves the sprite's 4 points in local space.

      Simply returns the sprite's original and unmodified dimensions. No
      transforms will be applied, meaning rotation and scaling are absent
      and the points can be considered as local or model space. These
      points can be used as the starting basis of an `AABB`_ or for custom
      collision detections.

      Return
      ------
         SpriteBounds
            The four vertex bounds of the sprite in local space.

      Example
      -------
        >>> import pyasge
        >>> sprite = pyasge.Sprite()
        >>> sprite.loadTexture("/data/game/background.jpg")
        >>> print(sprite.getLocalBounds())

      Warning
      -------
      When comparing bounding volumes, ensure they are all generated
      from the same space. Mixing model and world bounding boxes will not
      have the equivalent transforms applied.

      See Also
      --------
      SpriteBounds


      .. _AABB: https://manbeardgames.com/docs/tutorials/monogame-3-8/collision-detection/aabb-collision/
  )");

  asge_sprite.def(
      "getWorldBounds",
      [](ASGE::GLSprite &self) { return self.getWorldBounds(); }, R"(
      Retrieves the sprite's 4 points in transformed world space.

      Returns the 4 vertices that delimit the sprite's position in world space.
      Any transforms (scaling and rotation) have already been applied. This is
      useful for when you need to know the projected location i.e. calculating
      a bounding volume.

      Return
      ------
         SpriteBounds
            The four vertex bounds of the sprite in world space.

      Example
      -------
        >>> import pyasge
        >>> sprite = pyasge.Sprite()
        >>> sprite.loadTexture("/data/game/background.jpg")
        >>> print(sprite.getWorldBounds())

      Warning
      -------
      When comparing bounding volumes, ensure they are all generated
      from the same space. Mixing model and world bounding boxes will not
      have the equivalent transforms applied.

      See Also
      --------
      SpriteBounds
  )");

  asge_sprite.def(
      "setMagFilter",
      [](ASGE::GLSprite &self, ASGE::Texture2D::MagFilter filter) {
        self.setMagFilter(filter);
      }, py::arg("magfilter"), R"(
      Sets the magnification filter on the attached texture.

      Use this function to alter the texture sampling behaviour when the attached
      texture is being read during the rendering phase. Low resolution artwork,
      often known as pixel art should use nearest neighbour to retain the crispness
      of the original.

      Parameters
      ----------
      magfilter : MagFilter
        The magnification filtering to apply to the texture.

      Example
      -------
        >>> import pyasge
        >>> sprite = pyasge.Sprite()
        >>> sprite.loadTexture("/data/image.png")
        >>> sprite.scale = 5
        >>> sprite.setMagFilter(pyasge.MagFilter.NEAREST)

      |filtering|

      .. |filtering| image:: ../_static/images/filtering.png

      See Also
      --------
      MagFilter
  )");

  asge_sprite.def(
      "attach",
      [](ASGE::GLSprite &sprite, ASGE::GLTexture *texture, ASGE::Sprite::AttachMode mode) {
        return sprite.attach(texture, static_cast<ASGE::Sprite::AttachMode>(mode));
      }, py::arg("texture"), py::arg("attach_mode"), R"(
      Attaches a :class:`Texture` object to the sprite.

      When sprites are rendered they sample images or textures to colour the
      pixels. You can use this function to replace the texture that's being
      used during the rendering phase.

      :texture: The replacement texture to attach
      :type: :class:`pyasge.Texture`
      :attach_mode: The flags to apply when attaching the texture to the sprite
      :type: :class:`pyasge.Sprite.AttachMode`

      .. code-block::
        :caption: Example

        >>> self.sprite = pyasge.Sprite()
        >>> self.texture = self.renderer.createNonCachedTexture("/data/image.png")
        >>> self.sprite.attach(texture, pyasge.Sprite.AttachFlags(
            pyasge.Sprite.AttachFlags.KEEP_UVS |
            pyasge.Sprite.AttachFlags.KEEP_ROTATION))

      .. seealso::
        pyasge.Texture
  )");

  asge_sprite.def(
      "attach",
      [](ASGE::GLSprite &sprite, ASGE::GLTexture *texture) {
        return sprite.attach(texture, ASGE::Sprite::AttachMode::DEFAULT);
      }, py::arg("texture"), R"(
      Attaches a :class:`Texture` object to the sprite.

      When sprites are rendered they sample images or textures to colour the
      pixels. You can use this function to replace the texture that's being
      used during the rendering phase.

      :texture: The replacement texture to attach
      :type: :class:`pyasge.Texture`

      .. code-block::
        :caption: Example

        >>> self.sprite = pyasge.Sprite()
        >>> self.texture = self.renderer.createNonCachedTexture("/data/image.png")
        >>> self.sprite.attach(self.texture)

      .. seealso::
        pyasge.Texture
  )");

  asge_sprite.def(
      "loadTexture",
      [](ASGE::GLSprite &self, const std::string& file_path) {
        return self.ASGE::Sprite::loadTexture(file_path);
      }, py::arg("file_path"), R"(
      Loads a texture and attaches it to the sprite.

      Uses a texture caching system to attempt to load the file from the ASGE
      IO subsystem. If it loads successfully, the texture is cached and the
      dimensions set according to the source image. A boolean is used to return
      whether or not it loaded successfully.

      Parameters
      ----------
         filename : str
            The texture (sprite) filename to load.

      Return
      ------
         bool
            Whether or not it was successfully loaded

      Example
      -------
        >>> import pyasge
        >>> sprite = pyasge.Sprite()
        >>> if sprite.loadTexture("/data/game/background.jpg" is True:
        >>>   print("texture loaded")
  )");

  asge_sprite.def_property(
      "texture",
      [](ASGE::GLSprite &self) {
        return dynamic_cast<ASGE::GLTexture *>(self.getTexture());
      },
      [](ASGE::GLSprite &sprite, ASGE::GLTexture *texture) {
        return sprite.attach(texture, ASGE::Sprite::AttachMode::DEFAULT);
      },
      py::return_value_policy::reference, R"(
      The texture attached to the sprite.

      When sprites are rendered they sample images or textures to colour the
      pixels. You can use this property to replace the texture that's being
      used during the rendering phase or to retrieve the currently attached
      one.

      :getter: Will return a reference to the currently active texture
               assigned to to the sprite. It's possible that a sprite may
               have no texture, so it contents should be checked to make
               sure it is not ``None`` to prevent undefined behaviour.
      :setter: Attaches a ``Texture`` object to the sprite. This will replace
               the texture that's being used during the rendering phase.
      :type: Texture

      Example
      -------
        >>> import pyasge
        >>> sprite = pyasge.Sprite()
        >>> if sprite.texture is not None:
        >>>     print("sprite has a texture attached")

      Warning
      -------
      As a reference is being returned, the texture is only safe to
      access whilst it has not been destroyed. Once the texture's
      memory is freed, this reference will no longer be valid.

      See Also
      --------
      Texture
  )");

  asge_sprite.def(
      "getTexture",
      [](ASGE::GLSprite &self) {
        return dynamic_cast<ASGE::GLTexture *>(self.getTexture());
      },
      py::return_value_policy::reference, R"(
      Retrieves the texture attached to the sprite.

      Will return a reference to the currently active texture assigned to
      to the sprite. It's possible that a sprite may have no texture, so
      it contents should be checked to make sure it is not ``None`` to prevent
      undefined behaviour.

      Return
      ------
         Texture
            The texture associated with the sprite. *May be None or null*.


      Warning
      -------
      As a reference is being returned, the texture is only safe to
      access whilst it has not been destroyed. Once the texture's
      memory is freed, this reference will no longer be valid.


      Example
      -------
        >>> import pyasge
        >>> sprite = pyasge.Sprite()
        >>> if sprite.getTexture is not None:
        >>>     print("sprite has a texture attached")

      See Also
      --------
      Texture
  )");

  asge_sprite.def_property_readonly("midpoint", &ASGE::Sprite::midpoint, R"(
      Calculates the mid-point of the sprite.

      Sprites origins are normally 0,0, which maps to the top left. This
      function returns the mid-point of the sprite based on its width and height
      and also the x,y position it's currently in.

      :getter: Will return the calculated midpoint of the sprite based on its
               position in the world and its length and width. This function
               automatically applies the sprite's scale.
      :type: Point2D

      Note
      -------
      This midpoint is scaled using the sprites scale factor.

      Example
      -------
      >>> # set a camera to follow the player's mid-point
      >>> self.camera.lookAt(self.data.player.midpoint)
  )");

  asge_sprite.def("__repr__", [](const ASGE::GLSprite &sprite) {

    // nolint
    std::stringstream ss;
    ss << "xpos:\t\t" << std::to_string(sprite.xPos());
    ss << "ypos:\t\t" << std::to_string(sprite.yPos()) << std::endl;
    ss << "width:\t\t" << std::to_string(sprite.width());
    ss << "height:\t\t" << std::to_string(sprite.height()) << std::endl;
    ss << "rotation:\t" << std::to_string(sprite.rotationInRadians());
    ss << "scale:\t\t" << std::to_string(sprite.scale());
    ss << "zorder:\t\t" << std::to_string(sprite.getGlobalZOrder()) << std::endl;
    ss << "color.r:\t" << std::to_string(sprite.colour().r);
    ss << "color.g:\t" << std::to_string(sprite.colour().g);
    ss << "color.b:\t" << std::to_string(sprite.colour().b);
    ss << "color.a:\t" << std::to_string(sprite.opacity()) << std::endl;
    ss << "flipped_x:\t" << std::boolalpha << sprite.isFlippedOnX();
    ss << "\t\tflipped_y:\t" << std::boolalpha << sprite.isFlippedOnY() << std::endl;
    ss << "\tpixel shader attached:\t\t" << std::boolalpha << sprite.hasPixelShader() << std::endl;
    ss << "\tsrc_top_left  [" << std::to_string(sprite.srcRect()[0]) << "]";
    ss << "\tsrc_top_right [" << std::to_string(sprite.srcRect()[1]) << "]";
    ss << "\tsrc_btm_right [" << std::to_string(sprite.srcRect()[2]) << "]";
    ss << "\tsrc_btm_left  [" << std::to_string(sprite.srcRect()[3]) << "]" << std::endl;

    return ss.str();
  });

    asge_sprite.def(py::pickle(
    [](const ASGE::GLSprite &p) { // __getstate__
        /* Return a tuple that fully encodes the state of the object */
        return py::make_tuple(
                p.dimensions(),
                p.srcRect()[0], p.srcRect()[1], p.srcRect()[2], p.srcRect()[3],
                p.getGlobalZOrder(), p.rotationInRadians(), p.scale(),
                p.opacity(), p.flipFlags(), p.colour(), p.getPixelShader(),
                p.getTexture()
                );
    },
    [](py::tuple t) { // __setstate__
        if (t.size() != 2)
            throw std::runtime_error("Invalid state!");

        auto p = ASGE::GLSprite();

        auto dims = t[0].cast<std::tuple<int, int>>();
        p.width(std::get<0>(dims));
        p.height(std::get<1>(dims));
        p.srcRect()[0] = t[1].cast<float>();
        p.srcRect()[1] = t[2].cast<float>();
        p.srcRect()[2] = t[3].cast<float>();
        p.srcRect()[3] = t[4].cast<float>();
        p.setGlobalZOrder(t[5].cast<int16_t>());

        return p;
    }));
}
