#pragma once

#include <cstdlib>
#include <cstring>
#include <stdexcept>
#include <initializer_list>

template<typename T>
concept Number = std::is_integral_v<T> || std::is_floating_point_v<T>;

template<Number NumT>
class Matrix {
public:
    Matrix() : mItems(nullptr), mRows(0), mCols(0) {}

    explicit Matrix(std::size_t rows, std::size_t cols) {
        if (!rows || !cols) {
            mItems = nullptr;
            mRows = 0;
            mCols = 0;
            return;
        }

        mItems = new NumT[cols * rows];
        mRows = rows;
        mCols = cols;
    }

    Matrix(const std::initializer_list<std::initializer_list<NumT>>& list) {
        if (!list.size() || !(*list.begin()).size()) {
            mItems = nullptr;
            mRows = 0;
            mCols = 0;
            return;
        }

        mRows = list.size();
        mCols = (*list.begin()).size();
        mItems = new NumT[mRows * mCols];

        std::size_t i = 0;
        for (auto row : list) {
            for (NumT elem : row) {
                mItems[i++] = elem;
            }
        }
    }

    Matrix(const Matrix& other) {
        if (!other.mItems) {
            mItems = nullptr;
            mRows = 0;
            mCols = 0;
            return;
        }

        mItems = new NumT[other.mCols * other.mRows];
        mRows = other.mRows;
        mCols = other.mCols;

        memcpy(mItems, other.mItems, sizeof(NumT) * mCols * mRows);
    }

    template<Number OtherNumT>
    friend class Matrix;

    template<Number OtherNumT>
    Matrix(const Matrix<OtherNumT>& other) {
        if (!other.mItems) {
            mItems = nullptr;
            mRows = 0;
            mCols = 0;
            return;
        }

        mItems = new NumT[other.mCols * other.mRows];
        mRows = other.mRows;
        mCols = other.mCols;

        for(std::size_t i = 0; i < mCols * mRows; ++i) {
            mItems[i] = static_cast<NumT>(other.mItems[i]);
        }
    }

    Matrix(Matrix&& other) noexcept {
        memcpy(this, &other, sizeof(Matrix));

        other.mItems = nullptr;
        other.mRows = other.mCols = 0;
    }

    void clear() {
        if (mItems) delete[] mItems;
        mItems = nullptr;
        mRows = 0;
        mCols = 0;
    }

    ~Matrix() {
        if (mItems) delete[] mItems;
    }

    Matrix& operator =(const Matrix& other) {
        if (this == &other)
            return *this;

        clear();

        if (!other.mItems) {
            return *this;
        }

        mItems = new NumT[other.mCols * other.mRows];
        mRows = other.mRows;
        mCols = other.mCols;

        memcpy(mItems, other.mItems, sizeof(NumT) * mCols * mRows);

        return *this;
    }

    Matrix& operator =(Matrix&& other) noexcept {
        if (this == &other)
            return *this;

        clear();

        memcpy(this, &other, sizeof(Matrix));

        other.mItems = nullptr;
        other.mRows = other.mCols = 0;

        return *this;
    }

    std::size_t rows() const {
        return mRows;
    }
    std::size_t cols() const {
        return mCols;
    }

    NumT& at(std::size_t i, std::size_t j) {
        if (i >= mRows || j >= mCols)
            throw std::out_of_range("invalid indeces to access at matrix: (" + std::to_string(i) + ", " + std::to_string(j) + ")");

        std::size_t index = i * mCols + j;
        return mItems[index];
    }

    const NumT& at(std::size_t i, std::size_t j) const {
        return const_cast<Matrix *>(this)->at(i, j);
    }

    const NumT *operator[](std::size_t i) const {
        return mItems + i * mCols;
    }

    bool operator ==(const Matrix& other) const {
        if (rows() != other.rows() || cols() != other.cols())
            return false;

        for (std::size_t i = 0; i < rows(); ++i) {
            for (std::size_t j = 0; j < cols(); ++j) {
                if (at(i, j) != other.at(i, j))
                    return false;
            }
        }

        return true;
    }

    void swap_rows(std::size_t row1, std::size_t row2) {
        for (std::size_t j = 0; j < mCols; ++j) {
            std::swap(at(row1, j), at(row2, j));
        }
    }

    void swap_cols(std::size_t col1, std::size_t col2) {
        for (std::size_t i = 0; i < mRows; ++i) {
            std::swap(at(i, col1), at(i, col2));
        }
    }

    void fill_random() {
        for (std::size_t i = 0; i < mRows * mCols; ++i) {
            int rand_int = rand();
            if (std::is_integral_v<NumT>) {
                mItems[i] = rand_int % 2;
            } else {
                mItems[i] = (float)rand_int / RAND_MAX;
            }
        }
    }
private:
    NumT* mItems;
    std::size_t mRows;
    std::size_t mCols;
};

