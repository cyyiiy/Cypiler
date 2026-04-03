#include "compiler.h"
#include <iostream>
#include <filesystem>

#include <utils/compiler_exception.h>
#include <utils/file_reader.h>
#include <utils/file_writer.h>
#include <precompiler/precompiler.h>
#include <tokenizer/tokenizer.h>
#include <parser/parser.h>
#include <generator/generator.h>


compiler::compiler(std::filesystem::path source_code_path) : m_source_code_path(std::move(source_code_path))
{
}


std::string compiler::compile(const std::filesystem::path& assembly_out_path, bool log_messages)
{
    // 1. Open file

    if (log_messages) std::cout << "Compiling " << m_source_code_path << "...\n\n";

    std::string content;
    if (!file_reader::read_file(m_source_code_path, ".cypp", content))
    {
        throw compiler_exception("File reader error: " + content);
    }

    if (log_messages) std::cout << "Raw source:\n----------\n" << content << "\n==========\n\n";
    
    
    // 2. Precompile source code
    
    precompiler precompiler(content);
    std::string code;
    try
    {
        code = precompiler.precompile();
    }
    catch (const compiler_exception& e)
    {
        throw compiler_exception("Precompiler error: " + std::string(e.what()));
    }

    if (log_messages)
    {
        std::cout << "Precompiled code:\n----------\n";
        std::cout << code << "\n";
        std::cout << "==========\n\n";
    }
    
    
    // 3. Tokenize precompiled code

    tokenizer tokenizer(code);
    std::vector<token> tokens;
    try
    {
        tokens = tokenizer.tokenize();
    }
    catch (const compiler_exception& e)
    {
        throw compiler_exception("Tokenizer error: " + std::string(e.what()));
    }

    if (log_messages)
    {
        std::cout << "Tokens:\n----------\n";
        for (const auto& token : tokens)
        {
            std::cout << token.to_string() << "\n";
        }
        std::cout << "==========\n\n";
    }


    // 4. Parse tokens

    parser parser(tokens);
    parse_result parse_result;
    try
    {
        parse_result = parser.parse();
    }
    catch (const compiler_exception& e)
    {
        throw compiler_exception("Parser error: " + std::string(e.what()));
    }

    if (log_messages)
    {
        std::cout << "Parsed nodes:\n----------\n";
        for (const auto& node : parse_result.m_root_nodes)
        {
            std::cout << node->to_string() << "\n";
        }
        std::cout << "==========\n\n";
    }


    // 5. Generate assembly
    
    if (parse_result.is_empty())
    {
        throw compiler_exception("Generator error: Parse result is empty");
    }

    generator generator(parse_result);
    const std::string assembly = generator.generate();

    if (log_messages)
    {
        std::cout << "Assembly code:\n----------\n";
        std::cout << assembly << "\n";
        std::cout << "==========\n\n";
    }
    
    
    // 6. Write assembly to file

    if (!assembly_out_path.empty())
    {
        std::string error;
        if (!file_writer::write_file(assembly_out_path, assembly, error))
        {
            throw compiler_exception("File writer error: " + error);
        }
        
        if (log_messages) std::cout << "Assembly file generated at " << assembly_out_path << "\n";
    }

    
    // Return compiled assembly code
    return assembly;
}
