#include "gtest/gtest.h"
#include <exception>
#include <gtest/gtest.h>

#include <gmock/gmock.h>
#include <stdexcept>

#include "../lib/array.hpp"


TEST(ARRAY_INIT, Full) {
    using array_type = ohtuzh::array<double, 5>;
    ASSERT_NO_THROW(array_type({1.0, 2.0, 3.1, 4.5, 5.7}));
}

TEST(ARRAY_INIT, Correct) {
    ohtuzh::array<int, 5> arr = {1, 2, 3, 4, 5};
    ASSERT_THAT(arr, testing::ElementsAre(1, 2, 3, 4, 5));
}

TEST(ARRAY_AT, NormalCase) {
    ohtuzh::array<int, 5> arr = {1, 2, 3, 4, 5};
    ASSERT_EQ(arr.at(2), 3);
}

TEST(ARRAY_AT, ExceptionCase) {
    ohtuzh::array<int, 5> arr = {1, 2, 3, 4, 5};
    ASSERT_THROW(arr.at(999), std::out_of_range);
}

#define MY_ASSERT_ANY_THROW(expr)   \
    try {                           \
        expr;                       \
        ASSERT_TRUE(false);         \
    } catch(...) {                  \
        ASSERT_TRUE(true);          \
    }                               \

TEST(ARRAY_AT, ExceptionCaseWithMyAssert) {
    ohtuzh::array<int, 5> arr = {1, 2, 3, 4, 5};
    MY_ASSERT_ANY_THROW(arr.at(999));
}
