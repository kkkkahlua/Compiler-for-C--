.data
_prompt: .asciiz "Enter an integer:"
_ret: .asciiz "\n"
.globl main
.text
main:
  move $fp, $sp
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -32
  addi $sp, $sp, -32
  addi $sp, $sp, -32
  addi $sp, $sp, -32
  li $t0, 0
  li $t1, 0
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
  move $t2, $v0
  move $t3, $t2
  sw $t0, -4($fp)
  sw $t1, -8($fp)
  sw $t3, -28($fp)
label1:
  lw $t0, -8($fp)
  lw $t1, -28($fp)
  sw $t0, -8($fp)
  sw $t1, -28($fp)
  blt $t0, $t1, label2
  j label3
label2:
  lw $t0, -8($fp)
  li $t1, 4
  mul $t2, $t0, $t1
  addi $t1, $fp, -60
  add $t3, $t2, $t1
  li $t1, -1
  sw $t1, 0($t3)
  addi $t0, $t0, 1
  sw $t0, -8($fp)
  j label1
label3:
  li $t0, 0
  li $t1, 1
  sw $t0, -8($fp)
  sw $t1, -24($fp)
label4:
  lw $t0, -24($fp)
  li $t1, 1
  sw $t0, -24($fp)
  beq $t0, $t1, label5
  j label6
label5:
  lw $t0, -8($fp)
  lw $t1, -28($fp)
  sw $t0, -8($fp)
  sw $t1, -28($fp)
  beq $t0, $t1, label7
  j label8
label7:
  li $t0, 1
  li $t1, 0
  sw $t0, -12($fp)
  sw $t1, -16($fp)
label9:
  lw $t0, -16($fp)
  lw $t1, -28($fp)
  sw $t0, -16($fp)
  sw $t1, -28($fp)
  blt $t0, $t1, label10
  j label11
label10:
  lw $t0, -16($fp)
  li $t1, 4
  mul $t2, $t0, $t1
  addi $t1, $fp, -92
  add $t3, $t2, $t1
  li $t1, 1
  sw $t1, 0($t3)
  li $t1, 4
  mul $t2, $t0, $t1
  addi $t1, $fp, -124
  add $t4, $t2, $t1
  li $t1, 1
  sw $t1, 0($t4)
  li $t1, 4
  mul $t2, $t0, $t1
  addi $t1, $fp, -156
  add $t5, $t2, $t1
  li $t1, 1
  sw $t1, 0($t5)
  addi $t0, $t0, 1
  sw $t0, -16($fp)
  j label9
label11:
  li $t0, 0
  sw $t0, -16($fp)
label12:
  lw $t0, -16($fp)
  lw $t1, -28($fp)
  sw $t0, -16($fp)
  sw $t1, -28($fp)
  blt $t0, $t1, label13
  j label14
label13:
  lw $t0, -16($fp)
  li $t1, 4
  mul $t2, $t0, $t1
  addi $t1, $fp, -60
  add $t3, $t2, $t1
  lw $t1, 0($t3)
  li $t2, 4
  mul $t3, $t1, $t2
  addi $t1, $fp, -92
  add $t2, $t3, $t1
  lw $t1, 0($t2)
  li $t3, 1
  sw $t0, -16($fp)
  bne $t1, $t3, label15
  j label18
label18:
  lw $t0, -16($fp)
  li $t1, 4
  mul $t2, $t0, $t1
  addi $t1, $fp, -60
  add $t3, $t2, $t1
  lw $t1, 0($t3)
  li $t2, 4
  mul $t3, $t1, $t2
  addi $t1, $fp, -124
  add $t2, $t3, $t1
  lw $t1, 0($t2)
  li $t3, 1
  sw $t0, -16($fp)
  bne $t1, $t3, label15
  j label17
label17:
  lw $t0, -16($fp)
  li $t1, 4
  mul $t2, $t0, $t1
  addi $t1, $fp, -60
  add $t3, $t2, $t1
  lw $t1, 0($t3)
  li $t2, 4
  mul $t3, $t1, $t2
  addi $t1, $fp, -156
  add $t2, $t3, $t1
  lw $t1, 0($t2)
  li $t3, 1
  sw $t0, -16($fp)
  bne $t1, $t3, label15
  j label16
label15:
  li $t0, 0
  lw $t2, -28($fp)
  move $t1, $t2
  sw $t0, -12($fp)
  sw $t1, -16($fp)
  sw $t2, -28($fp)
  j label19
label16:
  lw $t0, -16($fp)
  li $t1, 4
  mul $t2, $t0, $t1
  addi $t1, $fp, -60
  add $t3, $t2, $t1
  lw $t1, 0($t3)
  li $t2, 4
  mul $t3, $t1, $t2
  addi $t1, $fp, -92
  add $t2, $t3, $t1
  li $t1, 0
  sw $t1, 0($t2)
  li $t1, 0
  sw $t0, -16($fp)
  sw $t1, -20($fp)
label20:
  lw $t0, -28($fp)
  li $t1, 1
  sub $t2, $t0, $t1
  lw $t1, -20($fp)
  sw $t1, -20($fp)
  sw $t0, -28($fp)
  blt $t1, $t2, label21
  j label22
label21:
  lw $t0, -20($fp)
  addi $t1, $t0, 1
  li $t2, 4
  mul $t3, $t1, $t2
  addi $t1, $fp, -124
  add $t2, $t3, $t1
  li $t1, 4
  mul $t3, $t0, $t1
  addi $t1, $fp, -124
  add $t4, $t3, $t1
  lw $t1, 0($t2)
  sw $t1, 0($t4)
  addi $t0, $t0, 1
  sw $t0, -20($fp)
  j label20
label22:
  lw $t0, -28($fp)
  li $t1, 1
  sub $t2, $t0, $t1
  li $t1, 4
  mul $t3, $t2, $t1
  addi $t1, $fp, -124
  add $t2, $t3, $t1
  li $t1, 1
  sw $t1, 0($t2)
  lw $t1, -16($fp)
  li $t3, 4
  mul $t4, $t1, $t3
  addi $t3, $fp, -60
  add $t5, $t4, $t3
  lw $t3, 0($t5)
  li $t4, 0
  sw $t1, -16($fp)
  sw $t0, -28($fp)
  bne $t3, $t4, label23
  j label24
label23:
  lw $t0, -16($fp)
  li $t1, 4
  mul $t2, $t0, $t1
  addi $t1, $fp, -60
  add $t3, $t2, $t1
  lw $t1, 0($t3)
  li $t2, 1
  sub $t3, $t1, $t2
  li $t1, 4
  mul $t2, $t3, $t1
  addi $t1, $fp, -124
  add $t3, $t2, $t1
  li $t1, 0
  sw $t1, 0($t3)
  sw $t0, -16($fp)
label24:
  lw $t0, -28($fp)
  li $t1, 1
  sub $t2, $t0, $t1
  sw $t2, -20($fp)
  sw $t0, -28($fp)
label25:
  lw $t0, -20($fp)
  li $t1, 0
  sw $t0, -20($fp)
  bgt $t0, $t1, label26
  j label27
label26:
  lw $t0, -20($fp)
  li $t1, 1
  sub $t2, $t0, $t1
  li $t1, 4
  mul $t3, $t2, $t1
  addi $t1, $fp, -156
  add $t2, $t3, $t1
  li $t1, 4
  mul $t3, $t0, $t1
  addi $t1, $fp, -156
  add $t4, $t3, $t1
  lw $t1, 0($t2)
  sw $t1, 0($t4)
  li $t1, 1
  sub $t0, $t0, $t1
  sw $t0, -20($fp)
  j label25
label27:
  li $t0, 1
  lw $t1, -16($fp)
  li $t2, 4
  mul $t3, $t1, $t2
  addi $t2, $fp, -60
  add $t4, $t3, $t2
  lw $t2, -28($fp)
  li $t3, 1
  sub $t5, $t2, $t3
  lw $t3, 0($t4)
  sw $t1, -16($fp)
  sw $t2, -28($fp)
  sw $t0, -156($fp)
  bne $t3, $t5, label28
  j label29
label28:
  lw $t0, -16($fp)
  li $t1, 4
  mul $t2, $t0, $t1
  addi $t1, $fp, -60
  add $t3, $t2, $t1
  lw $t1, 0($t3)
  addi $t2, $t1, 1
  li $t1, 4
  mul $t3, $t2, $t1
  addi $t1, $fp, -156
  add $t2, $t3, $t1
  li $t1, 0
  sw $t1, 0($t2)
  sw $t0, -16($fp)
label29:
  lw $t0, -16($fp)
  addi $t0, $t0, 1
  sw $t0, -16($fp)
label19:
  j label12
label14:
  lw $t0, -12($fp)
  li $t1, 1
  sw $t0, -12($fp)
  beq $t0, $t1, label30
  j label31
label30:
  lw $t0, -4($fp)
  addi $t0, $t0, 1
  sw $t0, -4($fp)
label31:
  lw $t0, -8($fp)
  li $t1, 1
  sub $t0, $t0, $t1
  sw $t0, -8($fp)
  j label39
label8:
  lw $t0, -8($fp)
  li $t1, 0
  sw $t0, -8($fp)
  bge $t0, $t1, label36
  j label35
label36:
  lw $t0, -8($fp)
  li $t1, 4
  mul $t2, $t0, $t1
  addi $t1, $fp, -60
  add $t3, $t2, $t1
  lw $t1, -28($fp)
  li $t2, 1
  sub $t4, $t1, $t2
  lw $t2, 0($t3)
  sw $t0, -8($fp)
  sw $t1, -28($fp)
  bge $t2, $t4, label34
  j label35
label34:
  lw $t0, -8($fp)
  li $t1, 4
  mul $t2, $t0, $t1
  addi $t1, $fp, -60
  add $t3, $t2, $t1
  li $t1, -1
  sw $t1, 0($t3)
  li $t1, 1
  sub $t0, $t0, $t1
  sw $t0, -8($fp)
  j label8
label35:
  lw $t0, -8($fp)
  li $t1, -1
  sw $t0, -8($fp)
  beq $t0, $t1, label37
  j label38
label37:
  li $t0, 0
  sw $t0, -24($fp)
  j label39
label38:
  lw $t0, -8($fp)
  li $t1, 4
  mul $t2, $t0, $t1
  addi $t1, $fp, -60
  add $t3, $t2, $t1
  lw $t1, 0($t3)
  addi $t2, $t1, 1
  li $t1, 4
  mul $t3, $t0, $t1
  addi $t1, $fp, -60
  add $t4, $t3, $t1
  sw $t2, 0($t4)
  addi $t0, $t0, 1
  sw $t0, -8($fp)
label39:
  j label4
label6:
  addi $sp, $sp, -4
  sw $a0, 0($sp)
  lw $t0, -4($fp)
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
  addi $sp, $sp, 156
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
  
