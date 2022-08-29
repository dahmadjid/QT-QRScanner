#include "CSVParser.h"
#include <fstream>
#include <QDebug>
#include <QString>
namespace CSV {


    std::unordered_map<std::string, RowInfo> CSVParser::parseFile(const char *csv_file_path) {
        std::fstream csv_file;
        csv_file.open(csv_file_path, std::ios_base::in);
        unsigned int name_length = 0;
        unsigned int email_length = 0;
        unsigned int comma_count = 0;
        unsigned int line_number = 0;
        unsigned int student_info_end_index = 0;

        std::unordered_map<std::string, RowInfo> csv_info_map;
        std::string line;
        bool header_row = true;
        bool end_of_student_info = false;
        HeaderInfo header_info;
        std::string header_element = "";
        unsigned int duplicate_number = 0; // to avoid duplicate headers in map

        while (std::getline(csv_file, line))
        {
            end_of_student_info = false;
            unsigned int i = 0;
            comma_count = 0;
            for (i = 0; i < line.length(); i++)
            {
               
               
                if (line[i] == ',' || (i == line.length() - 1))
                {
                    if (header_row)  // adds header element when comma reached in header row
                    {
                        if(header_info.columns.find(header_element) == header_info.columns.end())
                        {
                            header_info.columns[header_element] = comma_count;
                        }
                        else
                        {
                            header_element += "_";
                            header_element +=  std::to_string(duplicate_number);
                            header_info.columns[header_element] = comma_count;
                            duplicate_number += 1;
                        }
                        
                        header_element = "";
                    }

                    if (comma_count == 0)
                    {
                        email_length = i;
                        comma_count += 1;
                    }
                    else if (comma_count == 1)
                    {
                        if (i == line.length() - 1) 
                        {
                            name_length = i - email_length;

                        }
                        else 
                        {
                            name_length = i - email_length - 1;
                        }
                        comma_count += 1;
                    }
                    else 
                    {
                        comma_count += 1;
                    }
                    
                    if ((line[i + 1] == '0' || line[i + 1] == '1') && (line[i + 2] == ',' || line[i + 2] == '\r' || (i + 2) >= line.length()))
                    {
                        student_info_end_index = i - 1;
                        end_of_student_info = true;
                        break;
                    }
                }
                else if (header_row)
                {
                    if (i == line.length() - 1) // this adds the last header element 
                    {
                        if(header_info.columns.find(header_element) == header_info.columns.end())
                        {
                            header_info.columns[header_element] = comma_count;
                        }
                        else
                        {

                            header_element += "_";
                            header_element +=  std::to_string(duplicate_number);
                            header_info.columns[header_element] = comma_count;
                            duplicate_number += 1;
                        }
                        
                        header_element = "";
                    }
                    else // construct the header element between each comma
                    {
                        header_element+=line[i];
                    }
                }                
            }

            if (end_of_student_info == false) // this is when there is no sessions
            {
                student_info_end_index = i - 1;  // -1 because \r is counted
            }
            if (header_row)
            {
                header_info.number_of_columns = comma_count;
                header_row = false;
            }
            else
            {
                unsigned int line_length = line.length();
                std::string temp =  line.substr(0, email_length + name_length + 1);

                if (temp[temp.length() - 1] == '\r')
                {
                    temp = temp.substr(0, temp.length() - 1);
                }
                csv_info_map[temp] = {email_length, name_length, student_info_end_index, line_number, line_length};
                header_info.number_of_sessions = header_info.number_of_columns - comma_count;
            }

            line_number+=1;
        }
        std::cout << "header_info: " <<  header_info.number_of_columns<< ", " << header_info.number_of_sessions <<  std::endl;
        
        for (auto kv : header_info.columns)
        {
            std::cout << kv.first << ": " << kv.second << ", ";
        }
        std::cout << std::endl;
        m_headers.push_back(std::move(header_info));

        return csv_info_map;
    }


    std::vector<std::unordered_map<std::string, RowInfo>> CSVParser::parseMultiple(std::vector<std::string> files)
    {
        std::vector<std::unordered_map<std::string, RowInfo>> vec;
        for (const auto& f: files)
        {
            vec.push_back(parseFile(f.c_str()));
        }
        return vec;
    }

}
