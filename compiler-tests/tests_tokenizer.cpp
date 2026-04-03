#include "doctest.h"
#include <compiler/tokenizer/tokenizer.h>
#include <compiler/utils/compiler_exception.h>

TEST_SUITE_BEGIN("Tests Tokenizer");

TEST_CASE("Tokenize Exit Instruction")
{
    // Setup
    // ===============================
    const std::string input_code = "exit(0);"
    ;
    const std::vector<token> desired_output = {
        token(token_type::istr_exit),
        token(token_type::sntx_par_open),
        token(token_type::val_numeric, "0"),
        token(token_type::sntx_par_close),
        token(token_type::sntx_semicolon)
    };
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
        CHECK(std::string(e.what()) == "There shouldn't be an exception.");
    }
    
    CHECK(output_tokens == desired_output);
}

TEST_CASE("Tokenize Print Instruction")
{
    // Setup
    // ===============================
    const std::string input_code = "print(\"Hello, World!\");"
    ;
    const std::vector<token> desired_output = {
        token(token_type::istr_print),
        token(token_type::sntx_par_open),
        token(token_type::val_text, "Hello, World!"),
        token(token_type::sntx_par_close),
        token(token_type::sntx_semicolon)
    };
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
        CHECK(std::string(e.what()) == "There shouldn't be an exception.");
    }
    
    CHECK(output_tokens == desired_output);
}

TEST_CASE("Tokenize Constant Declaration and Usage")
{
    // Setup
    // ===============================
    const std::string input_code = 
        "const int constant = 0;\n"
        "exit(constant);"
    ;
    const std::vector<token> desired_output = {
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
        CHECK(std::string(e.what()) == "There shouldn't be an exception.");
    }
    
    CHECK(output_tokens == desired_output);
}

TEST_CASE("Tokenize Unknown Syntax")
{
    // Setup
    // ===============================
    // Note: € symbol will never be added to the language
    const std::string input_code = "exit(0); €";
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