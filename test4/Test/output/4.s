.data
_ret: .asciiz "\n"
.globl main
.text
main:
  move $fp, $sp
  li $t0, 3
  li $t1, 12
  mul $t2, $t1, $t1
  addi $t3, $t2, 13
  li $t2, 13
  div $t3 $t2
  mflo $t4
  addi $t2, $t4, 1
  div $t1 $t3
  mflo $t4
  mul $t5, $t3, $t2
  add $t6, $t4, $t5
  addi $sp, $sp, -4
  sw $a0, 0($sp)
  move $a0, $t6
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
  li $t4, 2
  mul $t5, $t6, $t4
  add $t4, $t0, $t5
  addi $sp, $sp, -4
  sw $a0, 0($sp)
  move $a0, $t4
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
  add $t5, $t1, $t3
  add $t7, $t5, $t2
  div $t1 $t4
  mflo $t5
  add $s0, $t7, $t5
  add $t0, $s0, $t0
  addi $sp, $sp, -4
  sw $a0, 0($sp)
  move $a0, $t0
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
  li $v0, 0
  jr $ra
  
write:
  li $v0, 1
  syscall
  li $v0, 4
  la $a0, _ret
  syscall
  move $v0, $zero
  jr $ra
  
