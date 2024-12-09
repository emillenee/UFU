 .data
vetor: 		.word	23,54,6,34,22,78,1,99 	
print1:		.asciiz 	"Vetor desordenado: "
virgula:	.asciiz 	", "
print2:		.asciiz 	"\nVetor ordenado: "

	
 .text
 .globl main
main:	li	$v0, 4
	la	$a0, print1
	syscall
	jal 	print
	
	la	$a0, vetor 	# vetor
	la	$a1, 0		# low
	la	$a2, 7		# high
	la	$a3, 0		# armazena $ra
	jal 	quicksort
	
	li	$v0, 4
	la	$a0, print2
	syscall

	jal 	print
	
	
	# Finaliza
	li	$v0, 10
	syscall
	
quicksort:
	addi	$sp, $sp, -12 	#guardamo na stack
	sw 	$ra, 0($sp) 
	sw	$a1, 4($sp)
	sw 	$a2, 8($sp)
	  
	move	$t0, $a1		# low $a1, i $t0 	$t0(i) = $a1(low)
	move	$t1, $a2		# high $a2,  j $t1	$t1(j) = $a2(high)
	
	add 	$t2, $a1, $a2	# $t2 = low + high
	div	$t9, $t2, 2	# pivot_index
	mul	$t9, $t9, 4	# posições em vetor de inteiro são multiplas de 4
	lw	$t2, vetor($t9)	# pivot
		
while1:	bgt	$t0, $t1, fim_qcksort
	j loop_w2
	
while2:	 addi	$t0, $t0, 1		# i++
loop_w2: mul	$t5, $t0, 4
	 lw	$t3, vetor($t5)		# $t3 recebe temporariamente o valor de vetor[i]
	 blt	$t3, $t2, while2	# enquanto vetot[i] < pivot repita 
	 j loop_w3
	
while3:	 addi	$t1, $t1, -1		# j--
loop_w3: mul	$t5, $t1, 4
	 lw	$t3, vetor($t5)		# $t3 recebe temporariamente o valor de vetor[j]
	 bgt	$t3, $t2, while3  	# enquanto vetot[j] > pivot repita while3 
	
swap:	bgt	$t0, $t1, fim_qcksort  	# if i > j volta pro while // i <= j faz o de baixo
	
	mul    $t5, $t0, 4
    	lw    $t3, vetor($t5)   # $t3 = vetor[i]
    	
    	mul    $t6, $t1, 4
    	lw    $t4, vetor($t6)   # $t4 = vetor[j]
  
    	sw    $t4, vetor($t5)   # vetor[i] = vetor[j]
	sw    $t3, vetor($t6)   # vetor[j] = temp
	
    	addi    $t0, $t0, 1    	# i++
    	addi    $t1, $t1,-1	# j--
    	
    	j while1

fim_qcksort:	bge	$a1, $t1, if2
		move 	$a2, $t1
		jal	quicksort

if2:		bge	$t0, $a2, retorna
		move	$a1, $t0
		jal	quicksort
	
retorna:		lw	$ra, 0($sp)
		lw	$a1, 4($sp)
		lw	$a2, 8($sp) 
		addi 	$sp, $sp, 12
		jr	$ra

	
print:	li	$t0, 7
	li 	$t1, 0		# contador
	li	$t2, 0
	move	$t3, $ra
loop:	lw	$t4, vetor($t2)
	li	$v0, 1
	la	$a0, ($t4)
	syscall
	li	$v0, 4
	la	$a0, virgula
	syscall
	add	$t2, $t2, 4
	add	$t1, $t1, 1
	ble     	$t1, $t0, loop
	
	lw	$t4, vetor($t2)
	li	$v0, 1
	la	$a0, ($t4)
	syscall
	
	move 	$ra, $t3
	jr 	$ra
