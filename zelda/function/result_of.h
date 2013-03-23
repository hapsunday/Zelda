/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    result_of.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZELDA_GUARD_RESULT_OF_H
#define ZELDA_GUARD_RESULT_OF_H

#include <zelda/function/is_callable.h>
#include <zelda/requires.h>
#include <boost/utility/result_of.hpp>
#include <boost/mpl/assert.hpp>

namespace zelda {

namespace detail {

template<class F>
struct result_check : boost::mpl::bool_<true>
{
};

template<class T1, class T2>
struct result_assert
{
    typedef typename boost::is_convertible<T1, T2>::type type;
    static_assert(type::value, "result_of protocol has incorrect return type");
};

#ifndef ZELDA_NO_VARIADIC_TEMPLATES
template<class F, class... T>
struct result_check<F(T...)>
: result_assert
< 
    ZELDA_XTYPEOF_TPL(zelda::declval<F>()(zelda::declval<T>()...)),
    typename boost::result_of<F(T...)>::type
>
{
};

#else

#define ZELDA_RESULT_OF_CHECK(z, n, data) \
template<class F BOOST_PP_COMMA_IF(n) ZELDA_PP_PARAMS_Z(z, n, class T)> \
struct result_check<F(ZELDA_PP_PARAMS_Z(z, n, T))> \
: result_assert \
<  \
    ZELDA_XTYPEOF_TPL( zelda::declval<F>()(ZELDA_PP_PARAMS_Z(z, n, zelda::declval<T, >() BOOST_PP_INTERCEPT)) ), \
    typename boost::result_of<F(ZELDA_PP_PARAMS_Z(z, n, T))>::type \
> \
{};
BOOST_PP_REPEAT_1(ZELDA_PARAMS_LIMIT, ZELDA_RESULT_OF_CHECK, ~)

#endif

template<class F, class Enable = void>
struct result_of_impl
{
};


template<class F>
struct result_of_impl<F, ZELDA_CLASS_REQUIRES(is_callable<F>)>
: boost::result_of<F> 
{
};

}

template<class Sig, class F=void, class Enable=void>
struct result_of;

template<class Sig>
struct result_of<Sig, void, void>
: detail::result_of_impl<Sig>
{};

#ifndef ZELDA_NO_VARIADIC_TEMPLATES

template<class F, class X, class... T>
struct result_of<F(T...), X, ZELDA_CLASS_REQUIRES(exclude boost::is_void<X>)>
: detail::result_of_impl<X(T...)>
{};

#else

#define ZELDA_RESULT_OF_GENERATE(z, n, data) \
template<class F, class X BOOST_PP_COMMA_IF(n) ZELDA_PP_PARAMS_Z(z, n, class T)> \
struct result_of<F(ZELDA_PP_PARAMS_Z(z, n, T)), X, ZELDA_CLASS_REQUIRES(exclude boost::is_void<X>)> \
: detail::result_of_impl<X(ZELDA_PP_PARAMS_Z(z, n, T))> \
{ \
};
BOOST_PP_REPEAT_1(ZELDA_PARAMS_LIMIT, ZELDA_RESULT_OF_GENERATE, ~)
#undef ZELDA_RESULT_OF_GENERATE

#endif

#ifdef ZELDA_TEST
namespace result_of_test {
    
struct no_result
{};

struct has_result
{
    template<class S>
    struct result
    {
        typedef S type;
    };
};

// typedef result_of<no_result>::apply_function<has_result> test1;
// typedef result_of<no_result()>::apply_function<has_result> test2;
}
#endif

}





#endif