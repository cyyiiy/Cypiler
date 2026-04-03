#include "doctest.h"
#include <compiler/compiler.h>
#include <compiler/utils/compiler_exception.h>

TEST_SUITE_BEGIN("Tests Pipeline");

TEST_CASE("Compile functional code")
{
    // Setup
    // ===============================
    const std::filesystem::path input_path = "tests-resources/test_cypp_code.cypp";
    const std::filesystem::path output_path = "tests-resources/test_compiler_pipeline.asm";
    const std::string desired_output = 
        "section .data\n"
        "    msg0 db \"Hello from cy++\", 10\n"
        "    len0 equ $ - msg0\n"
        "\n"
        "    msg1 db \"You can try this at home!\", 10\n"
        "    len1 equ $ - msg1\n"
        "\n"
        "section .text\n"
        "    global _start\n"
        "\n"
        "_start:\n"
        "    ; Print to console instruction\n"
        "    ; Print text value 0\n"
        "    mov rax, 1\n"
        "    mov rdi, 1\n"
        "    mov rsi, msg0\n"
        "    mov rdx, len0\n"
        "    syscall\n"
        "\n"
        "    ; Print to console instruction\n"
        "    ; Print text value 1\n"
        "    mov rax, 1\n"
        "    mov rdi, 1\n"
        "    mov rsi, msg1\n"
        "    mov rdx, len1\n"
        "    syscall\n"
        "\n"
        "    ; Exit instruction\n"
        "    mov rax, 60\n"
        "    mov rdi, 3\n"
        "    syscall"
    ;
    std::string output_assembly;
    
    // Execute
    // ===============================
    compiler compiler(input_path);
    try
    {
        output_assembly = compiler.compile(output_path, false);
    }
    
    // Verify
    // ===============================
    catch (const compiler_exception& e)
    {
        CHECK(std::string(e.what()) == "There shouldn't be an exception.");
    }
    
    CHECK(output_assembly == desired_output);
    
    // Teardown
    // ===============================
    std::filesystem::remove(output_path);
}

TEST_CASE("Compile empty parse result")
{
    // Setup
    // ===============================
    const std::filesystem::path input_path = "tests-resources/test_empty_parse_result.cypp";
    std::string output_assembly;
    
    // Execute
    // ===============================
    compiler compiler(input_path);
    try
    {
        output_assembly = compiler.compile("", false);
    }
    
    // Verify
    // ===============================
    catch (const compiler_exception& e)
    {
        CHECK(std::string(e.what()) == "Generator error: Parse result is empty");
    }
    
    CHECK(output_assembly.empty());
}

TEST_SUITE_END;