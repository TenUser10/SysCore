#pragma once
#include <string>
#include <vector>

enum class TokenType {
    Fn, Int, Return, If, Else, While,
    Ident, Number,
    Plus, Minus, Star, Slash,
    Assign, Eq, Neq, Lt, Lte, Gt, Gte,
    LParen, RParen, LBrace, RBrace, Comma, Semicolon, Arrow,
    Eof
};

struct Token {
    TokenType type;
    std::string lexeme;
    int line;
};

class Lexer {
public:
    explicit Lexer(const std::string& source);
    std::vector<Token> tokenize();

private:
    std::string src;
    size_t pos = 0;
    int line = 1;

    char peek() const;
    char peekNext() const;
    char advance();
    void skipWhitespaceAndComments();
    Token identifierOrKeyword();
    Token number();
};