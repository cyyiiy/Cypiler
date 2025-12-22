#pragma once
#include <string>
#include <optional>

class precompiler
{
public:
    explicit precompiler(std::string source);
    ~precompiler() = default;
    
    precompiler(const precompiler& other) = delete;
    precompiler(precompiler&& other) = delete;
    precompiler& operator=(const precompiler&) = delete;
    precompiler& operator=(precompiler&&) = delete;
    
    [[nodiscard]] std::string precompile();
    
private:
    [[nodiscard]] std::optional<char> peek_char() const;
    char consume_char();
    
    void skip_line();
    
    
    const std::string m_source;
    size_t m_read_index{ 0 };
    
    std::string m_precompiled;
};
