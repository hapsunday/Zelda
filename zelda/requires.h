/* 
 * File:   requires.h
 * Author: pfultz
 *
 * Created on November 17, 2011, 8:47 PM
 */

#ifndef ZELDA_REQUIRES_H
#define	ZELDA_REQUIRES_H

#include <zelda/tpl/integral_constant.h>
#include <zelda/tpl/fold.h>
#include <zelda/tpl/identity.h>
#include <zelda/tpl/type_list.h>
#include <zelda/pp.h>

namespace zelda{namespace requires_detail{
struct not_tag {};

template<class ... T>
struct requires_ 
{
    template<class X>
    struct not_state : X {};

    struct op
    {
        template<class X, class Y>
        struct apply
        : zelda::tpl::bool_<X::type::value and Y::type::value> {};

        template<class X>
        struct apply<X, not_tag>
        : zelda::tpl::identity<not_state<X> > {};

        template<class X, class Y>
        struct apply<not_state<X>, Y>
        : zelda::tpl::bool_<X::type::value and not Y::type::value> {};
    };

    typedef typename zelda::tpl::fold<zelda::tpl::type_list<T...>, zelda::tpl::bool_<true>, op>::type type;
};
}
}
#define ZELDA_DETAIL_REQUIRES_CLAUSE_DEFAULT(x) (x)
#define ZELDA_DETAIL_REQUIRES_CLAUSE_NOT(t, x) (zelda::requires_detail::not_tag)(x)
#define ZELDA_DETAIL_REQUIRES_CLAUSE_EACH(r, x) PP_TOKEN_TRANSFORM(not, ZELDA_DETAIL_REQUIRES_CLAUSE_NOT, ZELDA_DETAIL_REQUIRES_CLAUSE_DEFAULT, x)
#define ZELDA_DETAIL_REQUIRES_CLAUSE(...) zelda::requires_detail::requires_<PP_SEQ_ENUM(PP_SEQ_FOR_EACH(ZELDA_DETAIL_REQUIRES_CLAUSE_EACH, PP_ARGS_TO_SEQ(__VA_ARGS__)))>


#ifdef ZELDA_TEST
static_assert(ZELDA_DETAIL_REQUIRES_CLAUSE(zelda::tpl::bool_<true>)::type::value, "Failed");
static_assert(ZELDA_DETAIL_REQUIRES_CLAUSE(zelda::tpl::bool_<true>, zelda::tpl::bool_<true>)::type::value, "Failed");
static_assert(ZELDA_DETAIL_REQUIRES_CLAUSE(zelda::tpl::bool_<true>, not zelda::tpl::bool_<false>)::type::value, "Failed");
static_assert(ZELDA_DETAIL_REQUIRES_CLAUSE(not zelda::tpl::bool_<false>, zelda::tpl::bool_<true>)::type::value, "Failed");
static_assert(ZELDA_DETAIL_REQUIRES_CLAUSE(not zelda::tpl::bool_<false>)::type::value, "Failed");
#endif

//#define ZELDA_DETAIL_REQUIRES_CLAUSE(...) zelda::tpl::and_<__VA_ARGS__>

/**
 * The ZELDA_FUNCTION_REQUIRES macro is used to place conditions on template 
 * functions. NOTE: If an error occurs here it is because you are most likely
 * missing the return type, or the return type is missing parenthesis around it.
 * 
 * The macro is used in this way:
 *      ZELDA_FUNCTION_REQUIRES(Cond)(ReturnType)
 * Cond: Is the condition the function requires
 * ReturnType: Is the return type of the function
 * 
 * Here is an exatple of a sum function, that sums two numbers and requires the 
 * type to be numeric:
 *      template<class T>
 *      ZELDA_FUNCTION_REQUIRES(is_numeric<T>)(T)
 *      sum(T x, T y) { return x+y; }
 * 
 * 
 */
#define ZELDA_ERROR_PARENTHESIS_MUST_BE_PLACED_AROUND_THE_RETURN_TYPE(...) __VA_ARGS__>::type
#define ZELDA_FUNCTION_REQUIRES(...) typename zelda::tpl::if_<ZELDA_DETAIL_REQUIRES_CLAUSE(__VA_ARGS__), ZELDA_ERROR_PARENTHESIS_MUST_BE_PLACED_AROUND_THE_RETURN_TYPE
#define ZELDA_EXCLUDE(...) typename zelda::tpl::not_<typename zelda::tpl::or_<__VA_ARGS__>::type >::type

#define ZELDA_CLASS_REQUIRES(...) typename zelda::tpl::if_<ZELDA_DETAIL_REQUIRES_CLAUSE(__VA_ARGS__)>::type

#define ZELDA_REQUIRES(...) class Zelda_Enable = typename zelda::tpl::if_<ZELDA_DETAIL_REQUIRES_CLAUSE(__VA_ARGS__)>::type


#endif	/* ZELDA_REQUIRES_H */

