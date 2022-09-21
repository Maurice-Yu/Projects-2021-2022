	.file	"thermo_update.c"
	.text
	.globl	thermo_update
	.type	thermo_update, @function
thermo_update:
.LFB6:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movb	$0, -10(%rbp)
	movw	$0, -12(%rbp)
	leaq	-12(%rbp), %rax
	movq	%rax, %rdi
	call	set_temp_from_ports
	movl	%eax, -20(%rbp)
	movl	-12(%rbp), %eax
	leaq	THERMO_DISPLAY_PORT(%rip), %rsi
	movl	%eax, %edi
	call	set_display_from_temp
	movl	%eax, -16(%rbp)
	cmpl	$0, -20(%rbp)
	jne	.L2
	cmpl	$0, -16(%rbp)
	jne	.L2
	movl	$0, %eax
	jmp	.L4
.L2:
	movl	$1, %eax
.L4:
	movq	-8(%rbp), %rdx
	xorq	%fs:40, %rdx
	je	.L5
	call	__stack_chk_fail@PLT
.L5:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	thermo_update, .-thermo_update
	.globl	set_temp_from_ports
	.type	set_temp_from_ports, @function
set_temp_from_ports:
.LFB7:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movzwl	THERMO_SENSOR_PORT(%rip), %eax
	testw	%ax, %ax
	js	.L7
	movzwl	THERMO_SENSOR_PORT(%rip), %eax
	cmpw	$28800, %ax
	jle	.L8
.L7:
	movq	-24(%rbp), %rax
	movb	$3, 2(%rax)
	movq	-24(%rbp), %rax
	movw	$0, (%rax)
	movl	$1, %eax
	jmp	.L9
.L8:
	movzbl	THERMO_STATUS_PORT(%rip), %eax
	movzbl	%al, %eax
	andl	$32, %eax
	testl	%eax, %eax
	je	.L10
	movq	-24(%rbp), %rax
	movb	$2, 2(%rax)
	jmp	.L11
.L10:
	movq	-24(%rbp), %rax
	movb	$1, 2(%rax)
.L11:
	movzbl	THERMO_STATUS_PORT(%rip), %eax
	movzbl	%al, %eax
	andl	$4, %eax
	testl	%eax, %eax
	je	.L12
	movq	-24(%rbp), %rax
	movb	$3, 2(%rax)
	movq	-24(%rbp), %rax
	movw	$0, (%rax)
	movl	$1, %eax
	jmp	.L9
.L12:
	movq	-24(%rbp), %rax
	movzbl	2(%rax), %eax
	cmpb	$1, %al
	jne	.L13
	movzwl	THERMO_SENSOR_PORT(%rip), %eax
	cwtl
	andl	$31, %eax
	movl	%eax, -8(%rbp)
	movzwl	THERMO_SENSOR_PORT(%rip), %eax
	sarw	$5, %ax
	subw	$450, %ax
	movl	%eax, %edx
	movq	-24(%rbp), %rax
	movw	%dx, (%rax)
	cmpl	$15, -8(%rbp)
	jle	.L13
	movq	-24(%rbp), %rax
	movzwl	(%rax), %eax
	addl	$1, %eax
	movl	%eax, %edx
	movq	-24(%rbp), %rax
	movw	%dx, (%rax)
.L13:
	movq	-24(%rbp), %rax
	movzbl	2(%rax), %eax
	cmpb	$2, %al
	jne	.L14
	movzwl	THERMO_SENSOR_PORT(%rip), %eax
	cwtl
	andl	$31, %eax
	movl	%eax, -4(%rbp)
	cmpl	$15, -4(%rbp)
	jle	.L15
	movzwl	THERMO_SENSOR_PORT(%rip), %eax
	sarw	$5, %ax
	cwtl
	leal	-449(%rax), %edx
	movl	%edx, %eax
	sall	$3, %eax
	addl	%edx, %eax
	movslq	%eax, %rdx
	imulq	$1717986919, %rdx, %rdx
	shrq	$32, %rdx
	sarl	%edx
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	addw	$320, %ax
	movl	%eax, %edx
	movq	-24(%rbp), %rax
	movw	%dx, (%rax)
	jmp	.L14
.L15:
	movzwl	THERMO_SENSOR_PORT(%rip), %eax
	sarw	$5, %ax
	cwtl
	leal	-450(%rax), %edx
	movl	%edx, %eax
	sall	$3, %eax
	addl	%edx, %eax
	movslq	%eax, %rdx
	imulq	$1717986919, %rdx, %rdx
	shrq	$32, %rdx
	sarl	%edx
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	addw	$320, %ax
	movl	%eax, %edx
	movq	-24(%rbp), %rax
	movw	%dx, (%rax)
.L14:
	movl	$0, %eax
.L9:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	set_temp_from_ports, .-set_temp_from_ports
	.globl	set_display_from_temp
	.type	set_display_from_temp, @function
set_display_from_temp:
.LFB8:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$192, %rsp
	movl	%edi, -180(%rbp)
	movq	%rsi, -192(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$123, -136(%rbp)
	movl	$72, -132(%rbp)
	movl	$61, -128(%rbp)
	movl	$109, -124(%rbp)
	movl	$78, -120(%rbp)
	movl	$103, -116(%rbp)
	movl	$119, -112(%rbp)
	movl	$73, -108(%rbp)
	movl	$127, -104(%rbp)
	movl	$111, -100(%rbp)
	movl	$55, -96(%rbp)
	movl	$95, -92(%rbp)
	movl	$0, -88(%rbp)
	movl	$4, -84(%rbp)
	movl	-136(%rbp), %eax
	movl	%eax, -64(%rbp)
	movl	-132(%rbp), %eax
	movl	%eax, -60(%rbp)
	movl	-128(%rbp), %eax
	movl	%eax, -56(%rbp)
	movl	-124(%rbp), %eax
	movl	%eax, -52(%rbp)
	movl	-120(%rbp), %eax
	movl	%eax, -48(%rbp)
	movl	-116(%rbp), %eax
	movl	%eax, -44(%rbp)
	movl	-112(%rbp), %eax
	movl	%eax, -40(%rbp)
	movl	-108(%rbp), %eax
	movl	%eax, -36(%rbp)
	movl	-104(%rbp), %eax
	movl	%eax, -32(%rbp)
	movl	-100(%rbp), %eax
	movl	%eax, -28(%rbp)
	movl	-96(%rbp), %eax
	movl	%eax, -24(%rbp)
	movl	-92(%rbp), %eax
	movl	%eax, -20(%rbp)
	movl	-88(%rbp), %eax
	movl	%eax, -16(%rbp)
	movl	-84(%rbp), %eax
	movl	%eax, -12(%rbp)
	movl	$0, -160(%rbp)
	movl	$0, -156(%rbp)
	movl	$4, -152(%rbp)
	movzwl	-180(%rbp), %eax
	movw	%ax, -162(%rbp)
	movq	-192(%rbp), %rax
	movl	$0, (%rax)
	movzbl	-178(%rbp), %eax
	cmpb	$1, %al
	je	.L17
	movzbl	-178(%rbp), %eax
	cmpb	$2, %al
	je	.L17
	movl	$0, -160(%rbp)
	movl	-24(%rbp), %eax
	sall	$21, %eax
	orl	%eax, -160(%rbp)
	movl	-20(%rbp), %eax
	sall	$14, %eax
	orl	%eax, -160(%rbp)
	movl	-20(%rbp), %eax
	sall	$7, %eax
	orl	%eax, -160(%rbp)
	movq	-192(%rbp), %rax
	movl	-160(%rbp), %edx
	movl	%edx, (%rax)
	movl	$1, %eax
	jmp	.L35
.L17:
	movzbl	-178(%rbp), %eax
	cmpb	$1, %al
	jne	.L19
	cmpw	$-450, -162(%rbp)
	jl	.L20
	cmpw	$450, -162(%rbp)
	jle	.L19
.L20:
	movl	$0, -160(%rbp)
	movl	-24(%rbp), %eax
	sall	$21, %eax
	orl	%eax, -160(%rbp)
	movl	-20(%rbp), %eax
	sall	$14, %eax
	orl	%eax, -160(%rbp)
	movl	-20(%rbp), %eax
	sall	$7, %eax
	orl	%eax, -160(%rbp)
	movq	-192(%rbp), %rax
	movl	-160(%rbp), %edx
	movl	%edx, (%rax)
	movl	$1, %eax
	jmp	.L35
.L19:
	movzbl	-178(%rbp), %eax
	cmpb	$2, %al
	jne	.L21
	cmpw	$-490, -162(%rbp)
	jl	.L22
	cmpw	$1130, -162(%rbp)
	jle	.L21
.L22:
	movl	$0, -160(%rbp)
	movl	-24(%rbp), %eax
	sall	$21, %eax
	orl	%eax, -160(%rbp)
	movl	-20(%rbp), %eax
	sall	$14, %eax
	orl	%eax, -160(%rbp)
	movl	-20(%rbp), %eax
	sall	$7, %eax
	orl	%eax, -160(%rbp)
	movq	-192(%rbp), %rax
	movl	-160(%rbp), %edx
	movl	%edx, (%rax)
	movl	$1, %eax
	jmp	.L35
.L21:
	cmpw	$0, -162(%rbp)
	jns	.L23
	movl	$255, -156(%rbp)
	movzwl	-162(%rbp), %eax
	negl	%eax
	movw	%ax, -162(%rbp)
.L23:
	movl	$0, -80(%rbp)
	movl	$0, -76(%rbp)
	movl	$0, -72(%rbp)
	movl	$0, -68(%rbp)
	movl	$0, -148(%rbp)
	jmp	.L24
.L27:
	movzwl	-162(%rbp), %ecx
	movswl	%cx, %eax
	imull	$26215, %eax, %eax
	shrl	$16, %eax
	movl	%eax, %edx
	sarw	$2, %dx
	movl	%ecx, %eax
	sarw	$15, %ax
	subl	%eax, %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	subl	%eax, %ecx
	movl	%ecx, %edx
	movswl	%dx, %edx
	movl	-148(%rbp), %eax
	cltq
	movl	%edx, -80(%rbp,%rax,4)
	movzwl	-162(%rbp), %eax
	movswl	%ax, %edx
	imull	$26215, %edx, %edx
	shrl	$16, %edx
	sarw	$2, %dx
	sarw	$15, %ax
	subl	%eax, %edx
	movl	%edx, %eax
	movw	%ax, -162(%rbp)
	cmpw	$0, -162(%rbp)
	jne	.L25
	movl	-148(%rbp), %eax
	movl	%eax, -152(%rbp)
	jmp	.L26
.L25:
	addl	$1, -148(%rbp)
.L24:
	cmpl	$3, -148(%rbp)
	jle	.L27
.L26:
	movl	$0, -144(%rbp)
	jmp	.L28
.L29:
	movl	-144(%rbp), %eax
	cltq
	movl	-80(%rbp,%rax,4), %eax
	cltq
	movl	-64(%rbp,%rax,4), %esi
	movl	-144(%rbp), %edx
	movl	%edx, %eax
	sall	$3, %eax
	subl	%edx, %eax
	movl	%eax, %ecx
	sall	%cl, %esi
	movl	%esi, %eax
	orl	%eax, -160(%rbp)
	addl	$1, -144(%rbp)
.L28:
	cmpl	$3, -144(%rbp)
	jle	.L29
	movl	$3, -140(%rbp)
	jmp	.L30
.L31:
	movl	-16(%rbp), %eax
	notl	%eax
	movl	%eax, %esi
	movl	-140(%rbp), %edx
	movl	%edx, %eax
	sall	$3, %eax
	subl	%edx, %eax
	movl	%eax, %ecx
	sall	%cl, %esi
	movl	%esi, %eax
	notl	%eax
	andl	%eax, -160(%rbp)
	subl	$1, -140(%rbp)
.L30:
	movl	-140(%rbp), %eax
	cmpl	-152(%rbp), %eax
	jg	.L31
	cmpl	$0, -156(%rbp)
	je	.L32
	movl	-12(%rbp), %esi
	movl	-152(%rbp), %eax
	leal	1(%rax), %edx
	movl	%edx, %eax
	sall	$3, %eax
	subl	%edx, %eax
	movl	%eax, %ecx
	sall	%cl, %esi
	movl	%esi, %eax
	orl	%eax, -160(%rbp)
.L32:
	movzbl	-178(%rbp), %eax
	cmpb	$1, %al
	jne	.L33
	orl	$268435456, -160(%rbp)
.L33:
	movzbl	-178(%rbp), %eax
	cmpb	$2, %al
	jne	.L34
	orl	$536870912, -160(%rbp)
.L34:
	movq	-192(%rbp), %rax
	movl	-160(%rbp), %edx
	movl	%edx, (%rax)
	movl	$0, %eax
.L35:
	movq	-8(%rbp), %rdi
	xorq	%fs:40, %rdi
	je	.L36
	call	__stack_chk_fail@PLT
.L36:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	set_display_from_temp, .-set_display_from_temp
	.ident	"GCC: (Ubuntu 9.4.0-1ubuntu1~20.04) 9.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
