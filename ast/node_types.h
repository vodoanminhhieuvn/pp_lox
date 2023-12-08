#pragma once

#include <memory>
#include <optional>
#include <variant>
#include <vector>

#include <types/literal.h>
#include <types/token.h>
#include <types/uncopyable.h>

namespace wlox::AST {
using Types::Literal;
using Types::OptionalLiteral;
using Types::Token;
using Types::TokenType;
using Types::Uncopyable;

struct BinaryExpr;
struct GroupingExpr;
struct LiteralExpr;
struct UnaryExpr;
struct ConditionalExpr;
struct PostfixExpr;
struct VariableExpr;
struct AssignmentExpr;
struct LogicalExpr;
struct CallExpr;
struct FuncExpr;
struct GetExpr;
struct SetExpr;
struct ThisExpr;
struct SuperExpr;

using BinaryExprPtr = std::unique_ptr<BinaryExpr>;
using GroupingExprPtr = std::unique_ptr<GroupingExpr>;
using LiteralExprPtr = std::unique_ptr<LiteralExpr>;
using UnaryExprPtr = std::unique_ptr<UnaryExpr>;
using ConditionalExprPtr = std::unique_ptr<ConditionalExpr>;
using PostfixExprPtr = std::unique_ptr<PostfixExpr>;
using VariableExprPtr = std::unique_ptr<VariableExpr>;
using AssignmentExprPtr = std::unique_ptr<AssignmentExpr>;
using LogicalExprPtr = std::unique_ptr<LogicalExpr>;
using CallExprPtr = std::unique_ptr<CallExpr>;
using FuncExprPtr = std::unique_ptr<FuncExpr>;
using GetExprPtr = std::unique_ptr<GetExpr>;
using SetExprPtr = std::unique_ptr<SetExpr>;
using ThisExprPtr = std::unique_ptr<ThisExpr>;
using SuperExprPtr = std::unique_ptr<SuperExpr>;

using ExprPtrVariant =
    std::variant<BinaryExprPtr, GroupingExprPtr, LiteralExprPtr, UnaryExprPtr,
                 ConditionalExprPtr, PostfixExprPtr, VariableExprPtr,
                 AssignmentExprPtr, LogicalExprPtr, CallExprPtr, FuncExprPtr,
                 GetExprPtr, SetExprPtr, ThisExprPtr, SuperExprPtr>;

struct ExprStmt;
struct PrintStmt;
struct BlockStmt;
struct VarStmt;
struct IfStmt;
struct WhileStmt;
struct ForStmt;
struct FuncStmt;
struct RetStmt;
struct ClassStmt;

using ExprStmtPtr = std::unique_ptr<ExprStmt>;
using PrintStmtPtr = std::unique_ptr<PrintStmt>;
using BlockStmtPtr = std::unique_ptr<BlockStmt>;
using VarStmtPtr = std::unique_ptr<VarStmt>;
using IfStmtPtr = std::unique_ptr<IfStmt>;
using WhileStmtPtr = std::unique_ptr<WhileStmt>;
using ForStmtPtr = std::unique_ptr<ForStmt>;
using FuncStmtPtr = std::unique_ptr<FuncStmt>;
using RetStmtPtr = std::unique_ptr<RetStmt>;
using ClassStmtPtr = std::unique_ptr<ClassStmt>;

using StmtPtrVariant =
    std::variant<ExprStmtPtr, PrintStmtPtr, BlockStmtPtr, VarStmtPtr, IfStmtPtr,
                 WhileStmtPtr, ForStmtPtr, FuncStmtPtr, RetStmtPtr,
                 ClassStmtPtr>;

auto createBinaryEPV(ExprPtrVariant left, Token op, ExprPtrVariant right)
    -> ExprPtrVariant;
auto createUnaryEPV(Token op, ExprPtrVariant right) -> ExprPtrVariant;
auto createGroupingEPV(ExprPtrVariant right) -> ExprPtrVariant;
auto createLiteralEPV(OptionalLiteral literal) -> ExprPtrVariant;
auto createConditionalEPV(ExprPtrVariant condition, ExprPtrVariant then,
                          ExprPtrVariant elseBranch) -> ExprPtrVariant;
auto createPostfixEPV(ExprPtrVariant left, Token op) -> ExprPtrVariant;
auto createVariableEPV(Token varName) -> ExprPtrVariant;
auto createAssignmentEPV(Token varName, ExprPtrVariant expr) -> ExprPtrVariant;
auto createLogicalEPV(ExprPtrVariant left, Token op, ExprPtrVariant right)
    -> ExprPtrVariant;
auto createCallEPV(ExprPtrVariant callee, Token paren,
                   std::vector<StmtPtrVariant> fnBody) -> ExprPtrVariant;
auto createFuncEPV(std::vector<Token> params,
                   std::vector<StmtPtrVariant> fnBody) -> ExprPtrVariant;
auto createGetEPV(ExprPtrVariant expr, Token name) -> ExprPtrVariant;
auto createSetEPV(ExprPtrVariant expr, Token name, ExprPtrVariant value)
    -> ExprPtrVariant;
auto createThisEPV(Token keyword) -> ExprPtrVariant;
auto createSuperEPV(Token keyword, Token method) -> ExprPtrVariant;

auto createExprSPV(ExprPtrVariant expr) -> StmtPtrVariant;
auto createPrintSPV(ExprPtrVariant expr) -> StmtPtrVariant;
auto createBlockSPV(std::vector<StmtPtrVariant> statements) -> StmtPtrVariant;
auto createIfSPV(ExprPtrVariant condition, StmtPtrVariant thenBranch,
                 std::optional<StmtPtrVariant> elseBranch) -> StmtPtrVariant;
auto createWhileSPV(std::optional<ExprPtrVariant> condition,
                    StmtPtrVariant loopBody) -> StmtPtrVariant;
auto createForSPV(std::optional<StmtPtrVariant> initializer,
                  std::optional<ExprPtrVariant> condition,
                  std::optional<ExprPtrVariant> increment,
                  StmtPtrVariant loopBOdy) -> StmtPtrVariant;
auto createFuncSPV(Token fName, FuncExprPtr funcExpr) -> StmtPtrVariant;
auto createRetSPV(Token ret, std::optional<ExprPtrVariant> value)
    -> StmtPtrVariant;
auto createClassSPV(Token className, std::optional<ExprPtrVariant> superClass,
                    std::vector<StmtPtrVariant> methods) -> StmtPtrVariant;

struct BinaryExpr final : public Uncopyable {
  ExprPtrVariant left;
  Token op;
  ExprPtrVariant right;
  BinaryExpr(ExprPtrVariant left, Token op, ExprPtrVariant right);
};

struct GroupingExpr final : public Uncopyable {
  ExprPtrVariant expression;
  explicit GroupingExpr(ExprPtrVariant expression);
};

struct LiteralExpr final : public Uncopyable {
  OptionalLiteral literalVal;
  explicit LiteralExpr(OptionalLiteral value);
};

struct UnaryExpr final : public Uncopyable {
  Token op;
  ExprPtrVariant right;
  UnaryExpr(Token op, ExprPtrVariant right);
};

struct ConditionalExpr final : public Uncopyable {
  ExprPtrVariant condition;
  ExprPtrVariant thenBranch;
  ExprPtrVariant elseBranch;
  ConditionalExpr(ExprPtrVariant condition, ExprPtrVariant thenBranch,
                  ExprPtrVariant elseBranch);
};

struct PostfixExpr final : public Uncopyable {
  ExprPtrVariant left;
  Token op;
  PostfixExpr(ExprPtrVariant left, Token op);
};

struct VariableExpr final : public Uncopyable {
  Token varName;
  explicit VariableExpr(Token varName);
};

struct AssignmentExpr final : public Uncopyable {
  Token varName;
  ExprPtrVariant right;
  AssignmentExpr(Token varName, ExprPtrVariant right);
};

struct LogicalExpr final : public Uncopyable {
  ExprPtrVariant left;
  Token op;
  ExprPtrVariant right;
  LogicalExpr(ExprPtrVariant left, Token op, ExprPtrVariant right);
};

struct CallExpr final : public Uncopyable {
  ExprPtrVariant callee;
  Token paren;
  std::vector<ExprPtrVariant> arguments;
  CallExpr(ExprPtrVariant callee, Token paren,
           std::vector<ExprPtrVariant> arguments);
};

struct FuncExpr final : public Uncopyable {
  std::vector<Token> parameters;
  std::vector<StmtPtrVariant> body;
  FuncExpr(std::vector<Token> parameters, std::vector<StmtPtrVariant> body);
};

struct GetExpr final : public Uncopyable {
  ExprPtrVariant expr;
  Token name;
  GetExpr(ExprPtrVariant expr, Token name);
};

struct SetExpr final : public Uncopyable {
  ExprPtrVariant expr;
  Token name;
  ExprPtrVariant value;
  SetExpr(ExprPtrVariant expr, Token name, ExprPtrVariant value);
};

struct ThisExpr final : public Uncopyable {
  Token keyword;
  explicit ThisExpr(Token keyword);
};

struct SuperExpr final : public Uncopyable {
  Token keyword;
  Token method;
  explicit SuperExpr(Token keyword, Token method);
};

// Statment AST types;
struct ExprStmt final : public Uncopyable {
  ExprPtrVariant expression;
  explicit ExprStmt(ExprPtrVariant expr);
};

struct PrintStmt final : public Uncopyable {
  ExprPtrVariant expression;
  explicit PrintStmt(ExprPtrVariant expression);
};

struct BlockStmt final : public Uncopyable {
  std::vector<StmtPtrVariant> statements;
  explicit BlockStmt(std::vector<StmtPtrVariant> statements);
};

struct VarStmt final : public Uncopyable {
  Token varName;
  std::optional<ExprPtrVariant> initializer;
  explicit VarStmt(Token varName, std::optional<ExprPtrVariant> initializer);
};

struct IfStmt final : public Uncopyable {
  ExprPtrVariant condition;
  StmtPtrVariant thenBranch;
  std::optional<StmtPtrVariant> elseBranch;
  explicit IfStmt(ExprPtrVariant condition, StmtPtrVariant thenBranch,
                  std::optional<StmtPtrVariant> elseBranch);
};

struct WhileStmt final : public Uncopyable {
  ExprPtrVariant condition;
  StmtPtrVariant loopBody;
  explicit WhileStmt(ExprPtrVariant condition, StmtPtrVariant loopBody);
};

struct ForStmt final : public Uncopyable {
  std::optional<StmtPtrVariant> initializer;
  std::optional<ExprPtrVariant> condition;
  std::optional<ExprPtrVariant> increment;
  StmtPtrVariant loopBody;
  explicit ForStmt(std::optional<StmtPtrVariant> initializer,
                   std::optional<ExprPtrVariant> condition,
                   std::optional<ExprPtrVariant> increment,
                   StmtPtrVariant loopBody);
};

struct FuncStmt : public Uncopyable {
  Token funcName;
  FuncExprPtr funcExpr;
  FuncStmt(Token funcName, FuncExprPtr funcExpr);
};

struct RetStmt : public Uncopyable {
  Token ret;
  std::optional<ExprPtrVariant> value;
  RetStmt(Token ret, std::optional<ExprPtrVariant> value);
};

struct ClassStmt : public Uncopyable {
  Token className;
  std::optional<ExprPtrVariant> superClass;
  std::vector<StmtPtrVariant> methods;
  ClassStmt(Token className, std::optional<ExprPtrVariant> superClass,
            std::vector<StmtPtrVariant> methods);
};

}; // namespace wlox::AST
