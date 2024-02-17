#pragma once

#include <cinttypes>
#include <stdexcept>
#include <initializer_list>

namespace ohtuzh {

    template<typename T, size_t Size>
    class array {
    public:
        using value_type = T;

        array() = default;

        array(std::initializer_list<T> il) {
            if (il.size() > Size) {
                throw std::out_of_range("Initializer list is grather than size of vector");
            }
            size_t i = 0;
            for (const T& value: il) {
                data_[i] = value;
                ++i;
            }
        }

        T& operator[](const size_t index) {
            return data_[index];
        }

        const T& operator[](const size_t index) const {
            return data_[index];
        }

        T& at(const size_t index) {
            if (index >= Size) {
                throw std::out_of_range("Index out of a range");
            }
            return data_[index];
        }

        const T& at(const size_t index) const {
            if (index >= Size) {
                throw std::out_of_range("Index out of a range");
            }
            return data_[index];
        }

        T* begin() {
            return data_;
        }

        const T* begin() const {
            return data_;
        }

        T* end() {
            return data_ + Size;
        }

        const T* end() const {
            return data_ + Size;
        }

        size_t size() const {
            return Size;
        }

        ~array() = default;

    private:
        T data_[Size] {};
    };

} // namespace ohtuzh
