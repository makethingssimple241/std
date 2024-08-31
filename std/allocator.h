//
//  allocator.h
//  std
//
//  Created by MakeThingsSimple on 31/8/2024.
//

#ifndef std_allocator_h
#define std_allocator_h

#include <stdlib.h>

typedef void *(* pfn_allocator_allocate)(size_t);
typedef void (* pfn_allocator_free)(void *);

extern pfn_allocator_allocate allocator_allocate;
extern pfn_allocator_free allocator_free;

void std_allocator_init(pfn_allocator_allocate alloc_pfn, pfn_allocator_free free_pfn);

#endif /* std_allocator_h */