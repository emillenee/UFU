	.data
str1: 	.asciiz 				"O char digitado eh digito"
str2: 	.asciiz 				"O char digitado nao eh digito"
barraN:	.asciiz	 			"\n"

	.text
	.globl main
main:
	addi 	$a0, $zero, 0		# zerando
	addi 	$v0, $zero, 0
	jal	getchar
	add	$a0, $a0, $v0
	jal 	isDigit
	la	$a0, str1		# carregamos str1
	beq	$v0, 1, setStr2		# se n�o for digito subescrevemos $a0

retorno:	jal	print_string 		# passsa a string em $a0				
	la 	$a0, barraN
	jal 	print_string
	j 	main
	
setStr2:
	la	$a0, str2
	j	retorno


getchar: # out --> $v0: char
	lw 	$v0, 0xffff0000
	andi 	$v0, $v0, 0x01		# pega o bit mais a esquerda 0001, se quisesse pegar o seg. 
					# bit teriamos a conf 0010 que � 0x02, se quisessemos o quarto e
					# o primeiro apenas teriamos 1001 que � 0x05
	beq 	$v0, $zero, getchar
	lw 	$v0, 0xffff0004
	jr 	$ra

isDigit:
	blt	$a0, 48, notDigit		# 0 na ASCII
	bgt	$a0, 57, notDigit		# 9 na ASCII
	li	$v0, 0
	jr	$ra
	
notDigit:
	li	$v0, 1			# n�o � digito -> v0 = 1
	jr	$ra			# retornar para main
	

putchar: 				# in  --> $a0: char
	li 	$a1, 0xffff0008
	lw 	$v0, 0($a1)
	andi 	$v0, $v0, 0x01
	beq 	$v0, $zero, putchar
	sw 	$a0, 4($a1)
	jr 	$ra


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
