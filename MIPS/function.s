# Terrible program example but at least you know how functions work

# Simple program to show how a function is set up.


.data
prompt_1:       .asciiz "Enter a value: "
prompt_2:       .asciiz "Enter another value: "
result_1:         .asciiz "These values add to give "
result_2:         .asciiz ".\n"


.text
main:
        begin
        push    $ra
        li      $v0, 4
        li      $a0, prompt_1
        syscall

        li      $v0, 5
        syscall

        move    $a1, $v0

        li      $v0, 4
        li      $a0, prompt_2
        syscall

        li      $v0, 5
        syscall

        move    $t0, $v0

        li      $v0, 4
        li      $a0, result_1
        syscall

        move    $a0, $t0

        jal     sum_numbers

        move    $a0, $v0
        li      $v0, 1
        syscall

        li      $v0, 4
        li      $a0, result_2
        syscall

        pop     $ra
        end
        li      $v0, 0
        jr      $ra




.text
sum_numbers:
        # Args:
        # - $a0: int
        # - $a1: int
        # Returns:
        # - $v0: int

        # Frame:        [$s0]
        # These are the registers stored on the stack

        # Uses:         [$a0, $a1, $v0, $s0, $t0, $t1]
        # All the registers used

        # Clobbers:     [$v0, $t0, $t1]
        # These are the values that will be lost

        # Locals:
        # - $s0: stores the value of $a0
        # - $t0: runs as an iterator
        # - $t1: will be returned after values are added to it

sum_numbers__prologue:
        begin                   # Move frame pointer
        push    $ra
        push    $s0             # | $s0 $ra

        move    $s0, $a1
        li      $t0, 0
        move    $t1, $a0

sum_numbers__loop:
        bge	$t0, $s0, sum_numbers__end
        
        addi    $t1, $t1, 1

        addi    $t0, $t0, 1
        j       sum_numbers__loop
sum_numbers__end:
        move    $v0, $t1

sum_numbers__epilogue:
        pop     $s0     # | $s0 $ra
        pop     $ra
        end
        jr      $ra