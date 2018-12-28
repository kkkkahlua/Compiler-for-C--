.data
_prompt: .asciiz "Enter an integer:"
_ret: .asciiz "\n"
.globl main
.text
myPow:
  li $t0, 0
  beq $a0, $t0, label1
  j label2
label1:
  li $v0, 1
  jr $ra
label2:
  li $t0, 1
  beq $a0, $t0, label3
  j label4
label3:
  move $v0, $a1
  jr $ra
label4:
  li $t0, 2
  beq $a0, $t0, label5
  j label6
label5:
  mul $t0, $a1, $a1
  move $v0, $t0
  jr $ra
label6:
  li $t1, 2
  div $a0 $t1
  mflo $t2
  li $t1, 2
  mul $t3, $t2, $t1
  beq $a0, $t3, label7
  j label8
label7:
  li $t1, 2
  addi $sp, $sp, -4
  sw $a0, 0($sp)
  move $a0, $t1
  li $t1, 2
  div $a0 $t1
  mflo $t2
  addi $sp, $sp, -4
  sw $a1, 0($sp)
  move $a1, $t2
  addi $sp, $sp, -4
  sw $a2, 0($sp)
  move $a2, $a1
  addi $sp, $sp, -4
  sw $fp, 0($sp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  move $fp, $sp
  jal myPow
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  lw $a2, 0($sp)
  addi $sp, $sp, 4
  lw $a1, 0($sp)
  addi $sp, $sp, 4
  lw $a0, 0($sp)
  addi $sp, $sp, 4
  move $t1, $v0
  addi $sp, $sp, -4
  sw $a0, 0($sp)
  move $a0, $t1
  addi $sp, $sp, -4
  sw $fp, 0($sp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  move $fp, $sp
  jal myPow
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  lw $a0, 0($sp)
  addi $sp, $sp, 4
  move $t1, $v0
  move $v0, $t1
  jr $ra
label8:
  li $t2, 2
  addi $sp, $sp, -4
  sw $a0, 0($sp)
  move $a0, $t2
  li $t2, 2
  div $a0 $t2
  mflo $t3
  addi $sp, $sp, -4
  sw $a1, 0($sp)
  move $a1, $t3
  addi $sp, $sp, -4
  sw $a2, 0($sp)
  move $a2, $a1
  addi $sp, $sp, -4
  sw $fp, 0($sp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  move $fp, $sp
  jal myPow
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  lw $a2, 0($sp)
  addi $sp, $sp, 4
  lw $a1, 0($sp)
  addi $sp, $sp, 4
  lw $a0, 0($sp)
  addi $sp, $sp, 4
  move $t2, $v0
  addi $sp, $sp, -4
  sw $a0, 0($sp)
  move $a0, $t2
  addi $sp, $sp, -4
  sw $fp, 0($sp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  move $fp, $sp
  jal myPow
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  lw $a0, 0($sp)
  addi $sp, $sp, 4
  move $t2, $v0
  mul $t3, $a1, $t2
  move $v0, $t3
  jr $ra
label9:
  
main:
  move $fp, $sp
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
  move $t4, $v0
  move $t5, $t4
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
  move $t4, $v0
  move $t6, $t4
  addi $sp, $sp, -4
  sw $a0, 0($sp)
  move $a0, $t6
  addi $sp, $sp, -4
  sw $a1, 0($sp)
  move $a1, $t5
  addi $sp, $sp, -4
  sw $fp, 0($sp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  move $fp, $sp
  jal myPow
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  lw $a1, 0($sp)
  addi $sp, $sp, 4
  lw $a0, 0($sp)
  addi $sp, $sp, 4
  move $t4, $v0
  addi $sp, $sp, -4
  sw $a0, 0($sp)
  move $a0, $t4
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
  
