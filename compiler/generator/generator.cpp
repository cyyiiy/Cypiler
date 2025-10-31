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
    for (const auto& root_node : m_root_nodes)
    {
        const std::shared_ptr<node_root_exit>& exit_node = std::dynamic_pointer_cast<node_root_exit>(root_node);
        if (exit_node)
        {
            m_assembly << "    mov rax, 60\n";
            m_assembly << "    mov rdi, " << exit_node->m_expr_numeric->m_numeric_value << "\n";
            m_assembly << "    syscall\n\n";
            continue;
        }
        
        const std::shared_ptr<node_root_print>& print_node = std::dynamic_pointer_cast<node_root_print>(root_node);
        if (print_node)
        {
            m_assembly << "    mov rax, 1\n";
            m_assembly << "    mov rdi, 1\n";
            m_assembly << "    mov rsi, msg" << print_node->m_expr_text->m_assembly_text_index << "\n";
            m_assembly << "    mov rdx, len" << print_node->m_expr_text->m_assembly_text_index << "\n";
            m_assembly << "    syscall\n\n";
            continue;
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
