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

#include <Engine/Keys.hpp>
#include <pybind11/pybind11.h>
namespace py = pybind11;

void initKeyMacros(py::module_ &module) {

  constexpr auto MOD_SHIFT = 0x0001;
  constexpr auto MOD_CONTROL = 0x0002;
  constexpr auto MOD_ALT = 0x0004;
  constexpr auto MOD_SUPER = 0x0008;
  constexpr auto MOD_CAPS_LOCK = 0x0010;
  constexpr auto MOD_NUM_LOCK = 0x0020;

  auto sub = module.def_submodule(
    "KEYS",
    R"(
    The keys submodule is a collection of easy to use constants that
    describe the various codes for keys and the types of actions
    supported. These can be used to create key handlers that are
    easier to read and maintain. Key modifiers are stored in a
    bitfield and require bitmask operations to check if a flag is
    set. The examples below show how these constants can be used.

    Example
    ------------
    >>> import pyasge
    >>> def key_handler(event: pyasge.KeyEvent) -> None:
    >>>   if event.key is pyasge.KEYS.KEY_ENTER:
    >>>     if event.action is pyasge.KEYS.KEY_PRESSED:
    >>>       print("enter key press received.")
    >>>   if event.mods & pyasge.KEYS.MOD_SHIFT:
    >>>     print("shift key held")

    Example
    ------------
    >>> import pyasge
    >>> def key_handler(event: pyasge.KeyEvent) -> None:
    >>>   if event.key is pyasge.KEYS.KEY_W:
    >>>     if event.action is pyasge.KEYS.KEY_PRESSED:
    >>>       self.player.velocity.y = -1
    >>>     elif event.action is pyasge.KEYS.KEY_RELEASED:
    >>>       self.player.velocity.y = 0 )");

  // ACTIONS
  sub.attr("KEY_RELEASED") = &ASGE::KEYS::KEY_RELEASED;
  sub.attr("KEY_PRESSED") = &ASGE::KEYS::KEY_PRESSED;
  sub.attr("KEY_REPEATED") = &ASGE::KEYS::KEY_REPEATED;

  // MODIFIERS
  sub.attr("MOD_SHIFT") = &MOD_SHIFT;
  sub.attr("MOD_CONTROL") = &MOD_CONTROL;
  sub.attr("MOD_ALT") = &MOD_ALT;
  sub.attr("MOD_SUPER") = &MOD_SUPER;
  sub.attr("MOD_CAPS_LOCK") = &MOD_CAPS_LOCK;
  sub.attr("MOD_NUM_LOCK") = &MOD_NUM_LOCK;

  // KEYS
  sub.attr("KEY_SPACE") = &ASGE::KEYS::KEY_SPACE;
  sub.attr("KEY_APOSTROPHE") = &ASGE::KEYS::KEY_APOSTROPHE;
  sub.attr("KEY_COMMA") = &ASGE::KEYS::KEY_COMMA;
  sub.attr("KEY_MINUS") = &ASGE::KEYS::KEY_MINUS;
  sub.attr("KEY_PERIOD") = &ASGE::KEYS::KEY_PERIOD;
  sub.attr("KEY_SLASH") = &ASGE::KEYS::KEY_SLASH;
  sub.attr("KEY_SEMICOLON") = &ASGE::KEYS::KEY_SEMICOLON;
  sub.attr("KEY_EQUAL") = &ASGE::KEYS::KEY_EQUAL;
  sub.attr("KEY_0") = &ASGE::KEYS::KEY_0;
  sub.attr("KEY_1") = &ASGE::KEYS::KEY_1;
  sub.attr("KEY_2") = &ASGE::KEYS::KEY_2;
  sub.attr("KEY_3") = &ASGE::KEYS::KEY_3;
  sub.attr("KEY_4") = &ASGE::KEYS::KEY_4;
  sub.attr("KEY_5") = &ASGE::KEYS::KEY_5;
  sub.attr("KEY_6") = &ASGE::KEYS::KEY_6;
  sub.attr("KEY_7") = &ASGE::KEYS::KEY_7;
  sub.attr("KEY_8") = &ASGE::KEYS::KEY_8;
  sub.attr("KEY_9") = &ASGE::KEYS::KEY_9;
  sub.attr("KEY_A") = &ASGE::KEYS::KEY_A;
  sub.attr("KEY_B") = &ASGE::KEYS::KEY_B;
  sub.attr("KEY_C") = &ASGE::KEYS::KEY_C;
  sub.attr("KEY_D") = &ASGE::KEYS::KEY_D;
  sub.attr("KEY_E") = &ASGE::KEYS::KEY_E;
  sub.attr("KEY_F") = &ASGE::KEYS::KEY_F;
  sub.attr("KEY_G") = &ASGE::KEYS::KEY_G;
  sub.attr("KEY_H") = &ASGE::KEYS::KEY_H;
  sub.attr("KEY_I") = &ASGE::KEYS::KEY_I;
  sub.attr("KEY_J") = &ASGE::KEYS::KEY_J;
  sub.attr("KEY_K") = &ASGE::KEYS::KEY_K;
  sub.attr("KEY_L") = &ASGE::KEYS::KEY_L;
  sub.attr("KEY_M") = &ASGE::KEYS::KEY_M;
  sub.attr("KEY_N") = &ASGE::KEYS::KEY_N;
  sub.attr("KEY_O") = &ASGE::KEYS::KEY_O;
  sub.attr("KEY_P") = &ASGE::KEYS::KEY_P;
  sub.attr("KEY_Q") = &ASGE::KEYS::KEY_Q;
  sub.attr("KEY_R") = &ASGE::KEYS::KEY_R;
  sub.attr("KEY_S") = &ASGE::KEYS::KEY_S;
  sub.attr("KEY_T") = &ASGE::KEYS::KEY_T;
  sub.attr("KEY_U") = &ASGE::KEYS::KEY_U;
  sub.attr("KEY_V") = &ASGE::KEYS::KEY_V;
  sub.attr("KEY_W") = &ASGE::KEYS::KEY_W;
  sub.attr("KEY_X") = &ASGE::KEYS::KEY_X;
  sub.attr("KEY_Y") = &ASGE::KEYS::KEY_Y;
  sub.attr("KEY_Z") = &ASGE::KEYS::KEY_Z;
  sub.attr("KEY_LEFT_BRACKET") = &ASGE::KEYS::KEY_LEFT_BRACKET;
  sub.attr("KEY_BACKSLASH") = &ASGE::KEYS::KEY_BACKSLASH;
  sub.attr("KEY_RIGHT_BRACKET") = &ASGE::KEYS::KEY_RIGHT_BRACKET;
  sub.attr("KEY_GRAVE_ACCENT") = &ASGE::KEYS::KEY_GRAVE_ACCENT;
  sub.attr("KEY_WORLD_1") = &ASGE::KEYS::KEY_WORLD_1;
  sub.attr("KEY_WORLD_2") = &ASGE::KEYS::KEY_WORLD_2;
  sub.attr("KEY_ESCAPE") = &ASGE::KEYS::KEY_ESCAPE;
  sub.attr("KEY_ENTER") = &ASGE::KEYS::KEY_ENTER;
  sub.attr("KEY_TAB") = &ASGE::KEYS::KEY_TAB;
  sub.attr("KEY_BACKSPACE") = &ASGE::KEYS::KEY_BACKSPACE;
  sub.attr("KEY_DELETE") = &ASGE::KEYS::KEY_DELETE;
  sub.attr("KEY_UP") = &ASGE::KEYS::KEY_UP;
  sub.attr("KEY_DOWN") = &ASGE::KEYS::KEY_DOWN;
  sub.attr("KEY_LEFT") = &ASGE::KEYS::KEY_LEFT;
  sub.attr("KEY_RIGHT") = &ASGE::KEYS::KEY_RIGHT;
  sub.attr("KEY_MAX") = &ASGE::KEYS::KEY_UP;
}
