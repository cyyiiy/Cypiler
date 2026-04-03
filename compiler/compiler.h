#pragma once
#include <string>
#include <filesystem>

class compiler
{
public:
    explicit compiler(std::filesystem::path source_code_path);
    ~compiler() = default;

    compiler(const compiler& other) = delete;
    compiler(compiler&& other) = delete;
    compiler& operator=(const compiler& other) = delete;
    compiler& operator=(compiler&& other) = delete;

    /** Compiles the source code into linux 64-bit assembly.
     * 
     * @param assembly_out_path The path of the file to write the assembly result in. Won't write if the path is empty.
     * @param log_messages Set to false to disable log messages during the compilation process.
     * @return The assembly code, whether it has been written in an assembly file or not.
     */
    std::string compile(const std::filesystem::path& assembly_out_path, bool log_messages = true);
    
private:
    std::filesystem::path m_source_code_path;
};
