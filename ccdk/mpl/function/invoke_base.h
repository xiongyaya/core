#pragma once

#include<exception>

#include<ccdk/mpl/mpl_module.h>
#include<ccdk/mpl/util/forward.h>
#include<ccdk/mpl/util/move.h>

ccdk_namespace_mpl_fn_start

	struct bad_invoke_exception :public std::exception
	{
	private:
		const char* msg;
	public:
		CCDK_FORCEINLINE bad_invoke_exception(const char* inMsg) :msg{ inMsg } {}
		virtual char const* what() const noexcept override { return msg; }
	};

	template<
		typename Ret,      /*invoke Ret type */
		typename... Args   /*invoke Args type */
	>
	struct invoker_base
	{
		/* should be override by some derive, other should not call  this  */
		virtual void set_private_data(void* data) noexcept {};

		/*may throw exception when call content*/
		virtual Ret invoke(Args...) = 0;

		/* for copy */
		virtual invoker_base* clone() noexcept = 0;
	};

	
	template<
		typename Fn,       /* T is function object */
		typename Ret,
		typename... Args
	>
	struct function_object_invoker :public invoker_base<Ret, Args...>
	{
		Fn fn;

		CCDK_FORCEINLINE function_object_invoker(Fn&& inFn) noexcept :fn{ util::move(inFn) } {}

		virtual Ret invoke(Args... args) override { return fn(util::forward<Args>(args)...); }

		/*if alloc failed, just return nullptr */
		virtual invoker_base<Ret, Args...>* clone() noexcept override
		{
			return new(ptr::nothrow) function_object_invoker{ fn };
		}
	};

	
	template<
		typename Fn,      /* Fn is normal function ptr */
		typename Ret,
		typename... Args
	>
	struct normal_function_invoker :public invoker_base<Ret, Args...>
	{
		Fn fn;

		CCDK_FORCEINLINE normal_function_invoker(Fn inFn) noexcept : fn(inFn) {}

		virtual Ret invoke(Args... args) override { return t(util::forward<Args>(args)...); }

		/*if alloc failed, just return nullptr */
		virtual invoker_base<Ret, Args...>* clone() noexcept override
		{
			return new(ptr::nothrow) normal_function_invoker{ fn };
		}
	};

	
	template<
		typename Fn,       /* Fn is member function ptr, Class is Fn class type  */
		typename Class,
		typename Ret,
		typename... Args
	>
	struct member_function_invoker :public invoker_base<Ret, Args...>
	{
		Fn     fn;
		Class* clz;

		CCDK_FORCEINLINE member_function_invoker(Fn inFn) noexcept : fn(inFn), clz(nullptr) {}

		CCDK_FORCEINLINE member_function_invoker(Fn inFn, Class* inClass) noexcept : fn(inFn), clz(inClass) {}

		virtual void set_private_data(void* class_ptr) noexcept override { ccdk_assert(class_ptr != nullptr); clz = (Class*)class_ptr; }

		virtual Ret invoke(Args... args) override { return (clz->*fn)(util::forward<Args>(args)...); }

		/*if alloc failed, just return nullptr */
		virtual invoker_base<Ret, Args...>* clone() noexcept override
		{
			return new(ptr::nothrow) member_function_invoker{ fn, clz };
		}
	};

ccdk_namespace_mpl_fn_end