#pragma once


#include <iostream>
#include <vector>
#include <unordered_map>
namespace CSV
{ //


// TODO: Test that these numbers are correct.
    struct RowInfo
    {
        unsigned int email_length;
        unsigned int name_length;
        unsigned int student_info_end_index;
        unsigned int line_number;
        unsigned int line_length;
    };
    struct HeaderInfo
    {
        unsigned int number_of_columns;
        unsigned int number_of_sessions;
        std::unordered_map<std::string, unsigned int> columns;
    };
    class CSVParser
    {

    public:
        std::vector<std::unordered_map<std::string, RowInfo>> parseMultiple(std::vector<std::string> files);
        std::unordered_map<std::string, RowInfo> parseFile(const char* csv_file_path);
    private:

        std::vector<std::string> m_files;
        std::vector<HeaderInfo> m_headers;

    };
}

