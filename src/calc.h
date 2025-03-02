#ifndef CALC_H
#define CALC_H
#if defined NUMWORKS || defined NSPIRE_NEWLIB || defined TICE
#define STATUS_AREA_PX 18
#include "k_csdk.h"
#endif
#if defined FX || defined FXCG
#define STATUS_AREA_PX 24
#include "casio.h"
#endif

#endif // CALC_H
