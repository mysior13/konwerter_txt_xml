#pragma once
#include "file.h"

//Klasa przechowujaca zawartosc pliku txt
class FileTxt : public File
{
public:
	FileTxt() = default;
	FileTxt(const std::vector<std::string> &text);
	~FileTxt() = default;

	int Write_to_file(const std::string filename);	//zapis zawartosci pola text do pliku
};