#pragma once
#include <string>

enum class token_type
{
    // Instructions
    istr_exit,
    istr_print,

    // Values
    val_uint8,

    // Syntax
    sntx_semicolon,
    sntx_par_open,
    sntx_par_close,
    sntx_quote,
};

namespace token_utils
{
    std::string to_string(token_type type);
}