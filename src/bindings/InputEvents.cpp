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

#include "Bitset.hpp"
#include <Engine/InputEvents.hpp>
#include <pybind11/pybind11.h>
namespace py = pybind11;

void initInputEvents(py::module_ &module) {
  py::class_<ASGE::EventData>(module, "EventData");

  py::enum_<ASGE::EventType>(module, "EventType",
       R"(Input Event.

       Input events are signalled when specific inputs are detected. These
       include key presses, mouse button clicks, mouse movements and mouse
       scrolling. When the framework receives one of these events, it forwards
       the data packaged in one of these EventType classes. They contain all
       the relevant information about the event itself. )")

      .value("E_KEY", ASGE::EventType::E_KEY,
             "A key has been pressed or released.")
      .value("E_MOUSE_CLICK", ASGE::EventType::E_MOUSE_CLICK,
             "A mouse click event.")
      .value("E_MOUSE_SCROLL", ASGE::EventType::E_MOUSE_SCROLL,
             "A mouse scrolling event.")
      .value("E_MOUSE_MOVE", ASGE::EventType::E_MOUSE_MOVE,
             "The mouse has been moved..");

  py::class_<ASGE::KeyEvent, std::shared_ptr<ASGE::KeyEvent>>(
      module, "KeyEvent",
      R"(A key event provides any related information that can be used to drive
       a game. Along with the key that's involved in the action, the event
       provides details of whether it was pressed or released. This can help
       create logic based on both key releases and key presses.

       Example
       -------
       >>> import pyasge
       >>> def key_handler(event: pyasge.KeyEvent) -> None:
       >>>   if event.key is pyasge.KEYS.KEY_ENTER:
       >>>     if event.action is pyasge.KEYS.KEY_PRESSED:
       >>>       print("enter key press received.")
       >>>   if event.mods & pyasge.KEYS.MOD_SHIFT:
       >>>     print("shift key held") )")

      .def(py::init<>())
      .def_readonly("key", &ASGE::KeyEvent::key,
                    "The key involved in the event.")
      .def_readonly("scancode", &ASGE::KeyEvent::scancode,
                    "The unique scancode used to to represent the character.")
      .def_readonly("action", &ASGE::KeyEvent::action,
                    "Whether the key was pressed or released.")
      .def_readonly("mods", &ASGE::KeyEvent::mods,
                    " Any modifiers applied i.e. ctrl, shift etc.");

  py::class_<ASGE::ClickEvent, std::shared_ptr<ASGE::ClickEvent>>(
      module, "ClickEvent",
      R"(A click event provides any related information that can be used to drive
       a game through mouse clicks. The event details whether the mouse button
       was pressed or released, the button involved and also its x and y
       position on the screen. This positional data can be translated back to
       world space and used to establish where the user was clicking.

       Example
       -------
       >>> import pyasge
       >>> def click_event(self, event: pyasge.ClickEvent) -> None:
       >>> print(f"button: {event.button}")
       >>> print(f"action: {event.action}")
       >>> print(f"x position: {event.x} \ny position: {event.y}") )")

      .def(py::init<>())
      .def_readonly(
          "button", &ASGE::ClickEvent::button,
          "Mouse button. The mouse button clicked. pyasge.Input.BUTTON_PRESSED")
      .def_readonly("action", &ASGE::ClickEvent::action,
                    "Button action. Has it been pressed or released?")
      .def_readonly("x", &ASGE::ClickEvent::xpos,
                    "X. The current mouse position on the X axis.")
      .def_readonly("y", &ASGE::ClickEvent::ypos,
                    "Y. The current mouse position on the Y axis.")
      .def_readonly("mods", &ASGE::ClickEvent::mods,
                    "Modifiers. Any modifiers applied i.e. ctrl, shift etc.");

  py::class_<ASGE::ScrollEvent, std::shared_ptr<ASGE::ScrollEvent>>(
      module, "ScrollEvent",
      R"(A scroll event is generated when the mouse scroll wheel is moved. The
       data provided with this event is actually the delta in motion. This
       can be used to determine how far the wheel has been moved.

       Example
       -------
       >>> import pyasge
       >>> def scroll_event(self, event: pyasge.ScrollEvent) -> None:
       >>> print(f"x delta: {event.x_delta} \ny delta: {event.y_delta}") )")

      .def(py::init<>())
      .def_readonly(
          "x_delta", &ASGE::ScrollEvent::xoffset,
          "Delta X. The amount of change incurred by the scrolling action.")
      .def_readonly(
          "y_delta", &ASGE::ScrollEvent::yoffset,
          "Delta Y. The amount of change incurred by the scrolling action.");

  py::class_<ASGE::MoveEvent, std::shared_ptr<ASGE::MoveEvent>>(
      module, "MoveEvent",
      R"(A mouse movement event provides any related information that can be used
       to drive a game. This simply reports the x and y position of the mouse
       when the movement was detected.

       Example
       -------
       >>> import pyasge
       >>> def scroll_event(self, event: pyasge.ScrollEvent) -> None:
       >>> print(f"xpos: {event.x} \nypos: {event.y}") )")

      .def(py::init<>())
      .def_readonly("x", &ASGE::MoveEvent::xpos,
                    "X. The current mouse position on the X axis.")
      .def_readonly("y", &ASGE::MoveEvent::ypos,
                    "Y. The current mouse position on the Y axis.");
}
