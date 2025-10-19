# This file contains scanning in values, performing simple operations and
# printing results/messages.

# This program takes in n <= MAX_SIZE values (given by user) and a command 
# (either 'm' or 's'). The program computes the result and prints the result.

# Uses for $v0:
# https://courses.missouristate.edu/kenvollmar/mars/help/syscallhelp.html

MAX_SIZE = 10

.data
init_prompt1:   .asciiz "How many numbers: "
init_prompt2:   .asciiz "Command: "
init_prompt3:   .asciiz "Enter the values: "
too_many_err:   .asciiz "Error: That number is too high.\n"
too_small_err:  .asciiz "Error: That number is too low.\n"
bad_cmd_err:    .asciiz "Error: Not a vaid command.\n"
result:         .asciiz "Result: "

.align 2
numbers:        .word 0:MAX_SIZE * 4


.text
main:
begin_main:
        li      $v0, 4                  # Set v0 to 4 to print string
        li      $a0, init_prompt1
        syscall

        li      $v0, 5                  # Set v0 to 5 to scanf int
        syscall

        move    $s0, $v0                # Store n in s0

if0:
        blt	$s0, 1, error_small	        # If the number is too small
        bgt	$s0, MAX_SIZE, error_big	# If the number is too big
end0:
        li      $v0, 4
        li      $a0, init_prompt3
        syscall


        li      $t1, 0                  # Setting iterator
loop_read:
        bge     $t1, $s0, end_read

        li   $v0, 5                     #   scanf("%d", &numbers[i]);
        syscall                         

        mul     $t2, $t1, 4             # Int size is 4, so 4*i steps into numbers
        la      $t3, numbers
        add     $t4, $t3, $t2
        sw      $v0, ($t4)              # Store int

        addi    $t1, $t1, 1
        j       loop_read
end_read:

        li      $v0, 4                  # Set v0 to 4 to print string
        li      $a0, init_prompt2
        syscall

        li      $v0, 12                 # Scan in a character
        syscall

        move    $s1, $v0

if1:
        beq	$s1, 's', command_s	# If the number is too small
        beq	$s1, 'p', command_p	# If the number is too big


        li      $v0, 4                  # Set v0 to 4 to print string
        li      $a0, bad_cmd_err
        syscall

        j       end0

command_s:
        li      $t0, 0                  # Sum
        li      $t1, 0                  # Iterator
loop_s:
        bge     $t1, $s0, end_result

        mul     $t2, $t1, 4             # Int size is 4, so 4*i steps into numbers
        la      $t3, numbers
        add     $t4, $t3, $t2
        lw      $t5, ($t4)              # load int

        add     $t0, $t5, $t0

        addi    $t1, $t1, 1
        j       loop_s

command_p:
        li      $t0, 1                  # Prod
        li      $t1, 0                  # Iterator
loop_p:
        bge     $t1, $s0, end_result

        mul     $t2, $t1, 4             # Int size is 4, so 4*i steps into numbers
        la      $t3, numbers
        add     $t4, $t3, $t2
        lw      $t5, ($t4)              # Load int

        mul     $t0, $t5, $t0

        addi    $t1, $t1, 1
        j       loop_p

error_big:
        li      $v0, 4                  # Set v0 to 4 to print string
        li      $a0, too_many_err
        syscall
        j       begin_main

error_small:
        li      $v0, 4                  # Set v0 to 4 to print string
        li      $a0, too_small_err
        syscall
        j       begin_main

end_result:
        li      $v0, 4
        li      $a0, result
        syscall

        li      $v0, 1
        move    $a0, $t0
        syscall

        li      $v0, 11
        li      $a0, '\n'
        syscall

end_main:
    li   $v0, 0
    jr   $ra              # return

