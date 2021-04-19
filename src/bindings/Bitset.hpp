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

#include <bitset>
#include <pybind11/pybind11.h>

namespace pybind11 { namespace detail {
    template <unsigned long Size> struct type_caster<std::bitset<Size>> {
    public:
    /**
     * This macro establishes the name 'bitset' in
     * function signatures and declares a local variable
     * 'value' of type std::bitset<Size>
     */
    PYBIND11_TYPE_CASTER(std::bitset<Size>, _("bitset"));

    /**
     * Conversion part 1 (Python->C++): convert a PyObject into a
     * bitset instance or return false upon failure. The second argument
     * indicates whether implicit conversions should be applied.
     */
    bool load(handle src, bool /*implicit*/ )
    {
      PyObject* source = src.ptr();
      PyObject* tmp    = PyNumber_Long(source);
      if (tmp == nullptr)
      {
        return false;
      }

      auto as_ulong = PyLong_AsUnsignedLong(tmp);
      value         = as_ulong;
      Py_DECREF(tmp);

      /* Ensure return code was OK (to avoid out-of-range errors etc) */
      return PyErr_Occurred() == nullptr;
    }

    /**
     * Conversion part 2 (C++ -> Python): convert an std::bitset instance into
     * a Python object. The second and third arguments are used to
     * indicate the return value policy and parent object (for
     * ``return_value_policy::reference_internal``) and are generally
     * ignored by implicit casters.
     */
    static handle cast(std::bitset<Size> src, return_value_policy /* policy */, handle /* parent */)
    {
      return PyLong_FromLong(src.to_ulong());
    }
  };
}} // namespace pybind11::detail
