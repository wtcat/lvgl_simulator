/*
 * Copyright 2022 wtcat
 */
#ifndef BASE_ALLOCATOR_H_
#define BASE_ALLOCATOR_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C"{
#endif

struct mem_allocator {
    void *(*allocate)(struct mem_allocator *m, size_t size, void *user);
    void (*free)(struct mem_allocator *m, void *ptr, void *user);
    void *context;
};

static inline void *memory_allocate(struct mem_allocator *m, 
    size_t size, void *user) {
    return m->allocate(m, size, user);
}

static inline void memory_free(struct mem_allocator *m, 
    void *ptr, void *user) {
    m->free(m, ptr, user);
}

#ifdef __cplusplus
}
#endif
#endif /* BASE_ALLOCATOR_H_ */
