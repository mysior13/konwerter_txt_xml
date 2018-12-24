#include "file_xml.h"

FileXml::FileXml(const std::vector<std::string>& txt_text)
{
	for (auto i : txt_text)
	{
		text.push_back("<row>");
		std::stringstream ss(i);
		std::string item;
		while (std::getline(ss, item, ' '))
			text.push_back("<col>" + item + "</col>");
		text.push_back("</row>");
	}
}

void FileXml::Convert_to_txt(std::vector<std::string>& txt_text)
{
	rapidxml::xml_document<> doc;
	rapidxml::xml_node<> * root_node;

	std::stringstream text_stream;
	std::copy(text.begin(), text.end(), std::ostream_iterator<std::string>(text_stream, "\n"));

	std::vector<char> buffer((std::istreambuf_iterator<char>(text_stream)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');
	doc.parse<0>(&buffer[0]);
	root_node = doc.first_node("row");

	//Iteracja po rzedach
	for (rapidxml::xml_node<> * row_node = root_node; row_node; row_node = row_node->next_sibling())
	{
		std::string line;

		// Interacja po kolumnach
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
	}
}

int FileXml::Write_to_file(const std::string filename)
{
	return File::Write_to_file(filename, "xml");
}