/* Copyright (c) 2019 NXP Semiconductors
 *   
 * SPDX-License-Identifier: GPL3
 * Diego Dorta <diego.dorta@nxp.com>
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or 2 any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <https://www.gnu.org/licenses/>.
 */
#ifndef MATH_H
#define MATH_H

#include <assert.h>
#include <iostream>
#include <sstream>
#include <vector>

template <class T>
class Matrix
{
    public:
        Matrix<T>();        
        Matrix<T>(int height, int width);
        Matrix<T>(std::vector<std::vector<T>> const &array);
        
        Matrix<T> add(T const &value);
        Matrix<T> add(Matrix<T> const &m) const;
        
        Matrix<T> subtract(T const &value);
        Matrix<T> subtract(Matrix<T> const &m) const;
        
        Matrix<T> multiply(T const &value);
        Matrix<T> multiply(Matrix<T> const &m) const;        
        
        Matrix<T> dot(Matrix<T> const &m) const;
        Matrix<T> transpose() const;

        Matrix<T> applyFunction(T (*function)(T)) const;
        Matrix<T> subMatrix(int startHeight,
                            int startWidth,
                            int height,
                            int width) const;

        int getHeight();
        int getWidth();
        
        void fill(T const &value);
        void put(int h, int w, T const &value);
        T get(int h, int w) const;

        void print(std::ostream &flux) const;

        bool operator == (Matrix<T> const &m);
        bool operator != (Matrix<T> const &m);
        void operator += (Matrix<T> const &m);
        void operator -= (Matrix<T> const &m);
        void operator *= (Matrix<T> const &m);
        void operator += (T const &m);
        void operator -= (T const &m);
        void operator *= (T const &m);
        T& operator()(int y, int x);

    private:
        int height;
        int width;
        std::vector<std::vector<T>> array;
};

/* Include functions - modular */
#include "math.cpp"

#endif /* MATH_H defined */
