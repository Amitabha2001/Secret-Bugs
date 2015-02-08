; Interrupts.
.286 ;
.model TINY ;
extrn _onTimer:near ;
public _init_timer ;

.code

_timer_irq:
		
		cli ;

		push ss ;
		push bp ;
		push sp ;
		push es ;
		push ds ;

		cli ;

		mov ax , cs ;
		mov ds , ax ;
		mov es , ax ;

		sti ;

		call _onTimer ;
		
		cli ;

		pop ds ;
		pop es ;
		pop sp ;
		pop bp ;
		pop ss ;

		mov al , 20h ;
		mov dx , 20h ;
		out dx , al ;

		sti ;

		iret ;

_init_timer:
	push es ;

		cli ;

		mov ax , 0 ;
		mov es , ax ;

		mov bx , _timer_irq ;
		mov word ptr es:[32] , bx ;
		mov word ptr es:[34] , cs ;

		sti ;

	pop es ;
	ret ;

END
