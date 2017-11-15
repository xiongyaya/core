#pragma once

#include<core/mpl/base/bool_.h>
#include<core/mpl/type_traits/declval.h>

namespace core
{
	namespace mpl
	{
		template<typename F, typename T>
		struct is_convertible_helper
		{
			static constexpr void test(const T&) {}

			template<typename U, typename = decltype(test(declval<U>()))>
			static constexpr bool sfinae(int) { return true; }
			template<typename U> static constexpr bool sfinae(...) { return false; }
			static constexpr bool value = sfinae<F>(0);
		};

		template<typename From, typename To> struct is_convertible : bool_<is_convertible_helper<From, To>::value> {};
		template<typename From, typename To> constexpr bool is_convertible_v = is_convertible<From, To>::value;
	}
}