#pragma once

#include<ccdk/mpl/mpl_module.h>
#include<ccdk/mpl/util/forward.h>
#include<ccdk/mpl/type_traits/decay.h>
#include<ccdk/mpl/type_traits/add_top_const.h>
#include<ccdk/mpl/mcontainer/arg_pack.h>
#include<ccdk/mpl/mcontainer/forward_.h>


ccdk_namespace_mpl_util_start

template<template<class...> class T>
struct create_t
{
	template<typename... Args>
	CCDK_FORCEINLINE constexpr auto operator()(Args&& ...args) const noexcept
	{
		return T<Args...>{  util::forward<Args>(args)... };
	}
};

template<template<class...> class T>
struct create_const_t
{
	template<typename... Args>
	CCDK_FORCEINLINE constexpr auto operator()(Args&& ...args) const noexcept
	{
		return T< add_top_const_t< Args> ...>{ util::forward<Args>(args)... };
	}
};

ccdk_namespace_mpl_util_end
