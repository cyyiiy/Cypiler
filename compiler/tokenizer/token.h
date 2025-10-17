#pragma once
#include <string>
#include "token_type.h"


struct token
{
    explicit token(const token_type type, std::string raw_value = "") : m_type(type), m_raw_value(std::move(raw_value)) {}

    [[nodiscard]] std::string to_string() const;
    
    token_type m_type;
    std::string m_raw_value;
};

namespace token_utils
{
    std::string to_string(const token& token);
}