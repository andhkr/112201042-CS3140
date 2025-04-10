	.file	1 "a.c"
	.section .mdebug.abi32
	.previous
	.nan	legacy
	.module	fp=32
	.module	nooddspreg
	.abicalls
	.text
	.globl arr
	.section .bss,"aw",@nobits
	.align 2
	.type arr, @object
	.size arr, 40
arr:
	.space 40
	.globl key
	.align 2
	.type key, @object
	.size key, 4
key:
	.space 4
	.globl i
	.align 2
	.type i, @object
	.size i, 4
i:
	.space 4
	.globl l
	.align 2
	.type l, @object
	.size l, 4
l:
	.space 4
	.globl r
	.align 2
	.type r, @object
	.size r, 4
r:
	.space 4
	.globl mid
	.align 2
	.type mid, @object
	.size mid, 4
mid:
	.space 4
	.globl result
	.align 2
	.type result, @object
	.size result, 4
result:
	.space 4
	.globl a
	.align 2
	.type a, @object
	.size a, 4
a:
	.space 4
	.globl b
	.align 2
	.type b, @object
	.size b, 4
b:
	.space 4
	.globl c
	.align 2
	.type c, @object
	.size c, 4
c:
	.space 4
	.globl barr
	.align 0
	.type barr, @object
	.size barr, 10
barr:
	.space 10
	.globl final
	.align 0
	.type final, @object
	.size final, 1
final:
	.space 1
	.text
	.align 2
	.globl	main
	.set	nomips16
	.set	nomicromips
	.ent	main
	.type	main, @function
main:
	.frame	$fp,32,$31
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	reorder
	addiu	$sp,$sp,-32
	sw	$31,28($sp)
	sw	$fp,24($sp)
	move	$fp,$sp
	.cprestore	16
	add $8,$0,0
	addiu $fp, $fp, -4
	sw $8, 4($fp)
	la $8, l
	lw $9, 4($fp)
	addiu $fp, $fp, 4
	sw $9, 0($8)
	add $8,$0,9
	addiu $fp, $fp, -4
	sw $8, 4($fp)
	la $8, r
	lw $9, 4($fp)
	addiu $fp, $fp, 4
	sw $9, 0($8)
	add $8,$0,5
	addiu $fp, $fp, -4
	sw $8, 4($fp)
	lw $10,4($fp)
	addiu $fp, $fp, 4
	mul $10, $10, 4
	la $8, arr
	addu $8, $8, $10
	lw $8, 0($8)
	addiu $fp, $fp, -4
	sw $8, 4($fp)
	la $8, key
	lw $9, 4($fp)
	addiu $fp, $fp, 4
	sw $9, 0($8)
	add $8,$0,false
	addiu $fp, $fp, -4
	sw $8, 4($fp)
	la $8, final
	lw $9, 4($fp)
	addiu $fp, $fp, 4
	sw $9, 0($8)
	add $8,$0,10
	addiu $fp, $fp, -4
	sw $8, 4($fp)
	la $8, a
	lw $9, 4($fp)
	addiu $fp, $fp, 4
	sw $9, 0($8)
	add $8,$0,20
	addiu $fp, $fp, -4
	sw $8, 4($fp)
	la $8, b
	lw $9, 4($fp)
	addiu $fp, $fp, 4
	sw $9, 0($8)
	la $5,result
	lw $4, 0($5)
	move $5, $4
	la $4, $LC0
	jal printf
	move	$2,$0
	move	$sp,$fp
	lw	$31,28($sp)
	lw	$fp,24($sp)
	addiu	$sp,$sp,32
	j	$31
	.end	main
	.size	main, .-main
	.space	4
	.rdata
	.align	2
$LC0:
	.ascii  "%d \012\000"
	.align 2
	.ident	"GCC: (Ubuntu 10.3.0-1ubuntu1) 10.3.0"
	.section	.note.GNU-stack,"",@progbits
