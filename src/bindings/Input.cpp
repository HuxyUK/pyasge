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

#include <Engine/InputEvents.hpp>
#include <Engine/OpenGL/GLInput.hpp>
#include <Engine/Point2D.hpp>
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>

PYBIND11_MAKE_OPAQUE(std::vector<ASGE::GamePadData>);

namespace py = pybind11;

void initInput(py::module_ & module){

  py::class_<std::vector<ASGE::GamePadData>>(module, "GamePads")
    .def(py::init<>())
    .def("front", (const ASGE::GamePadData &(std::vector<ASGE::GamePadData>::*)() const) &std::vector<ASGE::GamePadData>::front)
    .def("back",  (const ASGE::GamePadData &(std::vector<ASGE::GamePadData>::*)() const) &std::vector<ASGE::GamePadData>::back)
    .def("__len__", [](std::vector<ASGE::GamePadData> &v) { return v.size(); })
    .def("__repr__", [](std::vector<ASGE::GamePadData> &v)
    {
        std::string list = "[";
        bool first = true;
        for (const auto &gamepad: v) {
          if (!first) {
            list += ", ";
          }
          list += std::to_string(gamepad.idx) + ": " + gamepad.name;
          first = false;
        }
        return list + "]";
      })

    .def("__iter__", [](std::vector<ASGE::GamePadData> &v)
    {
          return py::make_iterator(v.cbegin(), v.cend());
    },

    py::keep_alive<0, 1>()); /* Keep vector alive while iterator is used */


  py::enum_<ASGE::MOUSE::CursorMode>(
    module, "CursorMode",
    R"(Mouse cursor modes.)")

    .value(
      "NORMAL",
      ASGE::MOUSE::CursorMode::NORMAL,
      "Enables the cursor. The cursor will be shown and the user is free to "
      "leave the window and interact with other applications.")
    .value(
      "HIDDEN",
      ASGE::MOUSE::CursorMode::HIDDEN,
      "The cursor is no longer shown when positioned over the active game "
      "window, however, upon leaving the window the cursor will be shown, "
      "allowing interaction outside of the game window.")
    .value(
      "LOCKED", ASGE::MOUSE::CursorMode::LOCKED,
      "Simply, the cursor will be hidden and locked to the window. The user"
      "will not be able to leave the windowed area.");

  py::class_<ASGE::GLInput> input(
    module, "Input",
    R"(
    The input handler system.

    The input class is designed to work alongside the renderer and is
    responsible for sending events to interested parties. It will also provide
    helper functions that can retrieve non-event driven data such as the cursor
    position or the gamepad status. Much of the underlying implementation will
    be platform specific, whilst offering a compatible interface.
 )");

  input.def(py::init<>());

  input.def(
    "getGamePad",
    [](ASGE::GLInput& self, int index){
      return self.getGamePad(index);
    },
    py::arg("index"),
    R"(
    Retrieves gamepad data for the controller at the requested index.

    If no gamepad can be found at the given index the boolean connected
    is set to false. This can be used to check if a gamepad is no
    longer present. Useful for checking to see if it's been suddenly
    unplugged.

    :param: The controller index to retrieve data for.
    :return: pyasge.GamePad
 )");

  input.def(
    "getGamePad",
    [](ASGE::GLInput& self){
      return self.getGamePad();
    },
    R"(
    Retrieves the first connect gamepad.

    If no gamepad can be found then the boolean connected is set
    to false. This can be used to check if a gamepad is present
    and recognised by the game framework.

    :return: pyasge.GamePad
 )");

  input.def(
    "addCallback",
    &ASGE::Input::addCallbackFnc<std::function<void(const ASGE::SharedEventData)>>,
    R"(
     Registers a callback function.

     Registers a function that gets called upon a subscribed event type.
     Supports both keyboard and mouse functions. Gamepads do not use events
     and must be individually polled.

     Example
     -------
     >>> self.inputs.addCallback(pyasge.EventType.E_KEY,          self.key_handler)
     >>> self.inputs.addCallback(pyasge.EventType.E_MOUSE_CLICK,  self.mouse_click)
     >>> self.inputs.addCallback(pyasge.EventType.E_MOUSE_MOVE,   self.mouse_move)
     >>>
     >>> def input(self, event: pyasge.KeyEvent) -> None:
     >>>   print(f"key press received. {event.key}")
     >>>   print(f"mods received. {event.mods}")
     >>>   if event.mods & pyasge.KEYS.MOD_SHIFT:
     >>>     print("Shift set")
     >>>
     >>> def move_event(self, event: pyasge.MoveEvent) -> None:
     >>>   print(f"x position: {event.x}")
     >>>   print(f"y position: {event.y}")
     >>>
     >>> def click_event(self, event: pyasge.ClickEvent) -> None:
     >>>   print(f"x button: {event.button}")
     >>>   print(f"action: {event.action}")
     >>>   print(f"x position: {event.x} \ny position: {event.y}")
   )");

  input.def(
    "removeCallback", &ASGE::Input::unregisterCallback, py::arg("id"),
    R"(
    Removes a registered callback.

    Will attempt to remove a registered callback function using a given ID. The
    ID is returned from the addCallback function and should be retained to
    allow removal of the event subscription when it's no longer required.

    Warning
    -------
    Failing to remove a registered callback to an object that no longer exists
    will result in undefined behaviour. Always remove the callback when it is
    no longer required.
  )");

  input.def(
    "setCursorMode",
    &ASGE::GLInput::setCursorMode,
    py::arg("cursor_mode"),
    "Sets the cursor mode for the mouse.");

  input.def_property_readonly(
    "gamepads",
    [](ASGE::GLInput &self)
    {
      return self.getGamePads();
    },
    R"(
    Returns all connected gamepad states.

    :getter: Returns the down state of the A button.
    :type: pyasge.GamePads
    )"
  );

  input.def(
    "getCursorPos",
    [](const ASGE::GLInput& self)
    {
      double x = 0;
      double y = 0;
      self.getCursorPos(x, y);
      return ASGE::Point2D{ static_cast<float>(x), static_cast<float>(y) };
    },
    R"(
    Retrieves the mouse cursor position.

    :getter: Returns the down state of the A button.
    :type: pyasge.Point2D
 )");
};
