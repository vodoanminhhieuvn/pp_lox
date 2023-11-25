#include "literal.h"

namespace wlox::Types {

auto getLiteralString(const Literal &value) -> std::string {
  switch (value.index()) {
  case 0:
    return std::get<0>(value);
  case 1: {
    std::string result = std::to_string(std::get<1>(value));
    auto pos = result.find(".000000");
    if (pos != std::string::npos)
      result.erase(pos, std::string::npos);
    else
      result.erase(result.find_last_not_of('0') + 1, std::string::npos);

    return result;
  }
  default:
    static_assert(
        std::variant_size_v<Literal> == 2,
        "Looks like you forgot to update the case in getLiteralString()!");
    return "";
  }
}

auto makeOptionalLiteral(double dVal) -> OptionalLiteral {
  return OptionalLiteral(std::in_place, dVal);
}

auto makeOptionalLiteral(const std::string &lexeme) -> OptionalLiteral {
  return OptionalLiteral(std::in_place, lexeme);
}

} // namespace wlox::Types
