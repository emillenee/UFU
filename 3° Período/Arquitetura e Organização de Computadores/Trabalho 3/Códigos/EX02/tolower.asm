	.data
str1: 	.asciiz 				"Digite uma frase: "
barraN:	.asciiz	 			"\n"
str:	.space 100			# vetor pra str lida

	.text
	.globl main
	
main:	
	la	$a0, str1		# printa menuzinho S2
	jal	print_string	

	li	$a1, 0
	jal	getstr			# pega a string

	li	$a1, 0			# posi��o de leitura do vetor
	jal	tolower			# chama a tolower
	la	$a0, str
	jal	print_string
	
	li 	$v0, 10			# fim
	syscall

getstr:
	lw 	$v0, 0xffff0000		# coleta char por char
	andi 	$v0, $v0, 0x01  		# 1
	beq 	$v0, $zero, getstr
	lw 	$v0, 0xffff0004
	
	sb	$v0, str($a1)		# guarda o char lido no vetor de caracteres
	addi	$a1, $a1, 1
	bne	$v0, 10, getstr		# enquanto n�o \n continua lendo
	lb	$v0, str($zero)
	jr	$ra
	
tolower:
	lb	$t0, str($a1)
	beq 	$t0, 10, return
	blt	$t0, 'A', itera
	bgt	$t0, 'Z', itera
	
	addi 	$t0, $t0, 32
	sb	$t0, str($a1)
	
itera:	addi	$a1, $a1, 1
	j 	tolower
	
return: 
	jr $ra
	 
	
print_string: 	# $a0: string
	li 	$a1, 0xffff0000
	j 	ps_cond
ps_loop:
	lw 	$v0, 8($a1)
	andi 	$v0, $v0, 0x01
	beq 	$v0, $zero, ps_loop
	sw 	$t0, 12($a1)
ps_cond:
	lbu 	$t0, ($a0)
	addi 	$a0, $a0, 1
	bne 	$t0, $zero, ps_loop
	jr 	$ra

 	
	