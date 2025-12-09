#pragma once
#include <memory>
namespace AST_Storage
{
	enum class Type_Object { Class_obj, Method_obj, Comment_obj, Field_obj, Constructor_obj };
	enum class Type_Key { Private, Protected, Public, Free };
	class Object_Storage
	{
	public:
		virtual ~Object_Storage() = default;
		Object_Storage() = default;

		Object_Storage(const Object_Storage&) = delete;
		Object_Storage& operator=(const Object_Storage&) = delete;

		Object_Storage(Object_Storage&&) = default;
		Object_Storage& operator=(Object_Storage&&) = default;

		virtual void Add_Object(std::unique_ptr<Object_Storage>, Type_Object type_obj) {};
	};
 
}
 

