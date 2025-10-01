#pragma once
#include <stdexcept>
#include <string>
#include <map>

namespace AST_Storage {

    class CommentException : public std::runtime_error {
    public:
        explicit CommentException(const std::string& message)
            : std::runtime_error(message) {}
    };

    class InvalidCommentFormat : public CommentException {
    public:
        InvalidCommentFormat(const std::string& comment)
            : CommentException("Invalid comment format: " + comment) {
        }

        InvalidCommentFormat(const std::map<int, std::string>& comment_data)
            : CommentException("Invalid multi-line comment format") {
        }
    };

    class CommentNotFound : public CommentException {
    public:
        CommentNotFound(int line_num)
            : CommentException("Comment not found at line: " + std::to_string(line_num)) {
        }
    };

    class DuplicateComment : public CommentException {
    public:
        DuplicateComment(int line_num)
            : CommentException("Duplicate comment at line: " + std::to_string(line_num)) {
        }
    };

    class EmptyCommentError : public CommentException {
    public:
        EmptyCommentError()
            : CommentException("Comment text cannot be empty") {
        }
    };

    class InvalidLineNumber : public CommentException {
    public:
        InvalidLineNumber(int line_num)
            : CommentException("Invalid line number: " + std::to_string(line_num)) {
        }
    };

    class FilePathError : public CommentException {
    public:
        FilePathError(const std::string& file_path)
            : CommentException("Invalid file path: " + file_path) {
        }
    };

}  
