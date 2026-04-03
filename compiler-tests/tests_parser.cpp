#include "doctest.h"
#include <compiler/parser/parser.h>
#include <compiler/utils/compiler_exception.h>

#define IS_VALID(ptr) !!(ptr)


TEST_SUITE_BEGIN("Tests Parser");

TEST_CASE("Parse Exit Instruction")
{
    // Setup
    // ===============================
    // Code: exit(0);
    const std::vector<token> input_tokens = {
        token(token_type::istr_exit),
        token(token_type::sntx_par_open),
        token(token_type::val_numeric, "0"),
        token(token_type::sntx_par_close),
        token(token_type::sntx_semicolon)
    };
    parse_result output_nodes;
    
    // Execute
    // ===============================
    parser parser(input_tokens);
    try
    {
        output_nodes = parser.parse();
    }
    
    // Verify
    // ===============================
    catch (const compiler_exception& e)
    {
        CHECK(std::string(e.what()) == "There shouldn't be an exception.");
        return;
    }
    
    CHECK(output_nodes.m_root_nodes.size() == 1);
    CHECK(output_nodes.m_text_literals.size() == 0);
    
    auto output_node_exit = std::dynamic_pointer_cast<node_root_exit>(output_nodes.m_root_nodes[0]);
    REQUIRE(IS_VALID(output_node_exit));
    auto output_node_numeric_literal = std::dynamic_pointer_cast<node_expr_numeric_literal>(output_node_exit->m_expr_numeric);
    REQUIRE(IS_VALID(output_node_numeric_literal));
    CHECK(output_node_numeric_literal->m_numeric_value == "0");
}

TEST_CASE("Parse Exit Wrong Value Type")
{
    // Setup
    // ===============================
    // Code: exit("Hello, World!");
    const std::vector<token> input_tokens = {
        token(token_type::istr_exit),
        token(token_type::sntx_par_open),
        token(token_type::val_text, "Hello, World!"),
        token(token_type::sntx_par_close),
        token(token_type::sntx_semicolon)
    };
    parse_result output_nodes;
    
    // Execute
    // ===============================
    parser parser(input_tokens);
    try
    {
        output_nodes = parser.parse();
    }
    
    // Verify
    // ===============================
    catch (const compiler_exception& e)
    {
        CHECK(std::string(e.what()) == "Syntax error: required numeric expression, got <Value 'Text' - Hello, World!>");
    }
    
    CHECK(output_nodes.m_root_nodes.size() == 0);
    CHECK(output_nodes.m_text_literals.size() == 0);
}

TEST_CASE("Parse Exit Wrong Syntax")
{
    // Setup
    // ===============================
    // Code: exit)0);
    const std::vector<token> input_tokens = {
        token(token_type::istr_exit),
        token(token_type::sntx_par_close),
        token(token_type::val_numeric, "0"),
        token(token_type::sntx_par_close),
        token(token_type::sntx_semicolon)
    };
    parse_result output_nodes;
    
    // Execute
    // ===============================
    parser parser(input_tokens);
    try
    {
        output_nodes = parser.parse();
    }
    
    // Verify
    // ===============================
    catch (const compiler_exception& e)
    {
        CHECK(std::string(e.what()) == "Syntax error: required <Syntax 'Open Parenthesis'>, got <Syntax 'Close Parenthesis'>");
    }
    
    CHECK(output_nodes.m_root_nodes.size() == 0);
    CHECK(output_nodes.m_text_literals.size() == 0);
}

TEST_CASE("Parse Print Instruction")
{
    // Setup
    // ===============================
    // Code: print("Hello, World!");
    const std::vector<token> input_tokens = {
        token(token_type::istr_print),
        token(token_type::sntx_par_open),
        token(token_type::val_text, "Hello, World!"),
        token(token_type::sntx_par_close),
        token(token_type::sntx_semicolon)
    };
    parse_result output_nodes;
    
    // Execute
    // ===============================
    parser parser(input_tokens);
    try
    {
        output_nodes = parser.parse();
    }
    
    // Verify
    // ===============================
    catch (const compiler_exception& e)
    {
        CHECK(std::string(e.what()) == "There shouldn't be an exception.");
        return;
    }
    
    CHECK(output_nodes.m_root_nodes.size() == 1);
    CHECK(output_nodes.m_text_literals.size() == 1);
    
    auto output_node_print = std::dynamic_pointer_cast<node_root_print>(output_nodes.m_root_nodes[0]);
    REQUIRE(IS_VALID(output_node_print));
    auto output_node_text_literal = std::dynamic_pointer_cast<node_expr_text_literal>(output_node_print->m_expr_text);
    REQUIRE(IS_VALID(output_node_text_literal));
    CHECK(output_node_text_literal->m_text_value == "Hello, World!");
}

TEST_CASE("Parse Print Wrong Value Type")
{
    // Setup
    // ===============================
    // Code: print(0);
    const std::vector<token> input_tokens = {
        token(token_type::istr_print),
        token(token_type::sntx_par_open),
        token(token_type::val_numeric, "0"),
        token(token_type::sntx_par_close),
        token(token_type::sntx_semicolon)
    };
    parse_result output_nodes;
    
    // Execute
    // ===============================
    parser parser(input_tokens);
    try
    {
        output_nodes = parser.parse();
    }
    
    // Verify
    // ===============================
    catch (const compiler_exception& e)
    {
        CHECK(std::string(e.what()) == "Syntax error: required text expression, got <Value 'Numeric' - 0>");
    }
    
    CHECK(output_nodes.m_root_nodes.size() == 0);
    CHECK(output_nodes.m_text_literals.size() == 0);
}

TEST_CASE("Parse Print Missing Token")
{
    // Setup
    // ===============================
    // Code: print("Hello, World!")
    const std::vector<token> input_tokens = {
        token(token_type::istr_print),
        token(token_type::sntx_par_open),
        token(token_type::val_text, "Hello, World!"),
        token(token_type::sntx_par_close)
    };
    parse_result output_nodes;
    
    // Execute
    // ===============================
    parser parser(input_tokens);
    try
    {
        output_nodes = parser.parse();
    }
    
    // Verify
    // ===============================
    catch (const compiler_exception& e)
    {
        CHECK(std::string(e.what()) == "Syntax error: required <Syntax 'Semicolon'>, got nothing");
    }
    
    CHECK(output_nodes.m_root_nodes.size() == 0);
    CHECK(output_nodes.m_text_literals.size() == 0);
}

TEST_CASE("Parse Constant Declaration and Usage")
{
    // Setup
    // ===============================
    // Code:
    //  const int constant = 0;
    //  exit(constant);
    const std::vector<token> input_tokens = {
        token(token_type::istr_constant),
        token(token_type::type_int),
        token(token_type::custom_name, "constant"),
        token(token_type::sntx_equal),
        token(token_type::val_numeric, "0"),
        token(token_type::sntx_semicolon),
        
        token(token_type::istr_exit),
        token(token_type::sntx_par_open),
        token(token_type::custom_name, "constant"),
        token(token_type::sntx_par_close),
        token(token_type::sntx_semicolon)
    };
    parse_result output_nodes;
    
    // Execute
    // ===============================
    parser parser(input_tokens);
    try
    {
        output_nodes = parser.parse();
    }
    
    // Verify
    // ===============================
    catch (const compiler_exception& e)
    {
        CHECK(std::string(e.what()) == "There shouldn't be an exception.");
        return;
    }
    
    CHECK(output_nodes.m_root_nodes.size() == 1);
    CHECK(output_nodes.m_text_literals.size() == 0);
    
    auto output_node_exit = std::dynamic_pointer_cast<node_root_exit>(output_nodes.m_root_nodes[0]);
    REQUIRE(IS_VALID(output_node_exit));
    auto output_node_numeric_constant = std::dynamic_pointer_cast<node_expr_numeric_constant>(output_node_exit->m_expr_numeric);
    REQUIRE(IS_VALID(output_node_numeric_constant));
    CHECK(output_node_numeric_constant->m_custom_name == "constant");
    auto output_node_numeric_literal = std::dynamic_pointer_cast<node_expr_numeric_literal>(output_node_numeric_constant->m_expr_numeric);
    REQUIRE(IS_VALID(output_node_numeric_literal));
    CHECK(output_node_numeric_literal->m_numeric_value == "0");
}

TEST_CASE("Parse Non-Declared Constant Usage")
{
    // Setup
    // ===============================
    // Code: 
    //  exit(constant);
    const std::vector<token> input_tokens = {
        token(token_type::istr_exit),
        token(token_type::sntx_par_open),
        token(token_type::custom_name, "constant"),
        token(token_type::sntx_par_close),
        token(token_type::sntx_semicolon)
    };
    parse_result output_nodes;
    
    // Execute
    // ===============================
    parser parser(input_tokens);
    try
    {
        output_nodes = parser.parse();
    }
    
    // Verify
    // ===============================
    catch (const compiler_exception& e)
    {
        CHECK(std::string(e.what()) == "Constant name \"constant\" is not registered!");
    }
    
    CHECK(output_nodes.m_root_nodes.size() == 0);
    CHECK(output_nodes.m_text_literals.size() == 0);
}

TEST_CASE("Prase Wrong Type Constant Usage")
{
    // Setup
    // ===============================
    // Code:
    //  const int constant = 0;
    //  print(constant);
    const std::vector<token> input_tokens = {
        token(token_type::istr_constant),
        token(token_type::type_int),
        token(token_type::custom_name, "constant"),
        token(token_type::sntx_equal),
        token(token_type::val_numeric, "0"),
        token(token_type::sntx_semicolon),
        
        token(token_type::istr_print),
        token(token_type::sntx_par_open),
        token(token_type::custom_name, "constant"),
        token(token_type::sntx_par_close),
        token(token_type::sntx_semicolon)
    };
    parse_result output_nodes;
    
    // Execute
    // ===============================
    parser parser(input_tokens);
    try
    {
        output_nodes = parser.parse();
    }
    
    // Verify
    // ===============================
    catch (const compiler_exception& e)
    {
        CHECK(std::string(e.what()) == "Required constant of type <string>, got:\nConstant numeric - \"constant\"\n > Literal numeric value - 0");
    }
    
    CHECK(output_nodes.m_root_nodes.size() == 0);
    CHECK(output_nodes.m_text_literals.size() == 0);
}

TEST_SUITE_END;