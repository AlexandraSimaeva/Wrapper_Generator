#include "Class_inf.h"
namespace AST_Storage {
    Class_inf::Class_inf(std::vector<Method> methods,
        std::vector<Field> fields,
        std::string macros,
        std::string way_file,
        std::vector<std::unique_ptr<Comment>> comments)
        : methods(std::move(methods)),
        fields(std::move(fields)),
        macros(std::move(macros)),
        way_file(std::move(way_file)),
        comments(std::move(comments)) {
    }
 
}
