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

#define try \
    jmp_buf _eh; \
    _try(&_eh); \
    if (setjmp(_eh) == 0)
#define catch(_id) else if (exception.id == _id && _catch())
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

extern vector *_eh_frame;
extern struct exception exception;

noreturn void terminate(void);
terminate_handler get_terminate(void);
void set_terminate(terminate_handler f);

void _try(jmp_buf *buf);
bool _catch(void);
void _throw(void);

#endif /* std_exception_h */
