/*
@copyright Louis Dionne 2014
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#include <boost/hana/lazy.hpp>

#include <boost/hana/detail/assert.hpp>
#include <boost/hana/detail/constexpr.hpp>
#include <boost/hana/detail/injection.hpp>
#include <boost/hana/detail/number/comparable.hpp>

#include "comparable.hpp"
using namespace boost::hana;


BOOST_HANA_CONSTEXPR_LAMBDA auto f = detail::injection([]{});

BOOST_HANA_CONSTEXPR_LAMBDA auto invalid = [](auto x) {
    return x.this_function_must_not_be_instantiated;
};

template <int i>
constexpr auto x = detail::number<>(i);

int main() {
    // ap
    {
        BOOST_HANA_CONSTEXPR_ASSERT(equal(ap(lazy(f), lazy(x<0>)), lazy(f(x<0>))));
        BOOST_HANA_CONSTEXPR_ASSERT(equal(ap(lazy(f), lazy(x<0>), lazy(x<1>)), lazy(f(x<0>, x<1>))));
        BOOST_HANA_CONSTEXPR_ASSERT(equal(ap(lazy(f), lazy(x<0>), lazy(x<1>), lazy(x<2>)), lazy(f(x<0>, x<1>, x<2>))));

        // The function is not applied.
        ap(lazy(invalid), lazy(x<0>));
        ap(lazy(invalid), lazy(x<0>), lazy(x<1>));
        ap(lazy(invalid), lazy(x<0>), lazy(x<1>), lazy(x<2>));
    }

    // lift
    {
        BOOST_HANA_CONSTEXPR_ASSERT(equal(lift<Lazy>(x<0>), lazy(x<0>)));
        BOOST_HANA_CONSTEXPR_ASSERT(equal(lift<Lazy>(x<1>), lazy(x<1>)));
    }
}
