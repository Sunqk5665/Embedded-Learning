
#ifndef _CRC_CALC_H_
#define _CRC_CALC_H_

#include "stdint.h"

#ifdef _CRC_CALC_C_
#define CRC_CALC_EXT
#else
#define CRC_CALC_EXT extern
#endif


unsigned short GetCRC16(unsigned char *ptr,  unsigned char len);

#endif 
