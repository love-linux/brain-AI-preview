#ifndef BRAIN_STDLIB_H
#define BRAIN_STDLIB_H
#include <stddef.h>
void *malloc(size_t n);
void *calloc(size_t n, size_t s);
void *realloc(void *p, size_t n);
void free(void *p);
int atoi(const char *s);
long atol(const char *s);
long strtol(const char *s, char **e, int b);
unsigned long strtoul(const char *s, char **e, int b);
int abs(int x);
long labs(long x);
int rand(void);
void srand(unsigned s);
#define RAND_MAX 0x7fff
void qsort(void *b, size_t n, size_t s, int (*cmp)(const void *, const void *));
void *bsearch(const void *k, const void *b, size_t n, size_t s, int (*cmp)(const void *, const void *));
void exit(int code);
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#endif
