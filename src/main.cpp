#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <cstdlib>
#include <algorithm>

#include "colors.hpp"

void PrtError(std::string val) {
    SetColor(RED);
    std::cout << "\nERROR: " << val << "\n";
    SetColor(WHITE);
}

int main(int argc, char **argv) {
    if(argc < 2) {
        PrtError("no input directory!");
        return -1;
    }

    std::string m_firstArg = argv[1];
    if(m_firstArg == "--help") {
        std::cout << "\n";
        std::cout << "cff --help   - displays this message\n";
        std::cout << "\n";
        std::cout << "Usage:\n";
        std::cout << "cff {where to search} {args}\n";
        std::cout << "\n";
        std::cout << "Args:\n";
        std::cout << "--type       - specify what file type will be searched\n";
        std::cout << "--out        - enable text output and set where to store it\n";
        std::cout << "--cp         - enable copying files and set where to copy them\n";
        std::cout << "\n";
        std::cout << "Example:\n";
        std::cout << "cff D:/files --type png --out E:/cff/out.txt --cp E:/cff\n";

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
        PrtError("no type specified! Use '--type'!");
        return -1;
    }

    if(!isOut && !isCopy) {
        PrtError("no output specified! Use '--out' or '--cp'!");
        return -1;
    }

    SetColor(YELLOW);
    std::cout << "Searching in: ";
    SetColor(WHITE);
    std::cout << m_search;

    SetColor(YELLOW);
    std::cout << "\nType: ";
    SetColor(WHITE);
    std::cout << m_type;

    SetColor(YELLOW);
    std::cout << "\nOutput: ";
    SetColor(WHITE);
    if(isOut) {
        std::cout << m_out;
    } else {
        SetColor(BLUE);
        std::cout << "disabled";
        SetColor(WHITE);
    }

    SetColor(YELLOW);
    std::cout << "\nCopy: ";
    SetColor(WHITE);
    if(isCopy) {
        std::cout << m_copy;
    } else {
        SetColor(BLUE);
        std::cout << "disabled";
        SetColor(WHITE);
    }

    std::vector<std::string> m_pathes;

    for(const auto& file : std::filesystem::recursive_directory_iterator(m_search)) {
        std::string buf = file.path().string();
        if(buf.find(m_type) != std::string::npos) {
            m_pathes.push_back(buf);
            m_inputSize += std::filesystem::file_size(file);
        }
    }

    SetColor(GREEN);
    std::cout << "\nSearching ended! Found " << m_pathes.size() << " files!\n";
    SetColor(WHITE);

    if(isOut) {
        std::cout << "\nSaving directories to output file: " << m_out << "\n";
        std::fstream m_outFile;
        m_outFile.open(m_out, std::ios::out | std::ios::trunc);
        if(!m_outFile.good()) {
            PrtError("can't open '" + m_out + "'!");
            return -1;
        }
        for(auto& path : m_pathes) {
            m_outFile.write(&path[0], path.length());
            m_outFile << "\n";
        }
        m_outFile.close();

        SetColor(GREEN);
        std::cout << "\n\nSaved " << m_pathes.size() << " directories to output file: " << m_out << "\n";
        SetColor(WHITE);
    }

    if(isCopy) {
        std::filesystem::space_info cp = std::filesystem::space(m_copy);
        if(m_inputSize >= cp.available) {
            PrtError("files that you're trying to copy are too big!");
            return -1;
        }
        std::cout << "\nCopying files to: " << m_copy << "\n\n";
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

    SetColor(GREEN);
    std::cout << "\nProgram finished!\n";
    SetColor(WHITE);
    
    return 0;
}