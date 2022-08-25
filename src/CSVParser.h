#pragma once


#include <iostream>
#include <vector>
#include <map>
namespace CSVParser
{
    struct RowInfo
    {
        int email_length;
        int name_length;
        int data_start_index;
        int line_number;
    };

    struct HeaderInfo
    {
        int number_of_sessions;

    };

    class CSVParser
    {

    private:
        int number_of_sessions;
        std::map<std::string, RowInfo> parseFile(const char* csv_file_path); 



    };
}