#include "lexer.hpp"
#include <cctype>

Lexer::Lexer(const std::string& source) : src(source) {}

char Lexer::peek() const {
    return pos < src.size() ? src[pos] : '\0';
}

char Lexer::peekNext() const {
    return pos + 1 < src.size() ? src[pos + 1] : '\0';
}

char Lexer::advance() {
    char c = peek();
    if (c == '\n') line++;
    if (pos < src.size()) pos++;
    return c;
}

void Lexer::skipWhitespaceAndComments() {
    while (pos < src.size()) {
        char c = peek();
        if (std::isspace(static_cast<unsigned char>(c))) {
            advance();
        }
        else if (c == '/' && peekNext() == '/') {
            while (peek() != '\n' && peek() != '\0') advance();
        }
        else {
            break;
        }
    }
}

Token Lexer::identifierOrKeyword() {
    size_t start = pos;
    while (std::isalnum(static_cast<unsigned char>(peek())) || peek() == '_') {
        advance();
    }
    std::string text = src.substr(start, pos - start);
    if (text == "fn") return { TokenType::Fn, text, line };
    if (text == "int") return { TokenType::Int, text, line };
    if (text == "return") return { TokenType::Return, text, line };
    if (text == "if") return { TokenType::If, text, line };
    if (text == "else") return { TokenType::Else, text, line };
    if (text == "while") return { TokenType::While, text, line };
    return { TokenType::Ident, text, line };
}

Token Lexer::number() {
    size_t start = pos;
    while (std::isdigit(static_cast<unsigned char>(peek()))) {
        advance();
    }
    return { TokenType::Number, src.substr(start, pos - start), line };
}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    while (pos < src.size()) {
        skipWhitespaceAndComments();
        if (pos >= src.size()) break;

        char c = peek();
        if (std::isalpha(static_cast<unsigned char>(c)) || c == '_') {
            tokens.push_back(identifierOrKeyword());
            continue;
        }
        if (std::isdigit(static_cast<unsigned char>(c))) {
            tokens.push_back(number());
            continue;
        }

        advance();
        switch (c) {
        case '+': tokens.push_back({ TokenType::Plus, "+", line }); break;
        case '-':
            if (peek() == '>') { advance(); tokens.push_back({ TokenType::Arrow, "->", line }); }
            else tokens.push_back({ TokenType::Minus, "-", line });
            break;
        case '*': tokens.push_back({ TokenType::Star, "*", line }); break;
        case '/': tokens.push_back({ TokenType::Slash, "/", line }); break;
        case '=':
            if (peek() == '=') { advance(); tokens.push_back({ TokenType::Eq, "==", line }); }
            else tokens.push_back({ TokenType::Assign, "=", line });
            break;
        case '!':
            if (peek() == '=') { advance(); tokens.push_back({ TokenType::Neq, "!=", line }); }
            break;
        case '<':
            if (peek() == '=') { advance(); tokens.push_back({ TokenType::Lte, "<=", line }); }
            else tokens.push_back({ TokenType::Lt, "<", line });
            break;
        case '>':
            if (peek() == '=') { advance(); tokens.push_back({ TokenType::Gte, ">=", line }); }
            else tokens.push_back({ TokenType::Gt, ">", line });
            break;
        case '(': tokens.push_back({ TokenType::LParen, "(", line }); break;
        case ')': tokens.push_back({ TokenType::RParen, ")", line }); break;
        case '{': tokens.push_back({ TokenType::LBrace, "{", line }); break;
        case '}': tokens.push_back({ TokenType::RBrace, "}", line }); break;
        case ',': tokens.push_back({ TokenType::Comma, ",", line }); break;
        case ';': tokens.push_back({ TokenType::Semicolon, ";", line }); break;
        default: break;
        }
    }
    tokens.push_back({ TokenType::Eof, "", line });
    return tokens;
}