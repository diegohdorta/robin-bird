/* Copyright 2019 NXP Semiconductors
 *   
 * SPDX-License-Identifier: MIT
 * Diego Dorta <diego.dorta@nxp.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include "math.h"

template <class T>
Matrix<T>::Matrix(){}

template <class T>
Matrix<T>::Matrix(int height, int width)
{
    this->height = height;
    this->width = width;
    this->array = std::vector<std::vector<T>>
                        (height, std::vector<T>(width));
}

template <class T>
Matrix<T>::Matrix(std::vector<std::vector<T>> const &array)
{
    assert(array.size() != 0);
    this->height = array.size();
    this->width = array[0].size();
    this->array = array;
}

template <class T>
int Matrix<T>::getHeight()
{
    return height;
}

template <class T>
int Matrix<T>::getWidth()
{
    return width;
}

template <class T>
void Matrix<T>::fill(T const &value)
{
    int i;
    int j;
    
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            array[i][j] = value;
        }
    }
}

template <class T>
void Matrix<T>::put(int height, int width, T const &value)
{
    array[height][width] = value;
}

template <class T>
T Matrix<T>::get(int height, int width) const
{
    return array[height][width];
}

/* Add Functions */

template <class T>
Matrix<T> Matrix<T>::add(T const &value)
{
    int i;
    int j;
    
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            array[i][j] += value;
        }
    }
    return *this;
}

template <class T>
Matrix<T> Matrix<T>::add(Matrix const &m) const
{
    int i;
    int j;    
    assert(height == m.height &&
           width == m.width);
    Matrix r(height, width);
        
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            r.array[i][j] = array[i][j] + m.array[i][j];
        }
    }
    return r;
}

/* Subtract Functions */

template <class T>
Matrix<T> Matrix<T>::subtract(T const &value)
{
    int i;
    int j;
    
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++){
            array[i][j] -= value;
        }
    }
    return *this;
}

template <class T>
Matrix<T> Matrix<T>::subtract(Matrix const &m) const
{
    int i;
    int j;
    assert(height == m.height &&
           width == m.width);
    Matrix r(height, width);
    
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            r.array[i][j] = array[i][j] - m.array[i][j];
        }
    }
    return r;
}

/* Multiply Functions */

template <class T>
Matrix<T> Matrix<T>::multiply(T const &value)
{
    int i;
    int j;
    
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            array[i][j] *= value;
        }
    }
    return *this;
}

template <class T>
Matrix<T> Matrix<T>::multiply(Matrix const &m) const
{
    int i;
    int j;
    assert(height == m.height &&
           width == m.width);
    Matrix r(height, width);
    
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            r.array[i][j] = array[i][j] * m.array[i][j];
        }
    }
    return r;
}

template <class T>
Matrix<T> Matrix<T>::dot(Matrix const &m) const
{
    int i;
    int j;
    int h;
    assert(width == m.height);
    int mwidth = m.width;
    T w = 0;
    Matrix<T> r(height, mwidth);
    
    for (i = 0; i < height; i++) {
        for (j = 0; j < mwidth; j++) {
            for (h = 0; h < width; h++) {
                w += array[i][h] * m.array[h][j];
            }
            r.array[i][j] = w;
            w = 0;
        }
    }
    return r;
}

template <class T>
Matrix<T> Matrix<T>::transpose() const
{
    int i;
    int j;
    Matrix<T> r(width, height);
    
    for (i = 0; i < width; i++) {
        for (j = 0; j < height; j++) {
            r.array[i][j] = array[j][i];
        }
    }
    return r;
}

template <class T>
Matrix<T> Matrix<T>::applyFunction(T (*function)(T)) const
{
    int i;
    int j;
    Matrix<T> r(height, width);
    
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            r.array[i][j] = (*function)(array[i][j]);
        }
    }
    return r;
}

template <class T>
Matrix<T> Matrix<T>::subMatrix(int startHeight,
                               int startWidth,
                               int height,
                               int width) const
{
    int i;
    int j;
    assert(startHeight + height <= height &&
           startWidth + width <= width);
    Matrix<T> r(height, width);
    for (i = startHeight; i < startHeight + height; i++) {
        for (j = startWidth; j < startWidth + width; j++) {
            r.array[i - startHeight][j - startWidth] = array[i][j];
        }
    }
    return r;
}

template <class T>
void Matrix<T>::print(std::ostream &flux) const
{
    int i;
    int j;
    int k;
    int maxLength[width] = {};
    std::stringstream ss;

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            ss << array[i][j];
            if (maxLength[j] < ss.str().size()) {
                maxLength[j] = ss.str().size();
            }
            ss.str(std::string());
        }
    }
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            flux << array[i][j];
            ss << array[i][j];
            for (k = 0;
                 k < maxLength[j] - ss.str().size() + 1;
                 k++) {
                flux << " ";
            } ss.str(std::string());
        } flux << std::endl;
    }
}

template <class T>
bool Matrix<T>::operator == (Matrix const &m)
{
    int i;
    int j;
     
    if (height == m.height && width == m.width) {
        for (i = 0; i < height; i++) {
            for (j = 0; j < width; j++) {
                if (array[i][j] != m.array[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }
    return false;
}

template <class T>
bool Matrix<T>::operator != (Matrix const &m)
{
    return !operator == (m);
}

template <class T>
void Matrix<T>::operator += (Matrix const &m)
{
    this->array = add(m).array;
}

template <class T>
void Matrix<T>::operator -= (Matrix const &m)
{
    this->array = subtract(m).array;
}

template <class T>
void Matrix<T>::operator *= (Matrix const &m)
{
    this->array = multiply(m).array;
}

template <class T>
void Matrix<T>::operator += (T const &m)
{
    add(m);
}

template <class T>
void Matrix<T>::operator -= (T const &m)
{
    subtract(m);
}

template <class T>
void Matrix<T>::operator *= (T const &m)
{
    multiply(m);
}

template <class T>
T& Matrix<T>::operator() (int y, int x)
{
    assert(y < height && x < width);
    return array[y][x];
}

/* + operators */

template <class T>
Matrix<T> operator + (Matrix<T> const &a, Matrix<T> const &b)
{
    return a.add(b);
}

template <class T>
Matrix<T> operator + (Matrix<T> const &a, T const &b)
{
    Matrix<T> result = a;
    return result.add(b);
}

/* - operators */

template <class T>
Matrix<T> operator - (Matrix<T> const &a, Matrix<T> const &b)
{
    return a.subtract(b);
}

template <class T>
Matrix<T> operator - (Matrix<T> const &a, T const &b)
{
    Matrix<T> result = a;
    return result.subtract(b);
}

/* * operators */

template <class T>
Matrix<T> operator * (Matrix<T> const &a, Matrix<T> const &b)
{
    return a.multiply(b);
}

template <class T>
Matrix<T> operator * (Matrix<T> const &a, T const &b)
{
    Matrix<T> r = a;
    return r.multiply(b);
}

template <class T>
std::ostream& operator<<(std::ostream &flux, Matrix<T> const &m)
{
    m.print(flux);
    return flux;
}
