  .data
poly: 		.word 0:11 	# vetor de numeros com 10 espaços
qntN: 		.asciiz 	"Entre com o grau do polinomio (max 10): "
entrada:	.asciiz 	"Entre com um coeficiente: "
entradaX: 	.asciiz 	"Entre com o valor de X: "
saida:		.asciiz		"O resultado eh: "

  .text
  .globl main
main:	
	li 	$v0, 4 
	la 	$a0, entradaX 
	syscall
	
	li	$v0, 5	 
	syscall
	move 	$t3, $v0	 # valor X

	li 	$v0, 4 
	la 	$a0, qntN 
	syscall
	
	li	$v0, 5	 
	syscall
	move 	$t0, $v0 	# n, grau do polinomio
	
	li 	$t1, -1 	# contador 
	li	$t2, 0  	# posição atual no vetor

		
Coefs:	beq	$t0, $t1, Horner	
	li	$v0, 4 		# chamada sistema print_str
	la	$a0, entrada 	# endereço da string a imprimir
	syscall
	
				# obter o inteiro do usuario
	li	$v0, 5		# chamada sistema read_int
	syscall			# coloca o inteiro em $v0
		
				# armazenar valor no vetor
	sw	$v0, poly($t2)
	addi	$t2, $t2, 4
	addi	$t1, $t1, 1
	j Coefs

Horner:	xor	$t2, $t2, $t2 	# $t2 é a posição no vetor poly
	xor 	$t4, $t4, $t4 	# $t4 é o contador de iterações
	li	$t6, 0		# soma da função 
	lw  	$t7, poly($t2)	# carrega valor de poly[0]
	add	$t6, $t6, $t7	# soma_total = poly[0]
	
loop:	beq	$t4, $t0, FIM	# if pot_atual > pot_da_função goto FIM
	mul	$t6, $t6, $t3 	# a soma_total *= X
	addi	$t2, $t2, 4	# atualiza posicao de poly
	lw  	$t7, poly($t2)	# $t7 recebe o valor da proxima posição de poly
	add	$t6, $t6, $t7
	add	$t4, $t4, 1
	j	loop
	 

FIM:	li 	$v0, 4 
	la 	$a0, saida 
	syscall
	
	li 	$v0, 1
	move 	$a0, $t6
	syscall