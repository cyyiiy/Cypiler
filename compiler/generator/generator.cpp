#include "generator.h"


generator::generator(parse_result parse_result) : m_parse_result(std::move(parse_result))
{
}

std::string generator::generate()
{
    // Reset potential previous generation
    m_assembly.clear();

    // Data section, prepare text expressions
    m_assembly << "section .data\n";
    
    const std::vector<std::string> text_expressions = search_text_expressions();
    for (size_t i = 0; i < text_expressions.size(); i++)
    {
        m_assembly << "    msg" << i << " db \"" << text_expressions[i] << "\", 10\n";
        m_assembly << "    len" << i << " equ $ - msg" << i << "\n\n";
    }

    // Text section, declare main code
    m_assembly << "section .text\n";
    m_assembly << "    global _start\n\n";

    // Code section, write syscalls
    m_assembly << "_start:\n";

    const std::vector<std::shared_ptr<node_root>>& node_roots = m_parse_result.m_root_nodes;
    for (size_t i = 0; i < node_roots.size(); i++)
    {
        m_assembly << node_roots[i]->to_assembly();

        if (i < node_roots.size() - 1)
        {
            m_assembly << "\n\n";
        }
    }

    return m_assembly.str();
}

std::vector<std::string> generator::search_text_expressions() const
{
    std::vector<std::string> text_expressions;
    int num_text_expressions = 0;
    
    for (const std::shared_ptr<node_expr_text_literal>& node_text_literal : m_parse_result.m_text_literals)
    {
        text_expressions.push_back(node_text_literal->m_text_value);
        node_text_literal->m_assembly_text_index = num_text_expressions;
        num_text_expressions++;
    }

    return text_expressions;
}
