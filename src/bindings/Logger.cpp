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

#include <Engine/Logger.hpp>
#include <pybind11/pybind11.h>
namespace py = pybind11;

/// \brief   A logger that doesn't discriminate between log levels
/// \details The standard ASGE logger uses DEBUG/RELEASE builds to determine
///          which log levels should be logged. This replacement drop-in uses
///          a custom log function instead that doesn't perform a log level
///          check, thus allowing all log levels to work.

class PYASGELogger : public Logging::LoggerBase
{
public:
    PYASGELogger() = delete;

    explicit PYASGELogger(const Logging::LoggingConfig_t& config) :
            LoggerBase(config), levels(config.find("color") != config.end() ? colored : uncolored)
    {

    }

    void log(const std::string &message, Logging::LogLevel level) override
    {
      std::string output;
      output.reserve(message.length() + 64);
      output.append(Logging::timestamp());
      output.append(levels.find(level)->second);
      output.append(message);
      output.push_back('\n');
      log(output);
    }

    void log(const std::string &message) override
    {
      std::cout << message;
      std::cout.flush();
    }

protected:
    const std::unordered_map<Logging::LogLevel, std::string, Logging::EnumHasher> levels; //NOLINT
};

void initLogger(py::module_ &logger) {

  const Logging::LoggingConfig_t& config = { { "type", "pyasge" }, { "color", "" } };

  [[maybe_unused]] const bool pyasge_logger_registered =
          Logging::RegisterLogger("pyasge", [](const Logging::LoggingConfig_t &config) {
              Logging::LoggerBase *logger = new PYASGELogger(config); //NOLINT
              return logger;
          });

  logger.def("INFO", [config](const std::string& msg) { Logging::getLogger(config).log(msg, Logging::LogLevel::INFO); });
  logger.def("ERROR",[config](const std::string& msg) { Logging::getLogger(config).log(msg, Logging::LogLevel::ERRORS); });
  logger.def("WARN", [config](const std::string& msg) { Logging::getLogger(config).log(msg, Logging::LogLevel::WARN); });
  logger.def("DEBUG",[config](const std::string& msg) { Logging::getLogger(config).log(msg, Logging::LogLevel::DEBUG); });
  logger.def("TRACE",[config](const std::string& msg) { Logging::getLogger(config).log(msg, Logging::LogLevel::TRACE); });
  logger.def("LOG",  [config](const std::string& msg) { Logging::getLogger(config).log(Logging::timestamp() + " [LOG] " + msg + "\n"); });
}
