#include "token.h"

std::string token::to_string() const
{
    std::string out = token_utils::to_string(m_type);
    
    if (m_raw_value.empty()) return out;

    return out + " - " + m_raw_value;
}

std::string token_utils::to_string(const token& token)
{
    return token.to_string();
}
