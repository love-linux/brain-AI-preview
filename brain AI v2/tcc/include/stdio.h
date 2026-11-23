/* brain-ai: TinyCC（Brain・Windows CE）用の stdio.h。出力は crt.c がファイルに書く */
#ifndef BRAIN_STDIO_H
#define BRAIN_STDIO_H
#include <stdarg.h>
#include <stddef.h>
#ifndef _FILE_DEFINED            /* Windows CE 側のヘッダー（tcc\include\ce）が先に決めていればそれを使う */
#define _FILE_DEFINED
typedef struct _iobuf FILE;
#endif
FILE *brain_stdout(void);
#define stdout (brain_stdout())
#define stderr (brain_stdout())
#define EOF (-1)
int printf(const char *fmt, ...);
int vprintf(const char *fmt, va_list ap);
int puts(const char *s);
int putchar(int c);
int fprintf(FILE *f, const char *fmt, ...);
int vfprintf(FILE *f, const char *fmt, va_list ap);
int fputs(const char *s, FILE *f);
int fputc(int c, FILE *f);
#define putc fputc
int sprintf(char *s, const char *fmt, ...);
int _snprintf(char *s, size_t n, const char *fmt, ...);
#define snprintf _snprintf
int vsprintf(char *s, const char *fmt, va_list ap);
int _vsnprintf(char *s, size_t n, const char *fmt, va_list ap);
#define vsnprintf _vsnprintf
int sscanf(const char *s, const char *fmt, ...);
FILE *fopen(const char *name, const char *mode);
int fclose(FILE *f);
size_t fread(void *p, size_t s, size_t n, FILE *f);
size_t fwrite(const void *p, size_t s, size_t n, FILE *f);
char *fgets(char *s, int n, FILE *f);
int fflush(FILE *f);
#endif
