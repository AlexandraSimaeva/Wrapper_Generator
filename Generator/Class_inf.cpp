#include "Class_inf.h"
namespace AST_Storage {
    Class_inf::Class_inf(std::vector<std::unique_ptr<Method>> methods,
        std::vector<std::unique_ptr<Field>> fields, std::vector<std::unique_ptr<Constructor>> constructors,
        std::vector<std::unique_ptr<Class_inf>> inside_classtructs, std::string macros,
        std::string way_file, std::vector<std::unique_ptr<Comment>> comments)
        : methods(std::move(methods)),
        constructors(std::move(constructors)),
        inside_classtructs(std::move(inside_classtructs)),
        fields(std::move(fields)),
        macros(std::move(macros)),
        way_file(std::move(way_file)),
        comments(std::move(comments))
    {
    }
    Class_inf_inherited::Class_inf_inherited(
        std::vector<std::unique_ptr<Method>> methods,
        std::vector<std::unique_ptr<Field>> fields, std::vector<std::unique_ptr<Constructor>> constructors,
        std::vector<std::unique_ptr<Class_inf>> inside_classtructs, std::string macros,
        std::string way_file, std::vector<std::unique_ptr<Comment>> comments,
        std::string key_protect, std::string Inheritance_from)
        : Class_inf(std::move(methods),
            std::move(fields),
            std::move(constructors),
            std::move(inside_classtructs),
            std::move(macros),
            std::move(way_file),
            std::move(comments)),
        key_protect(std::move(key_protect)),
        Inheritance_from(std::move(Inheritance_from))
    {
    }
    void Class_inf::Add_Object(std::unique_ptr<Object_Storage> object, Type_Object type_obj)
    {
        if (!object) {
            throw std::invalid_argument("Null object passed to Add_Object");
        }
        //В будующем чекнуть на наличие проблем с утечкой памяти, ибо при неудачном привидении указатель потеряется)
        switch (type_obj)
        {
            case Type_Object::Class_obj:
            {
                std::unique_ptr<Class_inf> class_obj(dynamic_cast<Class_inf*>(object.release()));
                if (class_obj != nullptr) {
                    inside_classtructs.push_back(std::move(class_obj));
                }
                else {
                    throw std::invalid_argument("Object is not of type Class_inf");
                }
                break;
            }
            case Type_Object::Method_obj:
            {
                std::unique_ptr<Method> meth_obj(dynamic_cast<Method*>(object.release()));
                if (meth_obj != nullptr) {
                    methods.push_back(std::move(meth_obj));
                }
                else {
                    throw std::invalid_argument("Object is not of type Method");
                }
                break;
            }
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
                if( field_obj != nullptr) {
                    fields.push_back(std::move(field_obj));
                }
                else {
                    throw std::invalid_argument("Object is not of type Field");
                }
                break;
            }
            case Type_Object::Constructor_obj:
            {
                std::unique_ptr<Constructor> constr_obj(dynamic_cast<Constructor*>(object.release()));
                if (constr_obj != nullptr) {
                    constructors.push_back(std::move(constr_obj));
                }
                else {
                    throw std::invalid_argument("Object is not of type Constructor");
                }
                break;
            }
            default:
            {
                throw std::invalid_argument("invalid type");
            }

        }
    }
 
}
