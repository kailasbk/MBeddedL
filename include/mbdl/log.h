#ifndef _MBDL_LOGGING_H_
#define _MBDL_LOGGING_H_

#include "pros/apix.h"
#include <fstream>

namespace mbdl::log {
class CSV {
public:
    /**
	 * Creates a CSV object for using .csv files
	 * 
	 * @param path the path to the .csv file
	 * @param headers the headers of the .csv file
	 */
    CSV(std::string path, std::string headers);

    /** 
	 * Closes the .csv file when the CSV object is deleted
	 */
    ~CSV();

    /** 
	 * Opens the .csv file for use
	 */
    void open();

    /** 
	 * Closes the .csv file for use and saves all changes
	 */
    void close();

    /** 
	 * Saves all changes to the .csv file
	 */
    void save();

    /** 
	 * Writes changes into the file buffer
	 * 
	 * @param data the text data to write to the file
	 * @param close whether the file should be closed afterward
	 */
    void write(std::string data, bool close);

    /** 
	 * Adds a line of CSV to the file
	 * 
	 * @param data the double array data to write to the file, ending with \n
	 * @param close whether the file should be closed afterward
	 */
    void add(double data[], bool close);

    /** 
	 * Adds multiple lines of CSV data to the file
	 * 
	 * @param data data the double 2D array data to write to the file, ending with \n
	 * @param close whether the file should be closed afterward
	 */
    void add(double* data[], bool close);

    /** 
	 * Reads data from a line of CSV data and returns a pointer to the data
	 * 
	 * @param line the line (with 0 being the first line of data) to read from
	 * @return the pointer to the array of data
	 */
    double* read(std::uint32_t line);

    /** 
	 * Reads data from a file of CSV data and returns a pointer to the data
	 * 
	 * @return the pointer to the 2d array of data
	 */
    double** read();

    /** 
	 * Wipes the .csv file
	 */
    void clear();

private:
    std::fstream file;
    std::string path;
};

double end[1]{ '\n' };

inline namespace serial {
    /**
	 * Prints data into the stream
	 * 
	 * @param data the data to write into the stream
	 */
    template <typename T>
    void print(T data)
    {
        std::cout << data;
    }

    /**
	 * Prints data into the stream and makes newline
	 * 
	 * @param data the data to write into the stream
	 */
    template <typename T>
    void println(T data)
    {
        std::cout << data << '\n';
    }

    /**
	 * Prints a file from storage into the stream
	 * 
	 * @param path the path to the file
	 */
    void printfile(std::string path);

    /**
	 * Scans a line from the stream
	 * 
	 * @return the line in std::string format
	 */
    std::string scanln();

    /**
	 * Scans an item from the stream
	 */
    template <typename T>
    T scan()
    {
        T data;
        std::cin >> std::ws >> data;
        return data;
    }
}
}

#endif