#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <windows.h>
#include <cstdlib>
#include <algorithm>

int main(int argc, char **argv) {
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    if(argc == 0) {
        return -1;
    }

    std::string m_firstArg = argv[1];
    if(m_firstArg == "--help") {
        std::cout << std::endl;
        std::cout << "cff --help   - displays this message" << std::endl;
        std::cout << std::endl;
        std::cout << "Usage: " << std::endl;
        std::cout << "cff {where to search} {args}" << std::endl;
        std::cout << std::endl;
        std::cout << "Args: " << std::endl;
        std::cout << "--type       - specify what file type will be searched" << std::endl;
        std::cout << "--out        - enable text output and set where to store it" << std::endl;
        std::cout << "--cp         - enable copying files and set where to copy them" << std::endl;
        std::cout << std::endl;
        std::cout << "Example: " << std::endl;
        std::cout << "cff D:/files --type png --out E:/cff/out.txt --cp E:/cff" << std::endl;

        return 0;
    }

    std::string m_search = m_firstArg;
    std::string m_type;
    //std::string m_typeset;
    std::string m_out;
    std::string m_copy;

    bool isType = false;
    //bool isTypeset = false;
    bool isOut = false;
    bool isCopy = false;

    uintmax_t m_inputSize = 0;

    for(int i = 2; i < argc; i++) {
        std::string buf = argv[i];
        if(buf == "--type") {
            i++;
            isType = true;
            m_type = argv[i];
        } else if(buf == "--out") {
            i++;
            isOut = true;
            m_out = argv[i];
        } else if(buf == "--cp") {
            i++;
            isCopy = true;
            m_copy = argv[i];
        }
    }

    if(!isType) {
        SetConsoleTextAttribute(hOut, FOREGROUND_RED);
        std::cout << "ERROR: no type specified! Use '--type'!\n";
        SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

        return -1;
    }

    SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN);
    std::cout << "\nSearching in: ";
    SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    std::cout << m_search;

    SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN);
    std::cout << "\nType: ";
    SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    std::cout << m_type;

    if(isOut) {
        SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN);
        std::cout << "\nOutput: ";
        SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        std::cout << m_out;

        if(isCopy) {
            SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN);
            std::cout << "\nCopy: ";
            SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            std::cout << m_copy;
        } else {
            SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN);
            std::cout << "\nCopy: ";
            SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            std::cout << "disabled";
        }
    } else if(isCopy) {
        SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN);
        std::cout << "\nOutput: ";
        SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        std::cout << "diasbled";

        SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN);
        std::cout << "\nCopy: ";
        SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        std::cout << m_copy;
    } else {
        SetConsoleTextAttribute(hOut, FOREGROUND_RED);
        std::cout << "ERROR: no output specified! Use '--out' or '--cp'!\n";
        SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

        return -1;
    }

    std::vector<std::string> m_pathes;

    for(const auto& file : std::filesystem::recursive_directory_iterator(m_search)) {
        std::string buf = file.path().string();
        if(buf.find(m_type) != std::string::npos) {
            m_pathes.push_back(buf);
            m_inputSize += std::filesystem::file_size(file);
        }
    }

    SetConsoleTextAttribute(hOut, FOREGROUND_GREEN);
    std::cout << "\nSearching ended! Found " << m_pathes.size() << " files!\n";
    SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    if(isOut) {
        std::cout << "\nSaving directories to output file: " << m_out << std::endl;
        std::fstream m_outFile;
        m_outFile.open(m_out, std::ios::out | std::ios::trunc);
        if(!m_outFile.good()) {
            SetConsoleTextAttribute(hOut, FOREGROUND_RED);
            std::cout << "ERROR: can't open '" << m_out << "'!";
            SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

            return -1;
        }
        for(auto& path : m_pathes) {
            m_outFile.write(&path[0], path.length());
            m_outFile << std::endl;
        }
        m_outFile.close();

        SetConsoleTextAttribute(hOut, FOREGROUND_GREEN);
        std::cout << "\nSaved " << m_pathes.size() << " directories to output file: " << m_out << std::endl;
        SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }

    if(isCopy) {
        std::filesystem::space_info cp = std::filesystem::space(m_copy);
        if(m_inputSize >= cp.available) {
            SetConsoleTextAttribute(hOut, FOREGROUND_RED);
            std::cout << "ERROR: files that you're trying to copy are too big!\n";
            SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

            return -1;
        }
        std::cout << "\nCopying files to: " << m_copy << std::endl << std::endl;
        for(uint32_t i = 0; i < m_pathes.size(); i++) {
            std::string buf = m_pathes[i];
            std::string copyBuf;

            std::replace(buf.begin(), buf.end(), '\\', '/');
            std::reverse(buf.begin(), buf.end());

            std::size_t found = buf.find("/");
            if(found != std::string::npos) {
                for(uint32_t i = 0; i < found; i++) {
                    copyBuf += buf.at(i);
                }
                std::reverse(copyBuf.begin(), copyBuf.end());
            }

            if(std::filesystem::exists(m_copy + "/" + copyBuf)) {
                while(std::filesystem::exists(m_copy + "/" + copyBuf)) {
                    found = copyBuf.find(".");
                    if(found != std::string::npos) {
                        copyBuf.insert(found, "(copy)");
                    }
                }
            }

            std::ifstream src(m_pathes[i], std::ios::binary);
            std::ofstream dst(m_copy + "/" + copyBuf, std::ios::binary);

            dst << src.rdbuf();

            src.close();
            dst.close();

            std::cout << "Copied " << i + 1 << "/" << m_pathes.size() << " files" << '\r' << std::flush;
        }
    }

    SetConsoleTextAttribute(hOut, FOREGROUND_GREEN);
    std::cout << "\nProgram finished!\n";
    SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    
    return 0;
}