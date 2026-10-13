/*  see copyright notice in squirrel.h */
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

SQUIRREL_API void sqstd_seterrorhandlers(HSQUIRRELVM v);
SQUIRREL_API void sqstd_printcallstack(HSQUIRRELVM v);

SQUIRREL_API SQRESULT sqstd_throwerrorf(HSQUIRRELVM v, const SQChar *err, ...);

#ifdef __cplusplus
} /*extern "C"*/
#endif
