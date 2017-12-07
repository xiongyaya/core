#pragma once

#include<ccdk/type.h>
#include<ccdk/mpl/base/null_.h>
#include<ccdk/mpl/base/int_.h>
#include<ccdk/mpl/base/enable_if.h>
#include<ccdk/mpl/type_traits/decay.h>
#include<ccdk/mpl/type_traits/move.h>
#include<ccdk/mpl/container/ref_tuple.h>
#include<ccdk/mpl/function/operator.h>
#include<ccdk/mpl/base/val_pack.h>

namespace ccdk
{
	namespace mpl
	{
		namespace ph
		{
			//declare
			template<int8 NC, int8 LT, int8 RT,typename...>
			struct operation_t;

			template<typename T>
			struct placeholder_t;

			template<typename T>
			struct is_placeholder :false_ {};

			template<typename T>
			struct is_placeholder<placeholder_t<T> > :true_ {};
			

			constexpr inline int8 max(int8 a, int8 b)
			{
				return a < b ? b : a;
			}


			//left and right is instant veriable, no number placeholder
			template<typename Op, typename T1, typename T2 >
			struct operation_t<0, 0, 0, Op, T1, T2>
			{
			public:
				static constexpr int N = 0;
				static constexpr int L = 0;
				typedef operation_t<0, 0,0, Op, T1, T2> type;
			public:
				Op fn;
				T1 t1;
				T2 t2;

				operation_t(
					const T1& inT1,
					const T2& inT2)
					:t1{ inT1 }, t2{ inT2 }
				{}

				operation_t(
					T1&& inT1,
					T2&& inT2)
					:t1{ util::move(inT1) },
					t2{ util::move(inT2) }
				{}

				template<
					int S,
					typename T,
					typename = check_t< is_ref_tuple<T> >
				>
					decltype(auto)
					invoke(const T& t) const
				{
					return fn(t1, t2);
				}
			};

			//left is place holder and right is instant veriable
			template<int8 NC, int8 LT, typename Op, typename T1, typename T2 >
			struct operation_t<NC, LT, 0, Op, T1, T2>
			{
			public:
				static constexpr int N = NC;
				static constexpr int L = LT;
				typedef operation_t<NC, LT, 0, Op, T1, T2> type;
			public:
				Op fn;
				placeholder_t<T1> t1;
				T2 t2;

				operation_t(
					placeholder_t<T1>&& inT1,
					const T2& inT2)
					:t1{ util::move(inT1) },
					t2{ inT2 }
				{}

				operation_t(
					placeholder_t<T1>&& inT1,
					T2&& inT2)
					:t1{ util::move(inT1) },
					t2{ util::move(inT2) }
				{}

				template<
					int S,
					typename T,
					typename = check_t< is_ref_tuple<T> >
				>
					decltype(auto)
					invoke(const T& t) const
				{
					return fn( t1.template invoke<S>(t) , t2);
				}
			};


			//left is place holder and right is instant veriable
			template<int8 NC, int8 RT, typename Op, typename T1, typename T2 >
			struct operation_t<NC, 0, RT, Op, T1, T2>
			{
			public:
				static constexpr int N = NC;
				static constexpr int L = RT;
				typedef operation_t<NC, 0, RT, Op, T1, T2> type;
			public:
				Op fn;
				T1 t1;
				placeholder_t<T2> t2;

				operation_t(
					const T1& inT1,
					placeholder_t<T2>&& inT2)
					:t1{ inT1 },
					t2{ util::move(inT2) }
				{}

				operation_t(
					T1&& inT1,
					placeholder_t<T2>&& inT2)
					:t1{ util::move(inT1) },
					t2{ util::move(inT2) }
				{}

				template<
					int S,
					typename T,
					typename = check_t< is_ref_tuple<T> >
				>
					decltype(auto)
					invoke(const T& t) const
				{
					return fn(t1, t2.template invoke<S>(t) );
				}
			};

			

			//left and right is placeholder
			template<int8 NC, int8 LT, int8 RT, typename Op, typename T1, typename T2 >
			struct operation_t<NC, LT, RT, Op, T1, T2>
			{
			public:
				static constexpr int N = NC;
				static constexpr int L = max(LT+RT, max(LT, RT));
				typedef operation_t<NC, LT, RT, Op, T1, T2> type;
			private:
				Op fn;
				placeholder_t<T1> t1;
				placeholder_t<T2> t2;
			public:
				 operation_t(
					 placeholder_t<T1>&& inT1,
					 placeholder_t<T2>&& inT2)
					: t1{ util::move(inT1) },
					 t2{ util::move(inT2) }
				{}

				template<
					int S,
					typename T,
					typename = check_t< is_ref_tuple<T> >
					>
					decltype(auto) 
					invoke( const T& t ) const
				{
					return fn(
						t1.template invoke<S>(t),
						t2.template invoke<S + max(LT, 0) >(t)
					);
				}
			};

			template<typename T>
			struct placeholder_t
			{
			public:
				typedef placeholder_t<T> type;
				typedef T* value_type;
				static constexpr int L = T::L;
				static constexpr int N = T::N;
				static constexpr int CL = max(max(0,T::L), max(T::N,-T::N));
			private:
				value_type ptr;
			public:
				placeholder_t(value_type inPtr) noexcept
					:ptr(inPtr)
				{
					DebugValue("construct");
				}

				placeholder_t(placeholder_t&& p) noexcept
					:ptr{ p.ptr }
				{
					DebugValue("move");
					p.ptr = nullptr;
				}

				//just dispatch ptr's invoke
				template<
					int S,
					typename U
					>
				 decltype(auto)
					invoke(
						const U& t
					) const 
				{
					return  ptr->template invoke<S>(t);
				}

				//enter point
				template<
					typename... Args, 
					typename = check< sizeof...(Args) == CL >
				>
				decltype(auto)
				operator()(
					Args&&... args) const
				{
					//created tuple is right-ref
					return ptr->template invoke<0>(
						create_ref_tuple(args...)
					);
				}

				~placeholder_t() 
				{
					DebugValue("destruct");
					ptr::safe_delete(ptr);
				}
			};

			template<>
			struct placeholder_t<null_>
			{
				static constexpr int L = 1;
				static constexpr int N = 0;

				template<
					int S,
					typename U
				  >
				  decltype(auto)
					invoke(
						U& t
					) const noexcept
				{
					return t.template at<S>();
				}

			};


			template<int index>
			struct placeholder_t<int_<index>>
			{
				//for compute arg number
				static constexpr int L = -index;
				static constexpr int N = -index;

				template<
					int S,
					typename U
				>
					decltype(auto)
					invoke(
						U& t
					) const noexcept
				{
					return t.template at<index-1>();
				}
			};

			template<> struct placeholder_t<int_<0>> { placeholder_t() = delete; };

			using anonymous_holder =  placeholder_t<null_> ;
			template<int32 index> using number_holder =  placeholder_t<int_<index>> ;
		}

		//import to placeholder namespace
		namespace placeholder
		{
			constexpr ph::anonymous_holder _{};

			template<char... args>
			constexpr auto operator""_()
			{
				static_assert(val_first<char, args...>::value != '0', "number placeholder can't be 0_, need greater then 0");
				return ph::number_holder< literals::parse_integer<sizeof...(args)>({ args... }) >{};
			}
		}


		//overide all operation of placeholder_t
		namespace ph
		{
#define CCDK_MPL_PLACEHOLDER_BINARY(name, opsign) \
			template<typename T,typename U,typename = check_t< not_<is_placeholder<U>>>>                 \
				auto operator opsign (const placeholder_t<T>& p, U&& u)                                  \
				{	typedef operation_t< p.N, p.L, 0, op:: name ## _t, T, U> operation;                  \
					return placeholder_t< operation >{                                                   \
					new  operation{const_cast<placeholder_t<T>&&>(p),util::forward<U>(u)}};}             \
			template<typename T,typename U,typename = check_t< not_<is_placeholder<U>>>>                 \
				auto operator opsign (U&& u, const placeholder_t<T>& p)                                  \
				{	typedef operation_t< p.N, 0, p.L, op:: name ## _t, U, T> operation;                  \
					return placeholder_t< operation >{                                                   \
					new  operation{util::forward<U>(u),const_cast<placeholder_t<T>&&>(p)}};}             \
			template< typename T, typename U >                                                           \
				auto operator opsign ( const placeholder_t<T>& t, const placeholder_t<U>& u)             \
				{	typedef operation_t< -max(-u.N, -t.N), t.L, u.L, op:: name ## _t, T, U> operation;   \
					return placeholder_t< operation >{                                                   \
					new  operation{const_cast<placeholder_t<T>&&>(t), const_cast<placeholder_t<U>&&>(u)}};}

			CCDK_PP_FOREACH_TUPLE(CCDK_MPL_PLACEHOLDER_BINARY, (
				(add, +),
				(sub, -),
				(div, / ),
				(mul, *),
				(mod, %),
				(shl, << ),
				(shr, >> ),
				(logic_and, &&),
				(logic_or, || ),
				(bit_xor, ^),
				(bit_and, &),
				(bit_or, | ),
				(add_assign, +=),
				(sub_assign, -=),
				(mul_assign, *=),
				(div_assign, /=),
				(mod_assign, %=),
				(shl_assign, <<=),
				(shr_assign, >>=),
				(bit_xor_assign, ^=),
				(bit_and_assign, &=),
				(bit_or_assign, |=),
				(less, <),
				(greater, >),
				(lequal, <= ),
				(gequal, >= ),
				(equal, == ),
				(nequal, != )));
		}

	}
}