#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "../lib/algorithm.hpp"

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
    ASSERT_EQ(result, expect);
}
