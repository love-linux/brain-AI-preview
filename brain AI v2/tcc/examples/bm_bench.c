/* brainmath の試験と速さ比べ。Brain では tcc で実行し、「tcc だけ」と「brainmath.dll」の時間を比べる。
 * 答えはどちらも同じになるはず（下に正解も書く） */
int printf(const char *, ...);
#include <brainmath.h>
#if defined(_WIN32) && !defined(BM_NOTIME)
unsigned long __stdcall GetTickCount(void);
static unsigned ms(void) { return (unsigned)GetTickCount(); }
#else
static unsigned ms(void) { return 0; }         /* 試験用（時間は測らない） */
#endif

/* tcc だけで同じ計算 */
static double tcc_bench(int n) {
    double s = 0;
    int i;
    for (i = 0; i < n; i++) s = s * 0.999 + 0.5;
    return s;
}
static void tcc_solve(int n, double *A, double *b) {            /* ガウス消去（ピボット無し・対角優位の行列用） */
    int i, j, k;
    for (k = 0; k < n; k++)
        for (i = k + 1; i < n; i++) {
            double f = A[i * n + k] / A[k * n + k];
            for (j = k; j < n; j++) A[i * n + j] -= f * A[k * n + j];
            b[i] -= f * b[k];
        }
    for (i = n - 1; i >= 0; i--) {
        double s = b[i];
        for (j = i + 1; j < n; j++) s -= A[i * n + j] * b[j];
        b[i] = s / A[i * n + i];
    }
}

/* tcc の関数を DLL から呼んでもらう（ばね・おもり: y'' = -y） */
static void spring(double t, const double *y, double *d, void *u) { (void)t; (void)u; d[0] = y[1]; d[1] = -y[0]; }
static double cubic(double x, void *u) { (void)u; return x * x * x - 2 * x - 5; }
static double sq(double x, void *u) { (void)u; return x * x; }

#define N 60
static double A[N * N], A2[N * N], b[N], b2[N], x[N];

int main(void) {
    unsigned t0, t1, t2;
    int i, j, n = 200000;
    double r1, r2, y[2] = {1, 0};
    printf("brainmath version %d\n", bm_version());

    /* 1. 掛け算と足し算 n 回 */
    t0 = ms(); r1 = tcc_bench(n); t1 = ms(); r2 = bm_bench(n); t2 = ms();
    printf("bench %d 回: tcc %u ms / dll %u ms（答え %.6f %.6f、正解 500.000000 付近）\n", n, t1 - t0, t2 - t1, r1, r2);

    /* 2. 連立方程式 60 元 */
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) A[i * N + j] = (i == j) ? 4.0 : (i - j == 1 || j - i == 1) ? -1.0 : 0.0;
        b[i] = 1.0 + i % 3;
    }
    for (i = 0; i < N * N; i++) A2[i] = A[i];
    for (i = 0; i < N; i++) b2[i] = b[i];
    t0 = ms(); tcc_solve(N, A2, b2); t1 = ms(); bm_solve(N, A, b, x); t2 = ms();
    printf("solve %d 元: tcc %u ms / dll %u ms（x[0] %.9f %.9f、x[%d] %.9f %.9f）\n", N, t1 - t0, t2 - t1, b2[0], x[0], N - 1, b2[N - 1], x[N - 1]);

    /* 3. 行列式・逆行列（小さい行列） */
    {
        double M[9] = {2, 1, 0, 1, 3, 1, 0, 1, 4}, Mi[9], I[9];
        bm_inverse(3, M, Mi);
        bm_matmul(3, 3, 3, M, Mi, I);
        printf("det %.6f（正解 18）  M*inv(M) の対角 %.6f %.6f %.6f\n", bm_det(3, M), I[0], I[4], I[8]);
    }

    /* 4. 微分方程式: ばね（tcc の関数を DLL が呼ぶ）。t=2π で元に戻る */
    t0 = ms();
    bm_rk4(2, spring, 0, 0.0, 6.283185307179586 / 1000, 1000, y, 0);
    t1 = ms();
    printf("rk4 ばね 1 周: y=%.6f v=%.6f（正解 1 と 0）%u ms\n", y[0], y[1], t1 - t0);

    /* 5. 根と積分 */
    printf("root x^3-2x-5: %.9f（正解 2.094551482）  ∫0..1 x^2: %.9f（正解 0.333333333）\n",
           bm_root(cubic, 0, 2.0, 3.0, 1e-12), bm_integrate(sq, 0, 0.0, 1.0, 100));
    return 0;
}
