#include <iostream>
#include "utils/file_reader.h"
#include "tokenizer/tokenizer.h"


int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Incorrect usage! Should be called with 1 argument.\n";
        return EXIT_FAILURE;
    }

    std::cout << "Compiling " << argv[1] << "...\n\n";

    std::string content;
    if (!file_reader::read_file(argv[1], ".cypp", content))
    {
        std::cerr << content << "\n";
        return EXIT_FAILURE;
    }

    std::cout << "Raw source:\n----------\n" << content << "\n==========\n\n";

    tokenizer tokenizer(content);
    const std::vector<token> tokens = tokenizer.tokenize();

    std::cout << "Tokens:\n----------\n";
    for (const auto& token : tokens)
    {
        std::cout << token.to_string() << "\n";
    }
    std::cout << "==========\n\n";

    return EXIT_SUCCESS;
}