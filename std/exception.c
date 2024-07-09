//
//  exception.c
//  std
//
//  Created by MakeThingsSimple on 26/4/2024.
//

#include "exception.h"

#include <stdio.h>

__attribute__((noreturn)) void _terminate(void) {
    fprintf(stderr, "terminating due to uncaught exception: %s", exception.what);
    abort();
}

vector *_eh_frame = NULL;
struct exception exception;
static terminate_handler _terminate_handler = _terminate;

__attribute__((noreturn)) void terminate(void) {
    _terminate_handler();
}

terminate_handler get_terminate(void) {
    return _terminate_handler;
}

void set_terminate(terminate_handler f) {
    _terminate_handler = f;
}

void _try(jmp_buf *buf)
{
    if (!_eh_frame)
        _eh_frame = new_vector(jmp_buf *); // if this fails, the program crashes
    
    vector_push_back(_eh_frame, &buf);
}

bool _catch(void)
{
    vector_pop_back(_eh_frame);
    return true;
}

void _throw(void)
{
    jmp_buf **eh = vector_pop_back(_eh_frame);
    if (eh)
        longjmp(**eh, 1);
    else
        terminate();
}