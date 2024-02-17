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


} // namespace ohtuzh 
