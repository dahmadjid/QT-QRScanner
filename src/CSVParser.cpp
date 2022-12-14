#include "CSVParser.h"
#include <fstream>
#include <QDebug>
#include <QString>
#include <cstdio>
#include "Benchmark.h"

static std::istream& safeGetline(std::istream& is, std::string& t)
{
    t.clear();

    // The characters in the stream are read one-by-one using a std::streambuf.
    // That is faster than reading them one-by-one using the std::istream.
    // Code that uses streambuf this way must be guarded by a sentry object.
    // The sentry object performs various tasks,
    // such as thread synchronization and updating the stream state.

    std::istream::sentry se(is, true);
    std::streambuf* sb = is.rdbuf();

    for(;;) {
        int c = sb->sbumpc();
        switch (c) {
        case '\n':
            return is;
        case '\r':
            if(sb->sgetc() == '\n')
                sb->sbumpc();
            return is;
        case std::streambuf::traits_type::eof():
            // Also handle the case when the last line has no line ending
            if(t.empty())
                is.setstate(std::ios::eofbit);
            return is;
        default:
            t += (char)c;
        }
    }
}

namespace CSV {


void CSVParser::parseFile(const std::string& csv_file_path) 
{
    Benchmark("Parse File");
    unsigned int name_length = 0;
    unsigned int email_length = 0;
    unsigned int comma_count = 0;
    unsigned int line_number = 0;
    unsigned int student_info_end_index = 0;
    unsigned int offset = 0;
    std::unordered_map<std::string, RowInfo> csv_info_map;
    std::string line;
    bool header_row = true;
    bool end_of_student_info = false;
    HeaderInfo header_info;
    std::string header_element = "";
    unsigned int duplicate_number = 0; // to avoid duplicate headers in map


    std::ifstream csv_file(csv_file_path);

    while (!safeGetline(csv_file, line).eof())
    {
        if (line.length() < 4)
        {
            qDebug() << "ignoring empty line: " << line_number ;
            continue;
        }
        qInfo() << (int)line[line.length() - 1]; 
        end_of_student_info = false;
        unsigned int i = 0;
        comma_count = 0;
        for (i = 0; i < line.length(); i++)
        {
            if (line[i] == ',' || (i == line.length() - 1))
            {
                if (header_row)  // adds header element when comma reached in header row
                {
                    if (line[i] != ',')
                    {
                        header_element+=line[i];
                    }
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
                    if (line[i] == ',')
                    {
                        name_length = i - email_length - 1 ;

                    }
                    else 
                    {
                        name_length = i - email_length;
                    }
                    comma_count += 1;
                }
                else 
                {
                    comma_count += 1;
                }
                
                if ((line[i + 1] == '0' || line[i + 1] == '1') && (line[i + 2] == ',' || (i + 2) >= line.length()))
                {
                    student_info_end_index = i - 1;
                    end_of_student_info = true;
                    break;
                }
            }
            else
            {
                header_element+=line[i];
            }
//            else if (header_row)
//            {
//                if (i == line.length() - 1) // this adds the last header element
//                {
//                    if(header_info.columns.find(header_element) == header_info.columns.end())
//                    {
//                        header_info.columns[header_element] = comma_count;
//                    }
//                    else
//                    {

//                        header_element += "_";
//                        header_element +=  std::to_string(duplicate_number);
//                        header_info.columns[header_element] = comma_count;
//                        duplicate_number += 1;
//                    }
                    
//                    header_element = "";
//                }
//                else // construct the header element between each comma
//                {
//                    header_element+=line[i];
//                }

        }

        if (end_of_student_info == false) // this is when there is no sessions
        {

            student_info_end_index = i - 1;  // -1 because i is incremented one more time before breaking the loop
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
            csv_info_map[temp] = {email_length, name_length, student_info_end_index, line_number, line_length, offset};
            header_info.number_of_sessions = header_info.number_of_columns - comma_count;
        }
        #ifdef LINUX
            offset += line.length() + 2; // \r\n
        #endif

        #ifdef WINDOWS
            offset += line.length() + 2; // \n
        #endif
        line_number+=1;
    }
    qInfo() << "Header Info:--------------------------------------";
    qInfo() <<  header_info.number_of_columns<< ", " << header_info.number_of_sessions;
    
    for (auto kv : header_info.columns)
    {
        qInfo() << kv.first.c_str() << ": " << kv.second << ", ";
    }
    qInfo() << "---------------------------------------------------";
    

    qInfo() << "CSV Info Map:--------------------------------------";
    for (const auto& kv : csv_info_map)
    {
        qInfo() << kv.first.c_str() << ": " << kv.second.email_length << ", " << kv.second.name_length << ", " << kv.second.student_info_end_index << ", "  << kv.second.line_number << ", " << kv.second.line_length << ", " << kv.second.offset;

    }
    qInfo() << "---------------------------------------------------";
    m_headers.push_back(std::move(header_info));
    m_maps.push_back(std::move(csv_info_map));
    m_files.push_back(std::string(csv_file_path));
    csv_file.close();
    ready = true;
}


void CSVParser::parseMultiple(const std::vector<std::string>& files)
{
    m_headers.clear();
    m_maps.clear();
    m_files.clear();
    for (const auto& f: files)
    {
        parseFile(f);
    }
}



bool CSVParser::updateAttendance(const std::string& qr, const std::string& session)
{
    Benchmark("Update Attendance");
    int i = 0;
    bool name_found = false;
    for (const auto& map: m_maps)
    {
        if (map.find(qr) != map.end())
        {

            name_found = true;
            break;
        }
        else
        {
            i++;
        }
    }
    
    if (name_found)
    {
        
        auto& map = m_maps[i];
        const auto& student_info = map.at(qr);
        auto& header_info = m_headers[i];
        const std::string& csv_file_path = m_files[i];
        

        if (header_info.columns.find(session) != header_info.columns.end())
        {


            int session_index = header_info.columns.at(session);
            int number_of_student_info_headers = header_info.number_of_columns - header_info.number_of_sessions;
            session_index = session_index - number_of_student_info_headers; 

            if (session_index < 0) // this cant happen, smth went really wrong in parsing for this to happen
            {
                qCritical() << "session index negative file path: " << csv_file_path.c_str() << ", Session: " << session.c_str();
                return false;
            }
            else 
            {
                int position_to_write = student_info.offset + student_info.student_info_end_index + (session_index + 1) * 2 ;

                qInfo() << student_info.offset << "+" << student_info.student_info_end_index << "+" << (session_index + 1) * 2 << "=" << position_to_write;
                FILE * file_descriptor;
                file_descriptor = fopen(csv_file_path.c_str(), "r+b");

                if (file_descriptor != NULL) 
                {
                    fseek(file_descriptor, position_to_write, SEEK_SET);
                    fputc('1', file_descriptor);
                    fclose(file_descriptor);
                    return true;

                }

            }
          
        }
        else 
        {
            std::string line;
            std::ifstream csv_file(csv_file_path);
            std::fstream temp_csv_file;

            temp_csv_file.open("temp.csv", std::ios_base::out);
            if(!safeGetline(csv_file, line).eof())
            {
                #ifdef LINUX
                temp_csv_file << line + "," + session + "\r\n";
                #endif

                #ifdef WINDOWS
                temp_csv_file << line + "," + session + "\n";
                #endif
            }
            while (!safeGetline(csv_file, line).eof())
            {
                if (line.length() < 4)
                {
                    qDebug() << "ignoring empty line: ";
                    continue;
                }
                #ifdef LINUX
                temp_csv_file << line + ",0\r\n";
                #endif
                
                #ifdef WINDOWS
                temp_csv_file << line + ",0\n";
                #endif

            }

            csv_file.close();
            temp_csv_file.close();
            remove(csv_file_path.c_str());
            rename("temp.csv", csv_file_path.c_str());

            // updating internal data
            qInfo() << "Updating internal data:";
            for (auto& kv: map)
            {
                
                kv.second.line_length += 2;
    
   
                kv.second.offset += session.length() + 1 + 2 * (kv.second.line_number - 1);

                

            }

            header_info.columns[session] = header_info.number_of_columns ;
            header_info.number_of_columns += 1;
            header_info.number_of_sessions += 1;

            qInfo() << "Header Info:--------------------------------------";
            qInfo() <<  header_info.number_of_columns<< ", " << header_info.number_of_sessions;
            
            for (auto kv : header_info.columns)
            {
                qInfo() << kv.first.c_str() << ": " << kv.second << ", ";
            }
            qInfo() << "---------------------------------------------------";
            

            qInfo() << "CSV Info Map:--------------------------------------";
            for (const auto& kv : map)
            {
                qInfo() << kv.first.c_str() << ": " << kv.second.email_length << ", " << kv.second.name_length << ", " << kv.second.student_info_end_index << ", "  << kv.second.line_number << ", " << kv.second.line_length << ", " << kv.second.offset;

            }
            qInfo() << "---------------------------------------------------";



            int session_index = header_info.columns.at(session);
            int number_of_student_info_headers = header_info.number_of_columns - header_info.number_of_sessions;
            session_index = session_index - number_of_student_info_headers; 

            if (session_index < 0) // this cant happen, smth went really wrong in parsing for this to happen
            {
                qCritical() << "session index negative file path: " << csv_file_path.c_str() << ", Session: " << session.c_str();
                return false;
            }
            else 
            {
                int position_to_write = student_info.offset + student_info.student_info_end_index + (session_index + 1) * 2 ;

                qInfo() << student_info.offset << "+" << student_info.student_info_end_index << "+" << (session_index + 1) * 2 << "=" << position_to_write;
                FILE * file_descriptor;
                file_descriptor = fopen(csv_file_path.c_str(), "r+b");

                if (file_descriptor != NULL) 
                {
                    fseek(file_descriptor, position_to_write, SEEK_SET);
                    fputc('1', file_descriptor);
                    fclose(file_descriptor);
                    return true;

                }

            }
        }

        

    }
    else
    {
        qWarning() << "Student not found: " << qr.c_str();
    }
    return false;
}

std::string CSVParser::getNameOnly(const std::string& qr)
{
    int i = 0;
    bool name_found = false;
    for (const auto& map: m_maps)
    {
        if (map.find(qr) != map.end())
        {

            name_found = true;
            break;
        }
        else
        {
            i++;
        }
    }
    if (name_found)
    {
        return qr.substr(m_maps[i].at(qr).email_length + 1, m_maps[i].at(qr).name_length);
        
    }
    return "name not found";
}
 
// void CSVParser::generateQRs(int group_index)
// {
//     if (group_index >= m_files.size())
//     {
//         qInfo() << "Make sure to load CSV";
//         return;
//     }
//     for (const auto& kv: m_maps[group_index])
//     {
//         // TODO add creation of dir, if files exists dont recreate them
//         std::string file_name = "QR/";   // make sure to create the directory if it doesnt exist
//         file_name += kv.first + "_QR.png";

//         auto exampleQrPng1 = QrToPng(file_name, 300, 3, kv.first, true, qrcodegen::QrCode::Ecc::MEDIUM);

//         if (!exampleQrPng1.writeToPNG())
//         {
//             qCritical() << "Failed to write QR. Make sure that directory QR is created";

//         }
//     }
//     qInfo() << "Done creating QRs";
    

// }

}


