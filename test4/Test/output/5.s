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
  move $t1, $t0
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
  move $t2, $t0
  li $t0, 100
  sw $t1, -4($fp)
  sw $t2, -8($fp)
  bgt $t1, $t0, label1
  j label2
label1:
  lw $t0, -8($fp)
  li $t1, 50
  sw $t0, -8($fp)
  blt $t0, $t1, label3
  j label4
label3:
  lw $t0, -8($fp)
  lw $t1, -4($fp)
  add $t2, $t0, $t1
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
  sw $t1, -4($fp)
  sw $t0, -8($fp)
  j label5
label4:
  lw $t0, -8($fp)
  lw $t1, -4($fp)
  sub $t2, $t0, $t1
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
  sw $t1, -4($fp)
  sw $t0, -8($fp)
label5:
  j label17
label2:
  lw $t0, -4($fp)
  li $t1, 100
  sw $t0, -4($fp)
  beq $t0, $t1, label7
  j label8
label7:
  lw $t0, -8($fp)
  li $t1, 100
  sw $t0, -8($fp)
  blt $t0, $t1, label9
  j label10
label9:
  addi $sp, $sp, -4
  sw $a0, 0($sp)
  lw $t0, -8($fp)
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
  sw $t0, -8($fp)
  j label11
label10:
  lw $t0, -8($fp)
  li $t1, 100
  sub $t2, $t0, $t1
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
  sw $t0, -8($fp)
label11:
  j label17
label8:
  lw $t0, -4($fp)
  li $t1, 100
  sw $t0, -4($fp)
  blt $t0, $t1, label13
  j label17
label13:
  lw $t0, -8($fp)
  lw $t1, -4($fp)
  add $t2, $t0, $t1
  li $t3, 100
  sw $t1, -4($fp)
  sw $t0, -8($fp)
  bgt $t2, $t3, label15
  j label16
label15:
  lw $t0, -4($fp)
  addi $t1, $t0, 100
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
  sw $t0, -4($fp)
  j label17
label16:
  addi $sp, $sp, -4
  sw $a0, 0($sp)
  li $t0, 100
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
label17:
  lw $t0, -4($fp)
  lw $t1, -8($fp)
  add $t2, $t0, $t1
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
  li $v0, 0
  addi $sp, $sp, 8
  sw $t0, -4($fp)
  sw $t1, -8($fp)
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
  
