#pragma once
#include<ccdk/mpl/mpl_module.h>

ccdk_namespace_mpl_sp_start

	struct normal_deleter
	{
		template<typename T>
		constexpr void operator()(T*& t)
		{
			ptr::safe_delete(t);
		}
	};

	struct normal_derive_deleter
	{
		template<typename T>
		constexpr void __delete(T*& t)
		{
			ptr::safe_delete(t);
		}
	};

	struct normal_array_deleter
	{
		template<typename T>
		constexpr void operator()(T*& t)
		{
			ptr::safe_delete_array(t);
		}
	};

	struct normal_derive_array_deleter
	{
		template<typename T>
		constexpr void __delete(T*& t)
		{
			ptr::safe_delete_array(t);
		}
	};
ccdk_namespace_mpl_sp_end