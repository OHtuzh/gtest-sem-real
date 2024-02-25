#include "gtest/gtest.h"
#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "../lib/algorithm.hpp"

#include <tuple>
#include <vector>
#include <string>

struct IsEven {
    bool operator()(int i) const {
        return i % 2 == 0;
    }
};

TEST(FIND, EmptyCase) {
    std::vector<int> v;
    const auto result = ohtuzh::find(v.begin(), v.end(), 4);
    const auto expect = v.end();
    ASSERT_EQ(result, expect);
}

TEST(FIND, FoundCase) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    const auto result = ohtuzh::find(v.begin(), v.end(), 4);
    const auto expect = v.begin() + 3;
    ASSERT_EQ(result, expect);
}

TEST(FIND, NotFoundCase) {
    const std::vector<std::string> v = {"abc", "def", "qwe"};
    auto result = ohtuzh::find(v.begin(), v.end(), "some val");
    auto expect = v.end();
    ASSERT_EQ(result, expect);
}

TEST(FIND_IF, FoundCase) {
    const std::vector v = {1, 2, 3, 4, 5};
    auto result = ohtuzh::find_if(v.begin(), v.end(), IsEven{});
    auto expect = v.begin() + 1;
    ASSERT_EQ(result, expect);
}

TEST(FIND_IF, NotFoundCase) {
    const std::vector v = {1, 3, 5, 7, 9};
    auto result = ohtuzh::find_if(v.begin(), v.end(), IsEven{});
    auto expect = v.end();
    ASSERT_EQ(result, expect) << "Found even element in odd container!";
}

TEST(ACCUMULATE, DefaultSumInts) {
    std::vector<int> v{1, 2, 3, 4, 5};
    ASSERT_EQ(ohtuzh::accumulate(v.begin(), v.end(), 0), 15);
}

TEST(ACCUMULATE, DefaultWithPositiveInit) {
    std::vector<int> v{1, 2, 3, 4, 5};
    ASSERT_EQ(ohtuzh::accumulate(v.begin(), v.end(), 1), 16);
}

TEST(ACCUMULATE, DefaultWithNegativeInit) {
    std::vector<int> v{1, 2, 3, 4, 5};
    ASSERT_EQ(ohtuzh::accumulate(v.begin(), v.end(), -1), 14);
}

TEST(ACCUMULATE, EmptyContainer) {
    std::vector<int> v;
    ASSERT_EQ(ohtuzh::accumulate(v.begin(), v.end(), 0), 0);
}

class AccumulateIntTest : public ::testing::TestWithParam<std::tuple<std::vector<int>, int, int>> {
};

TEST_P(AccumulateIntTest, SimpleAccumulateTest) {
    const auto& vector_int = std::get<0>(GetParam());
    int init_value = std::get<1>(GetParam());
    int expected = std::get<2>(GetParam());
    ASSERT_EQ(ohtuzh::accumulate(vector_int.begin(), vector_int.end(), init_value), expected);
}

INSTANTIATE_TEST_SUITE_P(
    ACCUMULATE_SIMPLE,
    AccumulateIntTest,
    ::testing::Values(
        std::make_tuple(std::vector<int>{1, 2, 3, 4, 5}, 0, 15),
        std::make_tuple(std::vector<int>{}, 0, 0),
        std::make_tuple(std::vector<int>{1, 2, 3, 4, 5}, 1, 16),
        std::make_tuple(std::vector<int>{1, 2, 3, 4, 5}, -1, 14)
    )
);

class AccumulateStringTest : public ::testing::TestWithParam<std::tuple<std::vector<std::string>, std::string, std::string>> {
};

TEST_P(AccumulateStringTest, SimpleAccumulateTest) {
    const auto& vector_str = std::get<0>(GetParam());
    std::string init_value = std::get<1>(GetParam());
    std::string expected = std::get<2>(GetParam());
    ASSERT_EQ(ohtuzh::accumulate(vector_str.begin(), vector_str.end(), init_value), expected);
}

INSTANTIATE_TEST_SUITE_P(
    ACCUMULATE_SIMPLE,
    AccumulateStringTest,
    ::testing::Values(
        std::make_tuple(std::vector<std::string>{"Hello", ", world!"}, "", "Hello, world!")
    )
);

// The Best Testing Case:

template<typename T>
using AccumlateTestCases = std::vector<std::tuple<std::vector<T>, T, T>>;

const std::tuple<AccumlateTestCases<int>, AccumlateTestCases<std::string>> AllAccumlateTestCases = {
    {
        std::make_tuple(std::vector<int>{1, 2, 3, 4, 5}, 0, 15),
        std::make_tuple(std::vector<int>{}, 0, 0),
        std::make_tuple(std::vector<int>{1, 2, 3, 4, 5}, 1, 16),
        std::make_tuple(std::vector<int>{1, 2, 3, 4, 5}, -1, 14)
    },
    {
        std::make_tuple(std::vector<std::string>{"Hello", ", world!"}, "", "Hello, world!"),
        std::make_tuple(std::vector<std::string>{"Hello", ", world!"}, "Hi! ", "Hi! Hello, world!")
    }
};

template<typename T>
class AccumulateAnyTest : public ::testing::Test {
public:
    AccumulateAnyTest() : accumlate_test_case_(std::get<AccumlateTestCases<T>>(AllAccumlateTestCases)) {}

protected:
    AccumlateTestCases<T> accumlate_test_case_;
};

using AccumulateTestTypes = ::testing::Types<int, std::string>;

TYPED_TEST_SUITE(AccumulateAnyTest, AccumulateTestTypes);

TYPED_TEST(AccumulateAnyTest, AccumulateSimpleTest) {
    for (const auto& test_case: this->accumlate_test_case_) {
        const auto& data = std::get<0>(test_case);
        const auto& init = std::get<1>(test_case);
        const auto& expected = std::get<2>(test_case);
        ASSERT_EQ(ohtuzh::accumulate(data.begin(), data.end(), init), expected);
    }
}
