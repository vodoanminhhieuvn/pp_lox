#pragma once
#include <exception>
#include <vector>

#include <ast/node_types.h>
#include <errors_and_debug/error_reporter.h>
#include <types/token.h>

namespace wlox::Parser {
using AST::ExprPtrVariant;
using AST::StmtPtrVariant;

class RDParser {
public:
  explicit RDParser(const std::vector<Types::Token> &tokens,
                    ErrorsAndDebug::ErrorReporter &eReporter);

  class RDParseError : std::exception {};

  auto parse() -> std::vector<StmtPtrVariant>;

private:
  void program();
  auto declaration() -> std::optional<StmtPtrVariant>;
  auto varDecl() -> StmtPtrVariant;
  auto classDecl() -> StmtPtrVariant;
  auto funcDecl(const std::string &kind) -> StmtPtrVariant;
  auto funcBody(const std::string &kind) -> ExprPtrVariant;
  auto parameters() -> std::vector<Types::Token>;
  auto statement() -> StmtPtrVariant;
  auto exprStmt() -> StmtPtrVariant;
  auto printStmt() -> StmtPtrVariant;
  auto blockStmt() -> StmtPtrVariant;
  auto ifStmt() -> StmtPtrVariant;
  auto whileStmt() -> StmtPtrVariant;
  auto forStmt() -> StmtPtrVariant;
  auto returnStmt() -> StmtPtrVariant;

  // Expression Parsing
  auto expression() -> ExprPtrVariant;
  auto comma() -> ExprPtrVariant;
  auto assignment() -> ExprPtrVariant;
  auto conditional() -> ExprPtrVariant;
  auto logical_or() -> ExprPtrVariant;
  auto logical_and() -> ExprPtrVariant;
  auto equality() -> ExprPtrVariant;
  auto comparison() -> ExprPtrVariant;
  auto addition() -> ExprPtrVariant;
  auto multiplication() -> ExprPtrVariant;
  auto unary() -> ExprPtrVariant;
  auto postfix() -> ExprPtrVariant;
  auto call() -> ExprPtrVariant;
  auto arguments() -> std::vector<ExprPtrVariant>;
  auto primary() -> ExprPtrVariant;

  // Helper functions to implement the parser
  void advance();
  void consumeOrError(Types::TokenType tType, const std::string &errorMessage);
  using parserFn = ExprPtrVariant (RDParser::*)();
  auto
  consumeAnyBinaryExprs(const std::initializer_list<Types::TokenType> &types,
                        ExprPtrVariant expr, const parserFn &f)
      -> ExprPtrVariant;
  auto consumeOneLiteral() -> ExprPtrVariant;
  auto consumeOneLiteral(const std::string &str) -> ExprPtrVariant;
  auto consumeGroupingExpr() -> ExprPtrVariant;
  auto consumePostfixExpr(ExprPtrVariant expr) -> ExprPtrVariant;
  void consumeSemicolonOrError();
  auto consumeSuper() -> ExprPtrVariant;
  auto consumeUnaryExpr() -> ExprPtrVariant;
  auto consumeVarExpr() -> ExprPtrVariant;
  auto error(const std::string &eMessage) -> RDParseError;
  [[nodiscard]] auto getCurrentTokenType() const -> Types::TokenType;
  auto getTokenAndAdvance() -> Types::Token;
  [[nodiscard]] auto isAtEnd() const -> bool;
  [[nodiscard]] auto
  match(const std::initializer_list<Types::TokenType> &types) const -> bool;
  [[nodiscard]] auto match(Types::TokenType type) const -> bool;
  [[nodiscard]] auto matchNext(Types::TokenType type) -> bool;
  [[nodiscard]] auto peek() const -> Types::Token;
  void reportError(const std::string &message);
  void synchronize();
  void
  throwOnErrorProduction(const std::initializer_list<Types::TokenType> &types,
                         const parserFn &f);
  void throwOnErrorProductions();

  // The data the parser operates on.
  const std::vector<Types::Token> &tokens;
  std::vector<wlox::Types::Token>::const_iterator currentIter;
  // std::__wrap_iter<std::vector<cpplox::Types::Token>::const_pointer>
  // currentIter;
  ErrorsAndDebug::ErrorReporter &eReporter;
  std::vector<StmtPtrVariant> statements;

  static const int MAX_ARGS = 255;
};
} // namespace wlox::Parser
