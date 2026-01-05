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
            
            // Search for single line comment ("//")
            if (next_char.has_value() && next_char.value() == '/')
            {
                skip_line();
                if (!peek_char().has_value())
                {
                    // Prevent crash if 'skip_line' skipped until the end of the source
                    return m_precompiled;
                }
            }
        }
        
        m_precompiled += consume_char();
    }
    
    return m_precompiled;
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
    std::optional<char> next_char;
    while ((next_char = peek_char()).has_value())
    {
        if (next_char.value() == '\n' || next_char.value() == '\r')
        {
            // Encountered line break (do not consume it), line is skipped
            return;
        }
        
        consume_char();
    }
    
    // No more char in the source so line is technically skipped
}
