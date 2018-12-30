.data
_prompt: .asciiz "Enter an integer:"
_ret: .asciiz "\n"
.globl main
.text
main:
  move $fp, $sp
  addi $sp, $sp, -4
  li $t0, 0
  addi $sp, $sp, -4
  li $t1, 1
  addi $sp, $sp, -4
  li $t2, 0
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
  move $t3, $v0
  move $t4, $t3
  sw $t0, -4($fp)
  sw $t1, -8($fp)
  sw $t2, -12($fp)
  sw $t4, -16($fp)
label1:
  lw $t0, -12($fp)
  lw $t1, -16($fp)
  sw $t0, -12($fp)
  sw $t1, -16($fp)
  blt $t0, $t1, label2
  j label3
label2:
  addi $sp, $sp, -4
  lw $t0, -4($fp)
  lw $t1, -8($fp)
  add $t2, $t0, $t1
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
  move $t0, $t1
  move $t1, $t2
  lw $t3, -12($fp)
  addi $t3, $t3, 1
  sw $t0, -4($fp)
  sw $t1, -8($fp)
  sw $t3, -12($fp)
  sw $t2, -20($fp)
  j label1
label3:
  li $v0, 0
  addi $sp, $sp, 20
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
  
