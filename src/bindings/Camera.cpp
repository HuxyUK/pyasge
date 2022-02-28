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

#include <Engine/Camera.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

namespace py = pybind11;
void initCamera(py::module_ &module)
{
  PYBIND11_NUMPY_DTYPE(ASGE::Camera::CameraView, min_x, max_x, min_y, max_y);
  py::class_<ASGE::Camera::CameraView> camera_view(module, "CameraView", py::buffer_protocol(),
    R"(A an orthogonal camera view class.

       The camera view class describes a bounding box that is used to map
       the game world to the camera's lens. Objects outside of the the view
       will not be rendered. The camera view can be applied to the renderer
       during the drawing phase of the game. It's possible to swap camera
       views during a render cycle. The easiest way to generate the view
       is to use a Camera class, assign it a width and height and update
       its focal point using ``lookAt``.

       .. figure:: https://cdn.knowww.eu/59b8e93cd54a862e9d7e4049//R21wxTK0kJBo.png
          :alt: © Knowww 2017

          glm::ortho, © Knowww 2017

       Example
       -------
       >>> self.camera = pyasge.Camera(1024, 768)
       >>> self.camera = pyasge.Camera(1024, 768)
       >>> self.camera.lookAt(pyasge.Point2D(0, 0))
       >>> self.renderer.setProjectionMatrix(self.camera.view)
  )");

  camera_view.def(py::init());
  camera_view.def(py::init<const ASGE::Camera::CameraView&>());
  camera_view.def_readwrite("min_x", &ASGE::Camera::CameraView::min_x, "The minimum x world position.");
  camera_view.def_readwrite("max_x", &ASGE::Camera::CameraView::max_x, "The maximum x world position.");
  camera_view.def_readwrite("min_y", &ASGE::Camera::CameraView::min_y, "The minimum y world position.");
  camera_view.def_readwrite("max_y", &ASGE::Camera::CameraView::max_y, "The maximum y world position.");

  camera_view.def_buffer([](ASGE::Camera::CameraView &view) -> py::buffer_info {
    return py::buffer_info(
        &view,                                  /* Pointer to buffer */
        sizeof(float),                          /* Size of one scalar */
        py::format_descriptor<float>::format(), /* Python struct-style format descriptor */
        1,                                      /* Number of dimensions */
        {4},                                    /* Buffer dimensions */
        {sizeof(float)}                         /* Strides (in bytes) for each index */
    );
  });

  py::implicitly_convertible<py::tuple, ASGE::Camera::CameraView>();
  py::implicitly_convertible<py::list, ASGE::Camera::CameraView>();

  class PyCamera : public ASGE::Camera
  {
   public:
    using ASGE::Camera::Camera;
    void translate(float x, float y, float zoom) override
    {
      PYBIND11_OVERRIDE(void, ASGE::Camera, translate, x, y, zoom);
    }
    void translateX(float x) override
    {
      PYBIND11_OVERRIDE(void, ASGE::Camera, translateX, x);
    }
    void translateY(float y) override
    {
      PYBIND11_OVERRIDE(void, ASGE::Camera, translateY, y);
    }
    void translateZ(float zoom) override
    {
      PYBIND11_OVERRIDE(void, ASGE::Camera, translateZ, zoom);
    }
    void update(const ASGE::GameTime& game_time) override
    {
      PYBIND11_OVERRIDE(void, ASGE::Camera, update, game_time);
    }
  };

  py::class_<ASGE::Camera, PyCamera> camera(module, "Camera", py::dynamic_attr(),
    R"(A 2D orthogonal camera class.

       The Camera class is designed as a simple way to alter the view being
       drawn to the screen. The view described by the camera will be scaled
       to the viewport, so it is recommend to size it identically to the viewport
       or to at least use the same aspect ratio to prevent scaling artifacts.
       This basic implementation provides translation in the X and Y axis and use
       of Z to control the zoom level of the camera. In order to apply a
       translation to the camera, the translate function must be called.

       .. figure:: http://www.pbr-book.org/3ed-2018/Camera_Models/Ortho%20generate%20ray.svg
          :alt: pbr-book.org

          Physically Based Rendering: From Theory To Implementation,
          © 2004-2019 Matt Pharr, Wenzel Jakob, and Greg Humphreys

       Note
       -------
       The default implementation is to move the camera by the requested
       translation amount. There is no damping or smoothing applied. If this is
       required, the class should be inherited from and the update function
       overridden.

       Example
       -------
         >>> self.camera = pyasge.Camera(1024, 768)
         >>> self.camera.zoom = 0.5
         >>> self.renderer.setProjectionMatrix(self.camera.view)

  )");

  camera.def(py::init<float, float>(), py::arg("width"), py::arg("height"));

  camera.def(
    py::init<ASGE::Point2D, float, float>(),
    py::arg("focal_point"),
    py::arg("width"),
    py::arg("height"));

  camera.def_property(
    "zoom", &ASGE::Camera::getZoom, &ASGE::Camera::setZoom,
    R"(
    The camera's zoom level.

    :getter: Returns the current zoom.
    :setter: Sets the camera's zoom.
    :type: float
  )");

  camera.def_property_readonly(
    "view", py::overload_cast<>(&ASGE::Camera::getView, py::const_),
    R"(
    A view that describes the camera's framing.

    Use this to frame the action, which in turn is rendered to the window. This
    view can be used directly to control the projection matrix used for mapping
    to the game window. Everything inside the view will be mapped directly to
    the screens viewport. The bounding volume controls the depth of items
    rendered.

    .. figure:: http://www.pbr-book.org/3ed-2018/Camera_Models/Ortho%20viewing%20volume.svg
       :alt: pbr-book.org
       :align: center
       :width: 280px

       Physically Based Rendering: From Theory To Implementation,
       © 2004-2019 Matt Pharr, Wenzel Jakob, and Greg Humphreys

    Note
    -------
    As this is an orthographic view, the same rendered object will occupy an
    exact amount of screen space, regardless of its distance from the camera.
    There is no vanishing point in play. For example given a viewport that maps
    directly to the window size, a 100x100 sized sprite will use 100x100 pixels
    irrespective of its distance.

    Example
    -------
      >>> self.renderer.setProjectionMatrix(camera.view)

    :returns: Returns a struct used to represent the camera's view.
    :type: pyasge.CameraView
  )");

  camera.def(
    "lookAt", &ASGE::Camera::lookAt, py::arg("focal_point"),
    R"(
    Sets the camera's focal point, which controls the centering of the frame.
    For example directing the camera to focus at {0,0} will center {0,0} in the
    middle of the frame.
  )");

  camera.def(
    "translate", &ASGE::Camera::translate, py::arg("x"), py::arg("y"), py::arg("zoom"),
    R"(
    Sets the camera's translation and zoom value.

    Moves the camera to the x and y specified co-ordinates and also updates the
    zoom level. Could be useful for resetting the camera to a predefined
    position and zoom level.
  )");

  camera.def(
    "translateX", &ASGE::Camera::translateX, py::arg("x"),
    R"(Sets the camera's position on the x axis)"
  );

  camera.def(
    "translateY", &ASGE::Camera::translateY, py::arg("y"),
    R"(Sets the camera's position on the y axis)"
  );

  camera.def(
    "translateZ", &ASGE::Camera::translateZ, py::arg("zoom"),
    R"(Sets the camera's zoom level)"
  );

  camera.def(
    "resize", &ASGE::Camera::resize, py::arg("width"), py::arg("height"),
    R"(Resizes the camera's view.)"
  );

  camera.def(
    "clamp", &ASGE::Camera::clamp, py::arg("view_bounds"),
    R"(
    Clamps the camera's view.

    It is often desirable to clamp the field of vision for the camera to
    ensure only specific regions of the game screen are shown. Consider a
    tile map where the camera should not exceed the width or height of the
    map. This function can be used to clamp the view to a set of predefined
    values, representing `min_x`, `max_x`, `min_y` and `max_y`. These would
    then be used to simply clamp the view's x and y positions.

    :param view_bounds: The four bounds to use in xy space.
    :type view_bounds: :class:`CameraView`

    .. code-block::
       :caption: An example of clamping to a map made from 128x128 tiles. The
                 games design resolution is used to ensure only the visible
                 game map is shown. The camera's view is taken into consideration
                 as this can affect the visible viewing area.

       >>> view = pyasge.CameraView()
       >>> view.min_x = self.game_res[0] * 0.5 * self.camera.zoom,
       >>> view.max_x = self.map.width   * 128 - self.game_res[0] * 0.5 * self.camera.zoom,
       >>> view.min_y = self.game_res[1] * 0.5 * self.camera.zoom,
       >>> view.max_y = self.map.height  * 128 - self.game_res[1] * 0.5 * self.camera.zoom
       >>> self.camera.clamp(view)

    .. note::
      This version of the function uses the :class:`CameraView` data structure.
  )");

  camera.def(
    "clamp", [](ASGE::Camera& self, py::list& list) {
        if(list.size() != 4)
        {
          throw std::length_error("Lists for clamping the camera should contain 4 values only");
        }

        ASGE::Camera::CameraView view;
        view.min_x = list[0].cast<float>();
        view.max_x = list[1].cast<float>();
        view.min_y = list[2].cast<float>();
        view.max_y = list[3].cast<float>();
        self.clamp(view);}, py::arg("view_bounds"),
    R"(
    Clamps the camera's view.

    It is often desirable to clamp the field of vision for the camera to
    ensure only specific regions of the game screen are shown. Consider a
    tile map where the camera should not exceed the width or height of the
    map. This function can be used to clamp the view to a set of predefined
    values, representing `min_x`, `max_x`, `min_y` and `max_y`. These would
    then be used to simply clamp the view's x and y positions.

    :param view_bounds: The four bounds to use in xy space
    :type view_bounds: :class:`CameraView`

    .. note::
      This version of the function uses a python style list, comprising of
      four float values, representing the bounds of the view.

    .. code-block::
       :caption: An example of clamping to a map made from 128x128 tiles. The
                 games design resolution is used to ensure only the visible
                 game map is shown. The camera's view is taken into consideration
                 as this can affect the visible viewing area.

       >>> view = [
       >>>   self.game_res[0] * 0.5 * self.camera.zoom,
       >>>   self.map.width   * 128 - self.game_res[0] * 0.5 * self.camera.zoom,
       >>>   self.game_res[1] * 0.5 * self.camera.zoom,
       >>>   self.map.height  * 128 - self.game_res[1] * 0.5 * self.camera.zoom
       >>> ]
       >>> self.camera.clamp(view)

  )");

  camera.def_property_readonly(
    "position", &ASGE::Camera::position, "The camera's position on the XY axis");

  camera.def(
    "update", &ASGE::Camera::update, py::arg("game_time"),
    R"(
    Updates the camera.

    Out of the box there's no smoothing, interpolation or damping of the
    camera's movements. In order to allow greater custom behaviour, this
    function can be overridden by a child class and custom movement logic
    added.
  )");
}
