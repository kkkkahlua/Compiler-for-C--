.data
_prompt: .asciiz "Enter an integer:"
_ret: .asciiz "\n"
.globl main
.text
trap:
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
  li $t0, 0
  addi $sp, $sp, -4
  li $t1, 0
  addi $sp, $sp, -4
  li $t2, 0
  addi $sp, $sp, -4
  li $t3, 0
  addi $sp, $sp, -4
  li $t4, 0
  addi $sp, $sp, -4
  li $t5, 12
  addi $sp, $sp, -4
  li $t6, 0
  addi $sp, $sp, -48
  sw $t0, -36($fp)
  sw $t1, -40($fp)
  sw $t2, -44($fp)
  sw $t3, -48($fp)
  sw $t4, -52($fp)
  sw $t5, -56($fp)
  sw $t6, -60($fp)
label1:
  lw $t0, -44($fp)
  lw $t1, -56($fp)
  sw $t0, -44($fp)
  sw $t1, -56($fp)
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
  lw $t1, -44($fp)
  li $t2, 4
  mul $t3, $t1, $t2
  addi $t2, $fp, -108
  add $t4, $t3, $t2
  sw $t0, 0($t4)
  addi $t1, $t1, 1
  sw $t1, -44($fp)
  j label1
label3:
  li $t0, 0
  sw $t0, -44($fp)
label4:
  lw $t0, -44($fp)
  lw $t1, -56($fp)
  sw $t0, -44($fp)
  sw $t1, -56($fp)
  blt $t0, $t1, label7
  j label6
label7:
  lw $t0, -44($fp)
  li $t1, 4
  mul $t2, $t0, $t1
  addi $t1, $fp, -108
  add $t3, $t2, $t1
  lw $t1, 0($t3)
  li $t2, 0
  sw $t0, -44($fp)
  beq $t1, $t2, label5
  j label6
label5:
  lw $t0, -44($fp)
  addi $t0, $t0, 1
  sw $t0, -44($fp)
  j label4
label6:
  lw $t0, -44($fp)
  lw $t1, -56($fp)
  sw $t0, -44($fp)
  sw $t1, -56($fp)
  bge $t0, $t1, label8
  j label9
label8:
  li $v0, 0
  addi $sp, $sp, 76
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
  jr $ra
label9:
  lw $t0, -44($fp)
  li $t1, 4
  mul $t2, $t0, $t1
  addi $t1, $fp, -108
  add $t3, $t2, $t1
  lw $t1, 0($t3)
  move $t2, $t0
  li $t3, 0
  addi $t0, $t0, 1
  sw $t1, -36($fp)
  sw $t2, -40($fp)
  sw $t0, -44($fp)
  sw $t3, -52($fp)
label10:
  lw $t0, -44($fp)
  lw $t1, -56($fp)
  sw $t0, -44($fp)
  sw $t1, -56($fp)
  blt $t0, $t1, label11
  j label12
label11:
  lw $t0, -44($fp)
  li $t1, 4
  mul $t2, $t0, $t1
  addi $t1, $fp, -108
  add $t3, $t2, $t1
  lw $t1, 0($t3)
  lw $t2, -36($fp)
  sw $t2, -36($fp)
  sw $t0, -44($fp)
  blt $t1, $t2, label13
  j label14
label13:
  lw $t0, -44($fp)
  li $t1, 4
  mul $t2, $t0, $t1
  addi $t1, $fp, -108
  add $t3, $t2, $t1
  lw $t1, 0($t3)
  lw $t2, -36($fp)
  sub $t3, $t2, $t1
  lw $t1, -52($fp)
  add $t1, $t1, $t3
  sw $t2, -36($fp)
  sw $t0, -44($fp)
  sw $t1, -52($fp)
  j label15
label14:
  lw $t0, -48($fp)
  lw $t1, -52($fp)
  add $t0, $t0, $t1
  lw $t1, -44($fp)
  li $t2, 4
  mul $t3, $t1, $t2
  addi $t2, $fp, -108
  add $t4, $t3, $t2
  lw $t2, 0($t4)
  move $t3, $t1
  li $t4, 0
  sw $t2, -36($fp)
  sw $t3, -40($fp)
  sw $t1, -44($fp)
  sw $t0, -48($fp)
  sw $t4, -52($fp)
label15:
  lw $t0, -44($fp)
  addi $t0, $t0, 1
  sw $t0, -44($fp)
  j label10
label12:
  li $t0, 0
  li $t1, 0
  lw $t2, -56($fp)
  li $t3, 1
  sub $t4, $t2, $t3
  sw $t4, -44($fp)
  sw $t0, -52($fp)
  sw $t2, -56($fp)
  sw $t1, -60($fp)
label16:
  lw $t0, -44($fp)
  lw $t1, -40($fp)
  sw $t1, -40($fp)
  sw $t0, -44($fp)
  bgt $t0, $t1, label19
  j label18
label19:
  lw $t0, -44($fp)
  li $t1, 4
  mul $t2, $t0, $t1
  addi $t1, $fp, -108
  add $t3, $t2, $t1
  lw $t1, 0($t3)
  li $t2, 0
  sw $t0, -44($fp)
  beq $t1, $t2, label17
  j label18
label17:
  lw $t0, -44($fp)
  li $t1, 1
  sub $t0, $t0, $t1
  sw $t0, -44($fp)
  j label16
label18:
  lw $t0, -44($fp)
  li $t1, 4
  mul $t2, $t0, $t1
  addi $t1, $fp, -108
  add $t3, $t2, $t1
  lw $t1, 0($t3)
  li $t2, 1
  sub $t0, $t0, $t2
  sw $t0, -44($fp)
  sw $t1, -60($fp)
label20:
  lw $t0, -44($fp)
  lw $t1, -40($fp)
  sw $t1, -40($fp)
  sw $t0, -44($fp)
  bgt $t0, $t1, label21
  j label22
label21:
  lw $t0, -44($fp)
  li $t1, 4
  mul $t2, $t0, $t1
  addi $t1, $fp, -108
  add $t3, $t2, $t1
  lw $t1, 0($t3)
  lw $t2, -60($fp)
  sw $t0, -44($fp)
  sw $t2, -60($fp)
  blt $t1, $t2, label23
  j label24
label23:
  lw $t0, -44($fp)
  li $t1, 4
  mul $t2, $t0, $t1
  addi $t1, $fp, -108
  add $t3, $t2, $t1
  lw $t1, 0($t3)
  lw $t2, -60($fp)
  sub $t3, $t2, $t1
  lw $t1, -52($fp)
  add $t1, $t1, $t3
  sw $t0, -44($fp)
  sw $t1, -52($fp)
  sw $t2, -60($fp)
  j label25
label24:
  lw $t0, -48($fp)
  lw $t1, -52($fp)
  add $t0, $t0, $t1
  lw $t1, -44($fp)
  li $t2, 4
  mul $t3, $t1, $t2
  addi $t2, $fp, -108
  add $t4, $t3, $t2
  lw $t2, 0($t4)
  li $t3, 0
  sw $t1, -44($fp)
  sw $t0, -48($fp)
  sw $t3, -52($fp)
  sw $t2, -60($fp)
label25:
  lw $t0, -44($fp)
  li $t1, 1
  sub $t0, $t0, $t1
  sw $t0, -44($fp)
  j label20
label22:
  lw $t0, -48($fp)
  lw $t1, -52($fp)
  add $t2, $t0, $t1
  move $v0, $t2
  addi $sp, $sp, 76
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
  sw $t0, -48($fp)
  sw $t1, -52($fp)
  jr $ra
  
main:
  move $fp, $sp
  addi $sp, $sp, -4
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
  jal trap
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
  move $t0, $v0
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
  addi $sp, $sp, 4
  sw $t0, -4($fp)
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
  
