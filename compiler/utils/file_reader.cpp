#include "file_reader.h"
#include <filesystem>
#include <fstream>
#include <sstream>


bool file_reader::read_file(const std::string& file_path, const std::string& extension, std::string& out)
{
	std::filesystem::path path(file_path);

	if (!std::filesystem::exists(path))
	{
		out = "Given path doesn't exists!";
		return false;
	}
	
	if (!std::filesystem::is_regular_file(path))
	{
		out = "Given path does not point to a file!";
		return false;
	}

	if (path.extension() != extension)
	{
		out = "File extension is not " + extension + "!";
		return false;
	}

	std::ifstream file(path);
	if (!file)
	{
		out = "Unable to open the file!";
		return false;
	}

	std::ostringstream buffer;
	buffer << file.rdbuf();
	out = buffer.str();

	return true;
}
