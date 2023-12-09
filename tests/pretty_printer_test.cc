#include "gtest/gtest.h"
#include <vector>

#include "ast/node_types.h"
#include <ast/pretty_printer.h>
#include <types/literal.h>
#include <types/token.h>

TEST(PrettyPrinterTest, simple_expression_stmt) {
  using namespace wlox::AST;
  using namespace wlox::Types;

  std::vector<StmtPtrVariant> stmtVec;
  stmtVec.push_back({createExprSPV(createBinaryEPV(
      createUnaryEPV(Token(TokenType::MINUS, "-"),
                     createLiteralEPV(makeOptionalLiteral(123.0))),
      Token(TokenType::STAR, "*"),
      createGroupingEPV(createLiteralEPV(makeOptionalLiteral(45.67)))))});

  auto strs = PrettyPrinter::toString(stmtVec);
  EXPECT_EQ(1, strs.size());
  EXPECT_EQ("( (* (- 123) (group 45.67)));", strs[0]);
}
