#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <cstdlib>
#include <algorithm>

#include "api.hpp"

int main(int argc, char **argv) {
    cff::API m_api;

    if(argc < 2) {
        m_api.PrintError("no input directory!");
        m_api.Print("\nAdd '--help' argument to see some useful info!\n", cff::Color::YELLOW);
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
#if defined _WIN32
        std::cout << "cff D:/files --type png --out E:/cff/out.txt --cp E:/cff\n";
#elif defined __linux__
        std::cout << "cff /home/user/Pictures --type png --out home/user/Documents/out.txt --cp home/user/png-copy\n";
#endif

        return 0;
    }

    std::string m_search = m_firstArg;
    std::string m_type;
    //std::string m_typeset;
    std::string m_out = "disabled";
    std::string m_copy = "disabled";

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
        m_api.PrintError("no type specified! Use '--type'!");
        return -1;
    }

    if(!isOut && !isCopy) {
        m_api.PrintError("no output specified! Use '--out' or '--cp'!");
        return -1;
    }

    m_api.Print("Searching in: ", cff::Color::YELLOW);
    m_api.Print(m_search);

    m_api.Print("\nType: ", cff::Color::YELLOW);
    m_api.Print(m_type);

    m_api.Print("\nOutput: ", cff::Color::YELLOW);
    m_api.Print(m_out, cff::Color::BLUE);

    m_api.Print("\nCopy: ", cff::Color::YELLOW);
    m_api.Print(m_copy, cff::Color::BLUE);

    std::vector<std::string> m_pathes;

    for(const auto& file : std::filesystem::recursive_directory_iterator(m_search)) {
        std::string buf = file.path().string();
        if(buf.find(m_type) != std::string::npos) {
            m_pathes.push_back(buf);
            m_inputSize += std::filesystem::file_size(file);
        }
    }

    m_api.Print("\nSearching ended! Found " + std::to_string(m_pathes.size()) + " files!\n", cff::Color::GREEN);

    if(isOut) {
        m_api.Print("\nSaving directories to output file: " + m_out + "\n");
        std::fstream m_outFile;
        m_outFile.open(m_out, std::ios::out | std::ios::trunc);
        if(!m_outFile.good()) {
            m_api.PrintError("can't open '" + m_out + "'!");
            return -1;
        }
        for(auto& path : m_pathes) {
            m_outFile.write(&path[0], path.length());
            m_outFile << "\n";
        }
        m_outFile.close();

        m_api.Print("\n\nSaved " + std::to_string(m_pathes.size()) + " directories to output file: " + m_out + "\n", cff::Color::GREEN);
    }

    if(isCopy) {
        std::filesystem::space_info cp = std::filesystem::space(m_copy);
        if(m_inputSize >= cp.available) {
            m_api.PrintError("files that you're trying to copy are too big!");
            return -1;
        }
        m_api.Print("\nCopying files to: " + m_copy + "\n\n");
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

            m_api.Print("Copied " + std::to_string(i + 1) + "/" + std::to_string(m_pathes.size()) + " files" + '\r');
        }
    }

    m_api.Print("\nProgram finished!\n", cff::Color::GREEN);
    
    return 0;
}