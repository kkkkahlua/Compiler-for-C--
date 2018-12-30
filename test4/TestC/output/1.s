.data
_ret: .asciiz "\n"
.globl main
.text
process:
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
  li $t0, 3
  li $t0, 36
  lw $t1, 8($fp)
  li $t2, 321
  mul $t3, $t1, $t2
  li $t2, 2
  mul $t4, $t3, $t2
  mul $t2, $t1, $t0
  add $t3, $t4, $t2
  sub $t2, $t3, $t1
  mul $t3, $t0, $t1
  add $t4, $t2, $t3
  mul $t2, $t0, $t0
  add $t0, $t4, $t2
  add $t2, $t0, $t1
  add $t0, $t2, $t1
  li $t2, 23
  sub $t3, $t0, $t2
  addi $t0, $t3, 45
  li $t2, 3
  div $t0 $t2
  mflo $t3
  addi $t2, $t3, 336
  li $t3, 12
  mul $t4, $t1, $t3
  li $t3, 4
  div $t4 $t3
  mflo $t5
  sub $t3, $t2, $t5
  li $t2, 60
  sub $t4, $t3, $t2
  li $t2, 12
  div $t0 $t2
  mflo $t3
  li $t0, 24
  mul $t2, $t3, $t0
  add $t0, $t4, $t2
  addi $t2, $t0, 36
  addi $t0, $t2, 1
  addi $t2, $t1, 24
  addi $t0, $t2, 1
  move $v0, $t0
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
  sw $t0, -36($fp)
  jr $ra
  
main:
  move $fp, $sp
  addi $sp, $sp, -4
  li $t0, 13
  addi $sp, $sp, -4
  li $t1, 20
  addi $sp, $sp, -4
  li $t2, 15
  addi $sp, $sp, -4
  add $t3, $t0, $t1
  add $t4, $t3, $t2
  addi $sp, $sp, -4
  mul $t3, $t0, $t1
  li $t5, 2
  div $t2 $t5
  mflo $t6
  add $t5, $t3, $t6
  addi $sp, $sp, -4
  sub $t3, $t0, $t1
  sub $t6, $t3, $t2
  addi $sp, $sp, -4
  li $t3, 42
  addi $sp, $sp, -4
  li $t7, 0
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  add $s0, $t0, $t1
  add $s1, $s0, $t2
  addi $s0, $s1, 2000
  sub $t6, $s0, $t6
  sw $t0, -4($fp)
  sw $t1, -8($fp)
  sw $t2, -12($fp)
  sw $t4, -16($fp)
  sw $t5, -20($fp)
  sw $t6, -24($fp)
  sw $t3, -28($fp)
  sw $t7, -32($fp)
label1:
  lw $t0, -4($fp)
  lw $t1, -8($fp)
  add $t2, $t0, $t1
  lw $t3, -24($fp)
  sw $t0, -4($fp)
  sw $t1, -8($fp)
  sw $t3, -24($fp)
  blt $t2, $t3, label2
  j label3
label2:
  lw $t0, -32($fp)
  li $t1, 12
  mul $t2, $t0, $t1
  lw $t1, -28($fp)
  add $t3, $t1, $t2
  addi $t1, $t3, 4
  addi $t2, $t1, 5
  addi $t1, $t2, 2
  lw $t2, -24($fp)
  addi $sp, $sp, -4
  sw $t2, 0($sp)
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
  jal process
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
  addi $sp, $sp, 4
  move $t3, $v0
  lw $t4, -4($fp)
  li $t5, 2
  mul $t6, $t4, $t5
  add $t5, $t3, $t6
  sub $t3, $t5, $t2
  lw $t5, -12($fp)
  lw $t6, -16($fp)
  mul $t7, $t5, $t6
  add $s0, $t3, $t7
  add $t0, $t0, $t0
  add $t0, $t0, $t0
  add $t0, $t0, $t0
  add $t0, $t0, $t0
  add $t0, $t0, $t0
  addi $t3, $t0, 3
  li $t7, 1
  sub $t3, $t3, $t7
  addi $t3, $t3, 3
  li $t7, 6
  sub $t3, $t3, $t7
  addi $sp, $sp, -4
  sw $t4, 0($sp)
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
  jal process
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
  addi $sp, $sp, 4
  move $t7, $v0
  addi $s1, $t4, 3
  li $s2, 2
  sub $s3, $s1, $s2
  li $s1, 1
  sub $s2, $s3, $s1
  addi $sp, $sp, -4
  sw $s2, 0($sp)
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
  jal process
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
  addi $sp, $sp, 4
  move $s1, $v0
  sw $t4, -4($fp)
  sw $t5, -12($fp)
  sw $t6, -16($fp)
  sw $t2, -24($fp)
  sw $t1, -28($fp)
  sw $t0, -32($fp)
  sw $s0, -36($fp)
  sw $t3, -40($fp)
  beq $t7, $s1, label4
  j label5
label4:
  lw $t0, -24($fp)
  li $t1, 2
  sub $t2, $t0, $t1
  addi $t0, $t2, 1
  sw $t0, -24($fp)
label5:
  lw $t0, -4($fp)
  addi $t1, $t0, 2
  addi $t0, $t1, 1
  sw $t0, -4($fp)
  j label1
label3:
  lw $t0, -28($fp)
  li $t1, 12
  sub $t2, $t0, $t1
  sw $t0, -28($fp)
  sw $t2, -40($fp)
label6:
  lw $t0, -40($fp)
  lw $t1, -28($fp)
  sw $t1, -28($fp)
  sw $t0, -40($fp)
  blt $t0, $t1, label7
  j label8
label7:
  lw $t0, -4($fp)
  addi $t1, $t0, 58
  lw $t2, -28($fp)
  li $t3, 12
  sub $t4, $t2, $t3
  lw $t3, -40($fp)
  addi $t3, $t3, 1
  move $t4, $t2
  lw $t5, -8($fp)
  add $t6, $t0, $t5
  add $t7, $t0, $t5
  sw $t0, -4($fp)
  sw $t5, -8($fp)
  sw $t7, -12($fp)
  sw $t1, -24($fp)
  sw $t2, -28($fp)
  sw $t6, -32($fp)
  sw $t4, -36($fp)
  sw $t3, -40($fp)
  j label6
label8:
  addi $sp, $sp, -4
  sw $a0, 0($sp)
  lw $t0, -24($fp)
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
  lw $t0, -4($fp)
  lw $t1, -8($fp)
  add $t0, $t0, $t1
  add $t1, $t0, $t1
  add $t2, $t0, $t1
  add $t3, $t0, $t1
  add $t4, $t0, $t1
  add $t5, $t2, $t3
  add $t6, $t5, $t4
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
  li $v0, 0
  addi $sp, $sp, 40
  sw $t0, -4($fp)
  sw $t1, -8($fp)
  sw $t2, -12($fp)
  sw $t3, -24($fp)
  sw $t4, -36($fp)
  jr $ra
  
write:
  li $v0, 1
  syscall
  li $v0, 4
  la $a0, _ret
  syscall
  move $v0, $zero
  jr $ra
  
