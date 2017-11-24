#pragma once

#include<ccdk/mpl/base/bool_.h>

namespace ccdk
{
	namespace mpl
	{
		template<typename T> struct is_class:public bool_<__is_class(T)>{};
		template<typename T> constexpr bool is_class_v = is_class<T>::value;
	}
}