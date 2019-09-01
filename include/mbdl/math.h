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

template <int _size>
class Vector {
public:
    /**
	 * Creates the Vector
	 */
    Vector()
    {
        for (int i = 0; i < _size; i++) {
            data[i] = 0;
        }
    }

    /**
	 * Creates the Vector using an initializer list
	 */
    Vector(std::initializer_list<double> values)
    {
        std::initializer_list<double>::iterator it = values.begin();
        for (int i = 0; i < _size; i++) {
            data[i] = *(it + i);
        }
    }

    /**
	 * Operator for adding two Vectors
	 * 
	 * @param other the const reference to the second addend
	 * @return the sum of the two Vectors
	 */
    Vector operator+(Vector<_size> const& other)
    {
        Vector<_size> vec;
        for (int i = 0; i < _size; i++) {
            vec.data[i] = data[i] + other.data[i];
        }
        return vec;
    }

    /**
	 * Operator for subtracting two Vectors of the same dimensions
	 * 
	 * @param other the const reference to the subtrahend
	 * @return the difference between the two Vectors
	 */
    Vector operator-(Vector<_size> const& other)
    {
        Vector<_size> vec;
        for (int i = 0; i < _size; i++) {
            vec.data[i] = data[i] + other.data[i];
        }
        return vec;
    }

    /**
	 * Operator for multiplying a Vector by a scale
	 * 
	 * @param scale the number to scale the Vector by
	 * @return the result of scaling the Vector
	 */
    Vector operator*(double const& scale)
    {
        Vector<_size> vec;
        for (int i = 0; i < _size; i++) {
            vec.data[i] = data[i] * scale;
        }
        return vec;
    }

    /**
	 * Operator for accessing a specific Vector element
	 * 
	 * @param i the index of the element to access
	 * @return the i-th indexed element
	 */
    double& operator[](std::uint8_t i)
    {
        return data[i];
    }

    /**
	 * Get the size of the Vector
	 * 
	 * @return the size of the Vector
	 */
    std::uint8_t size()
    {
        return _size;
    }

private:
    double data[_size];
};

template <int rows, int columns>
class Matrix {
public:
    /**
	 * Creates the Matrix of specified size
	 */
    Matrix()
    {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                data[i][j] = 0;
            }
        }
    }

    /**
	 * Creates the Matrix using an initializer list
	 */
    Matrix(std::initializer_list<std::initializer_list<double>> values)
    {
        std::initializer_list<std::initializer_list<double>>::iterator it = values.begin();
        for (int i = 0; i < rows; i++) {
            std::initializer_list<double>::iterator jt = (*(it + i)).begin();
            for (int j = 0; j < columns; j++) {
                data[i][j] = *(jt + j);
            }
        }
    }

    /**
	 * Operator for multiplying a Matrix by a Vector
	 * 
	 * @param other the const reference to the Vector
	 * @return the Vector product of the Matrix * Vector 
	 */
    Vector<columns> operator*(Vector<columns>& other)
    {
        Vector<columns> vec;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                vec[i] += other[j] * data[i][j];
            }
        }
        return vec;
    }

    /**
	 * Operator to accessing a specific row of the matrix
	 * 
	 * @param i the index of the row being accessed
	 * @return the pointer to the i-th row
	 */
    double* operator[](std::uint8_t i)
    {
        return &data[i][0];
    }

private:
    double data[rows][columns];
};
}

#endif