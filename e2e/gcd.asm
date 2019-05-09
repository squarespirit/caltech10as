    ; Constants
    .const a 00     ; However, a is immediately loaded into the accumulator
    .const b 01

    ; Euclid's algorithm doesn't work if either a or b is zero.
    ; So we have to check these cases.
    LDD $a          ; If a == 0, go to ReturnZero
    CMPI 0
    JE ReturnZero   ; (Don't need NOP, next load is harmless)
    LDD $b          ; If b == 0, go to ReturnZero
    CMPI 0
    JE ReturnZero   ; (Don't need NOP, next load is harmless)
    ; Neither a nor b are zero. Go to main algorithm.
    LDD $a          ; Main loop assumes that a is in acc
    JMP EuclidLoop
    NOP
ReturnZero:
    LDI 0           ; Return zero in acc
    RTS

EuclidLoop:
SubLoop:            ; While acc >= b, acc -= b
    CMP $b          ; If acc < b, go to end of loop
    JB SubLoopEnd
    NOP
    SUB $b
    JMP SubLoop
    NOP
SubLoopEnd:
    CMPI 0          ; If acc != 0...
    ; We will branch later on this.
    ; The algorithm says to check "if b != 0" after swapping 
    ; acc and b, but we cannot compare b with an immediate
    ; value, so it is easiest to check the acc now.
    ; The following LD/STs don't change the flags.

    ; Swap b and acc by doing this:
    STD 2           ; Move acc to 02
    LDD $b          ; Move b to 03
    STD 3
    LDD 2           ; Move 02 to b
    STD $b
    LDD 3           ; Move 03 to acc

    JNE EuclidLoop  ; The destination address is 100 - E = F2
    NOP

    RTS
