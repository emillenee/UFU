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
	li	$t6, 4  	# const 4
	move	$t7, $t3	# aramzena a pot de X
	li	$t9, 0		# soma da função 
		
Coefs:beq	$t0, $t1, Trad	
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
  	
				# inicia $t9 com o valor sem X
Trad:	mul	$t5, $t0, $t6	# amazena a posição de memoria a ser pega de poly
	lw   	$t4, poly($t5)	# $t4 amazena o coeficiente atual
	add	$t9, $t9, $t4
	addi 	$t0, $t0, -1	
	
loop:	blt 	$t0, $zero, FIM	
	mul	$t5, $t0, $t6  	
	lw   	$t4, poly($t5) 	
	mul	$t8, $t4, $t7 	# $t8 = termo_atual * pot_X
	add     $t9, $t9, $t8	#atualisa o valor da soma
	mul	$t7, $t7, $t3	# atualiza a potencia de X
	addi 	$t0, $t0, -1	#decrementa o $t0
	j 	loop

FIM:	li 	$v0, 4 
	la 	$a0, saida 
	syscall

	li 	$v0, 1
	move 	$a0, $t9
	syscall
	

                  
                                             
                  
                  
                  
                             
                  
                  
                  
                 
