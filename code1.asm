main:
li	$t0,4
sw	$t0,-1016($sp)
lw	$t0,-1016($sp)
sw	$t0,0($sp)
li	$t0,2
sw	$t0,-1020($sp)
li	$t0,3
sw	$t0,-1024($sp)
li	$t0,5
sw	$t0,-1028($sp)
lw	$t0,-1028($sp)
sw	$t0,-712($sp)
li	$t0,2
sw	$t0,-1032($sp)
li	$t0,3
sw	$t0,-1036($sp)
lw	$t0,-712($sp)
sw	$t0,-1040($sp)
lw	$t0,0($sp)
sw	$t0,-1044($sp)
lw	$t0,-1040($sp)
lw	$t1,-1044($sp)
sub	$t2,$t0,$t1
sw	$t2,-1040($sp)
lw	$t0,-1040($sp)
sw	$t0,-4($sp)
li	$t0,2
sw	$t0,-1048($sp)
li	$t0,3
sw	$t0,-1052($sp)
li	$t0,11
sw	$t0,-1056($sp)
lw	$t0,-1056($sp)
sw	$t0,-776($sp)
lw	$t0,0($sp)
sw	$t0,-1060($sp)
li	$t0,3
sw	$t0,-1064($sp)
lw	$t0,-1060($sp)
lw	$t1,-1064($sp)
sub	$t2,$t0,$t1
sw	$t2,-1060($sp)
lw	$t0,-4($sp)
sw	$t0,-1068($sp)
li	$t0,6
sw	$t0,-1072($sp)
lw	$t0,-1072($sp)
sw	$t0,-768($sp)
li	$t0,1
sw	$t0,-1076($sp)
li	$t0,1
sw	$t0,-1080($sp)
li	$t0,100
sw	$t0,-1084($sp)
lw	$t0,-1084($sp)
sw	$t0,-704($sp)
lw	$t0,0($sp)
sw	$t0,-1088($sp)
li	$v0,4
la	$a0, MSG
syscall
lw	$t0,-1088($sp)
li	$v0,1
move	$a0,$t0
syscall
lw	$t0,-4($sp)
sw	$t0,-1092($sp)
li	$v0,4
la	$a0, MSG
syscall
lw	$t0,-1092($sp)
li	$v0,1
move	$a0,$t0
syscall
li	$t0,2
sw	$t0,-1096($sp)
li	$t0,3
sw	$t0,-1100($sp)
lw	$t0,-712($sp)
sw	$t0,-1104($sp)
li	$v0,4
la	$a0, MSG
syscall
lw	$t0,-1104($sp)
li	$v0,1
move	$a0,$t0
syscall
li	$t0,1
sw	$t0,-1108($sp)
li	$t0,1
sw	$t0,-1112($sp)
lw	$t0,-704($sp)
sw	$t0,-1116($sp)
li	$v0,4
la	$a0, MSG
syscall
lw	$t0,-1116($sp)
li	$v0,1
move	$a0,$t0
syscall
li	$t0,2
sw	$t0,-1120($sp)
li	$t0,3
sw	$t0,-1124($sp)
lw	$t0,-776($sp)
sw	$t0,-1128($sp)
li	$v0,4
la	$a0, MSG
syscall
lw	$t0,-1128($sp)
li	$v0,1
move	$a0,$t0
syscall
li	$t0,1
sw	$t0,-1132($sp)
li	$t0,1
sw	$t0,-1136($sp)
lw	$t0,-768($sp)
sw	$t0,-1140($sp)
li	$v0,4
la	$a0, MSG
syscall
lw	$t0,-1140($sp)
li	$v0,1
move	$a0,$t0
syscall
jr	$ra

	.data
MSG:	.asciiz "\n OUTPUT = "