.data
_prompt: .asciiz "Enter an integer:"
_ret: .asciiz "\n"
.globl main
.text
main:
  move $fp, $sp
  addi $sp, $sp, -20
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  li $t0, 0
  sw $t0, -28($fp)
label1:
  lw $t0, -28($fp)
  li $t1, 5
  sw $t0, -28($fp)
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
  lw $t1, -28($fp)
  li $t2, 4
  mul $t3, $t1, $t2
  addi $t2, $fp, -20
  add $t4, $t3, $t2
  sw $t0, 0($t4)
  addi $t1, $t1, 1
  sw $t1, -28($fp)
  j label1
label3:
  li $t0, 1
  sw $t0, -28($fp)
label4:
  lw $t0, -28($fp)
  li $t1, 5
  sw $t0, -28($fp)
  blt $t0, $t1, label5
  j label6
label5:
  lw $t1, -28($fp)
  move $t0, $t1
  sw $t1, -28($fp)
  sw $t0, -32($fp)
label7:
  lw $t0, -32($fp)
  li $t1, 0
  sw $t0, -32($fp)
  bgt $t0, $t1, label10
  j label9
label10:
  lw $t0, -32($fp)
  li $t1, 1
  sub $t2, $t0, $t1
  li $t1, 4
  mul $t3, $t2, $t1
  addi $t1, $fp, -20
  add $t2, $t3, $t1
  li $t1, 4
  mul $t3, $t0, $t1
  addi $t1, $fp, -20
  add $t4, $t3, $t1
  lw $t1, 0($t2)
  lw $t3, 0($t4)
  sw $t0, -32($fp)
  bgt $t1, $t3, label8
  j label9
label8:
  lw $t0, -32($fp)
  li $t1, 4
  mul $t2, $t0, $t1
  addi $t1, $fp, -20
  add $t3, $t2, $t1
  lw $t1, 0($t3)
  li $t2, 1
  sub $t3, $t0, $t2
  li $t2, 4
  mul $t4, $t3, $t2
  addi $t2, $fp, -20
  add $t3, $t4, $t2
  li $t2, 4
  mul $t4, $t0, $t2
  addi $t2, $fp, -20
  add $t5, $t4, $t2
  lw $t2, 0($t3)
  sw $t2, 0($t5)
  li $t2, 1
  sub $t3, $t0, $t2
  li $t2, 4
  mul $t4, $t3, $t2
  addi $t2, $fp, -20
  add $t3, $t4, $t2
  sw $t1, 0($t3)
  li $t2, 1
  sub $t0, $t0, $t2
  sw $t1, -24($fp)
  sw $t0, -32($fp)
  j label7
label9:
  lw $t0, -28($fp)
  addi $t0, $t0, 1
  sw $t0, -28($fp)
  j label4
label6:
  li $t0, 0
  sw $t0, -28($fp)
label11:
  lw $t0, -28($fp)
  li $t1, 5
  sw $t0, -28($fp)
  blt $t0, $t1, label12
  j label13
label12:
  lw $t0, -28($fp)
  li $t1, 4
  mul $t2, $t0, $t1
  addi $t1, $fp, -20
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
  sw $t0, -28($fp)
  j label11
label13:
  li $v0, 0
  addi $sp, $sp, 32
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
  
