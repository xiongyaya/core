#pragma once

#include<ccdk/mpl/base/type_.h>
#include<ccdk/mpl/base/enable_if.h>
#include<ccdk/mpl/mcontainer/val_pack.h>
#include<ccdk/mpl/type_traits/remove_dim.h>
#include<ccdk/mpl/type_traits/array_length.h>
#include<ccdk/mpl/iterator/reverse_iterator.h>
#include<ccdk/mpl/iterator/algorithm/seq_find.h>
#include<ccdk/text/text_module.h>
#include<ccdk/text/char_traits.h>

ccdk_namespace_text_start

using namespace mpl;

// string literial include '\0'
template< typename Char, uint32 Length>
class string_literial
{
public:
	using char_type = Char;
	using this_type = string_literial;

	using value_type     = Char;
	using size_type      = uint32;
	using different_type = int32;
	using traits_type    = char_traits<Char>;
		
	using pointer         = Char*;
	using const_pointer   = Char const*;
	using reference       = Char&;
	using const_reference = Char const&;

	using iterator               = pointer;
	using const_iterator         = const_pointer;
	using reverse_iterator       = it::reverse_iterator<iterator>;
	using const_reverse_iterator = it::reverse_iterator<const_iterator>;

	static constexpr uint32   npos    = uint32(-1);
	static constexpr uint32   max_pos = uint32(-2);

	template<typename Char2, uint32 Length2>
	friend class string_literial;

private:
	Char storage[Length];
	
	//copy from c-string literal
	template<uint32... indice>
	CCDK_FORCEINLINE constexpr string_literial(
		indice_pack<indice...>, const_pointer str)
		noexcept : storage{ str[indice]..., Char(0) } {}

	//merge 3-way
	template< uint32... indice1, uint32... indice2, uint32... indice3 >
	CCDK_FORCEINLINE constexpr string_literial( 
		indice_pack<indice1...>, indice_pack<indice2...>, indice_pack<indice3...>,
		const_pointer str1, const_pointer str2) {}

	// insert a char
	template< uint32... indice1, uint32... indice2>
	CCDK_FORCEINLINE constexpr string_literial( 
		indice_pack<indice1...>, indice_pack<indice2...>, char_type c, const_pointer str)
		:storage { str[indice1]..., c, str[indice2]... } {}

public:

	//copy from c-string literial
	template<uint32 N>
	CCDK_FORCEINLINE constexpr string_literial(Char const(&arr)[N]) noexcept
		: string_literial{ make_indice_c<N - 1>, arr } {
		static_assert(N == Length, "use _literial function to construct string_literial");
	}


	//to c-string
	CCDK_FORCEINLINE constexpr size_type size() const { return Length - 1; }


//////////////////////////////////////////////////////////////////////////////////////////////////
//// data access 

	// index and compile-time index
	CCDK_FORCEINLINE reference operator[](uint32 index) { return storage[index]; }
	CCDK_FORCEINLINE const_reference operator[](uint32 index) const noexcept { return storage[index]; }
	CCDK_FORCEINLINE reference at(uint32 index) { return storage[index]; }
	CCDK_FORCEINLINE const_reference at(uint32 index) const noexcept { return storage[index]; }
	template< typename T, T index > CCDK_FORCEINLINE constexpr Char operator[](compile_t<T,index>) { return storage[index]; }
	template< typename T, T index > CCDK_FORCEINLINE constexpr Char operator[](compile_t<T,index>) const { return storage[index]; }
	//access front
	CCDK_FORCEINLINE constexpr reference front() noexcept { return storage[0]; }
	CCDK_FORCEINLINE constexpr const_reference front() const noexcept { return storage[0]; }
	//access back
	CCDK_FORCEINLINE constexpr reference back(uint32 ith = 1) noexcept { return storage[Length - ith];}
	CCDK_FORCEINLINE constexpr const_reference back(uint32 ith = 1) const noexcept {return storage[Length - ith];}
	//raw string 
	CCDK_FORCEINLINE constexpr pointer c_str() { return storage; }
	CCDK_FORCEINLINE constexpr const_pointer c_str() const { return storage; }

	// equal
	template<typename Char2, uint32 Length2>
	CCDK_FORCEINLINE constexpr bool operator==(
		const string_literial<Char2,Length2>& other) const {
		if (Length != Length2) return false;
		for (uint32 i = 0; i < Length; ++i)
			if (storage[i] != other.storage[i]) 
				return false;
		return true;
	}

///////////////////////////////////////////////////////////////////////////////////////
//// find

	//find char
	template<int32 N>
	CCDK_FORCEINLINE constexpr size_type find_index(Char c) const {
		return find_index_impl<N>(mpl::bool_c<(N < 0)>, c);
	}

	//find sub-string position
	template<int32 Nth, uint32 L, typename = check<(Nth>0)> >
	CCDK_FORCEINLINE constexpr size_type find_index(
		string_literial<Char,L> const& other) const {

		uint32 next[L - 1];
		it::alg_impl::build_next(next, other.storage, L - 1);
		size_type offset = 0;
		for (uint32 i = 0; i < Nth && offset < size(); ++i) {
			offset += it::alg_impl::kmp(next, c_str() + offset,
				size() - offset, other.c_str(), other.size());
		}
		if (offset < size()) offset -= other.size();
		return offset;

	}


/////////////////////////////////////////////////////////////////////////////////
//// substr

	//const version substr
	template<
		uint32 start, uint32 end,
		typename = check_in_range2<start, end, 0, Length> >
	CCDK_FORCEINLINE constexpr auto substr() const { 
		return string_literial<Char, end - start + 1>{ 
			make_indice_from<start, end>{}, storage }; 
	}

/////////////////////////////////////////////////////////////////////////////////
//// replace 
	
	//non-const version char replace 
	CCDK_FORCEINLINE auto replace(Char from, Char to){
		return replace([](Char c) { return c == from; }, to);
	}

	//non-const version FN replace
	template<typename FN>
	CCDK_FORCEINLINE auto replace(FN Fn, Char to) {
		for (uint32 i = 0; i < Length; ++i) {
			if (Fn(storage[i])) {
				storage[i] = to;
			}
		}
		return *this;
	}

	//const version
	template< uint32 index, typename = check_in_range<index , 0, Length> >
	CCDK_FORCEINLINE constexpr auto replace(Char c) const { 
		return string_literial<Char, Length>{
			make_indice<index>{}, make_indice_from<index + 1,Length>{}, c, storage 
		}; 
	}

	//replace string
	template<uint32 N2>
	CCDK_FORCEINLINE constexpr auto replace(
		string_literial<Char, N2> const& other) const {


	}

private:

	//find char from forward
	template<int32 N>
	CCDK_FORCEINLINE constexpr size_type find_index_impl(mpl::false_, Char c) const {
		int32 count = 0;
		for (int i = 0; i < Length; ++i) {
			if (c == storage[i])
				if(++count == N)
					return i;
		}
		return Length;
	}

	//find char from backward
	template<int32 N>
	CCDK_FORCEINLINE constexpr size_type find_index_impl(mpl::true_, Char c) const {
		int32 count = 0;
		for (int i = 1; i <= Length; ++i) {
			if (c == storage[Length-i])
				if (++count == -N)
					return i;
		}
		return Length;
	}

public:

	CCDK_FORCEINLINE void debug_value(const char* title="") const {
		DebugValueItBegin(title);
		DebugValueIt(storage);
		DebugValueItEnd();
	}

};

template<typename Char, uint32 N>
inline constexpr auto _literal(Char const(&arr)[N])
{
	return string_literial<Char, N>{ arr };
}

ccdk_namespace_text_end