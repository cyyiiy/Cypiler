#include "doctest.h"
#include <compiler/precompiler/precompiler.h>
#include <compiler/utils/compiler_exception.h>

TEST_SUITE_BEGIN("Tests Precompiler");

TEST_CASE("Precompile No Comment")
{
    // Setup
    // ===============================
    const std::string input_code = 
        "const int a = 0;\n"
        "exit(a);"
    ;
    const std::string desired_output = input_code;
    std::string output_code;
    
    // Execute
    // ===============================
    precompiler precompiler(input_code);
    try
    {
        output_code = precompiler.precompile();
    }
    
    // Verify
    // ===============================
    catch (const compiler_exception& e)
    {
        CHECK(std::string(e.what()) == "There shouldn't be an exception.");
        return;
    }
    
    CHECK(output_code == desired_output);
}

TEST_CASE("Precompile Single Line Comment")
{
    // Setup
    // ===============================
    const std::string input_code =
        "const int a = 0; // Some comment\n"
        "exit(a);\n"
        "// Other comment"
    ;
    const std::string desired_output = 
        "const int a = 0; \n"
        "exit(a);\n"
        ""
    ;
    std::string output_code;
    
    // Execute
    // ===============================
    precompiler precompiler(input_code);
    try
    {
        output_code = precompiler.precompile();
    }
    
    // Verify
    // ===============================
    catch (const compiler_exception& e)
    {
        CHECK(std::string(e.what()) == "There shouldn't be an exception.");
        return;
    }
    
    CHECK(output_code == desired_output);
}

TEST_CASE("Precompile Multi Lines Comment")
{
    // Setup
    // ===============================
    const std::string input_code = 
        "const int a = 0;\n"
        "/* Multi lines\n"
        "comment*/\n"
        "exit(a);"
    ;
    const std::string desired_output = 
        "const int a = 0;\n"
        "\n"
        "exit(a);"
    ;
    std::string output_code;
    
    // Execute
    // ===============================
    precompiler precompiler(input_code);
    try
    {
        output_code = precompiler.precompile();
    }
    
    // Verify
    // ===============================
    catch (const compiler_exception& e)
    {
        CHECK(std::string(e.what()) == "There shouldn't be an exception.");
        return;
    }
    
    CHECK(output_code == desired_output);
}

TEST_CASE("Precompile Unclosed Multi Lines Comment")
{
    // Setup
    // ===============================
    const std::string input_code = 
        "const int a = 0;\n"
        "/* Multi lines\n"
        "unclosed comment\n"
        "exit(a);"
    ;
    std::string output_code;
    
    // Execute
    // ===============================
    precompiler precompiler(input_code);
    try
    {
        output_code = precompiler.precompile();
    }
    
    // Verify
    // ===============================
    catch (const compiler_exception& e)
    {
        CHECK(std::string(e.what()) == "Multi-line comment is not closed. Need \"*/\".");
    }
    
    CHECK(output_code.empty());
}

TEST_SUITE_END;