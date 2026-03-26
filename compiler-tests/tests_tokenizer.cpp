#include "doctest.h"
#include <compiler/tokenizer/tokenizer.h>
#include <compiler/utils/compiler_exception.h>
#include <iostream>

TEST_SUITE_BEGIN("Tests Tokenizer");

TEST_CASE("Tokenize Functional Code")
{
    // Setup
    // ===============================
    const std::string input_code =
        "const int value = 0;\n"
        "exit(value);"
    ;
    const std::vector<token> desired_output = {
        token(token_type::istr_constant),
        token(token_type::type_int),
        token(token_type::custom_name, "value"),
        token(token_type::sntx_equal),
        token(token_type::val_numeric, "0"),
        token(token_type::sntx_semicolon),
        
        token(token_type::istr_exit),
        token(token_type::sntx_par_open),
        token(token_type::custom_name, "value"),
        token(token_type::sntx_par_close),
        token(token_type::sntx_semicolon)
    };
    
    // Execute
    // ===============================
    tokenizer tokenizer(input_code);
    const std::vector<token> output_tokens = tokenizer.tokenize();
    
    // Verify
    // ===============================
    CHECK(output_tokens == desired_output);
    
}

TEST_CASE("Tokenize Dysfunctional Code")
{
    // Setup
    // ===============================
    const std::string input_code =
        "const string exit == 0\n"
        "int)value(;"
    ;
    const std::vector<token> desired_output = {
        token(token_type::istr_constant),
        token(token_type::type_string),
        token(token_type::istr_exit),
        token(token_type::sntx_equal),
        token(token_type::sntx_equal),
        token(token_type::val_numeric, "0"),
        
        token(token_type::type_int),
        token(token_type::sntx_par_close),
        token(token_type::custom_name, "value"),
        token(token_type::sntx_par_open),
        token(token_type::sntx_semicolon)
    };
    
    // Execute
    // ===============================
    tokenizer tokenizer(input_code);
    const std::vector<token> output_tokens = tokenizer.tokenize();
    
    // Verify
    // ===============================
    CHECK(output_tokens == desired_output);
    
}

TEST_CASE("Tokenize Unknown Syntax")
{
    // Setup
    // ===============================
    const std::string input_code = "exit(0); €";
    // Note: € symbol will never be added to the language
    std::vector<token> output_tokens;
    
    // Execute
    // ===============================
    tokenizer tokenizer(input_code);
    try
    {
        output_tokens = tokenizer.tokenize();
    }
    
    // Verify
    // ===============================
    catch (const compiler_exception& e)
    {
        CHECK(std::string(e.what()) == "Unknown syntax: €");
    }
    
    CHECK(output_tokens.empty());
}

TEST_CASE("Tokenize Missing Closing Quote")
{
    // Setup
    // ===============================
    const std::string input_code = "print(\"Hello, world!);";
    std::vector<token> output_tokens;
    
    // Execute
    // ===============================
    tokenizer tokenizer(input_code);
    try
    {
        output_tokens = tokenizer.tokenize();
    }
    
    // Verify
    // ===============================
    catch (const compiler_exception& e)
    {
        CHECK(std::string(e.what()) == "Missing closing quote");
    }
    
    CHECK(output_tokens.empty());
    
}

TEST_CASE("Tokenize Line Break Inside Quotes")
{
    // Setup
    // ===============================
    const std::string input_code = 
        "print(\"Hello, \n"
        "world!\");"
    ;
    std::vector<token> output_tokens;
    
    // Execute
    // ===============================
    tokenizer tokenizer(input_code);
    try
    {
        output_tokens = tokenizer.tokenize();
    }
    
    // Verify
    // ===============================
    catch (const compiler_exception& e)
    {
        CHECK(std::string(e.what()) == "Line break inside quotes");
    }
    
    CHECK(output_tokens.empty());
    
}

TEST_SUITE_END;