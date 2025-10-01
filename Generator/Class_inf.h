#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Comment.h"
#include "Method.h"
#include "Field.h"
#include "Constructor.h"
#include "Destructor.h"
namespace AST_Storage
{
	class Class_inf
	{
		private:
			std::vector<Method> methods;
			std::vector<Field>  fields;
			std::string macros;
			std::string way_file;
			std::vector<std::unique_ptr<Comment>> comments;
		public:
			Class_inf(std::vector<Method> methods, 
				std::vector<Field>  fields, std::string macros, 
				std::string way_file, std::vector<std::unique_ptr<Comment>> comments);
		 
	};
	class Class_inf_inherited: public Class_inf
	{
		private:
			std::string key_protect;
			Class_inf& Inheritance_from;
		public:

	};
		 
	 
	 
	 
 
}
 
 
