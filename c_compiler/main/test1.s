	.file	"test1.c"
	.text
	.globl	fact
	.type	fact, @function
fact:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movl	$0, -4(%rbp)
	movl	-4(%rbp), %eax
	cltd
	idivl	-20(%rbp)
	movl	%eax, -4(%rbp)
	movl	-20(%rbp), %eax
	cmpl	-4(%rbp), %eax
	setge	%al
	movzbl	%al, %eax
	movl	%eax, -4(%rbp)
	movl	-20(%rbp), %eax
	cmpl	-4(%rbp), %eax
	setle	%al
	movzbl	%al, %eax
	movl	%eax, -4(%rbp)
	movl	-20(%rbp), %eax
	cmpl	-4(%rbp), %eax
	setne	%al
	movzbl	%al, %eax
	movl	%eax, -4(%rbp)
	movl	-20(%rbp), %eax
	cmpl	-4(%rbp), %eax
	setg	%al
	movzbl	%al, %eax
	movl	%eax, -4(%rbp)
	movl	-20(%rbp), %eax
	cmpl	-4(%rbp), %eax
	setl	%al
	movzbl	%al, %eax
	movl	%eax, -4(%rbp)
	movl	-20(%rbp), %eax
	cltd
	idivl	-4(%rbp)
	movl	%eax, -4(%rbp)
	cmpl	$1, -20(%rbp)
	jne	.L2
	movl	-20(%rbp), %eax
	jmp	.L3
.L2:
	movl	-20(%rbp), %eax
	subl	$1, %eax
	movl	%eax, %edi
	call	fact
	imull	-20(%rbp), %eax
.L3:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	fact, .-fact
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$2, -8(%rbp)
	cmpl	$1, -8(%rbp)
	jle	.L5
	movl	-8(%rbp), %eax
	movl	%eax, %edi
	call	fact
	movl	%eax, -4(%rbp)
	jmp	.L6
.L5:
	movl	$1, -4(%rbp)
.L6:
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
