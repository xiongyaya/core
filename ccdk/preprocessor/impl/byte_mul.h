#pragma once

#include<ccdk/preprocessor/impl/byte_add.h>
#include<ccdk/preprocessor/impl/byte_shift_attribute.h>
#include<ccdk/preprocessor/impl/byte_shift_left.h>

#include<ccdk/preprocessor/seq_unpack.h>
#include<ccdk/preprocessor/bool_and.h>
#include<ccdk/preprocessor/uint8_less.h>

//helper function FOR CCDK_PP_BYTE_SHIFT_ATTR expand
#define CCDK_PP_BYTE_MUL_CONNECT_REPARSE1(x, y) CCDK_PP_BYTE_MUL_CONNECT_REPARSE1_STEP1(x, y)
#define CCDK_PP_BYTE_MUL_CONNECT_REPARSE1_STEP1(x, y) CCDK_PP_BYTE_MUL_CONNECT_REPARSE1_STEP2(x y)
#define CCDK_PP_BYTE_MUL_CONNECT_REPARSE1_STEP2(result) result
//for CCDK_PP_UNPACK expand
#define CCDK_PP_BYTE_MUL_CONNECT_REPARSE2(x, y) CCDK_PP_BYTE_MUL_CONNECT_REPARSE2_STEP1(x, y)
#define CCDK_PP_BYTE_MUL_CONNECT_REPARSE2_STEP1(x, y) CCDK_PP_BYTE_MUL_CONNECT_REPARSE2_STEP2(x y)
#define CCDK_PP_BYTE_MUL_CONNECT_REPARSE2_STEP2(result) result

//for last add
#define CCDK_PP_BYTE_MUL_SHIFT_LEFT_IF(Condi, byte, n) CCDK_PP_IF(Condi, CCDK_PP_BYTE_SHIFT_LEFT(byte,n), (0,0,0,0,0,0,0,0) )
#define CCDK_PP_BYTE_MUL_UNCHANGE_IF(Condi, byte)      CCDK_PP_IF(Condi, byte, (0,0,0,0,0,0,0,0) )

//    0 1 1 0 1 1 1 0           bit_width 6
//  X 0 0 0 0 0 1 1 0           bit_width 2
//  ------------------
//    
// if byte1 or byte2 is 0,1,2,4,8,16,32,64,128 do shift_left instead of mul
// else compare bit_width of byte1 and byte2, do sperate-shift-add operation
#define CCDK_PP_BYTE_MUL(byte1, byte2)	                                                                       \
			CCDK_PP_BYTE_MUL_CONNECT_REPARSE1( CCDK_PP_BYTE_MUL_ATTR_EXPLICITE,                                  \
				(byte1,byte2,CCDK_PP_BYTE_SHIFT_ATTR(byte1),CCDK_PP_BYTE_SHIFT_ATTR(byte2)) )

#define CCDK_PP_BYTE_MUL_ATTR_EXPLICITE(byte1, byte2, can_shift1, lzeros1, rzeros1, bit_width1, can_shift2, lzeros2, rzeros2, bit_width2) \
			CCDK_PP_IF( CCDK_PP_OR(can_shift1, can_shift2),                             \
				CCDK_PP_BYTE_MUL_SHIFT_INSTEAD,                                        \
				CCDK_PP_BYTE_MUL_SPERATE_ADD_INSTEAD)(                                 \
					byte1, byte2, can_shift1, lzeros1, rzeros1, bit_width1,           \
								  can_shift2, lzeros2, rzeros2, bit_width2)

// shift instead of mul
#define CCDK_PP_BYTE_MUL_SHIFT_INSTEAD(byte1, byte2, can_shift1, _0, rzeros1, bit_width1, can_shift2,_1, rzeros2, bit_width2) \
			CCDK_PP_IF(can_shift1,                                         \
				CCDK_PP_BYTE_MUL_SHIFT_BYTE2_INSTEAD,                      \
				CCDK_PP_BYTE_MUL_SHIFT_BYTE1_INSTEAD)(byte1, byte2, rzeros1, rzeros2)

#define CCDK_PP_BYTE_MUL_SHIFT_BYTE1_INSTEAD(byte1, _0, _1, rzeros2) CCDK_PP_BYTE_SHIFT_LEFT(byte1, rzeros2)     
#define CCDK_PP_BYTE_MUL_SHIFT_BYTE2_INSTEAD(_0, byte2, rzeros1, _1) CCDK_PP_BYTE_SHIFT_LEFT(byte2, rzeros1)     

//bit add instead of mul
#define CCDK_PP_BYTE_MUL_SPERATE_ADD_INSTEAD(byte1, byte2, can_shift1, lzeros1, rzeros1, bit_width1, can_shift2, lzeros2, rzeros2, bit_width2) \
			CCDK_PP_IF( CCDK_PP_LESS(bit_width1, bit_width2),                \
				CCDK_PP_BYTE_MUL_DO_UNPACK_BYTE1,                           \
				CCDK_PP_BYTE_MUL_DO_UNPACK_BYTE2)(byte1, byte2, lzeros1, bit_width1, lzeros2, bit_width2)

#define CCDK_PP_BYTE_MUL_DO_UNPACK_BYTE1(byte1, byte2, lzeros1,bit_width1, lzeros2,bit_width2) \
			CCDK_PP_BYTE_MUL_CONNECT_REPARSE2( CCDK_PP_BYTE_MUL_DO_SPERATE_SHIFT_ADD,           \
				(byte2,bit_width1, CCDK_PP_UNPACK( CCDK_PP_BYTE_SHIFT_LEFT( byte1, lzeros1) )))

#define CCDK_PP_BYTE_MUL_DO_UNPACK_BYTE2(byte1, byte2, lzeros1,bit_width1, lzeros2,bit_width2) \
			CCDK_PP_BYTE_MUL_CONNECT_REPARSE2( CCDK_PP_BYTE_MUL_DO_SPERATE_SHIFT_ADD,           \
				(byte1, bit_width2, CCDK_PP_UNPACK( CCDK_PP_BYTE_SHIFT_LEFT(byte2, lzeros2) )))

// dispatcher 
#define CCDK_PP_BYTE_MUL_DO_SPERATE_SHIFT_ADD(byte, bit_width, b7,b6,b5,b4,b3,b2,b1,b0) \
			CCDK_PP_BYTE_MUL_DO_SPERATE_SHIFT_ADD##bit_width (byte, b7, b6, b5, b4, b3, b2, b1, b0)

#define CCDK_PP_BYTE_MUL_DO_SPERATE_SHIFT_ADD2(byte, b7, b6, ...)  \
			CCDK_PP_BYTE_ADD( CCDK_PP_BYTE_SHIFT_LEFT(byte, 1), CCDK_PP_BYTE_MUL_UNCHANGE_IF(b6, byte) ) 

#define CCDK_PP_BYTE_MUL_DO_SPERATE_SHIFT_ADD3(byte, b7, b6, b5, ...)                                            \
			CCDK_PP_BYTE_ADD3( CCDK_PP_BYTE_SHIFT_LEFT(byte, 2),                                                  \
				CCDK_PP_BYTE_MUL_SHIFT_LEFT_IF(b6, byte, 1), CCDK_PP_BYTE_MUL_UNCHANGE_IF(b5,byte) )

#define CCDK_PP_BYTE_MUL_DO_SPERATE_SHIFT_ADD4(byte, b7, b6, b5, b4, ...)                                        \
			CCDK_PP_BYTE_ADD4( CCDK_PP_BYTE_SHIFT_LEFT(byte, 3), CCDK_PP_BYTE_MUL_SHIFT_LEFT_IF(b6, byte, 2),      \
				CCDK_PP_BYTE_MUL_SHIFT_LEFT_IF(b5, byte, 1), CCDK_PP_BYTE_MUL_UNCHANGE_IF(b4, byte))

#define CCDK_PP_BYTE_MUL_DO_SPERATE_SHIFT_ADD5(byte, b7, b6, b5, b4, b3, ...)                                    \
			   CCDK_PP_BYTE_ADD(  CCDK_PP_BYTE_SHIFT_LEFT(byte, 4), CCDK_PP_BYTE_ADD4(                             \
					CCDK_PP_BYTE_MUL_SHIFT_LEFT_IF(b6, byte, 3), CCDK_PP_BYTE_MUL_SHIFT_LEFT_IF(b6, byte, 2),     \
					CCDK_PP_BYTE_MUL_SHIFT_LEFT_IF(b5, byte, 1), CCDK_PP_BYTE_MUL_UNCHANGE_IF(b4, byte)))

#define CCDK_PP_BYTE_MUL_DO_SPERATE_SHIFT_ADD6(byte, b7, b6, b5, b4, b3, b2, ...)                                \
			   CCDK_PP_BYTE_ADD(                                                                                 \
					CCDK_PP_BYTE_ADD(                                                                            \
						CCDK_PP_BYTE_SHIFT_LEFT(byte, 5),CCDK_PP_BYTE_MUL_SHIFT_LEFT_IF(b6, byte, 4)),            \
					CCDK_PP_BYTE_ADD4(                                                                           \
						CCDK_PP_BYTE_MUL_SHIFT_LEFT_IF(b5, byte, 3), CCDK_PP_BYTE_MUL_SHIFT_LEFT_IF(b4, byte, 2), \
						CCDK_PP_BYTE_MUL_SHIFT_LEFT_IF(b3, byte, 1), CCDK_PP_BYTE_MUL_UNCHANGE_IF(b2, byte)))     \

#define CCDK_PP_BYTE_MUL_DO_SPERATE_SHIFT_ADD7(byte, b7, b6, b5, b4, b3, b2, b1, _)                              \
			   CCDK_PP_BYTE_ADD(                                                                                 \
					CCDK_PP_BYTE_ADD3( CCDK_PP_BYTE_SHIFT_LEFT(byte, 6),                                          \
						CCDK_PP_BYTE_MUL_SHIFT_LEFT_IF(b6, byte, 5), CCDK_PP_BYTE_MUL_SHIFT_LEFT_IF(b5, byte, 4)),\
					CCDK_PP_BYTE_ADD4(                                                                           \
						CCDK_PP_BYTE_MUL_SHIFT_LEFT_IF(b4, byte, 3), CCDK_PP_BYTE_MUL_SHIFT_LEFT_IF(b3, byte, 2), \
						CCDK_PP_BYTE_MUL_SHIFT_LEFT_IF(b2, byte, 1), CCDK_PP_BYTE_MUL_UNCHANGE_IF(b1, byte)))     

//both byte1 and byte2 is 8-bit-width means highest bit is 1, out-of-range
#define CCDK_PP_BYTE_MUL_DO_SPERATE_SHIFT_ADD8(...) (1,1,1,1,1,1,1,1)



