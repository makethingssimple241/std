//
//  cstddef.h
//  std
//
//  Created by MakeThingsSimple on 9/6/2024.
//

#ifndef std_cstddef_h
#define std_cstddef_h

#include <stdbool.h>

#define len(a)      sizeof(a) / sizeof((a)[0])
#define noreturn    __attribute__((noreturn))
#define null        0

#endif /* std_cstddef_h */
