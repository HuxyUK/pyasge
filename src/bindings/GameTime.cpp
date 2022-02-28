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

#include <Engine/GameTime.hpp>
#include <pybind11/chrono.h>
#include <pybind11/pybind11.h>
namespace py = pybind11;
void initGametime(py::module_ & module) {

  py::class_<ASGE::GameTime>(
    module, "GameTime",
    R"(Stores both frame and game deltas.

       Stores various measurements of delta time for the game. It will store the
       current time point which is used to calculate the delta between frames,
       the delta of the last frame and the entire delta since the game started.
       This can be used to control simulations and render functions to use
       non-fixed time steps.
  )")

    .def(py::init<>())
    .def_readonly("frame_delta", &ASGE::GameTime::frame_delta, "Returns the delta time between rendered frames. Use for ``render`` function.")
    .def_readonly("fixed_delta", &ASGE::GameTime::fixed_delta, "Returns the fixed time-step interval. Use for ``fixedUpdate`` function.")
    .def_readonly("elapsed", &ASGE::GameTime::elapsed, "Total elapsed game time.")
    .def_property_readonly("frame_time", &ASGE::GameTime::deltaInSecs, "The delta time between rendered frames in seconds.")
    .def_property_readonly("fixed_timestep", &ASGE::GameTime::fixedTsInSecs, "The time-step between fixed updates in seconds.");
}
