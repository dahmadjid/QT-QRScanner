#include "CSVParser.h"
#include <fstream>


namespace CSVParser
{


    std::map<std::string, RowInfo> CSVParser::parseFile(const char* csv_file_path)
    {
        std::fstream csv_file;
        csv_file.open(csv_file_path, std::ios_base::in);
        int name_length;
        int email_length;
        int student_info_end_index;
        int comma_count = 0;
        std::map<std::string, RowInfo> row;
        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == ',')
            {
                if (comma_count == 0)
                {
                    email_length = i;
                    comma_count +=1;
                }
                else if (comma_count == 1)
                {
                    name_length = i - email_length - 1;   
                    comma_count +=1;
                }
                else
                {
                    if ((line [i+1] == '0' || line [i+1] == '1') && (line [i+2] == ','))
                    {
                        student_info_end_index = i - 1;
                        return 
                    }
                }
                
            }
        }
    }














}