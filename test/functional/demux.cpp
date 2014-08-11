/*
@copyright Louis Dionne 2014
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#include <boost/hana/functional.hpp>

#include <boost/hana/detail/assert.hpp>
#include <boost/hana/detail/constexpr.hpp>
#include <boost/hana/detail/injection.hpp>
using namespace boost::hana;


BOOST_HANA_CONSTEXPR_LAMBDA auto f = detail::injection([]{});
BOOST_HANA_CONSTEXPR_LAMBDA auto g = detail::injection([]{});
BOOST_HANA_CONSTEXPR_LAMBDA auto h = detail::injection([]{});

int main() {
    BOOST_HANA_CONSTANT_ASSERT(equal(demux(f)(), f()));

    BOOST_HANA_CONSTEXPR_ASSERT(equal(demux(f, g)(1), f(g(1))));
    BOOST_HANA_CONSTEXPR_ASSERT(equal(demux(f, g)(1, '2'), f(g(1, '2'))));
    BOOST_HANA_CONSTEXPR_ASSERT(equal(demux(f, g)(1, '2', 3.3), f(g(1, '2', 3.3))));

    BOOST_HANA_CONSTEXPR_ASSERT(equal(demux(f, g, h)(1), f(g(1), h(1))));
    BOOST_HANA_CONSTEXPR_ASSERT(equal(demux(f, g, h)(1, '2'), f(g(1, '2'), h(1, '2'))));
    BOOST_HANA_CONSTEXPR_ASSERT(equal(demux(f, g, h)(1, '2', 3.3), f(g(1, '2', 3.3), h(1, '2', 3.3))));
}
