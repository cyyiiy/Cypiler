#include <iostream>
#include <fstream>
#include <sstream>


int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Incorrect usage! Should be called with 1 argument.\n";
        return EXIT_FAILURE;
    }

    std::fstream file(argv[1], std::ios::in);
    std::stringstream file_content;
    file_content << file.rdbuf();
    file.close();

    std::cout << "Compiling " << argv[1] << "...\n";
    std::cout << "Raw source:\n" << file_content.str() << "\n";
    return EXIT_SUCCESS;
}