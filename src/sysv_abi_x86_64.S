.text

# Invoke an arbitrary scalar System V AMD64 function.  The C++ marshaller
# classifies arguments into the six integer registers, eight SSE registers,
# and an unbounded array of eight-byte stack slots.
.globl underc_sysv_call
.type underc_sysv_call,@function
underc_sysv_call:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp
    movq %rdi, -8(%rbp)       # function
    movq %rsi, -16(%rbp)      # integer register values
    movq %rdx, -24(%rbp)      # SSE register values
    movq %r9, -32(%rbp)       # number of SSE registers used

    movq %r8, %rax
    shlq $3, %rax
    addq $15, %rax
    andq $-16, %rax
    subq %rax, %rsp

    xorq %rax, %rax
.Lcopy_call_stack:
    cmpq %r8, %rax
    jae .Lcall_stack_done
    movq (%rcx,%rax,8), %r10
    movq %r10, (%rsp,%rax,8)
    incq %rax
    jmp .Lcopy_call_stack
.Lcall_stack_done:
    movq -24(%rbp), %r10
    movq 0(%r10), %xmm0
    movq 8(%r10), %xmm1
    movq 16(%r10), %xmm2
    movq 24(%r10), %xmm3
    movq 32(%r10), %xmm4
    movq 40(%r10), %xmm5
    movq 48(%r10), %xmm6
    movq 56(%r10), %xmm7

    movq -16(%rbp), %r10
    movq 0(%r10), %rdi
    movq 8(%r10), %rsi
    movq 16(%r10), %rdx
    movq 24(%r10), %rcx
    movq 32(%r10), %r8
    movq 40(%r10), %r9
    movl -32(%rbp), %eax
    call *-8(%rbp)

    movq 16(%rbp), %r10
    movq %rax, (%r10)
    movq 24(%rbp), %r10
    movq %xmm0, (%r10)
    leave
    ret
.size underc_sysv_call, .-underc_sysv_call

# Entry point for generated callback trampolines.  The trampoline places its
# descriptor in r10 and jumps here without disturbing the caller's arguments.
.globl underc_sysv_callback_entry
.type underc_sysv_callback_entry,@function
underc_sysv_callback_entry:
    pushq %rbp
    movq %rsp, %rbp
    subq $160, %rsp

    movq %rdi, -48(%rbp)
    movq %rsi, -40(%rbp)
    movq %rdx, -32(%rbp)
    movq %rcx, -24(%rbp)
    movq %r8,  -16(%rbp)
    movq %r9,  -8(%rbp)
    movq %xmm0, -112(%rbp)
    movq %xmm1, -104(%rbp)
    movq %xmm2, -96(%rbp)
    movq %xmm3, -88(%rbp)
    movq %xmm4, -80(%rbp)
    movq %xmm5, -72(%rbp)
    movq %xmm6, -64(%rbp)
    movq %xmm7, -56(%rbp)

    movq %r10, %rdi
    leaq -48(%rbp), %rsi
    leaq -112(%rbp), %rdx
    leaq 16(%rbp), %rcx
    leaq -128(%rbp), %r8
    call underc_sysv_callback_invoke

    movq -128(%rbp), %rax
    movq -120(%rbp), %xmm0
    leave
    ret
.size underc_sysv_callback_entry, .-underc_sysv_callback_entry

.section .note.GNU-stack,"",@progbits
