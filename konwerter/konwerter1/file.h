#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>


class File
{
public:
	File() = default;
	~File() = default;

	virtual int Read_file(const std::string filename_incl_ext);	//funkcja odczytuje zawartosc okreslonego pliku i przypisanie jego zawartosci do pola text
	virtual void Display() const;	//funkcja wyswietla zawartosc pola text
	virtual int Write_to_file(const std::string filename, const std::string extension) const;	//zapis zawartosci pola text do pliku
	const std::vector<std::string>& get_text() const;	//referencja na pole text

protected:
	std::vector<std::string> text;	//pole przechowujace zawartosc pliku
};