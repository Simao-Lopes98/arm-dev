/* startup.S */

// Crucial to set the Thumb bit to 1 on the Reset_Handler
.thumb
.thumb_func

.global Reset_Handler
.extern main

// Reset handler - 1st register on the Stack
Reset_Handler:

    // Pointing to the beginning of the stack is done in vector stable
    
    // Clear bss
    LDR R1, =_sbss      // Load _sbss to R1
    LDR R2, =_ebss      // load _ebss to R2
    LDR R0, =0          // load zero

clearBss:
    SUB R3, R2, R1
    CMP R3, #0      // BSS is cleared
    BEQ bssCleared
    STR R0, [R1]    // Store the value in R0 to the address in R1.
    ADD R1, R1, #4  // Incrment R1 by 4 bytes (32 bits)
    B clearBss      // loop back to clearBss

bssCleared:
    
    // Copy data contents from Flash to RAM
    LDR R1, =_sdata
    LDR R2, =_edata
    LDR R3, =_la_data

copyData:
    SUB R4, R2, R1
    CMP R4, #0
    BEQ dataCopied
    LDR R0, [R3]
    STR R0, [R1]
    ADD R1, R1, #4
    ADD R3, R3, #4
    B copyData

dataCopied:
    BL main

hang:
    B hang


