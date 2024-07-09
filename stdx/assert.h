//
//  assert.h
//  std
//
//  Created by MakeThingsSimple on 26/6/2024.
//

/// @file assert.h
/// @note If `STDX_DISABLE_ASSERTS` is defined when including `stdx/assert.h`, `assert(expr)` expand to `(void)0`
/// If `STDX_ENABLE_ASSERT_HANDLER` is defined when including `stdx/assert.h`, assert macros expand to `((expr) ? ((void)0) : assertion_failed(#expr, __file__, __line__, __func__))`

#ifndef stdx_assert_h
#define stdx_assert_h

#include <assert.h>

#ifdef STDX_DISABLE_ASSERTS
    #define STDX_ASSERT(expr) (void)0
#else
    #ifdef STDX_ENABLE_ASSERT_HANDLER
        #define STDX_ASSERT(expr) ((expr) ? ((void)0) : assertion_failed(__FILE__, __LINE__, __func__, #expr))
    #endif
#endif

void assertion_failed(const char *file, unsigned long line, const char *function, const char *expr);

#endif /* stdx_assert_h */
