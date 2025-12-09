#include "pch.h"
#include "C:\Users\adsim\for work and studing\projects\Wrapper_Generator\Generator\Comment.cpp"
#include <map>
#include <string>
#include <climits>

using namespace AST_Storage;
class CommentTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Valid test data
        valid_long_comment_data = {
            {5, "/* Start of comment"},
            {6, " * Middle line"},
            {7, " */"}
        };

        valid_short_comment_text = "// Single line comment";
        valid_line_number = 10;
        valid_file_path = "test_file.cpp";
    }

    std::map<int, std::string> valid_long_comment_data;
    std::string valid_short_comment_text;
    int valid_line_number;
    std::string valid_file_path;
};

 