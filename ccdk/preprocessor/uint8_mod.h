#pragma once

#include<ccdk/preprocessor/impl/byte_mod.h>
#include<ccdk/preprocessor/impl/uint8_to_byte.h>
#include<ccdk/preprocessor/impl/byte_to_uint8.h>

#define CCDK_PP_MOD(x, y) CCDK_PP_BYTE_INT( CCDK_PP_BYTE_MOD( CCDK_PP_INT_BYTE(x), CCDK_PP_INT_BYTE(y)) )
