#include "mbdl/math.h"

double mbdl::math::equiv(double angle)
{
    if (angle > 0) { // if angle is positive
        return angle - (2 * PI) * ((int)angle / (2 * PI)); // return the angle minus the closest multiple of 2PI
    } else {
        return angle + (2 * PI) * ((int)(angle / (2 * PI)) + 1); // return the angle plus one more than multiple of 2PI
    }
}

double mbdl::math::DtoR(double angle)
{
    return angle * PI / 180; // return the degrees in radians
}

double mbdl::math::RtoD(double angle)
{
    return angle * 180 / PI; // return the radians in degrees
}

mbdl::math::Matrix::Matrix(std::uint8_t height, std::uint8_t width)
{
    rows = height; // set variable rows to height
    columns = width; // set variable columns to width
    data = new double*[rows]; // allocate rows-many double pointers and set their address them to data
    for (int i = 0; i < rows; i++) { // for each row i in all rows in the matrix
        data[i] = new double[columns]; // allocate a columns-size array of doubles and set their address to the i-th pointer
        for (int j = 0; j < columns; j++) { // for all doubles in the column
            data[i][j] = 0; // set the double to zero
        }
    }
}

mbdl::math::Vector mbdl::math::Matrix::operator*(Vector const& other)
{
    if (columns == other.size) { // if matrix muliplication is possible
        mbdl::math::Vector vec(other.size); // create an empty Vector
        for (int i = 0; i < rows; i++) { // for all rows in the matrix
            for (int j = 0; j < columns; j++) { // for all columns in the row
                vec[i] += other.data[j] * data[i][j]; // set the value to sum of the products
            }
        }
        return vec; // return the Vector
    } else { // if not possible
        return other; // return the Vector other
    }
}

double* mbdl::math::Matrix::operator[](std::uint8_t i)
{
    return this->data[i]; // return the pointer to the i-th row
}

mbdl::math::Vector::Vector(std::uint8_t size)
{
    this->size = size; // set variable size
    data = new double[size]; // allocate an size-large array of doubles and set data to their address
    for (int i = 0; i < size; i++) { // for each double in the array
        data[i] = 0; // set the value to 0
    }
}

mbdl::math::Vector mbdl::math::Vector::operator+(Vector const& other)
{
    if (size == other.size) { // if vectors and same size, addition is possible
        mbdl::math::Vector vec(this->size); // create a empty Vector
        for (int i = 0; i < size; i++) { // for each row in the vector
            vec.data[i] = data[i] + other.data[i]; // set the value to the sum of the two vectors
        }
        return vec; // return the vector
    } else { // if addition is not possible
        return *this; // return this vector
    }
}

mbdl::math::Vector mbdl::math::Vector::operator-(Vector const& other)
{
    if (size == other.size) { // if vectors and same size, subtraction is possible
        mbdl::math::Vector vec(this->size); // create a empty Vector
        for (int i = 0; i < size; i++) { // for each row in the vector
            vec.data[i] = data[i] - other.data[i]; // set the value to the difference of the two vectors
        }
        return vec; // return the vector
    } else { // of subtraction is not possible
        return *this; // return this vector
    }
}

mbdl::math::Vector mbdl::math::Vector::operator*(double const& scale)
{
    mbdl::math::Vector vec(this->size); // create an empty Vector
    for (int i = 0; i < size; i++) { // for each row in the vector
        vec.data[i] = data[i] * scale; // multiply the row value by the scale
    }
    return vec; // return the vector
}

double& mbdl::math::Vector::operator[](std::uint8_t i)
{
    return data[i]; // return a reference to the i-th double
}