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
		if (out_index != nullptr) 
		{
			*out_index = index;
		}
		if (out_unit != nullptr) 
		{
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
				if (clang_Location_isInSystemHeader(clang_getCursorLocation(current_cursor))) 
				{
					return CXChildVisit_Continue;
				} //skip headers //пропускаем заголовки
				Parse_File::Parser* parser = static_cast<Parser*>(client_data);
				AST_Storage::AST_Storage* storage = static_cast<AST_Storage::AST_Storage*>(client_data);
				 
				CXCursorKind kind = clang_getCursorKind(current_cursor);

				//parsing classes and structures //парсинг классов и структур
				if (kind == CXCursor_ClassDecl || kind == CXCursor_StructDecl) 
				{
					// 1. Getting class/structure name // 1.Получение имени класса/структуры
					std::string class_name = parser->get_name(current_cursor); 
					std::cout << class_name << std::endl; // Вместо вывода будет добавление в хранилище
					CXSourceLocation location = clang_getCursorLocation(current_cursor);
					// 2. Getting filename // Получение названия файла
					std::string file_name = parser->get_file_name(location);
					int line_number = parser->get_line_number(location);

					// 3. Checking macros// Проверка макросов
					std::vector<std::string> macros = parser->get_macros(current_cursor);

			 
					AST_Storage::Class_inf class_inf();
					return CXChildVisit_Recurse;
				}
				
			},
			& storage
		);
	}
	catch(ParserException::runtime_error)
	{
		if (unit != nullptr) 
		{
			clang_disposeTranslationUnit(unit);
		}
		if (index != nullptr) 
		{
			clang_disposeIndex(index);
		}
		throw;
	}
	if (unit != nullptr) 
	{
		clang_disposeTranslationUnit(unit);
	}
	if (index != nullptr) 
	{
		clang_disposeIndex(index);
	}
	throw;

}
//Method for getting name of the file // Метод для получения имени файла
std::string Parse_File::Parser::get_file_name(CXSourceLocation location) 
{
	CXFile file;
	unsigned line, column, offset;
	clang_getExpansionLocation(location, &file, &line, &column, &offset);

	CXString filename = clang_getFileName(file);
	std::string result = clang_getCString(filename);
	clang_disposeString(filename);

	return result;
}
//Method for getting name of an object //Метод для получения имени объекта
std::string Parse_File::Parser::get_name(CXCursor cursor)
{
	CXString cursor_name = clang_getCursorSpelling(cursor);
	std::string name = clang_getCString(cursor_name);
	clang_disposeString(cursor_name);
	return name;
}
//Method for getting number of the string// Метод для получения номера строки
int Parse_File::Parser::get_line_number(CXSourceLocation location) 
{
	CXFile file;
	unsigned line, column, offset;
	clang_getExpansionLocation(location, &file, &line, &column, &offset);
	return line;
}
//Method for getting macros // Метод для получения макроса
std::vector<std::string> Parse_File::Parser::get_macros(CXCursor cursor) 
{
	std::vector<std::string> macros;

	CXSourceRange range = clang_getCursorExtent(cursor);
	CXTranslationUnit unit = clang_Cursor_getTranslationUnit(cursor);
	CXToken* tokens = nullptr;
	unsigned num_tokens = 0;

	clang_tokenize(unit, range, &tokens, &num_tokens);

	// Аннотируем токены для идентификации макросов
	CXCursor* cursors = new CXCursor[num_tokens];
	clang_annotateTokens(unit, tokens, num_tokens, cursors);

	CXString cursor_name = clang_getCursorSpelling(cursor);
	std::string class_name = clang_getCString(cursor_name); 
	clang_disposeString(cursor_name);
	
	for (unsigned i = 0; i < num_tokens; i++) 
	{
		// Останавливаемся, когда доходим до имени класса
		CXString token_text = clang_getTokenSpelling(unit, tokens[i]);
		std::string token_str = clang_getCString(token_text);

		if (token_str == class_name) break;

		// Если это макрос - просто сохраняем его имя
		if (clang_getCursorKind(cursors[i]) == CXCursor_MacroExpansion) {
			macros.push_back(token_str);
		}

		clang_disposeString(token_text);
	}

	delete[] cursors;
	clang_disposeTokens(unit, tokens, num_tokens);

	return macros;
}
struct Inheritance_res
{

};