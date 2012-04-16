main:
li	$t0,6
sw	$t0,-100($sp)
lw	$t0,-100($sp)
sw	$t0,0($sp)
li	$t0,2
sw	$t0,-104($sp)
lw	$t0,-104($sp)
sw	$t0,-4($sp)
li	$t0,3
sw	$t0,-100($sp)
lw	$t0,-100($sp)
sw	$t0,-12($sp)
li	$t0,4
sw	$t0,-104($sp)
lw	$t0,-104($sp)
sw	$t0,-16($sp)
lw	$t0,0($sp)
sw	$t0,-108($sp)
lw	$t0,-4($sp)
sw	$t0,-112($sp)
lw	$t0,-108($sp)
lw	$t1,-112($sp)
sub	$t2,$t0,$t1
sw	$t2,-108($sp)
lw	$t0,-108($sp)
sw	$t0,-16($sp)
lw	$t0,-16($sp)
sw	$t0,-116($sp)
lw	$t0,-12($sp)
sw	$t0,-120($sp)
lw	$t0,-116($sp)
lw	$t1,-120($sp)
mult	$t0,$t1
mflo	$t0
sw	$t0,-116($sp)
lw	$t0,-116($sp)
sw	$t0,-8($sp)
lw	$t0,-8($sp)
sw	$t0,-124($sp)
li	$v0,4
la	$a0, MSG
syscall
lw	$t0,-124($sp)
li	$v0,1
move	$a0,$t0
syscall
lw	$t0,0($sp)
sw	$t0,-108($sp)
li	$v0,4
la	$a0, MSG
syscall
lw	$t0,-108($sp)
li	$v0,1
move	$a0,$t0
syscall
lw	$t0,-4($sp)
sw	$t0,-112($sp)
li	$v0,4
la	$a0, MSG
syscall
lw	$t0,-112($sp)
li	$v0,1
move	$a0,$t0
syscall
lw	$t0,-8($sp)
sw	$t0,-116($sp)
li	$v0,4
la	$a0, MSG
syscall
lw	$t0,-116($sp)
li	$v0,1
move	$a0,$t0
syscall
jr	$ra

	.data
MSG:	.asciiz "\n the result is = "