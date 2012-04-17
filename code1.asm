main:
b	label9
fibonacci:
lw	$t0,0($sp)
sw	$t0,-1000($sp)
li	$t0,0
sw	$t0,-1004($sp)
lw	$t0,-1000($sp)
lw	$t1,-1004($sp)
beq	$t0,$t1,label1
li	$t3,0
sw	$t3,-1008($sp)
b	label2
label1:
li	$t4,1
sw	$t4,-1008($sp)
label2:
li	$t0,0
lw	$t1,-1008($sp)
beq	$t1,$t0,label3
li	$t0,1
sw	$t0,-1012($sp)
lw	$v0,-1012($sp)
jr	$ra
b	label8
label3:
lw	$t0,0($sp)
sw	$t0,-1016($sp)
li	$t0,1
sw	$t0,-1020($sp)
lw	$t0,-1016($sp)
lw	$t1,-1020($sp)
beq	$t0,$t1,label4
li	$t3,0
sw	$t3,-1024($sp)
b	label5
label4:
li	$t4,1
sw	$t4,-1024($sp)
label5:
li	$t0,0
lw	$t1,-1024($sp)
beq	$t1,$t0,label6
li	$t0,1
sw	$t0,-1028($sp)
lw	$v0,-1028($sp)
jr	$ra
b	label7
label6:
sw	$t0,-996($sp)
sw	$t1,-992($sp)
sw	$t2,-988($sp)
sw	$t3,-984($sp)
sw	$t4,-980($sp)
sw	$t5,-976($sp)
sw	$t6,-972($sp)
sw	$t7,-968($sp)
sw	$ra,-964($sp)
lw	$t0,0($sp)
sw	$t0,-1032($sp)
li	$t0,1
sw	$t0,-1036($sp)
lw	$t0,-1032($sp)
lw	$t1,-1036($sp)
sub	$t2,$t0,$t1
sw	$t2,-1032($sp)
lw	$t0,-1032($sp)
sw	$t0,-100($sp)
li	$t0,100
sub	$sp,$sp,$t0
jal	fibonacci
li	$t0,100
add	$sp,$sp,$t0
lw	$t0,-996($sp)
lw	$t1,-992($sp)
lw	$t2,-988($sp)
lw	$t3,-984($sp)
lw	$t4,-980($sp)
lw	$t5,-976($sp)
lw	$t6,-972($sp)
lw	$t7,-968($sp)
lw	$ra,-964($sp)
sw	$v0,-1040($sp)
sw	$t0,-996($sp)
sw	$t1,-992($sp)
sw	$t2,-988($sp)
sw	$t3,-984($sp)
sw	$t4,-980($sp)
sw	$t5,-976($sp)
sw	$t6,-972($sp)
sw	$t7,-968($sp)
sw	$ra,-964($sp)
lw	$t0,0($sp)
sw	$t0,-1044($sp)
li	$t0,2
sw	$t0,-1048($sp)
lw	$t0,-1044($sp)
lw	$t1,-1048($sp)
sub	$t2,$t0,$t1
sw	$t2,-1044($sp)
lw	$t0,-1044($sp)
sw	$t0,-100($sp)
li	$t0,100
sub	$sp,$sp,$t0
jal	fibonacci
li	$t0,100
add	$sp,$sp,$t0
lw	$t0,-996($sp)
lw	$t1,-992($sp)
lw	$t2,-988($sp)
lw	$t3,-984($sp)
lw	$t4,-980($sp)
lw	$t5,-976($sp)
lw	$t6,-972($sp)
lw	$t7,-968($sp)
lw	$ra,-964($sp)
sw	$v0,-1052($sp)
lw	$t0,-1040($sp)
lw	$t1,-1052($sp)
add	$t2,$t0,$t1
sw	$t2,-1040($sp)
lw	$v0,-1040($sp)
jr	$ra
label7:
label8:

jr $ra
label9:
li	$t0,4
sw	$t0,-1000($sp)
li	$t0,5
sw	$t0,-1004($sp)
lw	$t0,-1000($sp)
lw	$t1,-1004($sp)
add	$t2,$t0,$t1
sw	$t2,-1000($sp)
lw	$t0,-1000($sp)
sw	$t0,0($sp)
lw	$t0,0($sp)
sw	$t0,-1008($sp)
li	$v0,4
la	$a0, MSG
syscall
lw	$t0,-1008($sp)
li	$v0,1
move	$a0,$t0
syscall
sw	$t0,-996($sp)
sw	$t1,-992($sp)
sw	$t2,-988($sp)
sw	$t3,-984($sp)
sw	$t4,-980($sp)
sw	$t5,-976($sp)
sw	$t6,-972($sp)
sw	$t7,-968($sp)
sw	$ra,-964($sp)
li	$t0,10
sw	$t0,-1012($sp)
lw	$t0,-1012($sp)
sw	$t0,-100($sp)
li	$t0,100
sub	$sp,$sp,$t0
jal	fibonacci
li	$t0,100
add	$sp,$sp,$t0
lw	$t0,-996($sp)
lw	$t1,-992($sp)
lw	$t2,-988($sp)
lw	$t3,-984($sp)
lw	$t4,-980($sp)
lw	$t5,-976($sp)
lw	$t6,-972($sp)
lw	$t7,-968($sp)
lw	$ra,-964($sp)
sw	$v0,-1016($sp)
lw	$t0,-1016($sp)
sw	$t0,0($sp)
li	$t0,5
sw	$t0,-1020($sp)
lw	$t0,-1020($sp)
sw	$t0,-4($sp)
lw	$t0,0($sp)
sw	$t0,-1024($sp)
li	$v0,4
la	$a0, MSG
syscall
lw	$t0,-1024($sp)
li	$v0,1
move	$a0,$t0
syscall
lw	$t0,-4($sp)
sw	$t0,-1028($sp)
li	$v0,4
la	$a0, MSG
syscall
lw	$t0,-1028($sp)
li	$v0,1
move	$a0,$t0
syscall
jr	$ra

	.data
MSG:	.asciiz "\n OUTPUT = "