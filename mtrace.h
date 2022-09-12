/*
 * Copyright 2022 wtcat
 */
#ifndef MTRACE_H_
#define MTRACE_H_

#ifdef __cplusplus
extern "C" {
#endif

int _ui_mem_init(void);
void* _ui_malloc(size_t size);
void* _ui_realloc(void* ptr, size_t size);
void _ui_free(void* ptr);

#ifdef __cplusplus
}
#endif
#endif /* MTRACE_H_ */
