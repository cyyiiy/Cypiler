#include "tokenizer.h"

tokenizer::tokenizer(std::string source) : m_source(std::move(source))
{
}


std::vector<token> tokenizer::tokenize()
{
    std::optional<char> next_char = peek_char();
    while (next_char.has_value())
    {
        // TODO: write the tokenizer
        char temp = consume_char();

        next_char = peek_char();
    }

    return {};
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