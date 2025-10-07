#pragma once
//#include "Parser.h"
#include <stdexcept>
#include <string>
namespace Parse_File
{
    class ParserException : public std::runtime_error { //Base exc // Базовое исключение 
    public:
        explicit ParserException(const std::string& message)
            : std::runtime_error(message) {}
    };

    class FileOpenException : public ParserException { // For not openning file // Для ситуации, когда не открывается файл
    private:
        std::string file_path_;
        std::string system_error_;

    public:
        FileOpenException(const std::string& file_path, const std::string& system_error = "")
            : ParserException("Failed to open file: " + file_path +
                (system_error.empty() ? "" : " - " + system_error)),
            file_path_(file_path), system_error_(system_error) {
        }

        const std::string& get_file_path() const { return file_path_; }
        const std::string& get_system_error() const { return system_error_; }
    };
}
 