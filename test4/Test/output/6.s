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
  li $t0, 2
  div $t2 $t0
  mflo $t3
  li $t0, 2
  mul $t4, $t3, $t0
  sw $t1, -4($fp)
  sw $t2, -8($fp)
  beq $t2, $t4, label1
  j label2
label1:
  li $t0, 1
  sw $t0, -12($fp)
  j label3
label2:
  lw $t1, -4($fp)
  move $t0, $t1
  sw $t1, -4($fp)
  sw $t0, -12($fp)
label3:
  lw $t0, -8($fp)
  li $t1, 2
  div $t0 $t1
  mflo $t0
  sw $t0, -8($fp)
label4:
  lw $t0, -8($fp)
  li $t1, 0
  sw $t0, -8($fp)
  bgt $t0, $t1, label5
  j label6
label5:
  lw $t0, -4($fp)
  mul $t0, $t0, $t0
  lw $t1, -8($fp)
  li $t2, 2
  div $t1 $t2
  mflo $t3
  li $t2, 2
  mul $t4, $t3, $t2
  sw $t0, -4($fp)
  sw $t1, -8($fp)
  bne $t1, $t4, label7
  j label8
label7:
  lw $t0, -12($fp)
  lw $t1, -4($fp)
  mul $t0, $t0, $t1
  sw $t1, -4($fp)
  sw $t0, -12($fp)
label8:
  lw $t0, -8($fp)
  li $t1, 2
  div $t0 $t1
  mflo $t0
  sw $t0, -8($fp)
  j label4
label6:
  addi $sp, $sp, -4
  sw $a0, 0($sp)
  lw $t0, -12($fp)
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
  addi $sp, $sp, 12
  sw $t0, -12($fp)
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
  
