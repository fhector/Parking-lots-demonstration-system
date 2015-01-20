;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;; Copyright (c) 2004-2007 threewater@up-tech.com, All rights reserved.
;;; 
;;; Startup Code for
;;;        HMS7202 : pagetable.s
;;;; by threewater	2004.5.17
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

        AREA	PageTable, DATA, NOINIT

        EXPORT L0PageTable

L0PageTable	SPACE	4096*4		;page size=(4G/1M) *4 byte

        END
