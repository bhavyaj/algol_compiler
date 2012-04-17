main:
b	label1
abc:
li	$t0,10
sw	$t0,-1000($sp)
lw	$t0,-1000($sp)
sw	$t0,-8($sp)
lw	$t0,0($sp)
sw	$t0,-1004($sp)
li	$v0,4
la	$a0, MSG
syscall
lw	$t0,-1004($sp)
li	$v0,1
move	$a0,$t0
syscall
lw	$t0,-4($sp)
sw	$t0,-1008($sp)
li	$v0,4
la	$a0, MSG
syscall
lw	$t0,-1008($sp)
li	$v0,1
move	$a0,$t0
syscall
lw	$t0,-8($sp)
sw	$t0,-1012($sp)
li	$v0,4
la	$a0, MSG
syscall
lw	$t0,-1012($sp)
li	$v0,1
move	$a0,$t0
syscall
lw	$t0,-8($sp)
sw	$t0,-1016($sp)
li	$v0,4
la	$a0, MSG
syscall
lw	$t0,-1016($sp)
li	$v0,1
move	$a0,$t0
syscall
lw	$t0,0($sp)
sw	$t0,-1020($sp)
lw	$t0,-4($sp)
sw	$t0,-1024($sp)
lw	$t0,-1020($sp)
lw	$t1,-1024($sp)
add	$t2,$t0,$t1
sw	$t2,-1020($sp)
lw	$t0,-8($sp)
sw	$t0,-1028($sp)
lw	$t0,-1020($sp)
lw	$t1,-1028($sp)
add	$t2,$t0,$t1
sw	$t2,-1020($sp)
lw	$t0,-8($sp)
sw	$t0,-1032($sp)
lw	$t0,-1020($sp)
lw	$t1,-1032($sp)
mult	$t0,$t1
mflo	$t0
sw	$t0,-1020($sp)
lw	$t0,-1020($sp)
sw	$t0,-8($sp)
lw	$t0,-8($sp)
sw	$t0,-1036($sp)
li	$v0,4
la	$a0, MSG
syscall
lw	$t0,-1036($sp)
li	$v0,1
move	$a0,$t0
syscall

jr $ra
label1:
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
li	$t0,3
sw	$t0,-1012($sp)
lw	$t0,-1012($sp)
sw	$t0,-108($sp)
li	$t0,100
sub	$sp,$sp,$t0
jal	abc
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
jr	$ra

	.data
MSG:	.asciiz "\n the result is = "