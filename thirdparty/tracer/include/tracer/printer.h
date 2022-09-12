/*
 * Copyright 2022 wtcat
 */
#ifndef BASE_PRINTER_H_
#define BASE_PRINTER_H_

#include <stdarg.h>

#ifdef __cplusplus
extern "C"{
#endif

struct printer {
    int (*printer)(void *context, const char *fmt, va_list ap_list);
    void *context;
};

static inline int virt_print(const struct printer *printer, 
    const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    int len = printer->printer(printer->context, fmt, ap);
    va_end(ap);
    return len;
}

void printf_printer_init(struct printer *printer);
void fprintf_printer_init(struct printer *printer, void *fp);

#ifdef __cplusplus
}
#endif
#endif /* BASE_PRINTER_H_ */