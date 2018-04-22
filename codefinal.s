.data
ghy:  .word 0
.text
main2:
	addi $sp,$sp,-4
	sw $s0,0($sp)
	addi $sp,$sp,-4
	sw $s1,0($sp)
	addi $sp,$sp,-4
	sw $t0,0($sp)
	addi $sp,$sp,-4
	sw $t1,0($sp)
	addi $sp,$sp,-4
	sw $t2,0($sp)
	addi $sp,$sp,-4
	sw $t3,0($sp)
	addi $sp,$sp,-4
	sw $t4,0($sp)
	addi $sp,$sp,-4
	sw $t5,0($sp)
	addi $sp,$sp,-4
	sw $t6,0($sp)
	addi $sp,$sp,-4
	sw $t7,0($sp)
	move $t0, $a0
	move $t1, $a1
	add $t2, $t0, $t1
	move $v0, $t2
	lw $t7,0($sp)
	addi $sp,$sp,4
	lw $t6,0($sp)
	addi $sp,$sp,4
	lw $t5,0($sp)
	addi $sp,$sp,4
	lw $t4,0($sp)
	addi $sp,$sp,4
	lw $t3,0($sp)
	addi $sp,$sp,4
	lw $t2,0($sp)
	addi $sp,$sp,4
	lw $t1,0($sp)
	addi $sp,$sp,4
	lw $t0,0($sp)
	addi $sp,$sp,4
	lw $s1,0($sp)
	addi $sp,$sp,4
	lw $s0,0($sp)
	addi $sp,$sp,4
	jr $ra
main:
	li $t3, 56
	sw $t3, ghy
	li $t3, 56
	move $a0, $t3
	li $t4, 30
	move $a1, $t4
	jal main2
	move $t5, $v0
	li $v0, 1
	move $a0, $t5
	syscall
	li $v0, 10
	syscall
