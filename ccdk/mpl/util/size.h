#pragma once

#include<ccdk/mpl/mpl_module.h>
#include<ccdk/mpl/base/compile_check.h>
#include<ccdk/mpl/type_traits/declval.h>
ccdk_namespace_mpl_util_start


#if defined( CCDK_COMPILER_MSVC ) 

//no suitable implements found, for msvc-17+ to  to get detail line and file error place
template< typename T, typename = check_t<false_> >
CCDK_FORCEINLINE void size(const T&) {}
template< typename T, typename = check_t<false_> >
CCDK_FORCEINLINE bool empty(const T&) { return false;  }


#elif defined( CCDK_COMPILER_GCC )

//no suitable implements found, for gcc  to get detail line and file error place 
template< typename T>
CCDK_FORCEINLINE void size(const T&);
template< typename T>
CCDK_FORCEINLINE bool empty(const T&);

#else //clang or some compiler not found suitable method

template< typename T>
CCDK_FORCEINLINE void size(const T&)
{
	static_assert(false_::value, "no suitable size function found");
}

template< typename T>
CCDK_FORCEINLINE bool empty(const T&)
{
	static_assert(false_::value, "no suitable size function found");
	return false;
}
#endif

template<typename T>
struct has_member_size
{
	template<typename P, typename = decltype( declval<P>().size() )>
	bool sfinae(int) { return true; }
	template<typename P>
	bool sfinae(...) { return false; }
	static constexpr bool value = sfinae<T>(0);
};


/* default call size(), need check has function T::size() */
template<typename Container, typename = check_t< has_member_size<Container>  >
CCDK_FORCEINLINE void size(const Container& ct) noexcept { return ct.size(); }

template<typename Container, typename = check_t< has_member_size<Container>  >
CCDK_FORCEINLINE bool empty(const Container& ct) noexcept { return ct.size()==0; }

ccdk_namespace_mpl_util_end
