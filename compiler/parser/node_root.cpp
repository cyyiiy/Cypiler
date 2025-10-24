#include "node_root.h"

std::string node_root_exit::to_string(const int offset) const
{
    std::string out = offset_to_string(offset);

    out += "Exit\n";
    out += m_expr_numeric->to_string(offset + 1);

    return out;
}
