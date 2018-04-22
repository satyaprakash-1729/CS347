.data
       var1: .word 10
       greater: .asciiz "\nNot equal to 10!\n"
       lesser: .asciiz "\nequal to 10!\n"
.text
main:
       lw $t0, var1

       li $v0, 5
       syscall
       move $t1, $v0
       beq $t1, $t0, here

       li $v0, 4
       la $a0, greater
       syscall
       j there

here:
       li $v0, 4
       la $a0, lesser
       syscall
there:
       li $v0, 10
       syscall