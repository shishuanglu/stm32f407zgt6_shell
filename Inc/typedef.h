#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__

#include "stdio.h"
#include "string.h"

typedef unsigned           char	bool;

typedef   signed          char S8;
typedef   signed short     int S16;
typedef   signed           int S32;

typedef unsigned          char U8;
typedef unsigned short     int U16;
typedef unsigned           int U32;

typedef void(*pf)(void);

typedef enum
{
	INVALID = 0,
	VALID = !INVALID,
}ValidStatus;

typedef enum
{
	FALSE = 0,
	TRUE = !FALSE,
}FalseStatus;


#endif

