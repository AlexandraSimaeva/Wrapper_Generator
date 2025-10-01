// Exeptions for project
#pragma once
#include <stdexcept>
#include <string>

namespace AST_Storage {

    class AST_Exception : public std::runtime_error {
    public:
        explicit AST_Exception(const std::string& message,
            const std::string& file = "",
            int line = 0)
            : std::runtime_error(format_message(message, file, line)),
            file_(file), line_(line) {
        }

        const std::string& get_file() const { return file_; }
        int get_line() const { return line_; }

    private:
        std::string file_;
        int line_;

        static std::string format_message(const std::string& msg,
            const std::string& file,
            int line) {
            if (file.empty()) return msg;
            return file + ":" + std::to_string(line) + ": " + msg;
        }
    };
}