/* brain-ai: TinyCC（Brain・Windows CE）用の math.h。関数は coredll にある（計算は改造 tcc の浮動小数点エミュレーター経由で正しく渡る） */
#ifndef BRAIN_MATH_H
#define BRAIN_MATH_H

double sin(double), cos(double), tan(double), asin(double), acos(double), atan(double), atan2(double, double);
double sinh(double), cosh(double), tanh(double), exp(double), log(double), log10(double), pow(double, double);
double sqrt(double), ceil(double), floor(double), fabs(double), fmod(double, double);
double frexp(double, int *), ldexp(double, int), modf(double, double *);
double _hypot(double, double), _copysign(double, double), _logb(double), _nextafter(double, double);
int _isnan(double), _finite(double);
float fabsf(float), floorf(float), sqrtf(float);
double atof(const char *);

#define hypot _hypot
#define copysign _copysign
#define logb _logb
#define nextafter _nextafter
#define isnan(x) _isnan((double)(x))
#define isfinite(x) _finite((double)(x))
#define isinf(x) (!_finite((double)(x)) && !_isnan((double)(x)))

/* float 版（coredll に無いものは double 版を使う） */
static inline float sinf(float x) { return (float)sin(x); }
static inline float cosf(float x) { return (float)cos(x); }
static inline float tanf(float x) { return (float)tan(x); }
static inline float asinf(float x) { return (float)asin(x); }
static inline float acosf(float x) { return (float)acos(x); }
static inline float atanf(float x) { return (float)atan(x); }
static inline float atan2f(float y, float x) { return (float)atan2(y, x); }
static inline float expf(float x) { return (float)exp(x); }
static inline float logf(float x) { return (float)log(x); }
static inline float log10f(float x) { return (float)log10(x); }
static inline float powf(float x, float y) { return (float)pow(x, y); }
static inline float ceilf(float x) { return (float)ceil(x); }
static inline float fmodf(float x, float y) { return (float)fmod(x, y); }
static inline double round(double x) { return x < 0 ? -floor(-x + 0.5) : floor(x + 0.5); }
static inline float roundf(float x) { return (float)round(x); }
static inline double trunc(double x) { return x < 0 ? ceil(x) : floor(x); }
static inline double log2(double x) { return log(x) / 0.69314718055994530942; }
static inline double exp2(double x) { return pow(2.0, x); }
static inline double cbrt(double x) { return x < 0 ? -pow(-x, 1.0 / 3) : pow(x, 1.0 / 3); }
static inline double fmin(double a, double b) { return a < b ? a : b; }
static inline double fmax(double a, double b) { return a > b ? a : b; }

static const union { unsigned long long u; double d; } __brain_inf = {0x7FF0000000000000ULL}, __brain_nan = {0x7FF8000000000000ULL};
#define HUGE_VAL (__brain_inf.d)
#define INFINITY ((float)__brain_inf.d)
#define NAN ((float)__brain_nan.d)

#define M_E 2.7182818284590452354
#define M_LOG2E 1.4426950408889634074
#define M_LOG10E 0.43429448190325182765
#define M_LN2 0.69314718055994530942
#define M_LN10 2.30258509299404568402
#define M_PI 3.14159265358979323846
#define M_PI_2 1.57079632679489661923
#define M_PI_4 0.78539816339744830962
#define M_1_PI 0.31830988618379067154
#define M_2_PI 0.63661977236758134308
#define M_SQRT2 1.41421356237309504880
#define M_SQRT1_2 0.70710678118654752440
#endif
