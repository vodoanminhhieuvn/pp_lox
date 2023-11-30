#include "scanner.h"
#include "types/literal.h"

#include <map>

#include <errors_and_debug/error_reporter.h>
#include <types/token.h>

namespace wlox {

using ErrorsAndDebug::ErrorReporter;
using Types::Literal;
using Types::OptionalLiteral;
using Types::Token;
using Types::TokenType;

namespace {
auto isAlpha(char c) -> bool {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_');
}

auto isAlphaNumeric(char c) -> bool { return c >= '0' && c <= '9'; }

auto ReserveOrIdentifier(const std::string &str) -> TokenType {
  static const std::map<std::string, TokenType> lookUpTable{
      {"and", TokenType::AND},       {"class", TokenType::CLASS},
      {"else", TokenType::ELSE},     {"false", TokenType::LOX_FALSE},
      {"fun", TokenType::FUN},       {"for", TokenType::FOR},
      {"if", TokenType::IF},         {"nil", TokenType::NIL},
      {"or", TokenType::OR},         {"print", TokenType::PRINT},
      {"return", TokenType::RETURN}, {"super", TokenType::SUPER},
      {"this", TokenType::THIS},     {"true", TokenType::LOX_TRUE},
      {"var", TokenType::VAR},       {"while", TokenType::WHILE}};

  auto iter = lookUpTable.find(str);
  if (iter == lookUpTable.end()) {
    return TokenType::IDENTIFIER;
  }
  return iter->second;
}

auto getLexeme(const std::string &source, size_t start, size_t end)
    -> std::string {
  return source.substr(start, end);
}

auto makeOptionalLiteral(TokenType t, const std::string &lexeme)
    -> OptionalLiteral {
  switch (t) {
  case TokenType::NUMBER:
    return Types::makeOptionalLiteral(std::stod(lexeme));
  case TokenType::STRING:
    return Types::makeOptionalLiteral(lexeme.substr(1, lexeme.size() - 2));
  default:
    return std::nullopt;
  }
}

} // namespace

Scanner::Scanner(const std::string &p_source, ErrorReporter &p_eReporter)
    : source(p_source), eReporter(p_eReporter) {}

void Scanner::addToken(TokenType t) {
  const std::string lexeme = getLexeme(source, start, current - start);
  tokens.emplace_back(t, lexeme, makeOptionalLiteral(t, lexeme), line);
}

void Scanner::advance() { ++current; }

void Scanner::skipBlockComment() {
  int nesting = 1;
  while (nesting > 0) {
    if (peek() == '\0') {
      eReporter.setError(line, "Block or comment not closed?");
      return;
    }

    if (peek() == '/' && peekNext() == '*') {
      advance();
      ++nesting;
    } else if (peek() == '*' && peekNext() == '/') {
      advance();
      --nesting;
    } else if (peek() == '\n') {
      ++line;
    }

    advance();
  }
}

void Scanner::skipComment() {
  while (!isAtEnd() && peek() != '\n') {
    advance();
  }
}

void Scanner::eatIdentifier() {
  while (isAlphaNumeric(peek()))
    advance();
}

} // namespace wlox
