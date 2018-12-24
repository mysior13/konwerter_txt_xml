#include<iostream>
#include<string>
#include <fstream>
#include<vector>
#include<sstream>
#include <iterator>
#include"rapidxml.hpp"

class File;
class File_txt;
class File_xml;


//??write_to_file w file a z pochodnych tylko rozszerzenie
class File
{
public:
	File() {};
	~File() {};

	virtual int Read_file(std::string filename)
	{
		std::ifstream txt_file(filename);

		std::string line;
		if (txt_file.is_open())
		{
			while (std::getline(txt_file, line))
			{
				text.push_back(line);
			}
			txt_file.close();
		}

		else
		{
			std::cout << "Unable to open file\n";
			return 1;
		}
		return 0;
	}
	virtual void Display() const
	{
		std::cout << "File display" << std::endl;
		for (auto i : text)
		{
			std::cout << i << '\n';
		}
	};
	/*virtual void Write_to_file(std::string filename)
	{
		std::cout << "Write_to_file base class\n";
	}*/
	virtual void Write_to_file(std::string filename, std::string extension) const
	{
		std::ofstream file;
		file.open(filename + "." + extension);
		for (auto i : text)
		{
			file << i << '\n';
		}

		file.close();
	}
	const std::vector<std::string>& get_text() const 
	{
		return text;
	};

protected:
	std::vector<std::string> text;
};

class File_txt : public File
{
public:
	File_txt() {};
	File_txt(const std::vector<std::string> &text)
	{
		for (auto i : text)
			this->text.push_back(i);
	}
	~File_txt() {};

	void Write_to_file(std::string filename)
	{
		File::Write_to_file(filename, "txt");
	}
};


class File_xml: public File
{
public:
	File_xml() {};
	File_xml(const std::vector<std::string>& txt_text)
	{
		for (auto i : txt_text)
		{
			text.push_back("<row>");
			std::stringstream ss(i);
			std::string item;
			while (std::getline(ss, item, ' '))
			{
				text.push_back("<col>"+item+"</col>");
			}
			text.push_back("</row>");
		}
	}
	~File_xml() {};

	void convert_to_txt(std::vector<std::string>& txt_text)
	{
		//nie ma takiego pliku - dodac

		rapidxml::xml_document<> doc;
		rapidxml::xml_node<> * root_node;
		// Read the xml file into a vector
		//std::ifstream theFile(filename);
		std::stringstream text_stream;
		std::copy(text.begin(), text.end(), std::ostream_iterator<std::string>(text_stream, "\n"));


		std::vector<char> buffer((std::istreambuf_iterator<char>(text_stream)), std::istreambuf_iterator<char>());
		buffer.push_back('\0');
		// Parse the buffer using the xml file parsing library into doc 
		doc.parse<0>(&buffer[0]);
		// Find our root node
		root_node = doc.first_node("row");
		// Iterate over the rows

		for (rapidxml::xml_node<> * row_node = root_node; row_node; row_node = row_node->next_sibling())
		{
			std::string line;
			// Interate over the columns

			if (rapidxml::xml_node<> *column_node = row_node->first_node("col"))
			{
				line += column_node->value();
				for (column_node = column_node->next_sibling(); column_node; column_node = column_node->next_sibling())
				{
					line += ' ';
					line += column_node->value();
				}

			}
			txt_text.push_back(line);
			//std::cout << '\n';
		}
	}
	void Write_to_file(std::string filename)
	{
		File::Write_to_file(filename, "xml");
	}
};

int check_argv_number(int argc)
{
	//sprawdzenie liczby arg wejsciowych
	if (argc < 2)
	{
		std::cerr << "Zbyt mala liczba argumentow\n";
		return 1;
	}
	if (argc > 2)
	{
		std::cerr << "Zbyt duza liczba argumentow\n";
		return 2;
	}
	return 0;
}


int main(int argc, char *argv[])
{
	if (check_argv_number(argc))
		return 1;

	std::string arg1(argv[1]);
	//std::string arg1("konwerter.xml");

	//wydzielenie rozszerzenia pliku
	int i_dot;

	for (i_dot = arg1.size() - 1; i_dot > 0; i_dot--)
	{
		if (arg1[i_dot] == '.')break;
	}

	if (i_dot == 0)
	{
		std::cerr << "Zly format pliku wejsciowego\n";
		return 1;
	}

	std::string filename(arg1,0, i_dot );
	std::string primary_file_extension(arg1, i_dot + 1);

	//std::cout << "filename = " << filename << '\n';
	//std::cout << "primary_file_extension = " << primary_file_extension << '\n';

	
	if (primary_file_extension != "txt" && primary_file_extension != "xml")
	{
		std::cerr << "Nieobslugiwane rozszerzenie pliku\n";
		return 1;
	}

	//std::string secondary_file_extension = (primary_file_extension == "txt") ? "xml" : "txt";

	//File *primary_file;
	//File *secondary_file;
	if (primary_file_extension == "txt")
	{
		File_txt primary_file = File_txt();
		if (primary_file.Read_file(arg1))
			return 1;
		File_xml secondary_file = File_xml(primary_file.get_text());
		secondary_file.Write_to_file(filename);
		std::cout << "Przekonwertowano plik z formatu txt do xml\n";
	}

	else
	{
		File_xml primary_file = File_xml();
		if (primary_file.Read_file(arg1))
			return 1;

		std::vector<std::string> converted;
		primary_file.convert_to_txt(converted);
		File_txt secondary_file = File_txt(converted);
		secondary_file.Write_to_file(filename);
		std::cout << "Przekonwertowano plik z formatu xml do txt\n";
	}
	
	getchar();
	return 0;
}