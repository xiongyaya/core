#pragma once

#include<ccdk/preprocessor/seq_size.h>
#include<ccdk/preprocessor/seq_at.h>
#include<ccdk/preprocessor/seq_expand.h>
#include<ccdk/preprocessor/uint8_sub_one.h>
#include<ccdk/preprocessor/uint8_if.h>
#include<ccdk/preprocessor/ingore.h>

 
//seq max length 63
#define CCDK_PP_FOREACH_TUPLE(call, seq, ...)  CCDK_PP_FOREACH_TUPLE_STEP1(call, seq, __VA_ARGS__)

#define CCDK_PP_FOREACH_TUPLE_STEP1(call, seq, ...)       CCDK_PP_FOREACH_TUPLE_STEP2(call, seq, CCDK_PP_SIZE(seq), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_STEP2(call, seq, size, ...) CCDK_PP_FOREACH_TUPLE_STEP3(call, seq, CCDK_PP_SUB1(size), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_STEP3(call, seq, count, ...)  CCDK_PP_FOREACH_TUPLE_VALUE0(call, seq, count, __VA_ARGS__)

#define CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE(x, y)       CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE_STEP1(x, y)
#define CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE_STEP1(x, y) CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE_STEP2(x y)
#define CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE_STEP2(result) result

//if pos == 0 stop
#define CCDK_PP_FOREACH_TUPLE_VALUE0(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 0), __VA_ARGS__) )  CCDK_PP_INT_IF(count, CCDK_PP_FOREACH_TUPLE_VALUE1, CCDK_PP_INGORE )(call, seq, CCDK_PP_SUB1(count), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_VALUE1(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 1), __VA_ARGS__) )   CCDK_PP_INT_IF(count, CCDK_PP_FOREACH_TUPLE_VALUE2, CCDK_PP_INGORE )(call, seq, CCDK_PP_SUB1(count), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_VALUE2(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 2), __VA_ARGS__) )   CCDK_PP_INT_IF(count, CCDK_PP_FOREACH_TUPLE_VALUE3, CCDK_PP_INGORE )(call, seq, CCDK_PP_SUB1(count), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_VALUE3(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 3), __VA_ARGS__) )   CCDK_PP_INT_IF(count, CCDK_PP_FOREACH_TUPLE_VALUE4, CCDK_PP_INGORE )(call, seq, CCDK_PP_SUB1(count), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_VALUE4(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 4), __VA_ARGS__) )   CCDK_PP_INT_IF(count, CCDK_PP_FOREACH_TUPLE_VALUE5, CCDK_PP_INGORE )(call, seq, CCDK_PP_SUB1(count), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_VALUE5(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 5), __VA_ARGS__) )   CCDK_PP_INT_IF(count, CCDK_PP_FOREACH_TUPLE_VALUE6, CCDK_PP_INGORE )(call, seq, CCDK_PP_SUB1(count), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_VALUE6(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 6), __VA_ARGS__) )   CCDK_PP_INT_IF(count, CCDK_PP_FOREACH_TUPLE_VALUE7, CCDK_PP_INGORE )(call, seq, CCDK_PP_SUB1(count), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_VALUE7(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 7), __VA_ARGS__) )   CCDK_PP_INT_IF(count, CCDK_PP_FOREACH_TUPLE_VALUE8, CCDK_PP_INGORE )(call, seq, CCDK_PP_SUB1(count), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_VALUE8(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 8), __VA_ARGS__) )   CCDK_PP_INT_IF(count, CCDK_PP_FOREACH_TUPLE_VALUE9, CCDK_PP_INGORE )(call, seq, CCDK_PP_SUB1(count), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_VALUE9(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 9), __VA_ARGS__) )   CCDK_PP_INT_IF(count, CCDK_PP_FOREACH_TUPLE_VALUE10, CCDK_PP_INGORE )(call, seq, CCDK_PP_SUB1(count), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_VALUE10(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 10), __VA_ARGS__) )   CCDK_PP_INT_IF(count, CCDK_PP_FOREACH_TUPLE_VALUE11, CCDK_PP_INGORE )(call, seq, CCDK_PP_SUB1(count), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_VALUE11(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 11), __VA_ARGS__) )   CCDK_PP_INT_IF(count, CCDK_PP_FOREACH_TUPLE_VALUE12, CCDK_PP_INGORE )(call, seq, CCDK_PP_SUB1(count), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_VALUE12(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 12), __VA_ARGS__) )   CCDK_PP_INT_IF(count, CCDK_PP_FOREACH_TUPLE_VALUE13, CCDK_PP_INGORE )(call, seq, CCDK_PP_SUB1(count), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_VALUE13(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 13), __VA_ARGS__) )   CCDK_PP_INT_IF(count, CCDK_PP_FOREACH_TUPLE_VALUE14, CCDK_PP_INGORE )(call, seq, CCDK_PP_SUB1(count), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_VALUE14(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 14), __VA_ARGS__) )   CCDK_PP_INT_IF(count, CCDK_PP_FOREACH_TUPLE_VALUE15, CCDK_PP_INGORE )(call, seq, CCDK_PP_SUB1(count), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_VALUE15(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 15), __VA_ARGS__) )   CCDK_PP_INT_IF(count, CCDK_PP_FOREACH_TUPLE_VALUE16, CCDK_PP_INGORE )(call, seq, CCDK_PP_SUB1(count), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_VALUE16(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 16), __VA_ARGS__) )   CCDK_PP_INT_IF(count, CCDK_PP_FOREACH_TUPLE_VALUE17, CCDK_PP_INGORE )(call, seq, CCDK_PP_SUB1(count), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_VALUE17(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 17), __VA_ARGS__) )   CCDK_PP_INT_IF(count, CCDK_PP_FOREACH_TUPLE_VALUE18, CCDK_PP_INGORE )(call, seq, CCDK_PP_SUB1(count), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_VALUE18(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 18), __VA_ARGS__) )   CCDK_PP_INT_IF(count, CCDK_PP_FOREACH_TUPLE_VALUE19, CCDK_PP_INGORE )(call, seq, CCDK_PP_SUB1(count), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_VALUE19(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 19), __VA_ARGS__) )   CCDK_PP_INT_IF(count, CCDK_PP_FOREACH_TUPLE_VALUE20, CCDK_PP_INGORE )(call, seq, CCDK_PP_SUB1(count), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_VALUE20(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 20), __VA_ARGS__) )   CCDK_PP_INT_IF(count, CCDK_PP_FOREACH_TUPLE_VALUE21, CCDK_PP_INGORE )(call, seq, CCDK_PP_SUB1(count), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_VALUE21(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 21), __VA_ARGS__) )   CCDK_PP_INT_IF(count, CCDK_PP_FOREACH_TUPLE_VALUE22, CCDK_PP_INGORE )(call, seq, CCDK_PP_SUB1(count), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_VALUE22(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 22), __VA_ARGS__) )   CCDK_PP_INT_IF(count, CCDK_PP_FOREACH_TUPLE_VALUE23, CCDK_PP_INGORE )(call, seq, CCDK_PP_SUB1(count), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_VALUE23(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 23), __VA_ARGS__) )   CCDK_PP_INT_IF(count, CCDK_PP_FOREACH_TUPLE_VALUE24, CCDK_PP_INGORE )(call, seq, CCDK_PP_SUB1(count), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_VALUE24(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 24), __VA_ARGS__) )   CCDK_PP_INT_IF(count, CCDK_PP_FOREACH_TUPLE_VALUE25, CCDK_PP_INGORE )(call, seq, CCDK_PP_SUB1(count), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_VALUE25(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 25), __VA_ARGS__) )   CCDK_PP_INT_IF(count, CCDK_PP_FOREACH_TUPLE_VALUE26, CCDK_PP_INGORE )(call, seq, CCDK_PP_SUB1(count), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_VALUE26(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 26), __VA_ARGS__) )   CCDK_PP_INT_IF(count, CCDK_PP_FOREACH_TUPLE_VALUE27, CCDK_PP_INGORE )(call, seq, CCDK_PP_SUB1(count), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_VALUE27(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 27), __VA_ARGS__) )   CCDK_PP_INT_IF(count, CCDK_PP_FOREACH_TUPLE_VALUE28, CCDK_PP_INGORE )(call, seq, CCDK_PP_SUB1(count), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_VALUE28(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 28), __VA_ARGS__) )   CCDK_PP_INT_IF(count, CCDK_PP_FOREACH_TUPLE_VALUE29, CCDK_PP_INGORE )(call, seq, CCDK_PP_SUB1(count), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_VALUE29(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 29), __VA_ARGS__) )   CCDK_PP_INT_IF(count, CCDK_PP_FOREACH_TUPLE_VALUE30, CCDK_PP_INGORE )(call, seq, CCDK_PP_SUB1(count), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_VALUE30(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 30), __VA_ARGS__) )   CCDK_PP_INT_IF(count, CCDK_PP_FOREACH_TUPLE_VALUE31, CCDK_PP_INGORE )(call, seq, CCDK_PP_SUB1(count), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_VALUE31(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 31), __VA_ARGS__) )   CCDK_PP_INT_IF(count, CCDK_PP_FOREACH_TUPLE_VALUE32, CCDK_PP_INGORE )(call, seq, CCDK_PP_SUB1(count), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_VALUE32(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 32), __VA_ARGS__) )   CCDK_PP_INT_IF(count, CCDK_PP_FOREACH_TUPLE_VALUE33, CCDK_PP_INGORE )(call, seq, CCDK_PP_SUB1(count), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_VALUE33(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 33), __VA_ARGS__) )   CCDK_PP_INT_IF(count, CCDK_PP_FOREACH_TUPLE_VALUE34, CCDK_PP_INGORE )(call, seq, CCDK_PP_SUB1(count), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_VALUE34(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 34), __VA_ARGS__) )   CCDK_PP_INT_IF(count, CCDK_PP_FOREACH_TUPLE_VALUE35, CCDK_PP_INGORE )(call, seq, CCDK_PP_SUB1(count), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_VALUE35(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 35), __VA_ARGS__) )   CCDK_PP_INT_IF(count, CCDK_PP_FOREACH_TUPLE_VALUE36, CCDK_PP_INGORE )(call, seq, CCDK_PP_SUB1(count), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_VALUE36(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 36), __VA_ARGS__) )   CCDK_PP_INT_IF(count, CCDK_PP_FOREACH_TUPLE_VALUE37, CCDK_PP_INGORE )(call, seq, CCDK_PP_SUB1(count), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_VALUE37(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 37), __VA_ARGS__) )   CCDK_PP_INT_IF(count, CCDK_PP_FOREACH_TUPLE_VALUE38, CCDK_PP_INGORE )(call, seq, CCDK_PP_SUB1(count), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_VALUE38(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 38), __VA_ARGS__) )   CCDK_PP_INT_IF(count, CCDK_PP_FOREACH_TUPLE_VALUE39, CCDK_PP_INGORE )(call, seq, CCDK_PP_SUB1(count), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_VALUE39(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 39), __VA_ARGS__) )   CCDK_PP_INT_IF(count, CCDK_PP_FOREACH_TUPLE_VALUE40, CCDK_PP_INGORE )(call, seq, CCDK_PP_SUB1(count), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_VALUE40(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 40), __VA_ARGS__) )   CCDK_PP_INT_IF(count, CCDK_PP_FOREACH_TUPLE_VALUE41, CCDK_PP_INGORE )(call, seq, CCDK_PP_SUB1(count), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_VALUE41(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 41), __VA_ARGS__) )   CCDK_PP_INT_IF(count, CCDK_PP_FOREACH_TUPLE_VALUE42, CCDK_PP_INGORE )(call, seq, CCDK_PP_SUB1(count), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_VALUE42(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 42), __VA_ARGS__) )   CCDK_PP_INT_IF(count, CCDK_PP_FOREACH_TUPLE_VALUE43, CCDK_PP_INGORE )(call, seq, CCDK_PP_SUB1(count), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_VALUE43(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 43), __VA_ARGS__) )   CCDK_PP_INT_IF(count, CCDK_PP_FOREACH_TUPLE_VALUE44, CCDK_PP_INGORE )(call, seq, CCDK_PP_SUB1(count), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_VALUE44(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 44), __VA_ARGS__) )   CCDK_PP_INT_IF(count, CCDK_PP_FOREACH_TUPLE_VALUE45, CCDK_PP_INGORE )(call, seq, CCDK_PP_SUB1(count), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_VALUE45(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 45), __VA_ARGS__) )   CCDK_PP_INT_IF(count, CCDK_PP_FOREACH_TUPLE_VALUE46, CCDK_PP_INGORE )(call, seq, CCDK_PP_SUB1(count), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_VALUE46(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 46), __VA_ARGS__) )   CCDK_PP_INT_IF(count, CCDK_PP_FOREACH_TUPLE_VALUE47, CCDK_PP_INGORE )(call, seq, CCDK_PP_SUB1(count), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_VALUE47(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 47), __VA_ARGS__) )   CCDK_PP_INT_IF(count, CCDK_PP_FOREACH_TUPLE_VALUE48, CCDK_PP_INGORE )(call, seq, CCDK_PP_SUB1(count), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_VALUE48(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 48), __VA_ARGS__) )   CCDK_PP_INT_IF(count, CCDK_PP_FOREACH_TUPLE_VALUE49, CCDK_PP_INGORE )(call, seq, CCDK_PP_SUB1(count), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_VALUE49(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 49), __VA_ARGS__) )   CCDK_PP_INT_IF(count, CCDK_PP_FOREACH_TUPLE_VALUE50, CCDK_PP_INGORE )(call, seq, CCDK_PP_SUB1(count), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_VALUE50(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 50), __VA_ARGS__) )   CCDK_PP_INT_IF(count, CCDK_PP_FOREACH_TUPLE_VALUE51, CCDK_PP_INGORE )(call, seq, CCDK_PP_SUB1(count), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_VALUE51(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 51), __VA_ARGS__) )   CCDK_PP_INT_IF(count, CCDK_PP_FOREACH_TUPLE_VALUE52, CCDK_PP_INGORE )(call, seq, CCDK_PP_SUB1(count), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_VALUE52(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 52), __VA_ARGS__) )   CCDK_PP_INT_IF(count, CCDK_PP_FOREACH_TUPLE_VALUE53, CCDK_PP_INGORE )(call, seq, CCDK_PP_SUB1(count), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_VALUE53(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 53), __VA_ARGS__) )   CCDK_PP_INT_IF(count, CCDK_PP_FOREACH_TUPLE_VALUE54, CCDK_PP_INGORE )(call, seq, CCDK_PP_SUB1(count), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_VALUE54(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 54), __VA_ARGS__) )   CCDK_PP_INT_IF(count, CCDK_PP_FOREACH_TUPLE_VALUE55, CCDK_PP_INGORE )(call, seq, CCDK_PP_SUB1(count), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_VALUE55(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 55), __VA_ARGS__) )   CCDK_PP_INT_IF(count, CCDK_PP_FOREACH_TUPLE_VALUE56, CCDK_PP_INGORE )(call, seq, CCDK_PP_SUB1(count), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_VALUE56(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 56), __VA_ARGS__) )   CCDK_PP_INT_IF(count, CCDK_PP_FOREACH_TUPLE_VALUE57, CCDK_PP_INGORE )(call, seq, CCDK_PP_SUB1(count), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_VALUE57(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 57), __VA_ARGS__) )   CCDK_PP_INT_IF(count, CCDK_PP_FOREACH_TUPLE_VALUE58, CCDK_PP_INGORE )(call, seq, CCDK_PP_SUB1(count), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_VALUE58(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 58), __VA_ARGS__) )   CCDK_PP_INT_IF(count, CCDK_PP_FOREACH_TUPLE_VALUE59, CCDK_PP_INGORE )(call, seq, CCDK_PP_SUB1(count), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_VALUE59(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 59), __VA_ARGS__) )   CCDK_PP_INT_IF(count, CCDK_PP_FOREACH_TUPLE_VALUE60, CCDK_PP_INGORE )(call, seq, CCDK_PP_SUB1(count), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_VALUE60(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 60), __VA_ARGS__) )   CCDK_PP_INT_IF(count, CCDK_PP_FOREACH_TUPLE_VALUE61, CCDK_PP_INGORE )(call, seq, CCDK_PP_SUB1(count), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_VALUE61(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 61), __VA_ARGS__) )   CCDK_PP_INT_IF(count, CCDK_PP_FOREACH_TUPLE_VALUE62, CCDK_PP_INGORE )(call, seq, CCDK_PP_SUB1(count), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_VALUE62(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 62), __VA_ARGS__) )   CCDK_PP_INT_IF(count, CCDK_PP_FOREACH_TUPLE_VALUE63, CCDK_PP_INGORE )(call, seq, CCDK_PP_SUB1(count), __VA_ARGS__)
#define CCDK_PP_FOREACH_TUPLE_VALUE63(call, seq, count, ...)   CCDK_PP_FOREACH_TUPLE_CONNECT_REPARSE( call, CCDK_PP_EXPAND( CCDK_PP_AT(seq, 63), __VA_ARGS__) )   