#pragma once
#include <vector>
#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include "CommentExceptions.h"
namespace AST_Storage
{
	class Comment
	{
	protected:
		Comment() = default; // protected constructor
		Comment(const Comment& other) = default;//constructor copy
	public:
		virtual ~Comment() = default; //destructor
		virtual Comment* clone() const = 0; //method copy
		virtual const std::string return_comment_text() = 0; // return text of the comment
		virtual const std::string return_path_file() = 0;
		virtual const int return_num_start() = 0; // return start number
		virtual const int return_num_end() = 0; // return end number
		virtual  void validate_construction_data() const = 0;
	};
	class Comment_long : public Comment //Comments start from "/*"
	{
	private:
		Comment_long(const Comment_long& other);//constructor copy
		std::map<int, std::string>  comment_num_string; // text comment
		std::string path_file = "";
		bool is_smth_before = false; // position flag
		bool is_smth_after = false; // position flag
		std::string text_comment = "";// text comment
		int num_starts = -1;
		int num_ends = -1;
	public:
		~Comment_long() override {}
		Comment* clone() const override { return new Comment_long(*this); }
		Comment_long(std::map<int, std::string> comment, bool before, bool after, std::string path_file); // Constructor base
		const std::string return_comment_text() override
		{ 
			if (text_comment.empty()) {
				throw EmptyCommentError();
			}
			return text_comment; 
		}
		const std::string return_path_file() override 
		{ 
			if (path_file.empty()) {
				throw FilePathError("Path file is empty");
			}
			return path_file; 
		}
		const int return_num_start() override 
		{   
			if (num_starts < 0) {
				throw InvalidLineNumber(num_starts);
			}
			return num_starts; 
		} // return start number
		const int return_num_end() override 
		{   
			if (num_ends < 0) {
				throw InvalidLineNumber(num_starts);
			}
			return num_ends; 
		} // return end number
		void validate_construction_data() const override {
			if (comment_num_string.empty()) {
				throw EmptyCommentError();
			}
			if (num_starts < 0 || num_ends < 0 || num_starts > num_ends) {
				throw InvalidLineNumber(num_starts);
			}
			if (path_file.empty()) {
				throw FilePathError("Empty file path");
			}
		}


	};
	class Comment_short : public Comment //Comments start from "//"
	{
	private:
		int num_string = -1;
		std::string text_comment = "";// text comment
		Comment_short(const Comment_short& other); //constructor copy
		std::string path_file = "";
		bool is_smth_before = false; // position flag
		bool is_smth_after = false; // position flag
	public:
		~Comment_short() override {}
		Comment* clone() const override { return new Comment_short(*this); }
		Comment_short(std::string text_comment, int num_string, bool before, bool after, std::string path_file);// Constructor base 
		const std::string return_comment_text() override 
		{ 
			if (text_comment.empty()) {
				throw EmptyCommentError();
			}
			return text_comment; 
		}
		const std::string return_path_file() override 
		{ 
			if (path_file.empty()) {
				throw FilePathError("Path file is empty");
			}
			return path_file; 
		}
		const int return_num_start() override 
		{ 
			if (num_string < 0) {
				throw InvalidLineNumber(num_string);
			}
			return num_string; 
		} // return start number
		const int return_num_end() override 
		{ 
			if (num_string < 0) {
				throw InvalidLineNumber(num_string);
			}
			return num_string; 
		} // return end number
		void validate_construction_data() const override {
			if (text_comment.empty()) {
				throw EmptyCommentError();
			}
			if (num_string < 0 ) {
				throw InvalidLineNumber(num_string);
			}
			if (path_file.empty()) {
				throw FilePathError("Empty file path");
			}
		}
	};


}