#include "file_reader.h"
#include <fstream>
#include <sstream>


bool file_reader::read_file(const std::filesystem::path& file_path, const std::string& extension, std::string& out)
{
	if (!std::filesystem::exists(file_path))
	{
		out = "Given path doesn't exists!";
		return false;
	}
	
	if (!std::filesystem::is_regular_file(file_path))
	{
		out = "Given path does not point to a file!";
		return false;
	}

	if (file_path.extension() != extension)
	{
		out = "File extension is not " + extension + "!";
		return false;
	}

	std::ifstream file(file_path);
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
