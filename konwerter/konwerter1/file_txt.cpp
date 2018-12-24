#include "file_txt.h"

FileTxt::FileTxt(const std::vector<std::string> &text)
{
	for (auto i : text)
		this->text.push_back(i);
}

int FileTxt::Write_to_file(const std::string filename)
{
	return File::Write_to_file(filename, "txt");
}