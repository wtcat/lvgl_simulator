/*
 * Copyright 2022 wtcat
 */
#ifndef MEM_TRACER_H_
#define MEM_TRACER_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C"{
#endif

#define MTRACER_INST_SIZE 256

#define MTRACER_DEFINE(name) \
    unsigned long name[(MTRACER_INST_SIZE + sizeof(long) - 1) / sizeof(long)]
#define MTRACER_DECLARE(name) \
    extern unsigned long name[]

struct printer;
struct mem_allocator;

/* Tracer Options */
#define MEM_CHECK_OVERFLOW 0x1
#define MEM_CHECK_INVALID  0x2

enum mem_dumper {
    MEM_DUMP_SORTED,
    MEM_DUMP_SEQUENCE
};

size_t mem_tracer_get_used(void* context);
void *mem_tracer_alloc(void *context, size_t size);
void mem_tracer_free(void *context, void *ptr);
void mem_tracer_dump(void *context, enum mem_dumper type);
void mem_tracer_set_path_length(void *context, size_t maxlen);
void mem_tracer_set_path_limits(void *context, int min, int max);
void mem_tracer_set_printer(void *context, const struct printer *vio);
int mem_tracer_set_path_separator(void *context, const char *separator);
void mem_tracer_init(void *context, struct mem_allocator *alloc, 
    unsigned int options);
void mem_tracer_deinit(void* context);
void mem_tracer_destory(void *context);


#ifdef __cplusplus
}
#endif
#endif // MEM_TRACER_H_
