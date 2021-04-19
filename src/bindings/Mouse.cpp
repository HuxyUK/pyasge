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

#include <Engine/Mouse.hpp>
#include <pybind11/pybind11.h>
namespace py = pybind11;

void initMouseMacros(py::module_ &module)
{
  auto sub = module.def_submodule(
    "MOUSE",
    R"(
    The mouse submodule is a collection of easy to use constants that
    describe the various codes for mouse buttons and the types of actions
    supported. These can be used to create input handlers that are
    easier to read and maintain.

    Example
    ------------
      >>> import pyasge
      >>> def click_event(self, event: pyasge.ClickEvent) -> None:
      >>>   if event.button is pyasge.MOUSE.MOUSE_BTN1:
      >>>     if event.action is pyasge.MOUSE.BUTTON_PRESSED:
      >>>       print("MOUSE BUTTON 1 PRESSED")
      >>>     else:
      >>>       print("MOUSE BUTTON 1 RELEASED")
  )");

  // ACTIONS
  sub.attr("BUTTON_PRESSED")  = ASGE::MOUSE::BUTTON_PRESSED;
  sub.attr("BUTTON_RELEASED") = ASGE::MOUSE::BUTTON_RELEASED;

  // BUTTONS
  sub.attr("MOUSE_BTN1") = ASGE::MOUSE::MOUSE_BTN1;
  sub.attr("MOUSE_BTN2") = ASGE::MOUSE::MOUSE_BTN2;
  sub.attr("MOUSE_BTN3") = ASGE::MOUSE::MOUSE_BTN3;
  sub.attr("MOUSE_BTN4") = ASGE::MOUSE::MOUSE_BTN4;
  sub.attr("MOUSE_BTN5") = ASGE::MOUSE::MOUSE_BTN5;
}
