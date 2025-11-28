#include "node_root.h"
#include <sstream>


std::string node_root_exit::to_string(const int offset) const
{
    std::string out = offset_to_string(offset);
    out += "Exit\n";
    out += m_expr_numeric->to_string(offset + 1);
    return out;
}

std::string node_root_exit::to_assembly() const
{
    std::stringstream out;
    out << "    mov rax, 60\n";
    out << "    mov rdi, " << m_expr_numeric->get_numeric_value() << "\n";
    out << "    syscall";
    return out.str();
}


std::string node_root_print::to_string(const int offset) const
{
    std::string out = offset_to_string(offset);
    out += "Print\n";
    out += m_expr_text->to_string(offset + 1);
    return out;
}

std::string node_root_print::to_assembly() const
{
    std::stringstream out;
    out << "    mov rax, 1\n";
    out << "    mov rdi, 1\n";
    out << "    mov rsi, msg" << m_expr_text->get_assembly_text_index() << "\n";
    out << "    mov rdx, len" << m_expr_text->get_assembly_text_index() << "\n";
    out << "    syscall";
    return out.str();
}
