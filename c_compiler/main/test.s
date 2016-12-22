	.text
	.globl	fact
fact:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$56, %rsp
	movl	%edi, -4(%rbp)
	movl	$4, -8(%rbp)
	movl	-4(%rbp), %ecx
	cmpl	$1, %ecx
	sete	%al
	movzbl	%al, %eax
	movl	%eax, -12(%rbp)
	movl	-12(%rbp), %ecx
	cmpl	$1, %ecx
	je	.lable2
	jmp	.lable1
.lable2:
	movl	-4(%rbp), %eax
	leave
	ret
	jmp	.lable0
.lable1:
	movl	-4(%rbp), %ecx
	subl	$1, %ecx
	movl	%ecx, -24(%rbp)
	movl	-24(%rbp), %edi
	call	fact
	movl	%eax, -28(%rbp)
	movl	-4(%rbp), %ecx
	movl	-28(%rbp), %eax
	imull	%eax, %ecx
	movl	%ecx, -20(%rbp)
	movl	-20(%rbp), %ecx
	movl	%ecx, -16(%rbp)
	movl	-16(%rbp), %eax
	leave
	ret
.lable0:
	movl	$4, -32(%rbp)
	movl	-4(%rbp), %ecx
	cmpl	$1, %ecx
	sete	%al
	movzbl	%al, %eax
	movl	%eax, -36(%rbp)
	movl	-36(%rbp), %ecx
	cmpl	$1, %ecx
	je	.lable5
	jmp	.lable4
.lable5:
	movl	-4(%rbp), %eax
	leave
	ret
	jmp	.lable3
.lable4:
	movl	-4(%rbp), %ecx
	subl	$1, %ecx
	movl	%ecx, -48(%rbp)
	movl	-48(%rbp), %edi
	call	fact
	movl	%eax, -52(%rbp)
	movl	-4(%rbp), %ecx
	movl	-52(%rbp), %eax
	imull	%eax, %ecx
	movl	%ecx, -44(%rbp)
	movl	-44(%rbp), %ecx
	movl	%ecx, -40(%rbp)
	movl	-40(%rbp), %eax
	leave
	ret
.lable3:
	.globl	main
main:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$36, %rsp
	movl	$4, -4(%rbp)
	movl	-4(%rbp), %ecx
	cmpl	$1, %ecx
	setg	%al
	movzbl	%al, %eax
	movl	%eax, -12(%rbp)
	movl	-12(%rbp), %ecx
	cmpl	$1, %ecx
	je	.lable8
	jmp	.lable7
.lable8:
	movl	-4(%rbp), %edi
	call	fact
	movl	%eax, -16(%rbp)
	movl	-16(%rbp), %ecx
	movl	%ecx, -8(%rbp)
	jmp	.lable6
.lable7:
	movl	$1, -8(%rbp)
.lable6:
	movl	$0, %eax
	leave
	ret
	movl	$4, -20(%rbp)
	movl	-20(%rbp), %ecx
	cmpl	$1, %ecx
	setg	%al
	movzbl	%al, %eax
	movl	%eax, -28(%rbp)
	movl	-28(%rbp), %ecx
	cmpl	$1, %ecx
	je	.lable11
	jmp	.lable10
.lable11:
	movl	-20(%rbp), %edi
	call	fact
	movl	%eax, -32(%rbp)
	movl	-32(%rbp), %ecx
	movl	%ecx, -24(%rbp)
	jmp	.lable9
.lable10:
	movl	$1, -24(%rbp)
.lable9:
	movl	$0, %eax
	leave
	ret
