.data
_prompt: .asciiz "Enter an integer:"
_ret: .asciiz "\n"
.globl main
.text
countSort:
  addi $sp, $sp, -20
  addi $sp, $sp, -40
  addi $sp, $sp, -20
  li $t0, 0
label1:
  li $t1, 10
  blt $t0, $t1, label2
  j label3
label2:
  li $t1, 4
  mul $t2, $t0, $t1
  addi $t1, $fp, -60
  add $t3, $t2, $t1
  li $t1, 0
  sw $t1, 0($t3)
  addi $t0, $t0, 1
  j label1
label3:
  li $t0, 0
label4:
  li $t1, 5
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
  move $t1, $v0
  li $t2, 4
  mul $t4, $t0, $t2
  addi $t2, $fp, -20
  add $t5, $t4, $t2
  sw $t1, 0($t5)
  li $t1, 4
  mul $t2, $t0, $t1
  addi $t1, $fp, -20
  add $t4, $t2, $t1
  lw $t1, 0($t4)
  li $t2, 4
  mul $t4, $t1, $t2
  addi $t1, $fp, -60
  add $t2, $t4, $t1
  lw $t1, 0($t2)
  addi $t2, $t1, 1
  li $t1, 4
  mul $t4, $t0, $t1
  addi $t1, $fp, -20
  add $t6, $t4, $t1
  lw $t1, 0($t6)
  li $t4, 4
  mul $t6, $t1, $t4
  addi $t1, $fp, -60
  add $t4, $t6, $t1
  sw $t2, 0($t4)
  addi $t0, $t0, 1
  j label4
label6:
  li $t0, 1
label7:
  li $t1, 10
  blt $t0, $t1, label8
  j label9
label8:
  li $t1, 4
  mul $t2, $t0, $t1
  addi $t1, $fp, -60
  add $t6, $t2, $t1
  li $t1, 1
  sub $t2, $t0, $t1
  li $t1, 4
  mul $t7, $t2, $t1
  addi $t1, $fp, -60
  add $t2, $t7, $t1
  lw $t1, 0($t6)
  lw $t6, 0($t2)
  add $t2, $t1, $t6
  li $t1, 4
  mul $t6, $t0, $t1
  addi $t1, $fp, -60
  add $t7, $t6, $t1
  sw $t2, 0($t7)
  addi $t0, $t0, 1
  j label7
label9:
  li $t0, 0
label10:
  li $t1, 5
  blt $t0, $t1, label11
  j label12
label11:
  li $t1, 4
  mul $t2, $t0, $t1
  addi $t1, $fp, -20
  add $t6, $t2, $t1
  li $t1, 4
  mul $t2, $t0, $t1
  addi $t1, $fp, -20
  add $s0, $t2, $t1
  lw $t1, 0($s0)
  li $t2, 4
  mul $s0, $t1, $t2
  addi $t1, $fp, -60
  add $t2, $s0, $t1
  lw $t1, 0($t2)
  li $t2, 1
  sub $s0, $t1, $t2
  li $t1, 4
  mul $t2, $s0, $t1
  addi $t1, $fp, -80
  add $s0, $t2, $t1
  lw $t1, 0($t6)
  sw $t1, 0($s0)
  li $t1, 4
  mul $t2, $t0, $t1
  addi $t1, $fp, -20
  add $t6, $t2, $t1
  lw $t1, 0($t6)
  li $t2, 4
  mul $t6, $t1, $t2
  addi $t1, $fp, -60
  add $t2, $t6, $t1
  lw $t1, 0($t2)
  li $t2, 1
  sub $t6, $t1, $t2
  li $t1, 4
  mul $t2, $t0, $t1
  addi $t1, $fp, -20
  add $s1, $t2, $t1
  lw $t1, 0($s1)
  li $t2, 4
  mul $s1, $t1, $t2
  addi $t1, $fp, -60
  add $t2, $s1, $t1
  sw $t6, 0($t2)
  addi $t0, $t0, 1
  j label10
label12:
  li $t0, 0
label13:
  li $t1, 5
  blt $t0, $t1, label14
  j label15
label14:
  li $t1, 4
  mul $t6, $t0, $t1
  addi $t1, $fp, -80
  add $s1, $t6, $t1
  addi $sp, $sp, -4
  sw $a0, 0($sp)
  lw $t1, 0($s1)
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
  j label13
label15:
  li $v0, 0
  addi $sp, $sp, 80
  jr $ra
  
bubbleSort:
  addi $sp, $sp, -20
  li $t1, 0
label16:
  li $t6, 5
  blt $t1, $t6, label17
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
  move $t6, $v0
  li $s1, 4
  mul $s2, $t1, $s1
  addi $s1, $fp, -20
  add $s3, $s2, $s1
  sw $t6, 0($s3)
  addi $t1, $t1, 1
  j label16
label18:
  li $t6, 1
label19:
  li $s1, 1
  beq $t6, $s1, label20
  j label21
label20:
  li $t6, 0
  li $t1, 1
label22:
  li $s1, 5
  blt $t1, $s1, label23
  j label24
label23:
  li $s1, 4
  mul $s2, $t1, $s1
  addi $s1, $fp, -20
  add $s4, $s2, $s1
  li $s1, 1
  sub $s2, $t1, $s1
  li $s1, 4
  mul $s5, $s2, $s1
  addi $s1, $fp, -20
  add $s2, $s5, $s1
  lw $s1, 0($s4)
  lw $s5, 0($s2)
  blt $s1, $s5, label25
  j label26
label25:
  li $t6, 1
  li $s1, 1
  sub $s2, $t1, $s1
  li $s1, 4
  mul $s4, $s2, $s1
  addi $s1, $fp, -20
  add $s2, $s4, $s1
  lw $s1, 0($s2)
  li $s2, 4
  mul $s4, $t1, $s2
  addi $s2, $fp, -20
  add $s5, $s4, $s2
  li $s2, 1
  sub $s4, $t1, $s2
  li $s2, 4
  mul $s6, $s4, $s2
  addi $s2, $fp, -20
  add $s4, $s6, $s2
  lw $s2, 0($s5)
  sw $s2, 0($s4)
  li $s2, 4
  mul $s5, $t1, $s2
  addi $s2, $fp, -20
  add $s6, $s5, $s2
  sw $s1, 0($s6)
label26:
  addi $t1, $t1, 1
  j label22
label24:
  j label19
label21:
  li $t1, 0
label27:
  li $s2, 5
  blt $t1, $s2, label28
  j label29
label28:
  li $s2, 4
  mul $s5, $t1, $s2
  addi $s2, $fp, -20
  add $s7, $s5, $s2
  addi $sp, $sp, -4
  sw $a0, 0($sp)
  lw $s2, 0($s7)
  move $a0, $s2
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
  addi $t1, $t1, 1
  j label27
label29:
  li $v0, 0
  addi $sp, $sp, 20
  jr $ra
  
main:
  move $fp, $sp
  addi $sp, $sp, -4
  sw $fp, 0($sp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  move $fp, $sp
  jal countSort
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  move $s2, $v0
  addi $sp, $sp, -4
  sw $fp, 0($sp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  move $fp, $sp
  jal bubbleSort
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  move $s5, $v0
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
  
