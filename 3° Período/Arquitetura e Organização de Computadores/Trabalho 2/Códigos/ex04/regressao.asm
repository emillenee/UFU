	.data
entrada:	.asciiz 	"Entre com a quantidade de pontos: "
vetorX: 	.word 0:21
vetorY: 	.word 0:21	
saidaA:		.asciiz		"O resultado de A eh: "
saidaB:		.asciiz		"O resultado de B eh: "

  .text
  .globl main
main:	
	li 	$v0, 4 
	la 	$a0, entrada 
	syscall
	
	li	$v0, 5	 
	syscall
	move 	$t0, $v0	# valor n

	li 	$t1, 0 		# contador 
	li	$t2, 0  	# posição atual no vetor
	
Vetores: beq	$t0, $t1, retornos	
	li	$v0, 42 	# chamada sistema print_str
	li 	$a1, 11
	syscall
	#li 	$a0, 5
	sw	$a0, vetorX($t2)# armazenar valor no vetor

	li	$v0, 42 	# chamada sistema print_str
	li	$a1, 11
	syscall
	
	sw	$a0, vetorY($t2)# armazenar valor no vetor
	
	addi	$t2, $t2, 4
	addi	$t1, $t1, 1
	
	j Vetores
	
retornos: 
	la $a0, ($t0)	# n
	la $a1, vetorX
	la $a2, vetorY
	
	jal regressao_linear
	
	li 	$v0, 4 
	la 	$a0,  saidaA
	syscall
	li 	$v0, 2
	add.s 	$f12, $f12, $f3
	syscall
	
	li 	$v0, 4 
	la 	$a0,  saidaB
	syscall
	
	li 	$v0, 2 
	add.s 	$f12, $f12, $f9
	syscall
	
	li	$v0, 10
	syscall
	
regressao_linear:
	add 	$a3, $a3, $ra 	# frame = 12 bytes
	#sw 	$ra, 0($sp) 	# save $ra
	li 	$t6, 0 		# contador 
	li	$t7, 0  	# posição atual no vetor
	
 
	
Loop:  	beq	$a0, $t6, AeB
	
	lw 	$t8, vetorX($t7)
	lw 	$t9, vetorY($t7)
	
	add  	$t4, $t4, $t8 	# $t4 é o Sx 
	add	$t5, $t5, $t9	# $t5 é o Sy
	
	mul 	$t1, $t8, $t8
	add     $t2, $t2, $t1	# $t2 é o Sxx
	
	mul 	$t1, $t8, $t9
	add     $t3, $t3, $t1	# $t3 é o Sxy

	addi	$t7, $t7, 4
	addi	$t6, $t6, 1
	
	j Loop
AeB:
	mul	$t6, $a0, $t3	# nSxy
	mul	$t7, $t4, $t5 	# Sx * Sy
	mul	$t8, $a0, $t2 	# nSxx
	mul	$t9, $t4, $t4 	# Sx * Sx
	
	sub 	$t6, $t6, $t7 	# nSxy - Sx*Sy
	sub 	$t8, $t8, $t9	# nSxx - Sx*Sx
	
	mtc1	$t4, $f4	# Sx pra float
	mtc1	$t5, $f6	# Sy para float
	
	mtc1	$t6, $f1	
	mtc1	$t8, $f2
	mtc1	$a0, $f8
	
	div.s	$f3, $f1, $f2 	# A
	
	mul.s	$f5, $f4, $f3	# A*Sx
	sub.s	$f7, $f6, $f5
	div.s	$f9, $f7, $f8   # B
	 
	#lw $ra, 0($sp) 		# restore $ra
	#addiu $sp, $sp, 4 	# free stack frame
	move 	$ra, $a3
	jr 	$ra
	
