#pragma once
#include <string>
#include <vector>
#include "token.h"


class tokenizer
{
public:
    explicit tokenizer(std::string source);
    ~tokenizer() = default;
    
    tokenizer(const tokenizer& other) = delete;
    tokenizer(tokenizer&& other) = delete;
    tokenizer& operator=(const tokenizer& other) = delete;
    tokenizer& operator=(tokenizer&& other) = delete;

    std::vector<token> tokenize();

private:
    const std::string m_source;
};
