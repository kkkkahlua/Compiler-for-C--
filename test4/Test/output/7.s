.data
_prompt: .asciiz "Enter an integer:"
_ret: .asciiz "\n"
.globl main
.text
main:
  move $fp, $sp
  addi $sp, $sp, -20
  li $t0, 0
label1:
  li $t1, 5
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
  move $t1, $v0
  li $t2, 4
  mul $t3, $t0, $t2
  addi $t2, $fp, -20
  add $t4, $t3, $t2
  sw $t1, 0($t4)
  addi $t0, $t0, 1
  j label1
label3:
  li $t0, 1
label4:
  li $t1, 5
  blt $t0, $t1, label5
  j label6
label5:
  move $t1, $t0
label7:
  li $t2, 0
  bgt $t1, $t2, label10
  j label9
label10:
  li $t2, 1
  sub $t3, $t1, $t2
  li $t2, 4
  mul $t5, $t3, $t2
  addi $t2, $fp, -20
  add $t3, $t5, $t2
  li $t2, 4
  mul $t5, $t1, $t2
  addi $t2, $fp, -20
  add $t6, $t5, $t2
  lw $t2, 0($t3)
  lw $t5, 0($t6)
  bgt $t2, $t5, label8
  j label9
label8:
  li $t2, 4
  mul $t3, $t1, $t2
  addi $t2, $fp, -20
  add $t5, $t3, $t2
  lw $t2, 0($t5)
  li $t3, 1
  sub $t5, $t1, $t3
  li $t3, 4
  mul $t6, $t5, $t3
  addi $t3, $fp, -20
  add $t5, $t6, $t3
  li $t3, 4
  mul $t6, $t1, $t3
  addi $t3, $fp, -20
  add $t7, $t6, $t3
  lw $t3, 0($t5)
  sw $t3, 0($t7)
  li $t3, 1
  sub $t5, $t1, $t3
  li $t3, 4
  mul $t6, $t5, $t3
  addi $t3, $fp, -20
  add $t5, $t6, $t3
  sw $t2, 0($t5)
  li $t3, 1
  sub $t1, $t1, $t3
  j label7
label9:
  addi $t0, $t0, 1
  j label4
label6:
  li $t0, 0
label11:
  li $t3, 5
  blt $t0, $t3, label12
  j label13
label12:
  li $t3, 4
  mul $t6, $t0, $t3
  addi $t3, $fp, -20
  add $s0, $t6, $t3
  addi $sp, $sp, -4
  sw $a0, 0($sp)
  lw $t3, 0($s0)
  move $a0, $t3
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
  j label11
label13:
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
  
