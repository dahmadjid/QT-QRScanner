#pragma once


#include <iostream>
#include <vector>
#include <unordered_map>
namespace CSV
{ //


// TODO:  add invalid csv checks. test invalid csv. benchmarks.
    struct RowInfo
    {
        unsigned int email_length;
        unsigned int name_length;
        unsigned int student_info_end_index;
        unsigned int line_number;
        unsigned int line_length;
        unsigned int offset;  
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
        bool updateAttendance(const std::string& qr, const std::string& session);
        void parseMultiple(const std::vector<std::string>& files);
        void parseFile(const std::string& csv_file_path);
    private:
        std::vector<std::unordered_map<std::string, RowInfo>> m_maps;
        std::vector<std::string> m_files;
        std::vector<HeaderInfo> m_headers;
    };
}

