/* coredll に無いものもあるので、ここで書く */
#ifndef BRAIN_CTYPE_H
#define BRAIN_CTYPE_H
static int isdigit(int c) { return c >= '0' && c <= '9'; }
static int isalpha(int c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); }
static int isalnum(int c) { return isdigit(c) || isalpha(c); }
static int isspace(int c) { return c == ' ' || (c >= '\t' && c <= '\r'); }
static int isupper(int c) { return c >= 'A' && c <= 'Z'; }
static int islower(int c) { return c >= 'a' && c <= 'z'; }
static int ispunct(int c) { return c > ' ' && c < 127 && !isalnum(c); }
static int isxdigit(int c) { return isdigit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'); }
static int isprint(int c) { return c >= ' ' && c < 127; }
static int isgraph(int c) { return c > ' ' && c < 127; }
static int iscntrl(int c) { return (c >= 0 && c < ' ') || c == 127; }
static int toupper(int c) { return islower(c) ? c - 32 : c; }
static int tolower(int c) { return isupper(c) ? c + 32 : c; }
#endif
