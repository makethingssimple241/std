//
//  assert.c
//  std
//
//  Created by MakeThingsSimple on 26/6/2024.
//

#include "assert.h"

#include <stdio.h>
#include <stdlib.h>

void assertion_failed(const char *file, unsigned long line, const char *function, const char *expr)
{
    fprintf(stderr, "%s:%lu:%s: Assertion failed: %s", file, line, function, expr);
    abort();
}
