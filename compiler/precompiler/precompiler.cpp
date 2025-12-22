#include "precompiler.h"

precompiler::precompiler(std::string source) : m_source(std::move(source))
{
}

std::string precompiler::precompile()
{
    // Reset potential previous precompilation
    m_read_index = 0;
    
    std::optional<char> next_char;
    while ((next_char = peek_char()).has_value())
    {
        if (next_char.value() == '/')
        {
            consume_char();
            next_char = peek_char();
            
            // Search for single line comment
            if (next_char.has_value() && next_char.value() == '/')
            {
                skip_line();
            }
        }
        
        m_precompiled += consume_char();
    }
}

std::optional<char> precompiler::peek_char() const
{
    if (m_read_index >= m_source.length())
        return {};

    return m_source.at(m_read_index);
}

char precompiler::consume_char()
{
    const char out = m_source.at(m_read_index);
    m_read_index++;
    return out;
}

void precompiler::skip_line()
{
    std::optional<char> next_char = peek_char();
    while (next_char.has_value())
    {
        if (next_char.value() == '\n' || next_char.value() == '\r')
        {
            // TODO: Handle line break (take care of line break symbol being multiple chars)
            return;
        }
        
        m_read_index++;
    }
    
    // No more char in the source so line is skipped
}
