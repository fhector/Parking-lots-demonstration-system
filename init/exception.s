;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;; Copyright (c) 2004-2007 threewater@up-tech.com, All rights reserved.
;;; 
;;; Startup Code for
;;;        S3C2410 : exception.s
;;;; by threewater	2005.2.23
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; Start here
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

	AREA    exception,CODE,READONLY
	IMPORT __use_no_semihosting_swi
	ENTRY
		
	IMPORT	ColdReset
	IMPORT	Enter_UNDEF
	IMPORT	Enter_SWI
	IMPORT	Enter_PABORT
	IMPORT	Enter_DABORT
	IMPORT	IRQ_Handler
	IMPORT	Enter_FIQ

	ldr	pc, =ColdReset		;reset
	ldr	pc, =Enter_UNDEF	;UndefinedInstruction
	ldr	pc, =Enter_SWI		;syscall_handler or SWI
	ldr	pc, =Enter_PABORT	;PrefetchAbort
	ldr	pc, =Enter_DABORT	;DataAbort
	b	.			;ReservedHandler
	ldr	pc, =IRQ_Handler	;IRQHandler
	ldr	pc, =Enter_FIQ		;FIQHandler
			
	LTORG	;for save exception address

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;; End of exception.c
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

			END
