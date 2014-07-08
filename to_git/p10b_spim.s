li $t1, $0
li $t2, 1
loop:srl $t3, $t2
sll $t3, $t3
seq $t4, $t3, $t1
and $t5, $t4, $t2
add $t1, $t1, $t5
li $t6, 10
addi $t2, $t2, 1
bne $2, $6 loop
