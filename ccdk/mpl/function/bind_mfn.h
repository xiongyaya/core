#pragma once

#include<ccdk/mpl/base/enable_if.h>
#include<ccdk/mpl/type_traits/remove_const.h>
#include<ccdk/mpl/type_traits/is_mfn_ptr.h>
#include<ccdk/mpl/util/addressof.h>

namespace ccdk
{
	namespace mpl
	{
		namespace fn_detail
		{
			template<
				typename F,
				typename C,
				typename Ret,
				typename... Args
			>
			struct member_function_t
			{
				//keep member function pointer
				F  fn;
				//keep object pointer
				C *obj; 


				member_function_t(const member_function_t&) = default;

				CCDK_FORCEINLINE
				member_function_t( F inFn, const C& inObj) noexcept
					:fn( inFn ),
					obj( util::addressof(inObj) )
				{}

				CCDK_FORCEINLINE
				Ret operator()(
					Args... args
					) const noexcept
				{
					return (obj->*fn)(args...);
				}
			};

			struct bind_mfn_t
			{
				template<
					typename F,
					typename C,
					typename Ret,
					typename... Args
				>
					CCDK_FORCEINLINE
					auto 
					bind_mfn_impl(
						F f,
						C* c,
						arg_pack<Args...>
					) const noexcept
				{
					return member_function_t< F, C, Ret, Args...>(f, c);
				}

				template<
					typename F,
					typename B = mfn_traits<F>,
					typename C = typename B::clazz,
					typename = check_t< is_mfn_ptr<F>>
				>
					CCDK_FORCEINLINE
					auto 
					operator()(
						F f,
						C& c
					)const noexcept
				{
					typedef remove_const_t<C> NC;
					return bind_mfn_impl<F, NC, typename B::ret>(
						f, 
						(NC*)(&c),
						typename B::args{}
					);
				}

				template<typename F,
					typename B = mfn_traits<F>,
					typename C = typename B::clazz,
					typename = check_t< is_mfn_ptr<F>>
				>
					CCDK_FORCEINLINE 
					auto 
					operator()(
						F f,
						C* c
					) const noexcept
				{
					typedef remove_const_t<C> NC;
					return bind_mfn_impl<F, NC, typename B::ret>(
						f, 
						(NC*)(c),
						typename B::args{}
					);
				}
			};
		}

		namespace fn
		{
			//bind_mfn is function object
			constexpr fn_detail::bind_mfn_t bind_mfn{};
		}
		
	}
}