#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

.section .text,"ax"
.cpu cortex-m3
.thumb
.syntax unified

.global funcexo1

.thumb_func

/*
int fibo (int n)
    {
    if (n > 1)
     return (fibo(n–1) + fibo(n–2));
    else
     return 1;
    };
*/
funcexo1:
fibo:
		subs r0,#1		// r0 = n-1; (r0: argument)
		bgt rcall	 	// goto rec if (n-1 > 0)
					    // else
		mov r0,#1	 	// r0 = 1 (returned value)
		bx  lr  		// return
rcall:
		push  {r0,lr}	// save n-1 and lr before recursive call
        bl  fibo	 	// r0 = fibo(n-1);
		push  {r0}		// put result on stack which contains: fibo(n-1), n-1, lr
		ldr r0,[sp,#4]	// get n-1 (in r0)
		sub r0,#1		// prepare n-2
		bl fibo			// r0 = fibo(n-2);

		pop {r1,r2,lr}  // pop fibo(n-1) (in r1)
						// pop n (in r2, unused)
						// pop return address (lr)
		add r0,r1		// r0 = fibo(n-1)+fibo(n-2)
		bx  lr  		// return


//.weak add_sat
.ltorg
