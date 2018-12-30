.data
_prompt: .asciiz "Enter an integer:"
_ret: .asciiz "\n"
.globl main
.text
search:
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
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  li $t0, 0
  sw $t0, -72($fp)
label1:
  lw $t0, -72($fp)
  li $t1, 5
  sw $t0, -72($fp)
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
  lw $t1, -72($fp)
  li $t2, 4
  mul $t3, $t1, $t2
  addi $t2, $fp, -52
  add $t4, $t3, $t2
  sw $t0, 0($t4)
  addi $t1, $t1, 1
  sw $t1, -72($fp)
  j label1
label3:
  li $t0, 0
  li $t1, 4
  sw $t0, -56($fp)
  sw $t1, -60($fp)
label4:
  lw $t0, -56($fp)
  lw $t1, -60($fp)
  sw $t0, -56($fp)
  sw $t1, -60($fp)
  ble $t0, $t1, label5
  j label6
label5:
  lw $t0, -56($fp)
  lw $t1, -60($fp)
  add $t2, $t0, $t1
  li $t3, 2
  div $t2 $t3
  mflo $t4
  li $t2, 4
  mul $t3, $t4, $t2
  addi $t2, $fp, -52
  add $t5, $t3, $t2
  lw $t2, 0($t5)
  lw $t3, 8($fp)
  sw $t3, 8($fp)
  sw $t0, -56($fp)
  sw $t1, -60($fp)
  sw $t4, -64($fp)
  sw $t2, -68($fp)
  beq $t2, $t3, label7
  j label8
label7:
  lw $t0, -64($fp)
  move $v0, $t0
  addi $sp, $sp, 52
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
  sw $t0, -64($fp)
  jr $ra
label8:
  li $t0, 0
  lw $t1, -56($fp)
  li $t2, 4
  mul $t3, $t1, $t2
  addi $t2, $fp, -52
  add $t4, $t3, $t2
  lw $t2, -68($fp)
  lw $t3, 0($t4)
  sw $t1, -56($fp)
  sw $t2, -68($fp)
  sw $t0, -76($fp)
  bgt $t2, $t3, label15
  j label13
label15:
  lw $t0, -56($fp)
  li $t1, 4
  mul $t2, $t0, $t1
  addi $t1, $fp, -52
  add $t3, $t2, $t1
  lw $t1, 8($fp)
  lw $t2, 0($t3)
  sw $t1, 8($fp)
  sw $t0, -56($fp)
  bge $t1, $t2, label14
  j label13
label14:
  lw $t0, 8($fp)
  lw $t1, -68($fp)
  sw $t0, 8($fp)
  sw $t1, -68($fp)
  blt $t0, $t1, label12
  j label13
label12:
  li $t0, 1
  sw $t0, -76($fp)
label13:
  lw $t0, -76($fp)
  li $t1, 0
  sw $t0, -76($fp)
  bne $t0, $t1, label9
  j label11
label11:
  li $t0, 0
  lw $t1, -56($fp)
  li $t2, 4
  mul $t3, $t1, $t2
  addi $t2, $fp, -52
  add $t4, $t3, $t2
  lw $t2, -68($fp)
  lw $t3, 0($t4)
  sw $t1, -56($fp)
  sw $t2, -68($fp)
  sw $t0, -80($fp)
  blt $t2, $t3, label18
  j label17
label18:
  li $t0, 0
  lw $t1, -56($fp)
  li $t2, 4
  mul $t3, $t1, $t2
  addi $t2, $fp, -52
  add $t4, $t3, $t2
  lw $t2, 8($fp)
  lw $t3, 0($t4)
  sw $t2, 8($fp)
  sw $t1, -56($fp)
  sw $t0, -84($fp)
  bge $t2, $t3, label19
  j label21
label21:
  lw $t0, 8($fp)
  lw $t1, -68($fp)
  sw $t0, 8($fp)
  sw $t1, -68($fp)
  blt $t0, $t1, label19
  j label20
label19:
  li $t0, 1
  sw $t0, -84($fp)
label20:
  lw $t0, -84($fp)
  li $t1, 0
  sw $t0, -84($fp)
  bne $t0, $t1, label16
  j label17
label16:
  li $t0, 1
  sw $t0, -80($fp)
label17:
  lw $t0, -80($fp)
  li $t1, 0
  sw $t0, -80($fp)
  bne $t0, $t1, label9
  j label10
label9:
  lw $t0, -64($fp)
  li $t1, 1
  sub $t2, $t0, $t1
  sw $t2, -60($fp)
  sw $t0, -64($fp)
  j label22
label10:
  lw $t0, -64($fp)
  addi $t1, $t0, 1
  sw $t1, -56($fp)
  sw $t0, -64($fp)
label22:
  j label4
label6:
  li $v0, -1
  addi $sp, $sp, 52
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
  sw $t1, 0($sp)
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
  jal search
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
  addi $sp, $sp, 4
  move $t0, $v0
  addi $sp, $sp, -4
  sw $a0, 0($sp)
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
  addi $sp, $sp, 4
  sw $t1, -4($fp)
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
  
