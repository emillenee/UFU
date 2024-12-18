.data
retang1: 	.space		30
retang2:		.space		30
temp:		.space		10
vec:		.word 		0,0,0,0,0,0,0,0 # para guardar as coordenadas
entrada:		.asciiz		"Entre com os retangulos\n" 
espaco:		.asciiz		" "
intersecao:	.asciiz		"Retangulo interse��o: "
sem_intersecao:   .asciiz		"Retangulos n�o se iterceptam"
.text
.globl main

main:
	la 	$a0, entrada
	jal	print_string
	
	la 	$a0, retang1
	jal	getstr		# pega primeiro ret�ngulo
	

	li	$a1, 0
	la 	$a0, retang2
	jal	getstr		# pega segundo ret�ngulo
	
			
	la 	$a2, retang1	# coordenadas separadas por espa�os
	li	$a3, 0		# ponto do vec sendo lido
	jal	getcoords
	
	
	la 	$a2, retang2	# coordenadas separadas por espa�os
	
	jal	getcoords
    	
	jal	check_intersection

		
	
getcoords: # exemplo 1 2 3 4
	move	$s0, $ra
loop:	lb    	$t0, 0($a2)	# carrega primeiro bit desse endere�o do vetor
    	beq    	$t0, 0, sair	# acabou a leitura do retangulo
    	la	$a0, 0($a2)	# endere�o de uma coordenada
    	jal	atoi
    	sw    	$v0, vec($a3)	# aramzena o retorno de atoi
    	addi	$a3, $a3, 4	# passa pra prox posi��o
    	addi	$a2, $a2, 1

    	j    	loop
    	
sair: 
	move	$ra, $s0
	jr 	$ra 
    	
atoi:# usa a0
    li $v0, 0             
    li $t0, 10           
    
atoi_loop:
        lb 	$t1, 0($a0)    		
        blt	$t1, '0', return  	# Se byte < '0' erro
        bgt 	$t1, '9', return  	# Se byte > '9' erro

        sub 	$t1, $t1, '0'      	# Converte para numero

        mul 	$v0, $v0, $t0   		# Anda uma casa, multiplica por 10
        add 	$v0, $v0, $t1   		# Adiciona valor atual

        addi 	$a0, $a0, 1
        addi	$a2, $a2, 1
        j 	atoi_loop

return:
        jr $ra

	
min:
	blt 	$a1, $a0, a1menor
	move	$v0, $a0
	jr 	$ra
	
a1menor:
	move	$v0, $a1
	jr 	$ra
	
max:
	bgt 	$a1, $a0, a1maior
	addi	$v0, $a0, 0
	jr 	$ra
	
a1maior:
	addi	$v0, $a1, 0
	jr 	$ra
	
check_intersection:
    
    # Carrega coordenadas dos limites do ret�ngulo 1
    la		$a0, vec 
    lw 		$t0, 0($a0)		#x0
    lw 		$t1, 4($a0)		#y0
    lw 		$t2, 8($a0)		#x1
    lw 		$t3, 12($a0)		#y1
    
    # Calcula x_min1, x_max1, y_min1, y_max1
    move		$a0, $t0
    move		$a1, $t2
    jal		min	    		# x_min1
    move		$t4, $v0
    
    move		$a0, $t0
    move		$a1, $t2
    jal		max	    		# x_max1
    move		$t5, $v0
    
    move		$a0, $t1
    move		$a1, $t3
    jal		min	    		# y_min1
    move		$t6 $v0
    
    move		$a0, $t1
    move		$a1, $t3
    jal		max	    		# y_max1
    move		$t7, $v0
    
    # Carrega coordenadas dos limites do ret�ngulo 2
    la		$a0, vec 	
    lw 		$t0, 16($a0) 		#x2
    lw 		$t1, 20($a0)		#y2
    lw 		$t2, 24($a0)		#x3
    lw 		$t3, 28($a0)		#y3
    
    # Calcula x_min2, x_max2, y_min2, y_max2
    addi		$a0, $t0, 0
    addi		$a1, $t2, 0
    jal		min	    		# x_min2
    addi		$t8, $v0, 0
    
    addi		$a0, $t0, 0
    addi		$a1, $t2, 0
    jal		max	    		# x_max2
    addi		$t9, $v0, 0
    
    addi		$a0, $t1, 0
    addi		$a1, $t3, 0
    jal		min	    		# y_min2
    addi		$s0 $v0,  0		# vulgo $t10
    		
    addi		$a0, $t1, 0
    addi		$a1, $t3, 0
    jal		max	    		# y_max2
    addi		$s1 $v0,  0		# vulgo $t11
    
    					# Verifica se h� interse��o nos eixos x e y
    					# Testa a condi��o de interse��o em x
    ble 		$t4, $t9, x_intersecao1  	# Se x_min1 <= x_max2, possivelmente interse��o
    j 		no_intersection           	# Caso contr�rio, sem interse��o
    
x_intersecao1:
    bge 		$t5, $t8, y_intersecao1  	# Se x_max1 >= x_min2, possivelmente interse��o
    j 		no_intersection           	# Caso contr�rio, sem interse��o
					
y_intersecao1:				# Testa a condi��o de interse��o em y
    ble 		$t6, $s1, y_intersecao2 	# Se y_min1 <= y_max2, possivelmente interse��o
    j 		no_intersection           	# Caso contr�rio, sem interse��o

y_intersecao2:
    bge 		$t7, $s0, calc_intersecao  # Se y_max1 >= y_min2, interse��o confirmada
    j 		no_intersection           	# Caso contr�rio, sem interse��o
    
calc_intersecao:
					# Calcula o ret�ngulo de interse��o:
    addi		$a0, $t4, 0
    addi		$a1, $t8, 0
    jal 		max    			# x_inter_min = max(x_min1, x_min2)
    addi		$s2, $v0, 0

    addi		$a0, $t5, 0
    addi		$a1, $t9, 0
    jal 		min    			# x_inter_max = min(x_max1, x_max2)
    addi		$s3, $v0, 0
    
    addi		$a0, $t6, 0
    addi		$a1, $s0, 0
    jal 		max    			# y_inter_min = max(y_min1, y_min2)
    addi		$s4, $v0, 0
    
    addi		$a0, $t7, 0
    addi		$a1, $s1, 0
    jal 		min    			# y_inter_max = min(y_max1, y_max2)
    addi		$s5, $v0, 0
    
    # Imprime o ret�ngulo de interse��o
    la 		$a0, intersecao
    jal 		print_string 
    
    move		$a0, $s2
    jal		print_number
    
    move		$a0, $s5
    jal		print_number
    
    move		$a0, $s3
    jal		print_number
    
    move		$a0, $s4
    jal		print_number
    
    j 		end_program
    
no_intersection:
    la 	$a0, sem_intersecao
    jal	print_string
    
end_program:    
    li 		$v0, 10   		# syscall para finalizar o programa
    syscall
   

getstr:
	lw 	$v0, 0xffff0000		# coleta char por char
	andi 	$v0, $v0, 0x01  		# paga o primeiro bit 
	beq 	$v0, $zero, getstr
	lw 	$v0, 0xffff0004
	
	sb	$v0, 0($a0)		# guarda o char lido no vetor de caracteres
	addi	$a0, $a0, 1
	bne	$v0, 10, getstr		# enquanto n�o '\n' continua lendo
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
	

print_number: # numero em $a0
    li      $a1, 0xffff0000       		# Endere�o base do MMIO (status)
pn_cond:
    lw      $v0, 8($a1)           		# Carrega o status da tela na controladora 
    andi    $v0, $v0, 0x01        		# dispon�vel para escrita?
    beq     $v0, $zero, pn_cond   		# Se n�o estiver liberado, loopa at� liberar

    li      $a1, 0xffff000c 
    add	   $a0, $a0, '0'      
    sw      $a0, 0($a1)    
        
    la      $a0, espaco
    move    $s1, $ra
    jal     print_string
    move    $ra, $s1
     
    jr      $ra