#pragma once
#include "Object_Storage.h"
#include "Comment.h"
namespace AST_Storage
{ 
	class Field:public Object_Storage
	{
	private:
		std::string name;
		bool is_const;
		std::string type;
		std::vector <std::unique_ptr<Comment>> comments;
	public:
		Field(std::string name, bool is_const, std::string type, std::vector <std::unique_ptr<Comment>> comments);
		void Add_Object(std::unique_ptr<Object_Storage>, Type_Object type_obj) override;
	};
}
