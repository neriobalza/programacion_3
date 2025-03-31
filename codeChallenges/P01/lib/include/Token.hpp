#pragma once

#include <string>

enum class TokenType
{
    EoF,
    Unit,
    Int,
    IsUnit,
    Pair,
    Fst,
    Snd,
    Neg,
    Add,
    Mul,
    Div,
    Mod,
    IfLesser,
    Val,
    Var,
    Let,
    Fun,
    Call,
    Identifier,
    LParen,
    RParen,
    Unknown
};

std::string to_string(TokenType token_type) noexcept;

TokenType from_string(const std::string& word) noexcept;

using Token = std::pair<TokenType, std::string>;
