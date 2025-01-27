//
//  exception.h
//  std
//
//  Created by MakeThingsSimple on 26/4/2024.
//

#ifndef std_exception_h
#define std_exception_h

#include "cstddef.h"
#include "vector.h"

#include <stdbool.h>
#include <setjmp.h>

/// @warning Must not return from <tt>try</tt>, @c catch or @c catchall as it will cause exception frames (<tt>jmp_buf</tt>s) in @c _eh_frame to not be popped properly
/// @note A @c for loop is used so that during the "first iteration", @c _try is called, pushing <tt>_frame.buf</tt>, and after the "first iteration" (@c _frame.ended is set to <tt>true</tt>), @c try_end is called, popping <tt>_frame.buf</tt>.
#define try \
    for (struct { jmp_buf buf; bool ended; } _frame = {.ended=false}; _frame.ended ? _try_end() : _try(&_frame.buf), !_frame.ended; _frame.ended = true) \
        if (setjmp(_frame.buf) == 0)
#define catch(_id) else if (exception.id == _id)
#define catchall else
#define rethrow _throw()
#define throw(_exception) do { exception = (_exception); rethrow; } while (0)

#define system_error(error_code, what_arg) (struct exception){.id=error_code, .what=what_arg}
#define new_exception(_type) (struct exception){.id=_type, .what=#_type}
#define new_exceptionx(_type, _what) (struct exception){.id=_type, .what=_what}

struct exception {
    int id;
    const char *what;
};

typedef noreturn void (*terminate_handler)(void);

extern vector _eh_frame;
extern struct exception exception;

noreturn void terminate(void);
terminate_handler get_terminate(void);
void set_terminate(terminate_handler f);

/// @brief Push @p buf to @c _eh_frame
void _try(jmp_buf *buf);
/// @brief Pop the top @c jmp_buf from @c _eh_frame
bool _try_end(void);
/// @brief Jumps to the "closest" @c catch
/// @details @c longjmp to the topmost @c jmp_buf of the @c _eh_frame or <tt>terminate</tt>ing if @c _eh_frame is empty.
void _throw(void);

#endif /* std_exception_h */
