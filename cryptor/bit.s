
.section .data

A:
	.byte 0x03

B:
	.int 0x00

.section .bss

.section .text
.code64

.global _start

	_start:

		movzbl	A,%EDX
		sall	$0x04,%EDX	# <<
		movl	%EDX,B		#

		movq	$0x01,%RAX
		movq	$0x01,%RDI	# write
		leaq	B,%RSI		# Addr
		movq	$0x01,%RDX	# Len
		syscall




		movq	$60,%RAX
		movq	$0x00,%RDI
		syscall
