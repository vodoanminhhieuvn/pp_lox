#pragma once

#include <exception>
#include <string>

#include "error_reporter.h"
#include <types/token.h>

namespace wlox::ErrorsAndDebug {
using Types::Token;

class RunTimeError : std::exception {};

auto reportRuntimeError(ErrorReporter &eReporter, const Token &token,
                        const std::string &message) -> RunTimeError;
} // namespace wlox::ErrorsAndDebug
