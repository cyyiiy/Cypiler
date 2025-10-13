#pragma once
#include <string>


class file_reader
{
public:
	static bool read_file(const std::string& file_path, const std::string& extension, std::string& out);
};

