#pragma once
#include <vector>
#include <memory>
#include <cstddef>
#include "Object_Storage.h"
namespace AST_Storage
{
	class AST_Storage
	{
	private:
		std::vector<std::unique_ptr<Object_Storage>> storage;

	public:
		AST_Storage() = default;
		virtual ~AST_Storage() = default;

		AST_Storage(const AST_Storage&) = delete;
		AST_Storage& operator=(const AST_Storage&) = delete;

		AST_Storage(AST_Storage&&) = default;
		AST_Storage& operator=(AST_Storage&&) = default;
		void addChild(std::unique_ptr<Object_Storage> child)
		{
			storage.push_back(std::move(child));
		}
		const std::vector<std::unique_ptr<Object_Storage>>& getStorage() const
		{
			return storage;
		}
		bool empty() const 
		{
			return storage.empty();
		}
		size_t size() const 
		{  
			return storage.size();
		}
	};

}
 
