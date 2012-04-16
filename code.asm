main:
li	$t0,3
sw	$t0,-100($sp)
lw	$t0,-100($sp)
sw	$t0,0($sp)
li	$t0,2
sw	$t0,-104($sp)
lw	$t0,-104($sp)
sw	$t0,-4($sp)
lw	$t0,0($sp)
sw	$t0,-108($sp)
lw	$t0,-4($sp)
sw	$t0,-112($sp)
lw	$t0,-108($sp)
lw	$t1,-112($sp)
li	$v0,4
la	$a0, MSG
syscall
add	$t2,$t0,$t1
li	$v0,1
move	$a0,$t2
syscall
sw	$t2,-108($sp)
lw	$t0,-108($sp)
sw	$t0,-8($sp)
jr	$ra

	.data
MSG: .asciiz "the result is = "
