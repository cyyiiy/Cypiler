#include "doctest.h"
#include <compiler/generator/generator.h>

TEST_SUITE_BEGIN("Tests Generator");

TEST_CASE("Generate Exit Instruction")
{
    // Setup
    // ===============================
    const parse_result input_nodes = {
        std::vector<std::shared_ptr<node_root>>{
            std::make_shared<node_root_exit>(std::make_shared<node_expr_numeric_literal>("0"))
        },
        std::vector<std::shared_ptr<node_expr_text_literal>>{}
    };
    const std::string desired_output = 
        "section .data\n"
        "section .text\n"
        "    global _start\n"
        "\n"
        "_start:\n"
        "    ; Exit instruction\n"
        "    mov rax, 60\n"
        "    mov rdi, 0\n"
        "    syscall"
    ;
    
    // Execute
    // ===============================
    generator generator(input_nodes);
    const std::string output_assembly = generator.generate();
    
    // Verify
    // ===============================
    CHECK(output_assembly == desired_output);
}

TEST_CASE("Generate Print Instruction")
{
    // Setup
    // ===============================
    const parse_result input_nodes = {
        std::vector<std::shared_ptr<node_root>>{
            std::make_shared<node_root_print>(std::make_shared<node_expr_text_literal>("Hello, World!"))
        },
        std::vector<std::shared_ptr<node_expr_text_literal>>{
            std::make_shared<node_expr_text_literal>("Hello, World!")
        }
    };
    const std::string desired_output = 
        "section .data\n"
        "    msg0 db \"Hello, World!\", 10\n"
        "    len0 equ $ - msg0\n"
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
        "    syscall"
    ;
    
    // Execute
    // ===============================
    generator generator(input_nodes);
    const std::string output_assembly = generator.generate();
    
    // Verify
    // ===============================
    CHECK(output_assembly == desired_output);
}

TEST_CASE("Generate Constant Usage")
{
    // Setup
    // ===============================
    const parse_result input_nodes = {
        std::vector<std::shared_ptr<node_root>>{
            std::make_shared<node_root_exit>(std::make_shared<node_expr_numeric_constant>(
                "constant", std::make_shared<node_expr_numeric_literal>("0"))
            )
        },
        std::vector<std::shared_ptr<node_expr_text_literal>>{}
    };
    const std::string desired_output = 
        "section .data\n"
        "section .text\n"
        "    global _start\n"
        "\n"
        "_start:\n"
        "    ; Exit instruction\n"
        "    mov rax, 60\n"
        "    mov rdi, 0\n"
        "    syscall"
    ;
    
    // Execute
    // ===============================
    generator generator(input_nodes);
    const std::string output_assembly = generator.generate();
    
    // Verify
    // ===============================
    CHECK(output_assembly == desired_output);
}