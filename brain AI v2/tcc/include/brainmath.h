/*
 * brainmath: Brain（Windows CE / ARM926、FPU 無し）用の計算の核。
 * 中身は CeGCC（-O2）で前もってコンパイルした brainmath.dll。tcc で書いたプログラムから普通の関数として呼ぶ。
 * tcc は浮動小数点を命令ごとのエミュレーターで計算するので遅い。何万回も回る計算はこちらに任せる。
 *
 * 行列は行優先（A[i*n + j] が i 行 j 列）。戻り値 0 = 成功、それ以外 = 失敗（特異など）。
 */
#ifndef BRAINMATH_H
#define BRAINMATH_H
#ifdef __cplusplus
extern "C" {
#endif

int bm_version(void);                                               /* 100 = 1.0 */

/* ベクトル */
double bm_dot(int n, const double *x, const double *y);             /* x・y */
double bm_norm(int n, const double *x);                             /* |x| */
void bm_axpy(int n, double a, const double *x, double *y);          /* y += a*x */

/* 行列 */
void bm_matvec(int m, int n, const double *A, const double *x, double *y);              /* y = A x（A は m×n） */
void bm_matmul(int m, int k, int n, const double *A, const double *B, double *C);       /* C = A B（m×k・k×n） */
int bm_solve(int n, const double *A, const double *b, double *x);   /* A x = b（部分ピボットのガウス消去。A・b は壊さない） */
int bm_inverse(int n, const double *A, double *Ainv);               /* 逆行列 */
double bm_det(int n, const double *A);                              /* 行列式 */

/* 微分方程式 dy/dt = f(t, y)（y は m 個）。ルンゲ＝クッタ 4 次で t0 から dt ずつ steps 回進める。
 * f は tcc で書いた関数をそのまま渡せる。out が NULL でなければ、各ステップの y を out[(k+1)*m + i] に書く */
typedef void (*bm_ode_fn)(double t, const double *y, double *dydt, void *user);
int bm_rk4(int m, bm_ode_fn f, void *user, double t0, double dt, int steps, double *y, double *out);

/* 1 変数の関数の根（二分法＋割線法）・数値積分（シンプソン） */
typedef double (*bm_fn1)(double x, void *user);
double bm_root(bm_fn1 f, void *user, double a, double b, double tol);
double bm_integrate(bm_fn1 f, void *user, double a, double b, int n);

/* 速さ比べ: s = s*0.999 + 0.5 を n 回（浮動小数点の掛け算と足し算） */
double bm_bench(int n);

#ifdef __cplusplus
}
#endif
#endif
