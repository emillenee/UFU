 .data
 digite: .asciiz "Digite um valor para n: "
 resultado_simples: .asciiz "O valor da serie harmonica (precisao simples) eh: "
 resultado_dupla: .asciiz "\nO valor da serie harmonica (precisao dupla) eh: "
 
 .text
 .globl main

main: 
	#Imprime mensagem
	li $v0, 4
	la $a0, digite
	syscall
	
	#Ler inteiro
	li $v0, 5
	syscall
	move $t0, $v0 #Move o valor de n lido para o registrador t0
	
	#Calcular a serie (simples)
	li $t1, 1  #i = 1
	li $t2, 0  #soma = 0
	mtc1 $t2, $f0
	mtc1 $t1, $f2
	cvt.s.w $f2, $f2
	
loop_simples: 
	bge  $t1, $t0, endloop_simples #Se i == n, vai para o fim do loop
	mtc1 $t1, $f4
	cvt.s.w $f4, $f4 # converte de word para precisao simples
	div.s $f6, $f2, $f4 #f6 = 1.0/i
	add.s $f0, $f0, $f6 #soma += 1/i
	addi $t1, $t1, 1 # i++
	j loop_simples #Volta para o começo do loop

endloop_simples:
	#Imprime resultado
	li $v0, 4
	la $a0, resultado_simples
	syscall
	
	#Imprime valor da soma
	mov.s $f12, $f0 #Move para o registrador esperado
	li $v0, 2 #Syscall para float
	syscall
	
	#Calcular a serie (dupla)
	li $t1, 1  #i = 1
	li $t2, 0  #soma = 0
	mtc1 $t2, $f0
	cvt.d.w $f0, $f0
	mtc1 $t1, $f2
	cvt.d.w $f2, $f2
	
loop_dupla:
	bge $t1, $t0, endloop_dupla
	mtc1 $t1, $f4
	cvt.d.w $f4, $f4 #Converte i para PF duplo
	div.d $f6, $f2, $f4
	add.d $f0, $f0, $f6
	addi $t1, $t1, 1
	j loop_dupla

endloop_dupla:
	#Imprime resultado (dupla)
	li $v0, 4
	la $a0, resultado_dupla
	syscall
	
	mov.d $f12, $f0
	li $v0, 3 #Syscall para double
	syscall
	
	#Termina o programa
	li $v0, 10
	syscall
