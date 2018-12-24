#include "file.h"

int File::Read_file(const std::string filename_incl_ext)
{
	std::ifstream file(filename_incl_ext);

	if ((file.rdstate() & std::ifstream::failbit) != 0)
	{
		std::cerr << "Nie mozna otworzyc pliku " << filename_incl_ext << '\n';
		return 1;
	}
	
	std::string line;
	while (std::getline(file, line))
		text.push_back(line);
	return 0;
}

void File::Display() const
{
	std::cout << "File display" << std::endl;
	for (auto i : text)
		std::cout << i << '\n';
};

int File::Write_to_file(const std::string filename, const std::string extension) const
{
	std::ofstream file;
	try
	{
		file.open(filename + "." + extension);
		for (auto i : text)
			file << i << '\n';
		file.close();
	}
	catch (const std::ofstream::failure& e)
	{
		std::cerr << "Nie mozna zapisac pliku" << e.what() << '\n';
		return 1;
	}
	return 0;
}

const std::vector<std::string>& File::get_text() const
{
	return text;
};
