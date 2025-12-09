#pragma once
#include <vector>
#include <string>
#include "Method.h"
#include "Destructor.h"
#include "Constructor.h"
namespace AST_Storage
{
	class Class_inf: public Object_Storage
	{
		protected:
			std::vector<std::unique_ptr<Method>> methods;
			std::vector<std::unique_ptr<Field>> fields;
			std::vector<std::unique_ptr<Constructor>> constructors;
			std::vector<std::unique_ptr<Class_inf>> inside_classtructs;
			std::string macros;
			std::string way_file;
			std::vector<std::unique_ptr<Comment>> comments;
		public:
			Class_inf(std::vector<std::unique_ptr<Method>> methods,
				std::vector<std::unique_ptr<Field>> fields, std::vector<std::unique_ptr<Constructor>> constructors,
				std::vector<std::unique_ptr<Class_inf>> inside_classtructs, std::string macros,
				std::string way_file, std::vector<std::unique_ptr<Comment>> comments);
			virtual ~Class_inf(){}
			void Add_Object(std::unique_ptr<Object_Storage>, Type_Object type_obj) override;
		 
	};
	class Class_inf_inherited: public Class_inf
	{
		private:
			std::string key_protect;
			std::string Inheritance_from;
		public:
			Class_inf_inherited(std::vector<std::unique_ptr<Method>> methods,
				std::vector<std::unique_ptr<Field>> fields, std::vector<std::unique_ptr<Constructor>> constructors,
				std::vector<std::unique_ptr<Class_inf>> inside_classtructs, std::string macros,
				std::string way_file, std::vector<std::unique_ptr<Comment>> comments, 
				std::string key_protect, std::string Inheritance_from);
	};
		 
	 
	 
	 
 
}
 
 
