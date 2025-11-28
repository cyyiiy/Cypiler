#include "node_expr.h"

std::string node_expr_numeric_literal::to_string(const int offset) const
{
    std::string out = offset_to_string(offset);
    out += "Literal numeric value - " + m_numeric_value;
    return out;
}

std::string node_expr_numeric_literal::get_numeric_value() const
{
    return m_numeric_value;
}


std::string node_expr_numeric_constant::to_string(const int offset) const
{
    std::string out = offset_to_string(offset);
    out += "Constant numeric - \"" + m_custom_name + "\"\n";
    out += m_expr_numeric->to_string(offset + 1);
    return out;
}

std::string node_expr_numeric_constant::get_numeric_value() const
{
    return m_expr_numeric->get_numeric_value();
}


std::string node_expr_text_literal::to_string(const int offset) const
{
    std::string out = offset_to_string(offset);
    out += "Text value - " + m_text_value;
    return out;
}

int node_expr_text_literal::get_assembly_text_index() const
{
    return m_assembly_text_index;
}


std::string node_expr_text_constant::to_string(const int offset) const
{
    std::string out = offset_to_string(offset);
    out += "Constant text - \"" + m_custom_name + "\"\n";
    out += m_expr_text->to_string(offset + 1);
    return out;
}

int node_expr_text_constant::get_assembly_text_index() const
{
    return m_expr_text->get_assembly_text_index();
}
