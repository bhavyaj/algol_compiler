b	main
b	label9
main:
b	label8
foo:
b	label4
bar:
lw	$t0,0($sp)
sw	$t0,-1000($sp)
lw	$t0,-4($sp)
sw	$t0,-1004($sp)
lw	$t0,-1000($sp)
lw	$t1,-1004($sp)
add	$t2,$t0,$t1
sw	$t2,-1000($sp)
lw	$t0,-8($sp)
sw	$t0,-1008($sp)
lw	$t0,-1000($sp)
lw	$t1,-1008($sp)
add	$t2,$t0,$t1
sw	$t2,-1000($sp)
lw	$t0,-1000($sp)
sw	$t0,-12($sp)
lw	$t0,-8($sp)
sw	$t0,-1012($sp)
lw	$t0,-12($sp)
sw	$t0,-1016($sp)
lw	$t0,-1012($sp)
lw	$t1,-1016($sp)
add	$t2,$t0,$t1
sw	$t2,-1012($sp)
lw	$t0,-1012($sp)
sw	$t0,-8($sp)
lw	$t0,-8($sp)
sw	$t0,-1020($sp)
li	$t0,60
sw	$t0,-1024($sp)
lw	$t0,-1020($sp)
lw	$t1,-1024($sp)
blt	$t0,$t1,label1
li	$t3,0
sw	$t3,-1028($sp)
b	label2
label1:
li	$t4,1
sw	$t4,-1028($sp)
label2:
li	$t0,0
lw	$t1,-1028($sp)
beq	$t1,$t0,label3
sw	$t0,-996($sp)
sw	$t1,-992($sp)
sw	$t2,-988($sp)
sw	$t3,-984($sp)
sw	$t4,-980($sp)
sw	$t5,-976($sp)
sw	$t6,-972($sp)
sw	$t7,-968($sp)
sw	$ra,-964($sp)
li	$t0,1
sw	$t0,-1032($sp)
lw	$t0,-1032($sp)
sw	$t0,-100($sp)
li	$t0,2
sw	$t0,-1036($sp)
lw	$t0,-1036($sp)
sw	$t0,-104($sp)
lw	$t0,-8($sp)
sw	$t0,-1040($sp)
lw	$t0,-1040($sp)
sw	$t0,-108($sp)
li	$t0,100
sub	$sp,$sp,$t0
jal	bar
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
sw	$v0,-1044($sp)
label3:
lw	$t0,-12($sp)
sw	$t0,-1048($sp)
li	$v0,4
la	$a0, MSG
syscall
lw	$t0,-1048($sp)
li	$v0,1
move	$a0,$t0
syscall

jr $ra
label4:
lw	$t0,0($sp)
sw	$t0,-1000($sp)
lw	$t0,-4($sp)
sw	$t0,-1004($sp)
lw	$t0,-1000($sp)
lw	$t1,-1004($sp)
add	$t2,$t0,$t1
sw	$t2,-1000($sp)
lw	$t0,-8($sp)
sw	$t0,-1008($sp)
lw	$t0,-1000($sp)
lw	$t1,-1008($sp)
add	$t2,$t0,$t1
sw	$t2,-1000($sp)
lw	$t0,-1000($sp)
sw	$t0,-12($sp)
lw	$t0,-8($sp)
sw	$t0,-1012($sp)
lw	$t0,-12($sp)
sw	$t0,-1016($sp)
lw	$t0,-1012($sp)
lw	$t1,-1016($sp)
add	$t2,$t0,$t1
sw	$t2,-1012($sp)
lw	$t0,-1012($sp)
sw	$t0,-8($sp)
lw	$t0,-8($sp)
sw	$t0,-1020($sp)
li	$t0,30
sw	$t0,-1024($sp)
lw	$t0,-1020($sp)
lw	$t1,-1024($sp)
blt	$t0,$t1,label5
li	$t3,0
sw	$t3,-1028($sp)
b	label6
label5:
li	$t4,1
sw	$t4,-1028($sp)
label6:
li	$t0,0
lw	$t1,-1028($sp)
beq	$t1,$t0,label7
sw	$t0,-996($sp)
sw	$t1,-992($sp)
sw	$t2,-988($sp)
sw	$t3,-984($sp)
sw	$t4,-980($sp)
sw	$t5,-976($sp)
sw	$t6,-972($sp)
sw	$t7,-968($sp)
sw	$ra,-964($sp)
li	$t0,4
sw	$t0,-1032($sp)
lw	$t0,-1032($sp)
sw	$t0,-100($sp)
li	$t0,5
sw	$t0,-1036($sp)
lw	$t0,-1036($sp)
sw	$t0,-104($sp)
lw	$t0,-8($sp)
sw	$t0,-1040($sp)
lw	$t0,-1040($sp)
sw	$t0,-108($sp)
li	$t0,100
sub	$sp,$sp,$t0
jal	bar
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
sw	$v0,-1044($sp)
label7:
lw	$t0,-12($sp)
sw	$t0,-1048($sp)
li	$v0,4
la	$a0, MSG
syscall
lw	$t0,-1048($sp)
li	$v0,1
move	$a0,$t0
syscall

jr $ra
label8:
li	$t0,4
sw	$t0,-1000($sp)
lw	$t0,-1000($sp)
sw	$t0,0($sp)
sw	$t0,-996($sp)
sw	$t1,-992($sp)
sw	$t2,-988($sp)
sw	$t3,-984($sp)
sw	$t4,-980($sp)
sw	$t5,-976($sp)
sw	$t6,-972($sp)
sw	$t7,-968($sp)
sw	$ra,-964($sp)
li	$t0,1
sw	$t0,-1004($sp)
lw	$t0,-1004($sp)
sw	$t0,-100($sp)
li	$t0,2
sw	$t0,-1008($sp)
lw	$t0,-1008($sp)
sw	$t0,-104($sp)
li	$t0,3
sw	$t0,-1012($sp)
lw	$t0,-1012($sp)
sw	$t0,-108($sp)
li	$t0,100
sub	$sp,$sp,$t0
jal	foo
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
label9:
jr	$ra

	.data
MSG:	.asciiz "\n OUTPUT = "