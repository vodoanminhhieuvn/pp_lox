#include <gtest/gtest.h>

#include <ast/node_types.h>

TEST(LiteralExprPrintTest, emptyscript) {
  wlox::Types::Literal literal = {"Testing LiteralExpr Printing"};
  wlox::AST::LiteralExpr literalExpr(literal);
  EXPECT_EQ("Testing LiteralExpr Printing",
            wlox::Types::getLiteralString(literalExpr.literalVal.value()));
}
