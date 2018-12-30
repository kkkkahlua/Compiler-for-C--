.data
_prompt: .asciiz "Enter an integer:"
_ret: .asciiz "\n"
.globl main
.text
countSort:
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
  addi $sp, $sp, -20
  addi $sp, $sp, -40
  addi $sp, $sp, -20
  addi $sp, $sp, -4
  li $t0, 0
  sw $t0, -116($fp)
label1:
  lw $t0, -116($fp)
  li $t1, 10
  sw $t0, -116($fp)
  blt $t0, $t1, label2
  j label3
label2:
  lw $t0, -116($fp)
  li $t1, 4
  mul $t2, $t0, $t1
  addi $t1, $fp, -92
  add $t3, $t2, $t1
  li $t1, 0
  sw $t1, 0($t3)
  addi $t0, $t0, 1
  sw $t0, -116($fp)
  j label1
label3:
  li $t0, 0
  sw $t0, -116($fp)
label4:
  lw $t0, -116($fp)
  li $t1, 5
  sw $t0, -116($fp)
  blt $t0, $t1, label5
  j label6
label5:
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
  lw $t1, -116($fp)
  li $t2, 4
  mul $t3, $t1, $t2
  addi $t2, $fp, -52
  add $t4, $t3, $t2
  sw $t0, 0($t4)
  li $t0, 4
  mul $t2, $t1, $t0
  addi $t0, $fp, -52
  add $t3, $t2, $t0
  lw $t0, 0($t3)
  li $t2, 4
  mul $t3, $t0, $t2
  addi $t0, $fp, -92
  add $t2, $t3, $t0
  lw $t0, 0($t2)
  addi $t2, $t0, 1
  li $t0, 4
  mul $t3, $t1, $t0
  addi $t0, $fp, -52
  add $t5, $t3, $t0
  lw $t0, 0($t5)
  li $t3, 4
  mul $t5, $t0, $t3
  addi $t0, $fp, -92
  add $t3, $t5, $t0
  sw $t2, 0($t3)
  addi $t1, $t1, 1
  sw $t1, -116($fp)
  j label4
label6:
  li $t0, 1
  sw $t0, -116($fp)
label7:
  lw $t0, -116($fp)
  li $t1, 10
  sw $t0, -116($fp)
  blt $t0, $t1, label8
  j label9
label8:
  lw $t0, -116($fp)
  li $t1, 4
  mul $t2, $t0, $t1
  addi $t1, $fp, -92
  add $t3, $t2, $t1
  li $t1, 1
  sub $t2, $t0, $t1
  li $t1, 4
  mul $t4, $t2, $t1
  addi $t1, $fp, -92
  add $t2, $t4, $t1
  lw $t1, 0($t3)
  lw $t3, 0($t2)
  add $t2, $t1, $t3
  li $t1, 4
  mul $t3, $t0, $t1
  addi $t1, $fp, -92
  add $t4, $t3, $t1
  sw $t2, 0($t4)
  addi $t0, $t0, 1
  sw $t0, -116($fp)
  j label7
label9:
  li $t0, 0
  sw $t0, -116($fp)
label10:
  lw $t0, -116($fp)
  li $t1, 5
  sw $t0, -116($fp)
  blt $t0, $t1, label11
  j label12
label11:
  lw $t0, -116($fp)
  li $t1, 4
  mul $t2, $t0, $t1
  addi $t1, $fp, -52
  add $t3, $t2, $t1
  li $t1, 4
  mul $t2, $t0, $t1
  addi $t1, $fp, -52
  add $t4, $t2, $t1
  lw $t1, 0($t4)
  li $t2, 4
  mul $t4, $t1, $t2
  addi $t1, $fp, -92
  add $t2, $t4, $t1
  lw $t1, 0($t2)
  li $t2, 1
  sub $t4, $t1, $t2
  li $t1, 4
  mul $t2, $t4, $t1
  addi $t1, $fp, -112
  add $t4, $t2, $t1
  lw $t1, 0($t3)
  sw $t1, 0($t4)
  li $t1, 4
  mul $t2, $t0, $t1
  addi $t1, $fp, -52
  add $t3, $t2, $t1
  lw $t1, 0($t3)
  li $t2, 4
  mul $t3, $t1, $t2
  addi $t1, $fp, -92
  add $t2, $t3, $t1
  lw $t1, 0($t2)
  li $t2, 1
  sub $t3, $t1, $t2
  li $t1, 4
  mul $t2, $t0, $t1
  addi $t1, $fp, -52
  add $t5, $t2, $t1
  lw $t1, 0($t5)
  li $t2, 4
  mul $t5, $t1, $t2
  addi $t1, $fp, -92
  add $t2, $t5, $t1
  sw $t3, 0($t2)
  addi $t0, $t0, 1
  sw $t0, -116($fp)
  j label10
label12:
  li $t0, 0
  sw $t0, -116($fp)
label13:
  lw $t0, -116($fp)
  li $t1, 5
  sw $t0, -116($fp)
  blt $t0, $t1, label14
  j label15
label14:
  lw $t0, -116($fp)
  li $t1, 4
  mul $t2, $t0, $t1
  addi $t1, $fp, -112
  add $t3, $t2, $t1
  addi $sp, $sp, -4
  sw $a0, 0($sp)
  lw $t1, 0($t3)
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
  addi $t0, $t0, 1
  sw $t0, -116($fp)
  j label13
label15:
  li $v0, 0
  addi $sp, $sp, 84
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
  
bubbleSort:
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
  addi $sp, $sp, -20
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  li $t0, 0
  sw $t0, -56($fp)
label16:
  lw $t0, -56($fp)
  li $t1, 5
  sw $t0, -56($fp)
  blt $t0, $t1, label17
  j label18
label17:
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
  lw $t1, -56($fp)
  li $t2, 4
  mul $t3, $t1, $t2
  addi $t2, $fp, -52
  add $t4, $t3, $t2
  sw $t0, 0($t4)
  addi $t1, $t1, 1
  sw $t1, -56($fp)
  j label16
label18:
  li $t0, 1
  sw $t0, -60($fp)
label19:
  lw $t0, -60($fp)
  li $t1, 1
  sw $t0, -60($fp)
  beq $t0, $t1, label20
  j label21
label20:
  li $t0, 0
  li $t1, 1
  sw $t1, -56($fp)
  sw $t0, -60($fp)
label22:
  lw $t0, -56($fp)
  li $t1, 5
  sw $t0, -56($fp)
  blt $t0, $t1, label23
  j label24
label23:
  lw $t0, -56($fp)
  li $t1, 4
  mul $t2, $t0, $t1
  addi $t1, $fp, -52
  add $t3, $t2, $t1
  li $t1, 1
  sub $t2, $t0, $t1
  li $t1, 4
  mul $t4, $t2, $t1
  addi $t1, $fp, -52
  add $t2, $t4, $t1
  lw $t1, 0($t3)
  lw $t4, 0($t2)
  sw $t0, -56($fp)
  blt $t1, $t4, label25
  j label26
label25:
  li $t0, 1
  lw $t1, -56($fp)
  li $t2, 1
  sub $t3, $t1, $t2
  li $t2, 4
  mul $t4, $t3, $t2
  addi $t2, $fp, -52
  add $t3, $t4, $t2
  lw $t2, 0($t3)
  li $t3, 4
  mul $t4, $t1, $t3
  addi $t3, $fp, -52
  add $t5, $t4, $t3
  li $t3, 1
  sub $t4, $t1, $t3
  li $t3, 4
  mul $t6, $t4, $t3
  addi $t3, $fp, -52
  add $t4, $t6, $t3
  lw $t3, 0($t5)
  sw $t3, 0($t4)
  li $t3, 4
  mul $t5, $t1, $t3
  addi $t3, $fp, -52
  add $t6, $t5, $t3
  sw $t2, 0($t6)
  sw $t1, -56($fp)
  sw $t0, -60($fp)
  sw $t2, -64($fp)
label26:
  lw $t0, -56($fp)
  addi $t0, $t0, 1
  sw $t0, -56($fp)
  j label22
label24:
  j label19
label21:
  li $t0, 0
  sw $t0, -56($fp)
label27:
  lw $t0, -56($fp)
  li $t1, 5
  sw $t0, -56($fp)
  blt $t0, $t1, label28
  j label29
label28:
  lw $t0, -56($fp)
  li $t1, 4
  mul $t2, $t0, $t1
  addi $t1, $fp, -52
  add $t3, $t2, $t1
  addi $sp, $sp, -4
  sw $a0, 0($sp)
  lw $t1, 0($t3)
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
  addi $t0, $t0, 1
  sw $t0, -56($fp)
  j label27
label29:
  li $v0, 0
  addi $sp, $sp, 32
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
  
main:
  move $fp, $sp
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
  jal countSort
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
  jal bubbleSort
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
  move $t1, $v0
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
  
