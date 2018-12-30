.data
_prompt: .asciiz "Enter an integer:"
_ret: .asciiz "\n"
.globl main
.text
swap:
  addi $sp, $sp, -4
  sw $s0, 0($sp)
  addi $sp, $sp, -4
  sw $s1, 0($sp)
  addi $sp, $sp, -4
  sw $s2, 0($sp)
  addi $sp, $sp, -4
  sw $s3, 0($sp)
  addi $sp, $sp, -4
  sw $s4, 0($sp)
  addi $sp, $sp, -4
  sw $s5, 0($sp)
  addi $sp, $sp, -4
  sw $s6, 0($sp)
  addi $sp, $sp, -4
  sw $s7, 0($sp)
  addi $sp, $sp, -4
  lw $t1, 8($fp)
  move $t0, $t1
  lw $t2, 12($fp)
  move $t1, $t2
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
  addi $sp, $sp, 4
  lw $s7, 0($sp)
  addi $sp, $sp, 4
  lw $s6, 0($sp)
  addi $sp, $sp, 4
  lw $s5, 0($sp)
  addi $sp, $sp, 4
  lw $s4, 0($sp)
  addi $sp, $sp, 4
  lw $s3, 0($sp)
  addi $sp, $sp, 4
  lw $s2, 0($sp)
  addi $sp, $sp, 4
  lw $s1, 0($sp)
  addi $sp, $sp, 4
  lw $s0, 0($sp)
  addi $sp, $sp, 4
  sw $t1, 8($fp)
  sw $t2, 12($fp)
  sw $t0, -36($fp)
  jr $ra
  
main:
  move $fp, $sp
  addi $sp, $sp, -20
  addi $sp, $sp, -4
  li $t0, 0
  sw $t0, -24($fp)
label1:
  lw $t0, -24($fp)
  li $t1, 5
  sw $t0, -24($fp)
  blt $t0, $t1, label2
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
  move $t0, $v0
  lw $t1, -24($fp)
  li $t2, 4
  mul $t3, $t1, $t2
  addi $t2, $fp, -20
  add $t4, $t3, $t2
  sw $t0, 0($t4)
  li $t0, 0
  sw $t1, -24($fp)
  bgt $t1, $t0, label4
  j label5
label4:
  lw $t0, -24($fp)
  li $t1, 4
  mul $t2, $t0, $t1
  addi $t1, $fp, -20
  add $t3, $t2, $t1
  lw $t1, 0($t3)
  addi $sp, $sp, -4
  sw $t1, 0($sp)
  li $t1, 1
  sub $t2, $t0, $t1
  li $t1, 4
  mul $t3, $t2, $t1
  addi $t1, $fp, -20
  add $t2, $t3, $t1
  lw $t1, 0($t2)
  addi $sp, $sp, -4
  sw $t1, 0($sp)
  addi $sp, $sp, -4
  sw $fp, 0($sp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  move $fp, $sp
  addi $sp, $sp, -4
  sw $t0, 0($sp)
  addi $sp, $sp, -4
  sw $t1, 0($sp)
  addi $sp, $sp, -4
  sw $t2, 0($sp)
  addi $sp, $sp, -4
  sw $t3, 0($sp)
  addi $sp, $sp, -4
  sw $t4, 0($sp)
  addi $sp, $sp, -4
  sw $t5, 0($sp)
  addi $sp, $sp, -4
  sw $t6, 0($sp)
  addi $sp, $sp, -4
  sw $t7, 0($sp)
  addi $sp, $sp, -4
  sw $t8, 0($sp)
  addi $sp, $sp, -4
  sw $t9, 0($sp)
  jal swap
  lw $t9, 0($sp)
  addi $sp, $sp, 4
  lw $t8, 0($sp)
  addi $sp, $sp, 4
  lw $t7, 0($sp)
  addi $sp, $sp, 4
  lw $t6, 0($sp)
  addi $sp, $sp, 4
  lw $t5, 0($sp)
  addi $sp, $sp, 4
  lw $t4, 0($sp)
  addi $sp, $sp, 4
  lw $t3, 0($sp)
  addi $sp, $sp, 4
  lw $t2, 0($sp)
  addi $sp, $sp, 4
  lw $t1, 0($sp)
  addi $sp, $sp, 4
  lw $t0, 0($sp)
  addi $sp, $sp, 4
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  addi $sp, $sp, 8
  move $t1, $v0
  sw $t0, -24($fp)
label5:
  lw $t0, -24($fp)
  addi $t0, $t0, 1
  sw $t0, -24($fp)
  j label1
label3:
  li $v0, 0
  addi $sp, $sp, 24
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
  
