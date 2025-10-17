#include "token_type.h"

std::string token_utils::to_string(const token_type type)
{
    switch (type)
    {
    // Instructions
        
    case token_type::istr_exit:
        return "Instruction 'Exit'";

    case token_type::istr_print:
        return "Instruction 'Print'";

        
    // Syntax

    case token_type::sntx_semicolon:
        return "Syntax 'Semicolon'";

    case token_type::sntx_par_open:
        return "Syntax 'Open Parenthesis'";

    case token_type::sntx_par_close:
        return "Syntax 'Close Parenthesis'";


    // Values

    case token_type::val_numeric:
        return "Value 'Numeric'";

    case token_type::val_text:
        return "Value 'Text'";

    default:
        return "Unimplemented token type!";
    }
}
