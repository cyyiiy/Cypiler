#pragma once
#include <string>
#include <filesystem>


class file_reader
{
public:
	static bool read_file(const std::filesystem::path& file_path, const std::string& extension, std::string& out);
};

