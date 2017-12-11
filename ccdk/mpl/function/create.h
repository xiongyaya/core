#pragma once

#include<ccdk/type.h>
#include<ccdk/compile.h>
#include<ccdk/mpl/util/forward.h>
#include<ccdk/mpl/type_traits/decay.h>


namespace ccdk
{
	namespace mpl
	{
		namespace fn_detail
		{
			template<template<typename...> typename T>
			struct create
			{
				template<typename... Args>
				CCDK_FORCEINLINE constexpr 
				auto  operator()(Args&& ...args) const noexcept
				{
					return T<decay_t<Args>...>{
						util::forward<Args>(args)...
					};
				}
			};

			template<template<typename...> typename T>
			struct create_raw
			{
				template<typename... Args>
				CCDK_FORCEINLINE constexpr 
				auto  operator()(Args&& ...args) const noexcept
				{
					return T<Args...>{ 
						util::forward<Args>(args)...
					};
				}
			};

			template<template<typename...> typename T>
			struct create_const_raw
			{
				template<typename... Args>
				CCDK_FORCEINLINE constexpr
				auto operator()(Args&& ...args) const noexcept
				{
					return T<Args const...>{ 
						util::forward<Args>(args)...
					};
				}
			};
		}
	}
}