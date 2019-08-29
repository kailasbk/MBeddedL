#ifndef _MBDL_MATH_H_
#define _MBDL_MATH_H_

#include "../api.h"

#define PI 3.14159265

namespace mbdl::math {
/**
 * Scales angle in radians to equivalent angle from 0 to 2pi
 * 
 * @param the input angle in radians
 * @return the equivalent angle in radians
 */
double equiv(double angle);

/**
 * Converts radians to degrees
 * 
 * @param the input angle in radians
 * @return the converted angle in degrees
 */
double RtoD(double angle);

/**
 * Converts degrees to radians
 * 
 * @param angle the input angle in degrees
 * @return the converted angle in radians
 */
double DtoR(double angle);

class Vector {
public:
    double* data;
    std::uint8_t size;

    /**
	 * Creates the Vector of a certain dimension
	 * 
	 * @param size the dimensions of the Vector
	 */
    Vector(std::uint8_t size);

    /**
	 * Deletes the Vector and frees memory
	 */
    ~Vector();

    /**
	 * Operator for adding two Vectors
	 * 
	 * @param other the const reference to the second addend
	 * @result the sum of the two Vectors
	 */
    Vector operator+(Vector const& other);

    /**
	 * Operator for subtracting two Vectors of the same dimensions
	 * 
	 * @param other the const reference to the subtrahend
	 * @result the difference between the two Vectors
	 */
    Vector operator-(Vector const& other);

    /**
	 * Operator for multiplying a Vector by a scale
	 * 
	 * @param scale the number to scale the Vector by
	 * @return the result of scaling the Vector
	 */
    Vector operator*(double const& scale);

    /**
	 * Operator for accessing a specific Vector element
	 * 
	 * @param i the index of the element to access
	 * @return the i-th indexed element
	 */
    double& operator[](std::uint8_t i);
};

class Matrix {
public:
    double** data;
    std::uint8_t rows, columns;

    /**
	 * Creates the Matrix of specified size
	 * 
	 * @param height the number of rows in the Matrix
	 * @param width the number of columns in the Matrix
	 */
    Matrix(std::uint8_t height, std::uint8_t width);

    /**
	 * Deletes the Matrix and frees memory
	 */
    ~Matrix();

    /**
	 * Operator for multiplying a Matrix by a Vector
	 * 
	 * @param other the const reference to the Vector
	 * @return the Vector product of the Matrix * Vector 
	 */
    Vector operator*(Vector const& other);

    /**
	 * Operator to accessing a specific row of the matrix
	 * 
	 * @param i the index of the row being accessed
	 * @return the pointer to the i-th row
	 */
    double* operator[](std::uint8_t i);
};
}

#endif