#include "error_reporter.h"
#include <iostream>

namespace wlox::ErrorsAndDebug {
void ErrorReporter::clearErrors() {
  errorMessages.clear();
  status = LoxStatus::OK;
}

auto ErrorReporter::getStatus() -> LoxStatus { return status; }

void ErrorReporter::printToStdErr() {
  for (auto &s : errorMessages) {
    std::cerr << s << "\n";
  }
}

void ErrorReporter::setError(int line, const std::string &message) {
  errorMessages.emplace_back("[Line " + std::to_string(line) +
                             "] Error: " + message);
  status = LoxStatus::ERROR;
}

} // namespace wlox::ErrorsAndDebug
