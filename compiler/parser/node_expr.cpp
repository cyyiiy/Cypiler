#include "node_expr.h"

std::string node_expr_numeric::to_string(const int offset) const
{
    std::string out = offset_to_string(offset);

    out += "Numeric value - " + m_numeric_value;
    
    return out;
}

std::string node_expr_text::to_string(const int offset) const
{
    std::string out = offset_to_string(offset);

    out += "Text value - " + m_text_value;

    return out;
}
