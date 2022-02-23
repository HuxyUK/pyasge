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

#include <Engine/Gamepad.hpp>
#include <pybind11/pybind11.h>
namespace py = pybind11;

void initGamepad(py::module_ &m)
{
  py::class_<ASGE::GamePadData>(
    m, "GamePad",
    R"( Data for connected gamepad.
        Data that represents the current state of a connected game pad.
        Includes the number of axis and buttons along with their current
        state. If a gamepad is not connected then the status of is_connected
        will be false. Do not work with non connected devices as it will
        lead to undefined behaviour. Currently, gamepad support is via
        polling and not events.

        Example
        -------
        >>> if self.inputs.getGamePad().connected:
        >>>
        >>>    '''use gamepad to adjust players velocity'''
        >>>    self.player.velocity.x = self.inputs.getGamePad().AXIS_LEFT_X
        >>>    self.player.velocity.y = self.inputs.getGamePad().AXIS_LEFT_Y
        >>>
        >>>    '''check to see if we should fire a at the enemy'''
        >>>    if self.inputs.getGamePad().A:
        >>>       self.player.fire()
        >>>
        >>>    '''check to see if we should exit the game'''
        >>>    if self.inputs.getGamePad().START:
        >>>       self.signalExit()


        Warning
        -------
        You must ensure the device is connected before attempting to use it as the
        axis and button data will be invalid if it is not and accessing it will
        lead to undefined behaviour or crashing)")

    .def_readonly(
      "name", &ASGE::GamePadData::name,
      R"( Whether or not the gamepad is currently connected. It's possible that
        a gamepad device may get disconnected during use, this can be used to
        ensure it's still connected.

        :getter: Returns True if connected
        :type: bool

        Example
        -------
        >>> if self.inputs.getGamePad().connected:
        >>>   print("Gamepad at idx is connected) )")


    .def_readonly(
      "connected", &ASGE::GamePadData::is_connected,
      R"( Whether or not the gamepad is currently connected. It's possible that
          a gamepad device may get disconnected during use, this can be used to
          ensure it's connected.

          :getter: Returns True if connected
          :type: bool

          Example
          -------
          >>> if self.inputs.getGamePad().connected:
          >>>   print("Gamepad at idx is connected) )")

    .def_property_readonly(
      "AXIS_LEFT_X",
      [](const ASGE::GamePadData& data) { return data.axis[ASGE::GAMEPAD::AXIS_LEFT_X]; },
      R"(
          The reading of the x-axis on the left stick.

          :getter: Returns the the x-axis value between [-1,1]
          :type: float

          Example
          -------
          >>> if self.inputs.getGamePad(0).connected:
          >>>   print(f"axis reads: {self.inputs.getGamePad(0).AXIS_LEFT_X}") )")

    .def_property_readonly(
      "AXIS_LEFT_Y",
      [](const ASGE::GamePadData& data) { return data.axis[ASGE::GAMEPAD::AXIS_LEFT_Y]; },
      R"(
          The reading of the y-axis on the left stick.

          :getter: Returns the the x-axis value between [-1,1]
          :type: float

          Example
          -------
          >>> if self.inputs.getGamePad(0).connected:
          >>>   print(f"axis reads: {self.inputs.getGamePad(0).AXIS_LEFT_Y}") )")

    .def_property_readonly(
      "AXIS_RIGHT_X",
      [](const ASGE::GamePadData& data) { return data.axis[ASGE::GAMEPAD::AXIS_RIGHT_X]; },
      R"(
          The reading of the x-axis on the right stick.

          :getter: Returns the the x-axis value between [-1,1]
          :type: float

          Example
          -------
          >>> if self.inputs.getGamePad(0).connected:
          >>>   print(f"axis reads: {self.inputs.getGamePad(0).AXIS_RIGHT_X}") )")

    .def_property_readonly(
      "AXIS_RIGHT_Y",
      [](const ASGE::GamePadData& data) { return data.axis[ASGE::GAMEPAD::AXIS_RIGHT_Y]; },
      R"(
          The reading of the y-axis on the right stick.

          :getter: Returns the the y-axis value between [-1,1]
          :type: float

          Example
          -------
          >>> if self.inputs.getGamePad(0).connected:
          >>>   print(f"axis reads: {self.inputs.getGamePad(0).AXIS_RIGHT_Y}") )")

    .def_property_readonly(
      "RIGHT_TRIGGER",
      [](const ASGE::GamePadData& data) { return data.axis[ASGE::GAMEPAD::AXIS_RIGHT_TRIGGER]; },
      R"(
          The reading of the axis on the right trigger.

          :getter: Returns the the axis value between [-1,1]
          :type: float )")

    .def_property_readonly(
      "LEFT_TRIGGER",
      [](const ASGE::GamePadData& data) { return data.axis[ASGE::GAMEPAD::AXIS_LEFT_TRIGGER]; },
      R"(
          The reading of the axis on the left trigger.

          :getter: Returns the the axis value between [-1,1]
          :type: float )")

    .def_property_readonly(
      "A", [](const ASGE::GamePadData& data){ return data.buttons[ASGE::GAMEPAD::BUTTON_A] == 1; },
      R"( The A button state.

          :getter: Returns the down state of the A button.
          :type: bool )")

    .def_property_readonly(
      "B", [](const ASGE::GamePadData& data){ return data.buttons[ASGE::GAMEPAD::BUTTON_B] == 1; },
      R"( The B button state.

          :getter: Returns the down state of the B button.
          :type: bool )")

    .def_property_readonly(
      "X", [](const ASGE::GamePadData& data){ return data.buttons[ASGE::GAMEPAD::BUTTON_X] == 1; },
      R"( The X button state.

          :getter: Returns the down state of the X button.
          :type: bool )")

    .def_property_readonly(
      "Y", [](const ASGE::GamePadData& data){ return data.buttons[ASGE::GAMEPAD::BUTTON_Y] == 1; },
      R"( The Y button state.

          :getter: Returns the down state of the Y button.
          :type: bool )")

    .def_property_readonly(
      "CROSS", [](const ASGE::GamePadData& data){ return data.buttons[ASGE::GAMEPAD::BUTTON_CROSS] == 1; },
      R"( The CROSS button state.

          :getter: Returns the down state of the CROSS button.
          :type: bool )")

    .def_property_readonly(
      "CIRCLE", [](const ASGE::GamePadData& data){ return data.buttons[ASGE::GAMEPAD::BUTTON_CIRCLE] == 1; },
      R"( The CIRCLE button state.

          :getter: Returns the down state of the CIRCLE button.
          :type: bool )")

    .def_property_readonly(
      "SQUARE", [](const ASGE::GamePadData& data){ return data.buttons[ASGE::GAMEPAD::BUTTON_SQUARE] == 1; },
      R"( The SQUARE button state.

          :getter: Returns the down state of the SQUARE button.
          :type: bool )")

    .def_property_readonly(
      "TRIANGLE", [](const ASGE::GamePadData& data){ return data.buttons[ASGE::GAMEPAD::BUTTON_TRIANGLE] == 1; },
      R"( The TRIANGLE button state.

          :getter: Returns the down state of the TRIANGLE button.
          :type: bool )")

    .def_property_readonly(
      "LEFT_BUMPER", [](const ASGE::GamePadData& data){ return data.buttons[ASGE::GAMEPAD::BUTTON_LEFT_BUMPER] == 1; },
      R"( The LEFT_BUMPER button state.

          :getter: Returns the down state of the LEFT_BUMPER button.
          :type: bool )")

    .def_property_readonly(
      "RIGHT_BUMPER", [](const ASGE::GamePadData& data){ return data.buttons[ASGE::GAMEPAD::BUTTON_RIGHT_BUMPER] == 1; },
      R"( The RIGHT_BUMPER button state.

          :getter: Returns the down state of the RIGHT_BUMPER button.
          :type: bool )")

    .def_property_readonly(
      "LEFT_THUMB", [](const ASGE::GamePadData& data){ return data.buttons[ASGE::GAMEPAD::BUTTON_LEFT_THUMB] == 1; },
      R"( The LEFT_THUMB button state.

          :getter: Returns the down state of the LEFT_THUMB button.
          :type: bool )")

    .def_property_readonly(
      "RIGHT_THUMB", [](const ASGE::GamePadData& data){ return data.buttons[ASGE::GAMEPAD::BUTTON_RIGHT_THUMB] == 1; },
      R"( The RIGHT THUMB button state.

          :getter: Returns the down state of the RIGHT THUMB button.
          :type: bool )")

    .def_property_readonly(
      "BACK", [](const ASGE::GamePadData& data){ return data.buttons[ASGE::GAMEPAD::BUTTON_BACK] == 1; },
      R"( The BACK button state.

          :getter: Returns the down state of the BACK button.
          :type: bool )")

    .def_property_readonly(
      "START", [](const ASGE::GamePadData& data){ return data.buttons[ASGE::GAMEPAD::BUTTON_START] == 1; },
      R"( The START button state.

          :getter: Returns the down state of the START button.
          :type: bool )")

    .def_property_readonly(
      "GUIDE", [](const ASGE::GamePadData& data){ return data.buttons[ASGE::GAMEPAD::BUTTON_GUIDE] == 1; },
      R"( The GUIDE button state.

          :getter: Returns the down state of the GUIDE button.
          :type: bool )")

    .def_property_readonly(
      "DPAD_UP", [](const ASGE::GamePadData& data){ return data.buttons[ASGE::GAMEPAD::BUTTON_DPAD_UP] == 1; },
      R"( The DPAD_UP button state.

          :getter: Returns the down state of the DPAD_UP button.
          :type: bool )")

    .def_property_readonly(
      "DPAD_DOWN", [](const ASGE::GamePadData& data){ return data.buttons[ASGE::GAMEPAD::BUTTON_DPAD_DOWN] == 1; },
      R"( The DPAD_DOWN button state.

          :getter: Returns the down state of the DPAD_DOWN button.
          :type: bool )")

    .def_property_readonly(
      "DPAD_RIGHT", [](const ASGE::GamePadData& data){ return data.buttons[ASGE::GAMEPAD::BUTTON_DPAD_RIGHT] == 1; },
      R"( The DPAD_RIGHT button state.

          :getter: Returns the down state of the DPAD_RIGHT button.
          :type: bool )")

    .def_property_readonly(
      "DPAD_LEFT", [](const ASGE::GamePadData& data){ return data.buttons[ASGE::GAMEPAD::BUTTON_DPAD_LEFT] == 1; },
      R"( The DPAD_LEFT button state.

          :getter: Returns the down state of the DPAD_LEFT button.
          :type: bool )")


    .def_readonly(
      "index", &ASGE::GamePadData::idx,
      R"( Each controller attached to the system has an index. This property can retrieve it.

          :getter: Returns the connected index for the GamePad.
          :type: int

          Example
          -------
          >>> print(f"index of controller reads: {self.inputs.getGamePad().index}") )");
}
