.data
_prompt: .asciiz "Enter an integer:"
_ret: .asciiz "\n"
.globl main
.text
swap:
  move $t0, $a1
  move $t1, $a0
  move $t2, $t0
  addi $sp, $sp, -4
  sw $a0, 0($sp)
  move $a0, $t1
  addi $sp, $sp, -4
  sw $fp, 0($sp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  move $fp, $sp
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  lw $a0, 0($sp)
  addi $sp, $sp, 4
  addi $sp, $sp, -4
  sw $a0, 0($sp)
  move $a0, $t2
  addi $sp, $sp, -4
  sw $fp, 0($sp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  move $fp, $sp
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  lw $a0, 0($sp)
  addi $sp, $sp, 4
  move $v0, $t1
  jr $ra
  
main:
  move $fp, $sp
  addi $sp, $sp, -20
  li $t3, 0
label1:
  li $t4, 5
  blt $t3, $t4, label2
  j label3
label2:
  addi $sp, $sp, -4
  sw $fp, 0($sp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  move $fp, $sp
  jal read
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  move $t4, $v0
  li $t5, 4
  mul $t6, $t3, $t5
  addi $t5, $fp, -20
  add $t7, $t6, $t5
  sw $t4, 0($t7)
  li $t4, 0
  bgt $t3, $t4, label4
  j label5
label4:
  li $t4, 4
  mul $t5, $t3, $t4
  addi $t4, $fp, -20
  add $t6, $t5, $t4
  lw $t4, 0($t6)
  addi $sp, $sp, -4
  sw $a0, 0($sp)
  move $a0, $t4
  li $t4, 1
  sub $t5, $t3, $t4
  li $t4, 4
  mul $t6, $t5, $t4
  addi $t4, $fp, -20
  add $t5, $t6, $t4
  lw $t4, 0($t5)
  addi $sp, $sp, -4
  sw $a1, 0($sp)
  move $a1, $t4
  addi $sp, $sp, -4
  sw $fp, 0($sp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  move $fp, $sp
  jal swap
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  lw $a1, 0($sp)
  addi $sp, $sp, 4
  lw $a0, 0($sp)
  addi $sp, $sp, 4
  move $t4, $v0
label5:
  addi $t3, $t3, 1
  j label1
label3:
  li $v0, 0
  jr $ra
  addi $sp, $sp, 20
  
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
  
