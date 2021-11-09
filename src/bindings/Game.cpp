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

#include <Engine/Game.hpp>
#include <Engine/GameSettings.hpp>
#include <Engine/OGLGame.hpp>
#include <Engine/OpenGL/GLSprite.hpp>
#include <Engine/Sprite.hpp>
#include <pybind11/pybind11.h>
#include <string>
namespace py = pybind11;

#include <pybind11/functional.h>

/*--------------------------------------------------------------*/
/*  THIS IS OUR PYTHON INHERITABLE VERSION OF GAME              */
/*--------------------------------------------------------------*/
class ASGEGame :
  public ASGE::OGLGame
{
 public:
  // python and protected don't go
  using ASGE::OGLGame::renderer;
  using ASGE::OGLGame::inputs;
  using ASGE::OGLGame::toggleFPS;
  using ASGE::OGLGame::signalExit;

  ASGEGame() : ASGE::OGLGame(ASGE::GameSettings{}){};
  explicit ASGEGame(const ASGE::GameSettings& settings) : ASGE::OGLGame(settings){};
  ~ASGEGame() override = default;
  void init(){};
  void update(const ASGE::GameTime& us) override
  {
    PYBIND11_OVERRIDE_PURE(void, ASGE::OGLGame, update, us);
  }

  void fixedUpdate(const ASGE::GameTime& us) override
  {
    PYBIND11_OVERRIDE_NAME(void, ASGE::OGLGame, "fixed_update", fixedUpdate, us);
  }

  void render(const ASGE::GameTime& us) override
  {
    PYBIND11_OVERRIDE_PURE(void, ASGE::OGLGame, render, us);
  }

};


void initGame(py::module_ &m) {
  py::class_<ASGE::OGLGame, ASGEGame> game (
    m, "ASGEGame",
    R"(
    An OpenGL game based on the ASGE Framework.

    A structure and interface for running an instance of an ASGE Game. Its
    primary focus is on storing access to the renderer and the input system,
    along with the running of a simple game loop. The input system is
    intrinsically linked to the renderer subsystem due to needing access to
    the window for polling events. To help speed up development, a typical
    ``fixedUpdate``, ``update`` and ``render`` function is provided, along with
    a struct representing GameTime. In order to create an instance of the game,
    an inherited class is needed which overrides the update and render functions.

    Example
    -------
     >>> class MyASGEGame(pyasge.ASGEGame):
     >>>   def __init__(self, settings):
     >>>     pyasge.ASGEGame.__init__(self, settings)
     >>>     self.handler = \
     >>>       self.inputs.addCallback(pyasge.EventType.E_KEY, self.key_handler)
     >>>
     >>>   def key_handler(self, event : pyasge.KeyEvent) -> None:
     >>>     pass
     >>>
     >>>   def update(self, game_time : pyasge.GameTime) -> None:
     >>>     pass
     >>>
     >>>   def render(self, game_time : pyasge.GameTime) -> None:
     >>>     pass
     >>>
     >>>
     >>> def main():
     >>>   settings = pyasge.GameSettings()
     >>>   settings.window_width = 608
     >>>   settings.window_height = 1080
     >>>   game = MyASGEGame(settings)
     >>>   game.run()

  )");

  game.def(py::init<>());
  game.def(py::init<ASGE::GameSettings>());

  game.def(
    "fixed_update", [](ASGEGame &self, const ASGE::GameTime& us) {
      self.fixedUpdate(us);
      },
    py::arg("gametime"),
    R"(
    Used to update the game using fixed time-steps instead of the regular frame
    update.

    This is useful when you only want to progress the game world i.e. physics
    with a deterministically known amount. It is best to use fixed updates as
    a divisible or multiple of the FPS count. This allows a smoother delivery of
    frame data. For example: 60/120 would deliver one fixed update per two
    renders. Under heavy load, code executed in this function will cause the
    game to become sluggish. Care should be taken to ensure the fixed update rate
    set can be met.

    :param gametime: Delta game time measurements.
    :type gametime: pyasge.GameTime

    Note
    ====
    You can find the amount of time between fixed time-steps by accessing the
    fixed_delta and fixed_time fields on the game time instance. This is the
    requested fixed time-step specified in the game settings.

    See Also
    ========
    GameTime

  )");

  game.def(
    "update", [](ASGEGame &self, const ASGE::GameTime& us) { self.update(us); },
      py::arg("gametime"),
    R"(
    Used to update the game world using variable time-steps. You can think of
    this as the \"render update\" and will always run once before the frame
    is rendered.

    Typically this is where you would process objects that are changed over
    time but do not need to be deterministic in their nature. Examples include
    operations such as animation and skinning. If the CPU becomes bogged down
    in FixedUpdate, a frame will be drawn but the amount of game time will be
    shortened, resulting in slower movement. Unity suggests that physics
    related code goes in ``fixed_update`` and the rest of your logic goes here.
    **This is generally good advice to beginners who lack experience.**

    :param gametime: Delta game time measurements.
    :type gametime: pyasge.GameTime

    Note
    ====
    You can find the amount of time between fixed time-steps by accessing the
    fixed_delta and fixed_time fields on the game time instance. This is the
    requested fixed time-step specified in the game settings.

    See Also
    ========
    GameTime

  )");

  game.def(
    "render", [](ASGEGame &self,const ASGE::GameTime& us) { self.render(us); },
      py::arg("gametime"),
    R"(
    Renders the game scene.

    All rendering actions should be processed inside this function. Before
    render is called the graphics pipeline will be flushed and reset ready
    for rendering to commence. Game objects should have already been updated
    in the corresponding update function. Updating them in the render function
    can result in unexpected graphical issues.

    :param gametime: Delta game time measurements.
    :type gametime: pyasge.GameTime

    See Also
    ========
    GameTime
  )");

  game.def("run", &ASGE::Game::run, R"(Starts the game loop.)");

  game.def(
    "signalExit",
    [](ASGEGame& self) {
      self.signalExit();
      PyErr_WarnEx(PyExc_DeprecationWarning,
                   "signalExit() is deprecated, use signal_exit() instead.",
                   1);
    },
    R"(Calling this will cause the window and the game to shutdown.)");

  game.def(
    "signal_exit",
    [](ASGEGame& self) { self.signalExit(); },
    R"(Calling this will cause the window and the game to shutdown.)");

  game.def_property_readonly(
    "renderer",
    [](const ASGEGame& self) { return self.renderer.get(); },
    py::return_value_policy::reference_internal,
    "The renderer responsible for the window.");

  game.def_property_readonly(
    "inputs",
    [](const ASGEGame& self) { return self.inputs.get(); },
    py::return_value_policy::reference_internal,
    "The inputs event manager.");

  game.def("toggleFPS", [](ASGEGame& self) { self.toggleFPS(); });
}
