 .data
 entrada:	.asciiz "Em e^x digite o valor de x: "
 saida:		.asciiz "O resultado eh: "
 epsilon:	.float 0.00001 
 valor1:        .float 1.0    

 .text
 .globl main

main: 	#imprime mensagem
	li $v0, 4 #impressão de string
	la $a0, entrada #conteúdo a ser impresso
	syscall
	
	li $v0, 6 # lê um inteiro
	syscall
	add.s $f2, $f2, $f0 # $f2 armazena X 
	
	l.s $f3, epsilon # carrega epsilon
	l.s $f7, valor1  # constante 1
	l.s $f1, valor1  # somatorio
	l.s $f9, valor1  # valor do fatorial  
	l.s $f6, valor1  # contador 
	
	add.s $f5, $f5, $f2 # guarda o valor de X em $f5
	
loop:	div.s $f4, $f2, $f9 # $f4 = pot / fat
	c.lt.s 4 $f4, $f3   # 0 se $f4 > $f3 ( prox. termo > 0.00001) 
	add.s $f1, $f1, $f4 # adicona o termo no somatório
	mul.s $f2, $f2, $f5 # pot anterior * X
	add.s $f6, $f6, $f7 # acha sucessor do fat. anterior
	mul.s $f9, $f9, $f6 # fat anterior * seu sucessor = fat. atual
	bc1f 4 loop         # se flag 4 = 0 volta pro loop
	
	li $v0, 4 #impressão de string
	la $a0, saida #conteúdo a ser impresso
	syscall
	
	li $v0, 2  #impressão de float
	add.s $f12, $f12, $f1  #conteúdo a ser impresso
	syscall
