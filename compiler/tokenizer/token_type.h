#pragma once
#include <string>

enum class token_type
{
    // Instructions
    istr_exit,
    istr_print,

    // Syntax
    sntx_semicolon,
    sntx_par_open,
    sntx_par_close,

    // Values
    val_numeric,
    val_text,
};

namespace token_utils
{
    std::string to_string(token_type type);
}