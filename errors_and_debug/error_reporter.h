#pragma once

#include <string>
#include <vector>

namespace wlox::ErrorsAndDebug {
enum struct LoxStatus { OK, ERROR };

class ErrorReporter {
public:
  void clearErrors();
  auto getStatus() -> LoxStatus;
  void printToStdErr();
  void setError(int line, const std::string &message);

private:
  std::vector<std::string> errorMessages;
  LoxStatus status = LoxStatus::OK;
};
} // namespace wlox::ErrorsAndDebug
