#pragma once
#include "file.h"
#include "rapidxml.hpp"
#include <sstream>
#include <iterator>

//Klasa przechowujaca zawartosc pliku xml
class FileXml : public File
{
	friend class FileXmlTest_Conversion_Test;
	friend class FileXmlTest_Constructor_Test;
public:
	FileXml() = default;
	FileXml(const std::vector<std::string>& txt_text);
	~FileXml() = default;

	void Convert_to_txt(std::vector<std::string>& txt_text); //funkcja konwertuje tresc pliku xml do formatu txt
	int Write_to_file(const std::string filename);	//zapis zawartosci pola text do pliku
};