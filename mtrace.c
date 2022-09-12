/*
 * Copyright 2022 wtcat
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tracer/printer.h"
#include "tracer/mem_tracer.h"
#include "mtrace.h"

static FILE* log_file;
static struct printer cout;
static MTRACER_DEFINE(mtrace_context);

#ifdef _WIN32
#pragma comment (lib,"tracer.lib")
#endif

static void _ui_mem_deinit(void) {
    mem_tracer_dump(mtrace_context, MEM_DUMP_SORTED);
    if (log_file) {
        fclose(log_file);
        log_file = NULL;
    }
    mem_tracer_deinit(mtrace_context);
}

int _ui_mem_init(void) {
    log_file = fopen("mtrace_dump.txt", "wb");
    fprintf_printer_init(&cout, log_file);
    mem_tracer_init(mtrace_context, NULL, 0);
    mem_tracer_set_printer(mtrace_context, &cout);
    mem_tracer_set_path_limits(&mtrace_context, 1, 20);
    mem_tracer_set_path_separator(&mtrace_context, "\n  -> ");
    atexit(_ui_mem_deinit);
    return 0;
}

void* _ui_malloc(size_t size) {
    size_t* p = mem_tracer_alloc(mtrace_context, size + sizeof(size_t));
    if (p) {
        *p = size;
        return p + 1;
    }
    return NULL;
}

void _ui_free(void* ptr) {
    size_t* p = (size_t*)ptr;
    mem_tracer_free(mtrace_context, p - 1);
}

void* _ui_realloc(void* ptr, size_t size) {
    size_t oldsize;
    void* np;
    if (size == 0)
        return ptr;
    if (ptr == NULL)
        return _ui_malloc(size);
    oldsize = ((size_t*)ptr)[-1];
    if (oldsize >= size)
        return ptr;
    np = _ui_malloc(size);
    if (np) {
        memcpy(np, ptr, oldsize);
        _ui_free(ptr);
    }
    return np;
}
