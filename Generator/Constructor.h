#pragma once
#include "Object_Storage.h"
#include "Field.h"
namespace AST_Storage
{
	class Constructor: public Object_Storage
	{
	private:
		std::string name;
		std::vector<std::unique_ptr<Comment>> comments;
		std::vector<std::unique_ptr<Field>> arguments;
	public:
		Constructor(std::string name, std::vector<std::unique_ptr<Field>> arguments, std::vector<std::unique_ptr<Comment>> comments);
		void Add_Object(std::unique_ptr<Object_Storage>, Type_Object type_obj) override;
	};
}
