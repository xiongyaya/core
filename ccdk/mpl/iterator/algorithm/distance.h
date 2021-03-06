#pragma once

#include<ccdk/mpl/base/compile_check.h>
#include<ccdk/mpl/iterator/iterator_traits.h>

ccdk_namespace_mpl_it_start

namespace alg_impl
{
	template<typename InputIt>
	CCDK_FORCEINLINE ptr::size_t distance_impl(InputIt begin, InputIt end, input_category) noexcept{
		ptr::size_t count = 0;
		for (; begin != end; ++begin, ++count);
		return count;
	}

	template<typename RandomIt>
	CCDK_FORCEINLINE ptr::size_t distance_impl(RandomIt begin, RandomIt end, random_category) noexcept{
		return end - begin;
	}
}

template<typename It>
CCDK_FORCEINLINE ptr::size_t distance(It begin, It end) noexcept{
	return alg_impl::distance_impl(begin, end, iterator_category_c<It>);
}

ccdk_namespace_mpl_it_end