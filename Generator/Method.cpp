#include "Method.h"
namespace AST_Storage
{
	Method::Method(std::string name, std::string return_type, bool is_override, bool is_virtual,
        std::vector<std::unique_ptr<Field>> arguments, std::vector<std::unique_ptr<Comment>> comments) :
		name(std::move(name)),
		return_type(std::move(return_type)),
		is_override(std::move(is_override)),
		is_virtual(std::move(is_virtual)),
		arguments(std::move(arguments)),
		comments(std::move(comments)) 
	{
	}
	void Method::Add_Object(std::unique_ptr<Object_Storage> object, Type_Object type_obj)
	{
        if (!object) {
            throw std::invalid_argument("Null object passed to Add_Object");
        }
        switch (type_obj)
        {
         
            case Type_Object::Comment_obj:
            {
                std::unique_ptr<Comment> comment_obj(dynamic_cast<Comment*>(object.release()));
                if (comment_obj != nullptr) {
                    comments.push_back(std::move(comment_obj)); // тута костыль, случае последующего использования object все полетит далеко и надолго
                }
                else {
                    throw std::invalid_argument("Object is not of type Comment");
                }
                break;
            }
            case Type_Object::Field_obj:
            {
                std::unique_ptr<Field> field_obj(dynamic_cast<Field*>(object.release()));
                if (field_obj != nullptr) {
                    arguments.push_back(std::move(field_obj));
                }
                else {
                    throw std::invalid_argument("Object is not of type Field");
                }
                break;
            }

        }
	}
}