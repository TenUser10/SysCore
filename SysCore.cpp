#include "lexer.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

static const char* tokenName(TokenType type) {
    switch (type) {
    case TokenType::Fn: return "Fn";
    case TokenType::Int: return "Int";
    case TokenType::Return: return "Return";
    case TokenType::If: return "If";
    case TokenType::Else: return "Else";
    case TokenType::While: return "While";
    case TokenType::Ident: return "Ident";
    case TokenType::Number: return "Number";
    case TokenType::Plus: return "Plus";
    case TokenType::Minus: return "Minus";
    case TokenType::Star: return "Star";
    case TokenType::Slash: return "Slash";
    case TokenType::Assign: return "Assign";
    case TokenType::Eq: return "Eq";
    case TokenType::Neq: return "Neq";
    case TokenType::Lt: return "Lt";
    case TokenType::Lte: return "Lte";
    case TokenType::Gt: return "Gt";
    case TokenType::Gte: return "Gte";
    case TokenType::LParen: return "LParen";
    case TokenType::RParen: return "RParen";
    case TokenType::LBrace: return "LBrace";
    case TokenType::RBrace: return "RBrace";
    case TokenType::Comma: return "Comma";
    case TokenType::Semicolon: return "Semicolon";
    case TokenType::Arrow: return "Arrow";
    case TokenType::Eof: return "Eof";
    }
    return "Unknown";
}

int main(int argc, char* argv[]) {
    std::string source;

    if (argc > 1) {
        std::ifstream file(argv[1]);
        if (!file) {
            std::cerr << "Failed to open file: " << argv[1] << "\n";
            return 1;
        }
        std::ostringstream ss;
        ss << file.rdbuf();
        source = ss.str();
    }
    else {
        source = R"(
            fn add(int a, int b) -> int {
                return a + b;
            }
            fn main() -> int {
                int x = 12;
                int y = 8;
                print(add(x, y));
                return 0;
            }
        )";
    }

    Lexer lexer(source);
    auto tokens = lexer.tokenize();

    std::cout << "SysCore Lexer Output:\n";
    for (const auto& t : tokens) {
        std::cout << "[Line " << t.line << "] " << tokenName(t.type) << " : '" << t.lexeme << "'\n";
    }

    return 0;
}