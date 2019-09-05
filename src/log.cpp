#include "mbdl/log.h"

namespace mbdl::log {
CSV::CSV(std::string path, std::string headers)
{
    this->path = path;
    file.open(path);
    write(headers, false);
}

CSV::~CSV()
{
    if (file.is_open()) {
        file.close();
    }
}

void CSV::open()
{
    if (!file.is_open()) {
        file.open(path);
    }
}

void CSV::close()
{
    file.close();
}

void CSV::save()
{
    file.flush();
}

void CSV::write(std::string data, bool close)
{
    file << data;
    if (close) {
        this->close();
    }
}

void CSV::add(double data[], bool close)
{
    std::string line = "";
    line += data[0];
    int i = 1;
    while (data[i] != '\n') {
        line += ",";
        line += data[i];
        i++;
    }
    line += '\n';
    write(line, close);
}

void CSV::add(double* data[], bool close)
{
    int i = 0;
    while (data[i][0] != '\n') {
        add(data[i], false);
    }

    if (close) {
        this->close();
    }
}

double* CSV::read(std::uint32_t line)
{
    // paste the file contents into an array
    file.seekg(0, file.end);
    int length = file.tellg();
    file.seekg(0, file.beg);
    char* buffer = new char[length];
    file.read(buffer, length);

    // declare tracking numbers
    int lineCount = 0;
    int charCount = 0;

    // skip through headers
    while (buffer[charCount] != '\n') {
        charCount++;
    }
    charCount++;

    // skip until you reach the desired line
    while (lineCount < line) {
        while (buffer[charCount] != '\n') {
            charCount++;
        }
        charCount++;
        lineCount++;
    }

    // determine the amount of items
    lineCount = charCount; // save position
    int itemCount = 1;
    while (buffer[charCount] != '\n') {
        if (buffer[charCount] == ',') {
            itemCount++;
        }
    }

    double* result = new double[itemCount];
    charCount = lineCount;
    for (int i = 0; i < itemCount; i++) {
        std::string str = "";
        while (buffer[charCount] != '\n' && buffer[charCount] != ',') {
            str += buffer[charCount];
        }
        result[i] = std::stod(str);
        charCount++;
    }

    delete[] buffer;
    return result;
}

double** CSV::read()
{
    std::fstream file(path);
    file.seekg(0, file.end);
    int length = file.tellg();
    file.seekg(0, file.beg);
    char* buffer = new char[length];
    file.read(buffer, length);

    // implement later

    delete[] buffer;
}

void CSV::clear()
{
    close();
    file.open(path, std::fstream::out | std::fstream::in | std::fstream::trunc);
}

inline namespace serial {
    std::string scanln()
    {
        char str[256];
        std::cin.getline(str, 256);
        return std::string(str);
    }

    void printfile(std::string path)
    {
        std::fstream file(path);
        file.seekg(0, file.end);
        int length = file.tellg();
        file.seekg(0, file.beg);
        char* buffer = new char[length];
        file.read(buffer, length);
        std::cout << "<FILE>\n";
        std::cout.write(buffer, length);
        std::cout << "</FILE>\n";

        delete[] buffer;
    }
}
}