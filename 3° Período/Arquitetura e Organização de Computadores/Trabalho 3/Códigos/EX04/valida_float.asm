.data
str1: 	.asciiz 				"Digite o float \n\n"
afirmat: .asciiz 				"� um float valido"
falso: 	.asciiz 				"N�o � um float valido"
barraN:	.asciiz	 			"\n"
str:	.space 100			# vetor pra str lida
#str:	.asciiz 				"ty12.12\n"

	.text
	.globl main
main:	
	la	$a0, str1		#instru��o inicial
	jal 	print_string
	
	li 	$a1, 0
	la	$a0, str
	jal 	getstr
	
	li	$a1, 0			# posi��o de leitura atual
	#li	$a2, 0			# estado do automato
	jal 	floatValidate
	
	addi	$a0, $v0, 0
	li	$v0, 1
	syscall
	
	li	$v0, 10
	syscall
	
	
floatValidate:
	lb	$a0, str($a1)

estado0:
	jal 	sinal			# retorna 1 para afirmativo e 0 para falso
	beq	$v0, 0, estado2
	
	addi 	$a1, $a1, 1
	lb	$a0, str($a1)
	
estado2:
	jal	isDigit
	beq	$a0, 46, estado3		# se a leitura for de um .
	addi 	$a1, $a1, 1
	lb	$a0, str($a1)
	beq	$v0, 1, estado2		# se a leitura for de digitos
	j 	fim

estado3:
	addi 	$a1, $a1, 1		# pega o proximo char
	lb	$a0, str($a1)
	beq	$a0, 10, fim
	jal	isDigit
	beq	$v0, 1, estado3		# se for digito loopa
	beq	$a0, 101, estado5		# se a leitura for de um 'e'
	beq	$a0, 69, estado5		# se a leitura for de um 'E'
	j 	fim

estado5: 
	addi 	$a1, $a1, 1		# pega o proximo char
	lb	$a0, str($a1)
	jal 	sinal
	beq	$v0, 0, estado7		# se n�o for sinal -> estado 7
	addi 	$a1, $a1, 1
	lb	$a0, str($a1)
	
estado7:
	beq	$a0, 10, fim
	jal	isDigit	
	addi 	$a1, $a1, 1
	lb	$a0, str($a1)
	beq	$v0, 1, estado7		# se a leitura for de digitos
	
	
fim:
	beq	$v0, 0, falsof 
	
	la	$a0, afirmat
	jal 	print_string
	
	li	$v0, 10
	syscall	
	
falsof:
	la	$a0, falso
	jal	print_string
	
	li	$v0, 10
	syscall	
	

sinal:	
	beq	$a0, 43, isSinal		# - na ASCII
	beq	$a0, 45, isSinal		# + na ASCII
	li 	$v0, 0
	jr 	$ra
	
isSinal: 
	li 	$v0, 1
	jr 	$ra
	
isDigit:
	blt	$a0, 48, notDigit		# 0 na ASCII
	bgt	$a0, 57, notDigit		# 9 na ASCII
	li	$v0, 1
	jr	$ra
	
notDigit:
	li	$v0, 0			# n�o � digito -> v0 = 1
	jr	$ra


getstr:
	lw 	$v0, 0xffff0000		# coleta char por char
	andi 	$v0, $v0, 0x01  		# 0x01 => 0001 0x03 => 0011
	beq 	$v0, $zero, getstr
	lw 	$v0, 0xffff0004
	
	sb	$v0, str($a1)		# guarda o char lido no vetor de caracteres
	addi	$a1, $a1, 1
	bne	$v0, 10, getstr		# enquanto n�o \n continua lendo
	lb	$v0, str($zero)
	jr	$ra
	
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
