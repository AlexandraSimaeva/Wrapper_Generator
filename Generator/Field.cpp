#include "Field.h"
namespace AST_Storage
{
	Field::Field(std::string name, bool is_const, std::string type, std::vector <std::unique_ptr<Comment>> comments) :
		name(std::move(name)),
		is_const(std::move(is_const)),
		type(std::move(type)),
		comments(std::move(comments)){ }
	void Field::Add_Object(std::unique_ptr<Object_Storage> object, Type_Object type_obj)
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
        }
		 
	}
}