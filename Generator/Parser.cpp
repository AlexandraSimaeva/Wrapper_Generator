#include "Parser.h"
bool Parse_File::Parser::check_open(const std::string& path_file, CXIndex* out_index,
	CXTranslationUnit* out_unit)
{
	CXIndex index = clang_createIndex(0, 0);
	CXTranslationUnit unit = clang_parseTranslationUnit(
		index,
		path_file.c_str(), nullptr, 0,
		nullptr, 0,
		CXTranslationUnit_None);

	if (unit == nullptr) {
		std::cerr << "Unable to parse translation unit. Quitting.\n";
		clang_disposeIndex(index);
		return false;
	}
	else
	{
		if (out_index != nullptr) {
			*out_index = index;
		}
		if (out_unit != nullptr) {
			*out_unit = unit;
		}
		std::cerr << "File is open.\n";
		return true;
	}
}
Parse_File::Parser::Parser(AST_Storage::AST_Storage& storage_object) : storage(storage_object)// Пока конструктор пустой в дальнейшем там будут параметры парсинга
{
}
void Parse_File::Parser::Parse(const std::string& path_file)//main function for parsing file // Главный метод для парсинга
{
	CXIndex index = nullptr;
	CXTranslationUnit unit = nullptr;
	bool res_check = check_open(path_file, &index, &unit);
	if(!res_check)
	{
		throw Parse_File::FileOpenException(path_file, "Cannot open file");
	}
	// in case of successful openning file index and unit get the results of parsing 
	//  В случае успешного открытия файла index и unit получают результаты парсинга
	CXCursor cursor = clang_getTranslationUnitCursor(unit);
	try
	{
		clang_visitChildren(
			cursor,
			[](CXCursor current_cursor, CXCursor parent, CXClientData client_data)
			{
				if (clang_Location_isInSystemHeader(clang_getCursorLocation(current_cursor))) {
					return CXChildVisit_Continue;
				} //skip headers //пропускаем заголовки
				AST_Storage::AST_Storage* storage = static_cast<AST_Storage::AST_Storage*>(client_data);
				return CXChildVisit_Recurse;
				CXCursorKind kind = clang_getCursorKind(current_cursor);

				//main 
				if (kind == CXCursor_ClassDecl || kind == CXCursor_StructDecl) {
					CXString cursor_name = clang_getCursorSpelling(current_cursor);
					std::string class_name = clang_getCString(cursor_name);
					clang_disposeString(cursor_name);
					std::cout << class_name << std::endl; // Вместо вывода будет добавление в хранилище

				}
			},
			& storage
		);
	}
	catch(ParserException::runtime_error)
	{
		if (unit != nullptr) {
			clang_disposeTranslationUnit(unit);
		}
		if (index != nullptr) {
			clang_disposeIndex(index);
		}
		throw;
	}
	if (unit != nullptr) {
		clang_disposeTranslationUnit(unit);
	}
	if (index != nullptr) {
		clang_disposeIndex(index);
	}
	throw;
}