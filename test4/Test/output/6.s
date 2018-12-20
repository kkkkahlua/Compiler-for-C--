.data
_prompt: .asciiz "Enter an integer:"
_ret: .asciiz "\n"
.globl main
.text
main:
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal read
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  move $t0, $v0
  move $t1, $t0
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal read
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  move $t0, $v0
  move $t2, $t0
  li $t0, 2
  div $t2 $t0
  mflo $t3
  li $t0, 2
  mul $t4, $t3, $t0
  beq $t2, $t4, label1
  j label2
label1:
  li $t0, 1
  j label3
label2:
  move $t0, $t1
label3:
  li $t3, 2
  div $t2 $t3
  mflo $t2
label4:
  li $t3, 0
  bgt $t2, $t3, label5
  j label6
label5:
  mul $t1, $t1, $t1
  li $t3, 2
  div $t2 $t3
  mflo $t4
  li $t3, 2
  mul $t5, $t4, $t3
  bne $t2, $t5, label7
  j label8
label7:
  mul $t0, $t0, $t1
label8:
  li $t3, 2
  div $t2 $t3
  mflo $t2
  j label4
label6:
  addi $sp, $sp, -4
  sw $a0, 0($sp)
  move $a0, $t0
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $a0, 0($sp)
  addi $sp, $sp, 4
  li $v0, 0
  jr $ra
  
read:
  li $v0, 4
  la $a0, _prompt
  syscall
  li $v0, 5
  syscall
  jr $ra
  
write:
  li $v0, 1
  syscall
  li $v0, 4
  la $a0, _ret
  syscall
  move $v0, $zero
  jr $ra
  
