/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    perfect_facade.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZELDA_GUARD_C03_PERFECT_FACADE_H
#define ZELDA_GUARD_C03_PERFECT_FACADE_H

#include <zelda/pp.h>
#include <zelda/config.h>
#include <zelda/function/result_of.h>
#include <zelda/forward.h>

// (()())       ((const)())
// (()(const))  ((const)(const))

#define ZELDA_PERFECT_ITERATE_END(...) ZELDA_PERFECT_ITERATE_END_I(__VA_ARGS__)
#define ZELDA_PERFECT_ITERATE_END_I(...) __VA_ARGS__ ## _EOF

#define ZELDA_PERFECT_PRODUCT_SEQ(n) BOOST_PP_CAT(ZELDA_PERFECT_PRODUCT_SEQ_, n)((())((const)))
#define ZELDA_PERFECT_PRODUCT_SEQ_1(x) x
#define ZELDA_PERFECT_PRODUCT_SEQ_2(x) ZELDA_PERFECT_PRODUCT_SEQ_1(ZELDA_PERFECT_PRODUCT_SEQ_STEP(x))
#define ZELDA_PERFECT_PRODUCT_SEQ_3(x) ZELDA_PERFECT_PRODUCT_SEQ_2(ZELDA_PERFECT_PRODUCT_SEQ_STEP(x))
#define ZELDA_PERFECT_PRODUCT_SEQ_4(x) ZELDA_PERFECT_PRODUCT_SEQ_3(ZELDA_PERFECT_PRODUCT_SEQ_STEP(x))
#define ZELDA_PERFECT_PRODUCT_SEQ_5(x) ZELDA_PERFECT_PRODUCT_SEQ_4(ZELDA_PERFECT_PRODUCT_SEQ_STEP(x))
#define ZELDA_PERFECT_PRODUCT_SEQ_6(x) ZELDA_PERFECT_PRODUCT_SEQ_5(ZELDA_PERFECT_PRODUCT_SEQ_STEP(x))
#define ZELDA_PERFECT_PRODUCT_SEQ_7(x) ZELDA_PERFECT_PRODUCT_SEQ_6(ZELDA_PERFECT_PRODUCT_SEQ_STEP(x))
#define ZELDA_PERFECT_PRODUCT_SEQ_8(x) ZELDA_PERFECT_PRODUCT_SEQ_7(ZELDA_PERFECT_PRODUCT_SEQ_STEP(x))
#define ZELDA_PERFECT_PRODUCT_SEQ_9(x) ZELDA_PERFECT_PRODUCT_SEQ_8(ZELDA_PERFECT_PRODUCT_SEQ_STEP(x))
#define ZELDA_PERFECT_PRODUCT_SEQ_10(x) ZELDA_PERFECT_PRODUCT_SEQ_9(ZELDA_PERFECT_PRODUCT_SEQ_STEP(x))
#define ZELDA_PERFECT_PRODUCT_SEQ_11(x) ZELDA_PERFECT_PRODUCT_SEQ_10(ZELDA_PERFECT_PRODUCT_SEQ_STEP(x))
#define ZELDA_PERFECT_PRODUCT_SEQ_12(x) ZELDA_PERFECT_PRODUCT_SEQ_11(ZELDA_PERFECT_PRODUCT_SEQ_STEP(x))
#define ZELDA_PERFECT_PRODUCT_SEQ_13(x) ZELDA_PERFECT_PRODUCT_SEQ_12(ZELDA_PERFECT_PRODUCT_SEQ_STEP(x))
#define ZELDA_PERFECT_PRODUCT_SEQ_14(x) ZELDA_PERFECT_PRODUCT_SEQ_13(ZELDA_PERFECT_PRODUCT_SEQ_STEP(x))
#define ZELDA_PERFECT_PRODUCT_SEQ_15(x) ZELDA_PERFECT_PRODUCT_SEQ_14(ZELDA_PERFECT_PRODUCT_SEQ_STEP(x))
#define ZELDA_PERFECT_PRODUCT_SEQ_16(x) ZELDA_PERFECT_PRODUCT_SEQ_15(ZELDA_PERFECT_PRODUCT_SEQ_STEP(x))
#define ZELDA_PERFECT_PRODUCT_SEQ_17(x) ZELDA_PERFECT_PRODUCT_SEQ_16(ZELDA_PERFECT_PRODUCT_SEQ_STEP(x))
#define ZELDA_PERFECT_PRODUCT_SEQ_18(x) ZELDA_PERFECT_PRODUCT_SEQ_17(ZELDA_PERFECT_PRODUCT_SEQ_STEP(x))
#define ZELDA_PERFECT_PRODUCT_SEQ_19(x) ZELDA_PERFECT_PRODUCT_SEQ_18(ZELDA_PERFECT_PRODUCT_SEQ_STEP(x))
#define ZELDA_PERFECT_PRODUCT_SEQ_20(x) ZELDA_PERFECT_PRODUCT_SEQ_20(ZELDA_PERFECT_PRODUCT_SEQ_STEP(x))

#define ZELDA_PERFECT_PRODUCT_SEQ_STEP(seq) ZELDA_PERFECT_ITERATE_END(ZELDA_PERFECT_PRODUCT_SEQ_STEP_1 seq) 
#define ZELDA_PERFECT_PRODUCT_SEQ_STEP_1(tail) (() tail) ((const) tail) ZELDA_PERFECT_PRODUCT_SEQ_STEP_2
#define ZELDA_PERFECT_PRODUCT_SEQ_STEP_2(tail) (() tail) ((const) tail) ZELDA_PERFECT_PRODUCT_SEQ_STEP_1
#define ZELDA_PERFECT_PRODUCT_SEQ_STEP_1_EOF
#define ZELDA_PERFECT_PRODUCT_SEQ_STEP_2_EOF


#define ZELDA_PERFECT_FACADE_SEQ(seq) ZELDA_PERFECT_ITERATE_END(ZELDA_PERFECT_FACADE_SEQ_1 seq)
#define ZELDA_PERFECT_FACADE_SEQ_1(seq) ZELDA_PERFECT_FACADE_OP(BOOST_PP_SEQ_SIZE(seq), seq) ZELDA_PERFECT_FACADE_SEQ_2
#define ZELDA_PERFECT_FACADE_SEQ_2(seq) ZELDA_PERFECT_FACADE_OP(BOOST_PP_SEQ_SIZE(seq), seq) ZELDA_PERFECT_FACADE_SEQ_1
#define ZELDA_PERFECT_FACADE_SEQ_1_EOF
#define ZELDA_PERFECT_FACADE_SEQ_2_EOF

#define ZELDA_PERFECT_FACADE_PARAMS_R(r, seq, ...) BOOST_PP_SEQ_FOR_EACH_I_R(r, ZELDA_PERFECT_FACADE_PARAMS_EACH, (__VA_ARGS__), seq) 
#define ZELDA_PERFECT_FACADE_PARAMS_EACH(r, data, i, const_) BOOST_PP_COMMA_IF(i) const_ ZELDA_PP_VARN_CAT(i, data)

#define ZELDA_PERFECT_FACADE_FORWARD_R(r, seq, T, x) BOOST_PP_SEQ_FOR_EACH_I_R(r, ZELDA_PERFECT_FACADE_FORWARD_EACH, (T, x), seq)
#define ZELDA_PERFECT_FACADE_FORWARD_EACH(r, data, i, const_) BOOST_PP_COMMA_IF(i) \
zelda::forward<const_ BOOST_PP_CAT(BOOST_PP_TUPLE_ELEM(2, 0, data), i)>\
( BOOST_PP_CAT(BOOST_PP_TUPLE_ELEM(2, 1, data), i) )

#define ZELDA_PERFECT_FACADE_OP(n, seq) \
template<ZELDA_PP_PARAMS_Z(2, n, class T)> \
typename zelda::result_of<zelda_private_perfect_facade_function_type(ZELDA_PERFECT_FACADE_PARAMS_R(1, seq, T, & BOOST_PP_INTERCEPT))>::type \
operator()(ZELDA_PERFECT_FACADE_PARAMS_R(1, seq, T, & x)) const \
{ return this->zelda_private_perfect_facade_function()( ZELDA_PERFECT_FACADE_FORWARD_R(1, seq, T, x) ); }

#define ZELDA_DETAIL_PERFECT_FACADE(z, n, data) \
ZELDA_PERFECT_FACADE_SEQ(ZELDA_PERFECT_PRODUCT_SEQ(n))

#define ZELDA_PERFECT_FACADE(type, f) \
typedef type zelda_private_perfect_facade_function_type; \
type zelda_private_perfect_facade_function() const \
{ \
    return f; \
} \
BOOST_PP_REPEAT_FROM_TO_1(1, ZELDA_PARAMS_LIMIT, ZELDA_DETAIL_PERFECT_FACADE, ~)

// Template parameters
#define ZELDA_PERFECT_FACADE_SEQ_TPL(tpl, seq) ZELDA_PERFECT_ITERATE_END(ZELDA_PERFECT_FACADE_SEQ_1_ ## tpl seq)
#define ZELDA_PERFECT_FACADE_SEQ_1_class(seq) ZELDA_PERFECT_FACADE_OP(BOOST_PP_SEQ_SIZE(seq), seq) ZELDA_PERFECT_FACADE_SEQ_2_class
#define ZELDA_PERFECT_FACADE_SEQ_2_class(seq) ZELDA_PERFECT_FACADE_OP(BOOST_PP_SEQ_SIZE(seq), seq) ZELDA_PERFECT_FACADE_SEQ_1_class
#define ZELDA_PERFECT_FACADE_SEQ_1_class_EOF
#define ZELDA_PERFECT_FACADE_SEQ_2_class_EOF

#define ZELDA_PERFECT_FACADE_SEQ_1_int(seq) ZELDA_PERFECT_FACADE_OP(BOOST_PP_SEQ_SIZE(seq), seq) ZELDA_PERFECT_FACADE_SEQ_2_int
#define ZELDA_PERFECT_FACADE_SEQ_2_int(seq) ZELDA_PERFECT_FACADE_OP(BOOST_PP_SEQ_SIZE(seq), seq) ZELDA_PERFECT_FACADE_SEQ_1_int
#define ZELDA_PERFECT_FACADE_SEQ_1_int_EOF
#define ZELDA_PERFECT_FACADE_SEQ_2_int_EOF

#define ZELDA_PERFECT_FACADE_SEQ_1_long(seq) ZELDA_PERFECT_FACADE_OP(BOOST_PP_SEQ_SIZE(seq), seq) ZELDA_PERFECT_FACADE_SEQ_2_long
#define ZELDA_PERFECT_FACADE_SEQ_2_long(seq) ZELDA_PERFECT_FACADE_OP(BOOST_PP_SEQ_SIZE(seq), seq) ZELDA_PERFECT_FACADE_SEQ_1_long
#define ZELDA_PERFECT_FACADE_SEQ_1_long_EOF
#define ZELDA_PERFECT_FACADE_SEQ_2_long_EOF

#define ZELDA_PERFECT_FACADE_OP_TPL(tpl, n, seq) \
template<tpl T_ ## tpl, ZELDA_PP_PARAMS_Z(2, n, class T)> \
typename zelda::result_of<typename zelda_private_perfect_facade_function_type<T_ ## tpl>::type(ZELDA_PERFECT_FACADE_PARAMS_R(1, seq, T, & BOOST_PP_INTERCEPT))>::type \
operator()(ZELDA_PERFECT_FACADE_PARAMS_R(1, seq, T, & x)) const \
{ return this->zelda_private_perfect_facade_function<T_ ## tpl>()( ZELDA_PERFECT_FACADE_FORWARD_R(1, seq, T, x) ); }

#define ZELDA_DETAIL_PERFECT_FACADE_TPL(z, n, tpl) \
ZELDA_PERFECT_FACADE_SEQ_TPL(tpl, ZELDA_PERFECT_PRODUCT_SEQ(n))

#define ZELDA_PERFECT_FACADE_TPL(type_, f, tpl) \
template<tpl T_ ## tpl> \
struct zelda_private_perfect_facade_function_type { typedef type_ type; }; \
typedef type zelda_private_perfect_facade_function_type; \
template<tpl T_ ## tpl>
type_ zelda_private_perfect_facade_function() const \
{ \
    return f; \
} \
BOOST_PP_REPEAT_FROM_TO_1(1, ZELDA_PARAMS_LIMIT, ZELDA_DETAIL_PERFECT_FACADE_TPL, tpl)


#endif
