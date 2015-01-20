;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;; Copyright (c) 2004-2007 threewater@up-tech.com, All rights reserved.
;;; 
;;; Startup Code for
;;;        HMS7202 : Stack.s
;;;; by threewater	2004.4.26
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

        AREA    Stacks, DATA, NOINIT

        EXPORT UserStack
        EXPORT SVCStack
        EXPORT UndefStack
        EXPORT IRQStack
        EXPORT AbortStack
        EXPORT FIQStack

			SPACE	4096
UserStack	SPACE	4096
SVCStack	SPACE	4096
UndefStack	SPACE	4096
AbortStack	SPACE	4096
IRQStack	SPACE	4096
FIQStack	SPACE	4

        END
