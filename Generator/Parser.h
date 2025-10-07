#pragma once
#include <iostream>
#include <clang-c/Index.h>
#include <fstream>
#include <sstream>
#include "Parser_Exception.h"
#include "AST_Storage.h"
namespace Parse_File
{
	class Parser
	{
	private:
		AST_Storage::AST_Storage& storage;
		bool check_open(const std::string& path_file, CXIndex* out_index = nullptr,
			CXTranslationUnit* out_unit = nullptr);// checks opening file // Проверяет открытие файла
		 
	public:
		Parser(AST_Storage::AST_Storage & storage_object);
		void Parse(const std::string& path_file);//main function for parsing file // Главный метод для парсинга
	};

}
 
