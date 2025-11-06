#pragma once
#include <string>
#include <filesystem>


class file_writer
{
public:
	static bool write_file(const std::filesystem::path& file_path, const std::string& content, std::string& out);
};

