#include "Comment.h"
namespace AST_Storage
{
	 
	Comment_long::Comment_long(const Comment_long& other) : Comment(other),  
		comment_num_string(other.comment_num_string),
		path_file(other.path_file),
		is_smth_before(other.is_smth_before),
		is_smth_after(other.is_smth_after),
		text_comment(other.text_comment),
		num_starts(other.num_starts),
		num_ends(other.num_ends)
	{
	}

	Comment_long::Comment_long(std::map<int, std::string> comment, bool before, bool after, std::string path_fl)  
	{
		if (comment.empty()) {
			throw EmptyCommentError();
		}

		comment_num_string = comment;
		is_smth_before = before;
		is_smth_after = after;
		path_file = path_fl;
		num_starts = comment.begin()->first;
		num_ends = comment.rbegin()->first;
		text_comment = "";
		for (const auto& pair : comment_num_string) {
			int current_line = pair.first;   
			std::string text = pair.second;

			text_comment += text;
 
			if (current_line != comment_num_string.rbegin()->first) {
				text_comment += "\n";
			}
		}
		if (text_comment.empty()) {
			throw EmptyCommentError();
		}
		validate_construction_data();
	}

	Comment_short::Comment_short(std::string text_comment, int num_string, bool before, bool after, std::string path_file)
		: text_comment(std::move(text_comment)),
		num_string(num_string),
		is_smth_before(before),
		is_smth_after(after),
		path_file(std::move(path_file)){}
	Comment_short::Comment_short(const Comment_short& other)
		: Comment(other),  
		num_string(other.num_string),
		text_comment(other.text_comment),
		path_file(other.path_file),
		is_smth_before(other.is_smth_before),
		is_smth_after(other.is_smth_after)
	{
		if (this->text_comment.empty()) {
			throw EmptyCommentError();
		}

		// Проверка валидности номера строки
		if (this->num_string < 0) {
			throw InvalidLineNumber(this->num_string);
		}

		// Проверка пустого пути к файлу
		if (this->path_file.empty()) {
			throw FilePathError("Path file is empty");
		}

		// Дополнительная проверка формата комментария
		if (this->text_comment.find("//") != 0) {
			throw InvalidCommentFormat("Short comment must start with '//'");
		}

		// Проверка на наличие только одной строки
		if (this->text_comment.find('\n') != std::string::npos) {
			throw InvalidCommentFormat("Short comment cannot contain newlines");
		}
		validate_construction_data();
	}
}