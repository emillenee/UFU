.data
str: 		.space 		100
antes:		.asciiz		"Digite a string a ser convertida\n"
strfinal:	.asciiz		"String convertida com sucesso"
menos1:		.asciiz		"Valor em v0 é -1"

.text
.globl main

main:
    la 	$a0, antes
    jal	print_string	# Imprime "Digite a string a ser convertida: "
    li 	$a1, 0
    
    jal	getstr
    la 	$a0, str
    
    jal	atoi            # Chama a função
    
    beq 	$v0, -1, erro
    la	$a0, strfinal
    jal 	print_string
    #move $t7, $v0       # Armazena o resultado em $t0

      
    li $v0, 10		# Finaliza o programa
    syscall
    
erro:
    la	$a0, menos1
    jal 	print_string
    
    li $v0, 10		# Finaliza o programa
    syscall
	

atoi:
    li $v0, 0             
    li $t0, 10           
    
    atoi_loop:
        lb $t1, 0($a0)    		
        beq $t1, 10, return  		# Se byte for null finaliza
        blt $t1, '0', atoi_erro  	# Se byte < '0' erro
        bgt $t1, '9', atoi_erro  	# Se byte > '9' erro

        sub $t1, $t1, '0'      		# Converte para numero

        mul $v0, $v0, $t0   		# Anda uma casa, multiplica por 10
        add $v0, $v0, $t1   		# Adiciona valor atual

        addi $a0, $a0, 1
        j atoi_loop

    return:
        jr $ra

    atoi_erro:
        li $v0, -1        # Retorna -1 se erro
        jr $ra
        

getstr:
	lw 	$v0, 0xffff0000		# coleta char por char
	andi 	$v0, $v0, 0x01  		# 1
	beq 	$v0, $zero, getstr
	lw 	$v0, 0xffff0004
	
	sb	$v0, str($a1)		# guarda o char lido no vetor de caracteres
	addi	$a1, $a1, 1
	bne	$v0, 10, getstr		# enquanto não \n continua lendo
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


