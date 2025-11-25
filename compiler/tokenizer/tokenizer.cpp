#include "tokenizer.h"
#include <utils/compiler_exception.h>


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

        if (isalpha(next_char.value()) || next_char.value() == '_')
        {
            m_tokens.push_back(search_alpha_token());
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

token tokenizer::search_alpha_token()
{
    // 1. Read the alpha token
    std::string token_buffer;
    std::optional<char> next_char = peek_char();
    while (next_char.has_value() && (isalnum(next_char.value()) || next_char.value() == '_' || next_char.value() == '-'))
    {
        token_buffer += consume_char();
        next_char = peek_char();
    }

    // 2. Search if the token is an instruction or a type
    token_type type = token_type::custom_name;
    if (test_instruction(token_buffer, type))
    {
        return token(type);
    }
    if (test_type(token_buffer, type))
    {
        return token(type);
    }
    
    // 3. If the token is not an instruction or a type, return it as a custom name
    return token(token_type::custom_name, token_buffer);
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

    case '=':
        return token(token_type::sntx_equal);

    default:
        throw compiler_exception("Unknown syntax: " + std::string{syntax_char});
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
        if (next_char.value() == '\n' || next_char.value() == '\r')
        {
            throw compiler_exception("Line break inside quotes");
        }
        
        text_buffer += consume_char();
        next_char = peek_char();
    }
    if (!next_char.has_value())
    {
        throw compiler_exception("Missing closing quote");
    }

    consume_char(); // Consume the closing quote
    return token(token_type::val_text, text_buffer);
}

bool tokenizer::test_instruction(const std::string& token_str, token_type& out_type)
{
    if (token_str == "exit")
    {
        out_type = token_type::istr_exit;
        return true;
    }
    if (token_str == "print")
    {
        out_type = token_type::istr_print;
        return true;
    }
    if (token_str == "const")
    {
        out_type = token_type::istr_constant;
        return true;
    }

    return false;
}

bool tokenizer::test_type(const std::string& token_str, token_type& out_type)
{
    if (token_str == "int")
    {
        out_type = token_type::type_int;
        return true;
    }

    if (token_str == "string")
    {
        out_type = token_type::type_string;
        return true;
    }

    return false;
}
