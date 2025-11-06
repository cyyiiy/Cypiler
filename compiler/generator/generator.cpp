#include "generator.h"


generator::generator(std::vector<std::shared_ptr<node_root>> root_nodes) : m_root_nodes(std::move(root_nodes))
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
    for (size_t i = 0; i < m_root_nodes.size(); i++)
    {
        m_assembly << m_root_nodes[i]->to_assembly();

        if (i < m_root_nodes.size() - 1)
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
    
    for (const auto& root_node : m_root_nodes)
    {
        const std::shared_ptr<node_root_print>& print_node = std::dynamic_pointer_cast<node_root_print>(root_node);
        if (print_node)
        {
            text_expressions.push_back(print_node->m_expr_text->m_text_value);
            print_node->m_expr_text->m_assembly_text_index = num_text_expressions;
            num_text_expressions++;
        }
    }

    return text_expressions;
}
