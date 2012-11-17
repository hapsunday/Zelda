/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    all_of.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZELDA_GUARD_ALGORITHM_ALL_OF_H
#define ZELDA_GUARD_ALGORITHM_ALL_OF_H

#include <zelda/function/builder.h>
#include <zelda/traits.h>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <boost/fusion/algorithm/query/all.hpp>
#include <algorithm>

#include <boost/bind.hpp>
#include <functional>

namespace zelda { 

ZELDA_FUNCTION_PIPE_OBJECT((all_of)(r, f)
        if (is_sequence<r>)(boost::fusion::all(r, f))
        else if (is_range<r>)(std::find_if(boost::begin(r), boost::end(r), boost::bind(std::logical_not<bool>(), boost::bind(f, _1))) != boost::end(r))

    )

}

#endif
