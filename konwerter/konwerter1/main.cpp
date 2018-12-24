#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <iterator>
#include <exception>
#include "file_txt.h"
#include "file_xml.h"
#include "my_functions.h"


int main(int argc, char *argv[])
{
	try 
	{
		check_argv_number(argc);
	}
	catch (const std::invalid_argument& e) {
		std::cerr << e.what()<<'\n';
		return 1;
	}

	std::string arg1(argv[1]);
	std::string filename;
	std::string primary_file_extension;
	
	try
	{
		extract_extension(arg1, filename, primary_file_extension);
	}
	catch (const std::invalid_argument& e) {
		std::cerr << e.what() << '\n';
		return 1;
	}

	if (primary_file_extension == "txt")
	{
		FileTxt primary_file;
		if (primary_file.Read_file(arg1))
			return 1;
		FileXml secondary_file = FileXml(primary_file.get_text());
		secondary_file.Write_to_file(filename);
		std::cout << "Przekonwertowano plik z formatu txt do xml\n";
	}

	else
	{
		FileXml primary_file;
		if (primary_file.Read_file(arg1))
			return 1;

		std::vector<std::string> converted;
		primary_file.Convert_to_txt(converted);
		FileTxt secondary_file = FileTxt(converted);
		if (secondary_file.Write_to_file(filename))
			return 1;
		std::cout << "Przekonwertowano plik z formatu xml do txt\n";
	}
	
	return 0;
}