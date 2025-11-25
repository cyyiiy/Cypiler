#pragma once
#include <string>

enum class token_type
{
    // Instructions
    istr_exit,
    istr_print,
    istr_constant,

    // Types
    type_int,
    type_string,

    // Syntax
    sntx_semicolon,
    sntx_par_open,
    sntx_par_close,
    sntx_equal,

    // Values
    val_numeric,
    val_text,

    // Others
    custom_name,
};

namespace token_utils
{
    std::string to_string(token_type type);
}