/* host2netl.S - host2netl_asm */

	.text
	.globl host2netl_asm

/*
	ASM implementation of host2netl for assignment one.
	Usage: 

	long host2netl_asm(&param)
*/

host2netl_asm:
		mov	%eax, 8(%ebp)
		bswap	%eax
		ret

