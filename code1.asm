main:
li	$t0,1
sw	$t0,-100($sp)

li	$t0,0
lw	$t1,-100($sp)
sub	$t2,$t0,$t1
sw	$t2,-104($sp)
lw	$t0,-104($sp)
sw	$t0,0($sp)
li	$t0,1
sw	$t0,-108($sp)
lw	$t0,-108($sp)
sw	$t0,0($sp)
label1:
li	$t0,10
sw	$t0,-116($sp)
lw	$t0,0($sp)
lw	$t1,-116($sp)
bge	$t0,$t1,label2
lw	$t0,0($sp)
sw	$t0,-120($sp)
li	$v0,4
la	$a0, MSG
syscall
lw	$t0,-120($sp)
li	$v0,1
move	$a0,$t0
syscall
li	$t0,2
sw	$t0,-112($sp)
lw	$t0,0($sp)
lw	$t1,-112($sp)
add	$t2,$t0,$t1
sw	$t2,0($sp)
b	label1
label2:
jr	$ra

	.data
MSG:	.asciiz "the result is = "