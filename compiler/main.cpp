#include <iostream>
#include <filesystem>

#include "utils/file_reader.h"
#include "utils/file_writer.h"
#include "tokenizer/tokenizer.h"
#include "parser/parser.h"
#include "generator/generator.h"


int main(int argc, char* argv[])
{
    // 0. Check arguments

    if (argc != 2)
    {
        std::cerr << "Incorrect usage! Should be called with 1 argument.\n";
        return EXIT_FAILURE;
    }


    // 1. Open file

    std::cout << "Compiling " << argv[1] << "...\n\n";

    std::string content;
    if (!file_reader::read_file(argv[1], ".cypp", content))
    {
        std::cerr << content << "\n";
        return EXIT_FAILURE;
    }

    std::cout << "Raw source:\n----------\n" << content << "\n==========\n\n";

    
    // 2. Tokenize source code

    tokenizer tokenizer(content);
    std::vector<token> tokens;
    try
    {
        tokens = tokenizer.tokenize();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Tokenizer error: " << e.what() << "\n";
        return EXIT_FAILURE;
    }

    std::cout << "Tokens:\n----------\n";
    for (const auto& token : tokens)
    {
        std::cout << token.to_string() << "\n";
    }
    std::cout << "==========\n\n";


    // 3. Parse tokens

    parser parser(tokens);
    std::vector<std::shared_ptr<node_root>> root_nodes;
    try
    {
        root_nodes = parser.parse();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Parser error: " << e.what() << "\n";
        return EXIT_FAILURE;
    }

    std::cout << "Parsed nodes:\n----------\n";
    for (const auto& node : root_nodes)
    {
        std::cout << node->to_string() << "\n";
    }
    std::cout << "==========\n\n";


    // 4. Generate assembly

    generator generator(root_nodes);
    const std::string assembly = generator.generate();

    std::cout << "Assembly code:\n----------\n";
    std::cout << assembly << "\n";
    std::cout << "==========\n\n";


    // 5. Write assembly to file

    std::filesystem::path asm_path = std::filesystem::path(argv[0]).parent_path();
    std::filesystem::path asm_name = std::filesystem::path(argv[1]).filename();
    asm_name.replace_extension(".asm");
    asm_path /= asm_name;

    std::string error;
    if (!file_writer::write_file(asm_path, assembly, error))
    {
        std::cerr << error << "\n";
        return EXIT_FAILURE;
    }

    std::cout << "Assembly file generated at " << asm_path << "\n";

    return EXIT_SUCCESS;
}