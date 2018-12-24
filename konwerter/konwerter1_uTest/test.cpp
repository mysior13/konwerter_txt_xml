#include "pch.h"
#include <stdexcept>
#include <exception>

#include <iostream>
#include <gtest/gtest.h>

#include "../konwerter1/my_functions.h"
#include "../konwerter1/file_xml.cpp"
#include "../konwerter1/file.cpp"

using namespace std;

//testy funkcji extract_extension()
TEST(ExtrExtTest, ExtractTxt) 
{
	string arg1 = "test.txt";
	string filename;
	string extension;

	EXPECT_NO_THROW(extract_extension(arg1, filename, extension));

	EXPECT_STREQ(filename.c_str(), "test");
	EXPECT_STREQ(extension.c_str(), "txt");
}

TEST(ExtrExtTest, Extract_wrong_extension) 
{
	string arg1 = "test.tx";
	string filename;
	string extension;

	EXPECT_THROW(
		{
			try 
			{
					extract_extension(arg1, filename, extension);
			}
			catch(const invalid_argument& e)
			{
				EXPECT_STREQ("Nieobslugiwane rozszerzenie pliku", e.what());
				throw;
			}
		}
	, invalid_argument);

}

TEST(ExtrExtTest, Extract_wrong_file_format)
{
	string arg1 = "testtxt";
	string filename;
	string extension;

	EXPECT_THROW(
		{
			try
			{
					extract_extension(arg1, filename, extension);
			}
			catch (const invalid_argument& e)
			{
				EXPECT_STREQ("Zly format pliku wejsciowego", e.what());
				throw;
			}
		}
	, invalid_argument);

}


//testy funkcji check_argv_number()
TEST(CheckArgvNumberTest, TwoArgument)
{
	int argv_nr = 2;

	EXPECT_NO_THROW(check_argv_number(argv_nr));
}

TEST(CheckArgvNumberTest, LessThanTwoArgument)
{
	int argv_nr = 0;

	EXPECT_THROW(
		{
			try
			{
				check_argv_number(argv_nr);
			}
			catch (const invalid_argument& e)
			{
				EXPECT_STREQ("Zbyt mala liczba argumentow", e.what());
				throw;
			}
		}
	, invalid_argument);

}

TEST(CheckArgvNumberTest, MoreThanTwoArgument)
{
	int argv_nr = 3;

	EXPECT_THROW(
		{
			try
			{
				check_argv_number(argv_nr);
			}
			catch (const invalid_argument& e)
			{
				EXPECT_STREQ("Zbyt duza liczba argumentow", e.what());
				throw;
			}
		}
	, invalid_argument);

}


//test funkcji Convert_to_txt() klasy FileXml
TEST(FileXmlTest, Conversion)
{
	FileXml f_xml;
	f_xml.text.push_back("<row>");
	f_xml.text.push_back("<col>1</col>");
	f_xml.text.push_back("<col>2</col>");
	f_xml.text.push_back("<col>3</col>");
	f_xml.text.push_back("</row>");
	f_xml.text.push_back("<row>");
	f_xml.text.push_back("<col>ala</col>");
	f_xml.text.push_back("<col>ma</col>");
	f_xml.text.push_back("<col>kota</col>");
	f_xml.text.push_back("</row>");
	vector<string> expected_output;
	expected_output.push_back("1 2 3");
	expected_output.push_back("ala ma kota");

	vector<string> output;
	f_xml.Convert_to_txt(output);

	ASSERT_EQ(2, output.size());
	for(int i=0;i<output.size();i++)
		EXPECT_STREQ(output[i].c_str(), expected_output[i].c_str());
}

//test konstruktora klasy FileXml
TEST(FileXmlTest, Constructor)
{
	vector<string> input;
	input.push_back("1 2 3");
	input.push_back("ala ma kota");
	vector<string> expected_output;
	expected_output.push_back("<row>");
	expected_output.push_back("<col>1</col>");
	expected_output.push_back("<col>2</col>");
	expected_output.push_back("<col>3</col>");
	expected_output.push_back("</row>");
	expected_output.push_back("<row>");
	expected_output.push_back("<col>ala</col>");
	expected_output.push_back("<col>ma</col>");
	expected_output.push_back("<col>kota</col>");
	expected_output.push_back("</row>");
	
	FileXml f_xml(input);

	ASSERT_EQ(10, f_xml.text.size());
	for (int i = 0;i < f_xml.text.size();i++)
		EXPECT_STREQ(f_xml.text[i].c_str(), expected_output[i].c_str());
}

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}