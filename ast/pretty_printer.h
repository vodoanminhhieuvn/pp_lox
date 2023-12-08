#pragma once

#include <string>
#include <vector>

#include "node_types.h"

namespace wlox::AST::PrettyPrinter {
[[nodiscard]] auto toString(const std::vector<AST::StmtPtrVariant> &statements)
    -> std::vector<std::string>;
[[nodiscard]] auto toString(const ExprPtrVariant &expression) -> std::string;
[[nodiscard]] auto toString(const StmtPtrVariant &statement)
    -> std::vector<std::string>;

} // namespace wlox::AST::PrettyPrinter
