#include <vector>

#include <Token.hpp>

std::string to_string(TokenType token_type) noexcept
{
    switch (token_type)
    {
    case TokenType::EoF:
        return "EoF";
    case TokenType::Unit:
        return "Unit";
    case TokenType::Int:
        return "Int";
    case TokenType::IsUnit:
        return "IsUnit";
    case TokenType::Pair:
        return "Pair";
    case TokenType::Fst:
        return "Fst";
    case TokenType::Snd:
        return "Snd";
    case TokenType::Neg:
        return "Neg";
    case TokenType::Add:
        return "Add";
    case TokenType::Mul:
        return "Mul";
    case TokenType::Div:
        return "Div";
    case TokenType::Mod:
        return "Mod";
    case TokenType::IfLesser:
        return "IfLesser";
    case TokenType::Val:
        return "Val";
    case TokenType::Var:
        return "Var";
    case TokenType::Let:
        return "Let";
    case TokenType::Fun:
        return "Fun";
    case TokenType::Call:
        return "Call";
    case TokenType::Identifier:
        return "Identifier";
    case TokenType::LParen:
        return "LParen";
    case TokenType::RParen:
        return "RParen";
    case TokenType::Unknown:
        return "Unknown";
    default:
        return "";
    }
}

TokenType from_string(const std::string& word) noexcept
{
    std::vector<std::pair<std::string, TokenType>> reserved_words{
        {"isunit", TokenType::IsUnit},
        {"pair", TokenType::Pair},
        {"fst", TokenType::Fst},
        {"snd", TokenType::Snd},
        {"iflesser", TokenType::IfLesser},
        {"val", TokenType::Val},
        {"var", TokenType::Var},
        {"let", TokenType::Let},
        {"fun", TokenType::Fun},
        {"call", TokenType::Call}};

    for (const auto& p: reserved_words)
    {
        if (p.first == word)
        {
            return p.second;
        }
    }

    return TokenType::Identifier;
}
