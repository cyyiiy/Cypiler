#include <iostream>
#include <filesystem>

#include <compiler/compiler.h>
#include <compiler/utils/compiler_exception.h>


int main(int argc, char* argv[])
{
    // Check arguments
    if (argc != 2)
    {
        std::cerr << "Incorrect usage! Should be called with 1 argument.\n";
        return EXIT_FAILURE;
    }
    const std::filesystem::path input_code_path = std::filesystem::path(argv[1]);
    
    // Compute assembly output file path
    std::filesystem::path asm_path = std::filesystem::path(argv[0]).parent_path();
    std::filesystem::path asm_name = std::filesystem::path(argv[1]).filename();
    asm_name.replace_extension(".asm");
    asm_path /= asm_name;
    
    // Compile the code
    compiler compiler(input_code_path);
    try
    {
        compiler.compile(asm_path, true);
    }
    catch (const compiler_exception& e)
    {
        std::cerr << e.what() << "\n";
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}