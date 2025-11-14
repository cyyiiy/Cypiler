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

    [[nodiscard]] std::vector<token> tokenize();

private:
    [[nodiscard]] std::optional<char> peek_char() const;
    char consume_char();

    [[nodiscard]] token search_alpha_token();
    [[nodiscard]] token search_syntax();
    
    [[nodiscard]] token get_value_numeric();
    [[nodiscard]] token get_value_text();
    
    [[nodiscard]] static bool test_instruction(const std::string& token_str, token_type& out_type);
    [[nodiscard]] static bool test_type(const std::string& token_str, token_type& out_type);

    
    const std::string m_source;
    size_t m_read_index{ 0 };

    std::vector<token> m_tokens;
};
