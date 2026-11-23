@ 例: ARM のアセンブリだけで書いたプログラム（Brain の tcc でアセンブルして実行）。
@ main から printf を呼び、1〜10 の合計と 10 の階乗を出す。結果はアプリの「実行結果」に出る。
    .text
    .global main
main:
    stmfd sp!, {r4, r5, lr}
    mov r4, #0              @ 合計
    mov r5, #1              @ i
1:
    add r4, r4, r5
    add r5, r5, #1
    cmp r5, #10
    ble 1b
    ldr r0, =msg_sum
    mov r1, r4
    bl printf

    mov r0, #10
    bl fact
    mov r1, r0
    ldr r0, =msg_fact
    bl printf

    mov r0, #0
    ldmfd sp!, {r4, r5, pc}

fact:                       @ 再帰で n!
    stmfd sp!, {r4, lr}
    mov r4, r0
    cmp r0, #1
    movle r0, #1
    ble 2f
    sub r0, r0, #1
    bl fact
    mul r1, r0, r4
    mov r0, r1
2:
    ldmfd sp!, {r4, pc}

    .data
msg_sum:
    .asciz "1+2+...+10 = %d\n"
msg_fact:
    .asciz "10! = %d\n"
