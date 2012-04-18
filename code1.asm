b	main
b	label1
main:
li.s	$f0,6.000000
s.s	$f0,-1000($sp)
l.s	$f0,-1000($sp)
s.s	$f0,0($sp)
li.s	$f0,4.000000
s.s	$f0,-1004($sp)
l.s	$f0,-1004($sp)
s.s	$f0,-4($sp)
li	$t0,22
sw	$t0,-1008($sp)
li	$t0,7
sw	$t0,-1012($sp)
lw	$t0,-1008($sp)
lw	$t1,-1012($sp)
sub	$t2,$t0,$t1
sw	$t2,-1008($sp)
lw	$t0,-1008($sp)
mtc1	$t0,$f0
cvt.s.w	$f0,$f0
s.s	$f0,-8($sp)
l.s	$f0,0($sp)
s.s	$f0,-1016($sp)
li	$v0,4
la	$a0, MSG
syscall
l.s	$f10,-1016($sp)
mov.s	$f12,$f10
li	$v0,2
syscall
l.s	$f0,-4($sp)
s.s	$f0,-1020($sp)
li	$v0,4
la	$a0, MSG
syscall
l.s	$f10,-1020($sp)
mov.s	$f12,$f10
li	$v0,2
syscall
l.s	$f0,-8($sp)
s.s	$f0,-1024($sp)
li	$v0,4
la	$a0, MSG
syscall
l.s	$f10,-1024($sp)
mov.s	$f12,$f10
li	$v0,2
syscall
label1:
jr	$ra

	.data
MSG:	.asciiz "\n OUTPUT = "