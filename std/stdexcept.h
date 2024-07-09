//
//  stdexcept.h
//  std
//
//  Created by MakeThingsSimple on 5/5/2024.
//

#ifndef std_stdexcept_h
#define std_stdexcept_h

#include <errno.h>

#define bad_alloc ENOMEM

#define out_of_range ERANGE
#define runtime_error EINVAL

#endif /* std_stdexcept_h */
