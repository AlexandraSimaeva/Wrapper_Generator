#include "Comment.h"
namespace AST_Storage
{
	 

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
	void Comment_long::Add_Object(std::unique_ptr<Object_Storage>, Type_Object type_obj)
	{

	}

	Comment_short::Comment_short(std::string text_comment, int num_string, bool before, bool after, std::string path_file)
		: text_comment(std::move(text_comment)),
		num_string(num_string),
		is_smth_before(before),
		is_smth_after(after),
		path_file(std::move(path_file))
	{}
	void Comment_short::Add_Object(std::unique_ptr<Object_Storage>, Type_Object type_obj)
	{

	}
 
}