#ifndef BRAIN_ASSERT_H
#define BRAIN_ASSERT_H
int printf(const char *fmt, ...);
void exit(int code);
#define assert(e) ((e) ? (void)0 : (printf("assert failed: %s (%s:%d)\n", #e, __FILE__, __LINE__), exit(1)))
#endif
