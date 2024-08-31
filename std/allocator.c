//
//  allocator.c
//  std
//
//  Created by MakeThingsSimple on 31/8/2024.
//

#include "allocator.h"
#include "cstddef.h"

pfn_allocator_allocate allocator_allocate = malloc;
pfn_allocator_free allocator_free = free;

void std_allocator_init(pfn_allocator_allocate alloc_pfn, pfn_allocator_free free_pfn) {
    allocator_allocate = alloc_pfn ? alloc_pfn : malloc;
    allocator_free = free_pfn ? free_pfn : free;
}