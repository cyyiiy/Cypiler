#include "tokenizer.h"
#include <iostream>


tokenizer::tokenizer(std::string source) : m_source(std::move(source))
{
}


std::vector<token> tokenizer::tokenize()
{
    // Reset potential previous tokenization
    m_read_index = 0;
    m_tokens.clear();
    
    std::optional<char> next_char;
    while ((next_char = peek_char()).has_value())
    {
        if (isspace(next_char.value()))
        {
            consume_char();
            continue;
        }

        if (isalpha(next_char.value()))
        {
            m_tokens.push_back(search_instruction());
            continue;
        }

        if (isdigit(next_char.value()))
        {
            m_tokens.push_back(get_value_numeric());
            continue;
        }

        if (next_char.value() == '"')
        {
            consume_char(); // Consume the opening quote
            m_tokens.push_back(get_value_text());
            continue;
        }

        m_tokens.push_back(search_syntax());
    }

    return m_tokens;
}

std::optional<char> tokenizer::peek_char() const
{
    if (m_read_index >= m_source.length())
        return {};

    return m_source.at(m_read_index);
}

char tokenizer::consume_char()
{
    const char out = m_source.at(m_read_index);
    m_read_index++;
    return out;
}

token tokenizer::search_instruction()
{
    // 1. Read the instruction
    std::string token_buffer;
    std::optional<char> next_char = peek_char();
    while (next_char.has_value() && isalpha(next_char.value()))
    {
        token_buffer += consume_char();
        next_char = peek_char();
    }

    // 2. Return token if the instruction exists
    if (token_buffer == "exit")
    {
        return token(token_type::istr_exit);
    }
    if (token_buffer == "print")
    {
        return token(token_type::istr_print);
    }
    
    std::cerr << "Unknown instruction: " << token_buffer << "\n";
    exit(EXIT_FAILURE);
}

token tokenizer::search_syntax()
{
    switch (const char syntax_char = consume_char())
    {
    case ';':
        return token(token_type::sntx_semicolon);

    case '(':
        return token(token_type::sntx_par_open);

    case ')':
        return token(token_type::sntx_par_close);

    default:
        std::cerr << "Unkown syntax: " << syntax_char << "\n";
        exit(EXIT_FAILURE);
    }
}

token tokenizer::get_value_numeric()
{
    std::string numeric_buffer;
    std::optional<char> next_char = peek_char();
    while (next_char.has_value() && isdigit(next_char.value()))
    {
        numeric_buffer += consume_char();
        next_char = peek_char();
    }
    
    return token(token_type::val_numeric, numeric_buffer);
}

token tokenizer::get_value_text()
{
    std::string text_buffer;
    std::optional<char> next_char = peek_char();
    while (next_char.has_value() && next_char.value() != '"')
    {
        text_buffer += consume_char();
        next_char = peek_char();
    }
    if (!next_char.has_value())
    {
        std::cerr << "Missing closing quote!\n";
        exit(EXIT_FAILURE);
    }

    consume_char(); // Consume the closing quote
    return token(token_type::val_text, text_buffer);
}
