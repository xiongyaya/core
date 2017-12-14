#pragma once

#include<ccdk/mpl/mpl_module.h>
#include<ccdk/mpl/util/forward.h>
#include<ccdk/mpl/type_traits/decay.h>
#include<ccdk/mpl/type_traits/add_top_const.h>
#include<ccdk/mpl/base/arg_pack_first.h>


ccdk_namespace_mpl_fn_start


	template<template<typename...> typename T>
	struct create_t
	{
		template<typename... Args>
		CCDK_FORCEINLINE constexpr 
		auto operator()(Args&& ...args) const noexcept
		{
			return T<decay_t<Args>...>{
				util::forward<Args>(args)...
			};
		}
	};

	template<template<typename...> typename T>
	struct create_raw_t
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
	struct create_const_raw_t
	{
		template<typename... Args>
		CCDK_FORCEINLINE constexpr
		auto operator()(Args&& ...args) const noexcept
		{
			//DebugTypeName<arg_pack_first_t<Args...>>();
			return T< add_top_const_t< Args> ...>{
				util::forward<Args>(args)...
			};
		}
	};

ccdk_namespace_mpl_fn_end