#pragma once

namespace ohtuzh {

    template<typename Iterator, typename T>
    Iterator find(Iterator begin, Iterator end, const T& val) {
        for (; begin != end && *begin != val; ++begin) {}
        return begin;
    }

    template<typename Iterator, typename Functor>
    Iterator find_if(Iterator begin, Iterator end, Functor functor) {
        for (; begin != end && !functor(*begin); ++begin) {}
        return begin;
    }

    template<typename Iterator, typename T>
    T accumulate(Iterator begin, Iterator end, T init) {
        for (; begin != end; ++begin) {
            init = init + *begin;
        }
        return init;
    }

    template<typename Iterator, typename T, typename BinaryOperation>
    T accumulate(Iterator begin, Iterator end, T init, BinaryOperation op) {
        for (; begin != end; ++begin) {
            init = op(init, *begin);
        }
        return init;
    }

} // namespace ohtuzh 
