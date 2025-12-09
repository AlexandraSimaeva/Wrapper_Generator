#pragma once
#include "Object_Storage.h"
#include "Comment.h"
#include "Field.h"
namespace AST_Storage
{
	class Method:public Object_Storage
	{
	private:
		std::string name;
		std::string return_type;
		std::vector<std::unique_ptr<Field>> arguments;
		bool is_override;
		bool is_virtual;
		std::vector<std::unique_ptr<Comment>> comments;
		//bool is_const;
	public:
		Method(std::string name, std::string return_type, bool is_override, bool is_virtual,
			std::vector<std::unique_ptr<Field>> arguments, std::vector<std::unique_ptr<Comment>> comments);
		void Add_Object(std::unique_ptr<Object_Storage>, Type_Object type_obj) override;
	};

	 
}
 
 