#include "pretty_printer.h"

#include <iterator>
#include <utility>
#include <vector>

#include "node_types.h"
#include <types/literal.h>

namespace wlox::AST {

namespace {
auto parenthesize(const std::string &name, const ExprPtrVariant &expr)
    -> std::string {
  return "(" + name + " " + PrettyPrinter::toString(expr) + ")";
}
} // namespace

} // namespace wlox::AST
