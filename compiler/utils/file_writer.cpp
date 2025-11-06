#include "file_writer.h"
#include <fstream>


bool file_writer::write_file(const std::filesystem::path& file_path, const std::string& content, std::string& out)
{
	std::ofstream file(file_path);
	if (!file)
	{
		out = "Unable to create/edit the file!";
		return false;
	}

	file << content;

	return true;
}
