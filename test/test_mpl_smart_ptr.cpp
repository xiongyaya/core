#include<cstdio>
#include<utility>
#include<memory>
#include<string>
#include<typeinfo>
#include<iostream>
#include<type_traits>
#include<cassert>
#include<functional>
#include<ccdk/mpl/type_traits.h>
#include<ccdk/mpl/base/arg_pack.h>
#include<ccdk/mpl/base/val_pack.h>
#include<ccdk/mpl/base/integer_.h>
#include<ccdk/mpl/base/int_.h>
#include<ccdk/mpl/function/arg.h>
#include<ccdk/mpl/function/function.h>
#include<ccdk/mpl/function/bind_mfn.h>
#include<ccdk/mpl/function/partial.h>
#include<ccdk/mpl/function/capture.h>
#include<ccdk/mpl/function/combine.h>
#include<ccdk/mpl/function/operator.h>
#include<ccdk/mpl/type_traits/select_case.h>
#include<ccdk/mpl/smart_ptr/scope_ptr.h>
#include<ccdk/mpl/smart_ptr/share_ptr.h>

using namespace ccdk;
using namespace ccdk::mpl;
using namespace ccdk::mpl::sp;

struct base
{
	virtual void test_size()
	{
		DebugValue("base");
	}
	virtual ~base()
	{
		DebugValue("base destructor");
	}
};

struct derive :public base
{
	virtual void test_size() override
	{
		DebugValue("derive");
	}

	virtual ~derive() override
	{
		DebugValue("derive destructor");
	}
};

using namespace ccdk::mpl;
int main()
{

	DebugNewTitle("test copy");

	test_copy_assign_t<int> t1 = 1;
	test_copy_assign_t<int> t2 = t1;

	DebugNewTitle("share_ptr")
	std::shared_ptr<int> sp2;

	DebugNewTitle("scope ptr");
	share_ptr<int> sp{ new int[5] };

	{
		int *p = new int;
		scope_ptr<void> vp{ new int };


		int *a = new int[2];
		DebugValue((int)p);
		DebugValue((int)&a[0]);
		DebugValue((int)&a[1]);
		base *ba = new base();
		base *bb = new derive();
		{
			scope_ptr<int> ptr{ p };
			scope_ptr<int[]> arr_ptr{ a };
			scope_ptr<base> bp1{ ba };
			scope_ptr<base> bp2{ bb };
			bp1->test_size();
			bp2->test_size();
		}
		DebugValue((int)p);
		DebugValue((int)&a[0]);
		DebugValue((int)&a[1]);
	}


	getchar();
	return 0;
}