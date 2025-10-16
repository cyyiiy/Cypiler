#pragma once
#include <string>
#include <vector>
#include <optional>
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
    std::optional<char> peak_char() const;
    [[nodiscard]] char consume_char();

    const std::string m_source;
    int m_read_index{ 0 };
};
