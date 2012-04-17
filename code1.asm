main:
li	$t0,2
sw	$t0,-1016($sp)
li	$t0,3
sw	$t0,-1020($sp)
li	$t0,5
sw	$t0,-1024($sp)
li	$t0,1
sw	$t0,-1028($sp)
lw	$t0,-1024($sp)
lw	$t1,-1028($sp)
sub	$t2,$t0,$t1
sw	$t2,-1024($sp)
lw	$t0,-1024($sp)
sw	$t0,-712($sp)
li	$t0,2
sw	$t0,-1032($sp)
li	$t0,3
sw	$t0,-1036($sp)
li	$t0,6
sw	$t0,-1040($sp)
lw	$t0,-1040($sp)
sw	$t0,-728($sp)
li	$t0,1
sw	$t0,-1044($sp)
li	$t0,3
sw	$t0,-1048($sp)
li	$t0,10
sw	$t0,-1052($sp)
lw	$t0,-1052($sp)
sw	$t0,-728($sp)
li	$t0,3
sw	$t0,-1056($sp)
lw	$t0,-1056($sp)
sw	$t0,0($sp)
li	$t0,2
sw	$t0,-1060($sp)
li	$t0,3
sw	$t0,-1064($sp)
lw	$t0,-712($sp)
sw	$t0,-1068($sp)
li	$v0,4
la	$a0, MSG
syscall
lw	$t0,-1068($sp)
li	$v0,1
move	$a0,$t0
syscall
li	$t0,1
sw	$t0,-1072($sp)
li	$t0,3
sw	$t0,-1076($sp)
lw	$t0,-728($sp)
sw	$t0,-1080($sp)
li	$v0,4
la	$a0, MSG
syscall
lw	$t0,-1080($sp)
li	$v0,1
move	$a0,$t0
syscall
li	$t0,2
sw	$t0,-1084($sp)
li	$t0,3
sw	$t0,-1088($sp)
lw	$t0,-728($sp)
sw	$t0,-1092($sp)
li	$v0,4
la	$a0, MSG
syscall
lw	$t0,-1092($sp)
li	$v0,1
move	$a0,$t0
syscall
jr	$ra

	.data
MSG:	.asciiz "\n the result is = "