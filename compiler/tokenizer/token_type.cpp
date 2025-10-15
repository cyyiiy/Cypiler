#include "token_type.h"

std::string token_utils::to_string(token_type type)
{
    switch (type)
    {
    case token_type::istr_exit:
        return "Instruction 'Exit'";

    case token_type::istr_print:
        return "Instruction 'Print'";

    case token_type::val_uint8:
        return "Value 'UInt8'";

    case token_type::sntx_semicolon:
        return "Syntax 'Semicolon'";

    case token_type::sntx_par_open:
        return "Syntax 'Open Parenthesis'";

    case token_type::sntx_par_close:
        return "Syntax 'Close Parenthesis'";

    case token_type::sntx_quote:
        return "Syntax 'Quote'";

    default:
        return "Unimplemented token type!";
    }
}
