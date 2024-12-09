.data

A:	.float	0:262144	#A[512][512]
B:	.float	0:262144	#B[512][512]
C:	.float	0:262144	#C[512][512]

lin:	.word	512
col:	.word	512

valor1: .float 	1.0

enter:  .asciiz 	"\n"
cabo:	.asciiz		"ACABOOOOOOOOOOOO"


.text
.globl main

main:	
	lw	$t0, lin
	lw	$t1, col
			
	jal rmo

	#jal mulmat_ijk
	
	jal mulmat_ikj
	
	li $v0, 4
	la $a0, cabo
	syscall
	
	li $v0, 10
	syscall
	
rmo:	move	$s0, $zero	# i
	move	$s1, $zero	# j
	li	$t2, 1		# $t2 = carrega const 1
	l.s	$f1, valor1	# $f1 = constF 1.0
	add.s	$f0, $f0, $f1	# $f0 = valor
	
loop:	mul	$s2, $s0, $t1 	# $s2 = i * cols
	add	$s2, $s2, $s1	# $s2 += j
	sll	$s2, $s2, 2	# $s2 *= 4 
	s.s	$f0, A($s2)	# A[i][j] = valor
	s.s	$f0, B($s2)	# B[i][j] = valor
	add.s	$f0, $f0, $f1	# valor++
	
	addi	$s1, $s1, 1	# j++
	bne	$s1, $t1, loop	# if(j < cols)		
	move	$s1, $zero	# j = 0
	addi	$s0, $s0, 1	# i++
	bne	$s0, $t0, loop	# if(i < lins)
	
	jr $ra
	
	
mulmat_ijk:	
	move	$s0, $zero	# i

for1:	bge	$s0, $t1, fim
	move	$s1, $zero	# j
	
for2:	bge	$s1, $t1, incI
	move	$s2, $zero	# k
	li	$t3, 0		# carrega const 0
	mtc1	$t3, $f6	# $f6 = 0 (sum = 0)
	
for3:	bge	$s2, $t1, c

	mul	$s3, $s0, $t1	# offset A[i][k]
	add	$s3, $s3, $s2
	sll	$s3, $s3, 2

	mul	$s4, $s2, $t1	# offset B[k][j]
	add	$s4, $s4, $s1
	sll	$s4, $s4, 2
	
	l.s	$f3, A($s3)
	l.s	$f4, B($s4)
		
	mul.s	$f5, $f3, $f4
	
	add.s	$f6, $f6, $f5
	
	addi	$s2, $s2, 1
	blt	$s2, $t0, for3
	
c:	mul	$s5, $s0, $t1	# offset C[i][j]
	add	$s5, $s5, $s1
	sll	$s5, $s5, 2
	s.s	$f6, C($s5) 	#C[i][j] = sum

	
incJ:	addi 	$s1, $s1, 1
	j	for2
	
incI:	addi 	$s0, $s0, 1
	j	for1
	
fim:	jr $ra




mulmat_ikj:	
	move	$s0, $zero	# i

for1_2:	bge	$s0, $t1, fim_2
	move	$s2, $zero	# k
	
for2_2:	bge	$s2, $t1, incI_2
	move	$s1, $zero	# j
	li	$t3, 0		# carrega const 0
	mtc1	$t3, $f6	# $f6 = 0 (sum = 0)
	
for3_2:	bge	$s1, $t1, c_2

	mul	$s3, $s0, $t1	# offset A[i][k]
	add	$s3, $s3, $s2
	sll	$s3, $s3, 2

	mul	$s4, $s2, $t1	# offset B[k][j]
	add	$s4, $s4, $s1
	sll	$s4, $s4, 2
	
	l.s	$f3, A($s3)
	l.s	$f4, B($s4)
		
	mul.s	$f5, $f3, $f4
	
	add.s	$f6, $f6, $f5
	
	addi	$s1, $s1, 1
	blt	$s1, $t0, for3_2
	
c_2:	mul	$s5, $s0, $t1	# offset C[i][j]
	add	$s5, $s5, $s1
	sll	$s5, $s5, 2
	s.s	$f6, C($s5) 	#C[i][j] = sum

	
incK_2:	addi 	$s2, $s2, 1
	j	for2_2
	
incI_2:	addi 	$s0, $s0, 1
	j	for1_2
	
fim_2:	jr $ra
	
	
