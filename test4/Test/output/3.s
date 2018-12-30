.data
_prompt: .asciiz "Enter an integer:"
_ret: .asciiz "\n"
.globl main
.text
main:
  move $fp, $sp
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
  li $t0, 0
  sw $t1, -4($fp)
  bgt $t1, $t0, label1
  j label2
label1:
  addi $sp, $sp, -4
  sw $a0, 0($sp)
  li $t0, 1
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
  j label6
label2:
  lw $t0, -4($fp)
  li $t1, 0
  sw $t0, -4($fp)
  blt $t0, $t1, label4
  j label5
label4:
  addi $sp, $sp, -4
  sw $a0, 0($sp)
  li $t0, -1
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
  j label6
label5:
  addi $sp, $sp, -4
  sw $a0, 0($sp)
  li $t0, 0
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
label6:
  li $v0, 0
  addi $sp, $sp, 4
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
  
