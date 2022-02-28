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

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

#include <bitset>
#include <pybind11/pybind11.h>

namespace py = pybind11;

void initGamesettings(py::module_&);
void initGametime(py::module_&);
void initCamera(py::module&);
void initColours(py::module&);
void initFont(py::module&);
void initGame(py::module_&);
void initGamepad(py::module&);
void initInput(py::module_&);
void initInputEvents(py::module&);
void initKeyMacros(py::module&);
void initLogger(py::module&);
void initMouseMacros(py::module&);
void initPixelBuffer(py::module&);
void initPoint2D(py::module_&);
void initResolution(py::module&);
void initRenderTarget(py::module&);
void initRenderer(py::module_&);
void initShader(py::module&);
void initSprite(py::module_ &);
void initSpritebounds(py::module&);
void initText(py::module&);
void initTexture2D(py::module&);
void initTile(py::module&);
void initValue(py::module&);
void initViewPort(py::module&);

PYBIND11_MODULE(pyasge, module)
{
  module.doc() = "pybind11 bindings for ASGE";

  initColours(module);
  initGametime(module);
  initGamesettings(module);
  initSpritebounds(module);
  initPoint2D(module);
  initLogger(module);
  initValue(module);
  initInputEvents(module);
  initGamepad(module);
  initKeyMacros(module);
  initMouseMacros(module);
  initTexture2D(module);
  initFont(module);
  initText(module);
  initPixelBuffer(module);
  initRenderTarget(module);
  initViewPort(module);
  initCamera(module);
  initShader(module);
  initSprite(module);
  initInput(module);
  initTile(module);
  initResolution(module);
  initRenderer(module);
  initGame(module);

#ifdef VERSION_INFO
  module.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
  module.attr("__version__") = "dev";
#endif

}
