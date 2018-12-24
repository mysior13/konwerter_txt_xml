#pragma once
#include <vector>
#include <stdexcept>
#include <exception>

void check_argv_number(int argc)
{
	//sprawdzenie liczby arg wejsciowych
	if (argc < 2)
	{
		throw std::invalid_argument("Zbyt mala liczba argumentow");
	}
	if (argc > 2)
	{
		throw std::invalid_argument("Zbyt duza liczba argumentow");
	}
}

//wydzielenie rozszerzenia pliku
void extract_extension(std::string arg1, std::string& filename, std::string& extension)
{
	int i_dot;

	for (i_dot = arg1.size() - 1; i_dot > 0; i_dot--)
	{
		if (arg1[i_dot] == '.')break;
	}

	if (i_dot == 0)
	{
		throw std::invalid_argument("Zly format pliku wejsciowego");
	}

	filename = std::string(arg1, 0, i_dot);
	extension = std::string(arg1, i_dot + 1);
	if (extension != "txt" && extension != "xml")
	{
		throw std::invalid_argument("Nieobslugiwane rozszerzenie pliku");
	}
}
