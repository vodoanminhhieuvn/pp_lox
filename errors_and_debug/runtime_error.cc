#include "runtime_error.h"
#include "errors_and_debug/error_reporter.h"

namespace wlox::ErrorsAndDebug {
auto reportRuntimeError(ErrorReporter &eReporter, const Token &token,
                        const std::string &message) -> RunTimeError {
  eReporter.setError(token.getLine(), token.getLexeme() + ": " + message);
  return RunTimeError();
}
} // namespace wlox::ErrorsAndDebug
