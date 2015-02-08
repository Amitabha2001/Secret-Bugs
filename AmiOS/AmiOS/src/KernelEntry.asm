; Boot Loader Entry .

.286 ; CPU (x86)
.model TINY , C; Tiny model.

extrn kmain:near ; Symbol for boot main.

.code
org 1000h       ; Load address of kernel.

main:
		jmp short start ;
		nop ;

start:		
		cli ; Disable Interrupts.
			mov ax , cs ;
			mov ds , ax ;
			mov es , ax ;
			mov ss , ax ;
		sti ; Enable Interrupts.
					
		jmp kmain ; Call Boot Main.
	    ret ;
END main ; End of main.

END

