# ; Begin with functions/executable code in the assmebly file via '.text' directive
#; MAKE SURE TO DELETE BEFORE TESTING
#; THERMO_SENSOR_PORT:
#	; .short 0
#; THERMO_DISPLAY_PORT:
#	; .int 0
#; THERMO_STATUS_PORT:
#	; .char 0
.data
ERROR_BOUND:  #bounds for error to check
	.int 28800
	.int 0
.text	
.global set_temp_from_ports
set_temp_from_ports:
        ## assembly instructions here
        movw  THERMO_SENSOR_PORT(%rip), %dx #moves the sensor to dx 
		movb  THERMO_STATUS_PORT(%rip), %cl   
		leaq  ERROR_BOUND(%rip), %r8
		cmpw 4(%r8),%dx  #if this is smaller then 0 jump to error 
		js .is_error
		cmpw %dx,(%r8)		#if this is greater then 28800 jump to error
		js .is_error
		andb $0b100,%cl
		movb $0b100, %r11b # i dont know why i did this
		cmpb %cl,%r11b  #if the status is error
		je .is_error
		movb  THERMO_STATUS_PORT(%rip), %cl   
		and $0b100000,%cl
		movb $0b100000, %r11b
		cmpb %cl,%r11b   #if the status is c or f
		je .isf
		jne .isc
		
.is_error:
	movb $3,2(%rdi)  # moves everything into arg one
	movw $0,(%rdi)
	movl $1, %eax  #ret 1
	ret
.isc:
#moves status into the status
	movb $1,2(%rdi)   
	#shift 5
	movb %dl, %r9b
	andb $0b11111,%r9b  # conversions
	sar $5,%dx			
	sub $450,%dx
	cmp $16,%r9b		
	#if remainder is greater then 16 take alternitive route
	jns .add1
	movw %dx,(%rdi)
	movl $0, %eax
	ret
.add1:
	inc %dx
	movw %dx,(%rdi)
	movl $0, %eax
    ret
.isf:
	movb $2,2(%rdi)  #change status to f
	movb %dl, %r9b 
	andb $0b11111,%r9b
	sar $5,%dx
	sub $450,%dx
	cmp $16,%r9b
	jns .add1f   	#alt route just adds one c
	imul $9, %dx   #beginning of f conversion
	movq $0,%rax #make sure it is zero
	movw %dx,%ax  #division prep   
	cwtl           # sign extend ax to long word
    cltq           # sign extend eax to quad word
    cqto           # sign extend rax to rdx 
	movq $5,%r11
	
	idivw %r11w    #dx is modifyied however we dont need it anymore
	add $320, %rax  #finished f conversion
	movw %ax,(%rdi)		
	movq $0, %rax
	ret
.add1f:
	inc %dx
	imul $9, %dx   #beginning of f conversion
	movw %dx,%ax  #division prep
	cwtl           # sign extend ax to long word
    cltq           # sign extend eax to quad word
    cqto           # sign extend rax to rdx 
	movw $5,%r11w
	idivw %r11w    #dx is modifyied however we dont need it anymore
	add $320, %rax  #finished f conversion
	movw %ax,(%rdi)		
	movq $0, %rax
    ret
#; a useful technique for this problem
 #       ; movX    SOME_GLOBAL_VAR(%rip), %reg   load global variable into register
	#										;  use movl / movq / movw / movb
     #                                        ;  and appropriately sized destination register
      #               ;  eventually return from the function
#
#;  Change to definine semi-global variables used with the next function 
#  via the '.data' directive
 .data
 	errange: 
		.short 1130
		.short -490
		.short 450
		.short -450
   iterater:  #used to iterate
		.int 0
		
	units:
		.int 0
		.int 0
		.int 0
		.int 0
 holder:  #used to hold positions/values                          #declare location an single integer named 'an_int'
      .int 0                #value 0
 	neghold:  #used to determine if the temp is negitive
		.int 0
   disptemp:
		.int 0 #used to hold the display
		
 mask:                      # this is the mask for the display  declare multiple ints sequentially starting at location
		 .int 0b1111011	
		 .int 0b1001000
		 .int 0b0111101
		 .int 0b1101101
		 .int 0b1001110
		 .int 0b1100111
		 .int 0b1110111
		 .int 0b1001001
		 .int 0b1111111
		 .int 0b1101111
		 .int 0b0110111
		 .int 0b1011111
		 .int 0b0000000
		 .int 0b0000100
		 .int 0b0110111
		 .int 0b1011111
		 .int 0b0000000
		 .int 0b0000100
#
#
#; Change back to defining functions/execurable instructions
  .text
  .global  set_display_from_temp
#
   set_display_from_temp:  
   #
   movq $1, %rax
   movl %edi,%r10d  #moves packed struct to r10
   leaq errange(%rip),%r9		#moves the error range values to r9
   leaq mask(%rip), %r11		#moves the array of masks to r11
   movl $0,(%rsi)		# clears out display might be random stuff in it
   shr $16, %r10			# shifts r10 to get the status
	
   cmpb $1,%r10b				#sees if it is one
   je .c
   cmpb $2,%r10b				# sees if it is two
   je .f
   je .error				#if its not one or two it will be an error
.error:  #moves certain bits into the display (rsi) to indicate error
	movq $2, %r9
	movl $0, %r8d
	movb $0b0110111,%r8b
	shl $7,%r8d
	or $0b1011111,%r8b
	shl $7,%r8d
	or $0b1011111,%r8b
	shl $7,%r8d
	movl %r8d,(%rsi)
	ret   
.f:
					
	 movq %rdi,%r10 #puts the temp back into r10
	 
	 cmpw %r10w, (%r9)		# if it is outside functioning range it will jump to error
	 js .error
	 cmpw 2(%r9),%r10w	    #same
	 js .error
	 #movb $0b0010, %r8b    #indicates fernenhight for the display	#shifts it to the last 4 bits
	 #movb %r8b,(%rsi)
	 jmp .assemble
.c:
	movq %rdi,%r10  # puts temp back into r10
	cmpw %r10w, 4(%r9)
	js .error
	cmpw 6(%r9),%r10w #if it is outside of the range will error
	js .error
	#movb $0b0001, %r8b
	#movb %r8b,(%rsi)
	jmp .assemble
.assemble:
	movq disptemp(%rip), %r9 # moves the mask to r9
	movl  holder(%rip),%r8d
	movw %r10w, %ax #moves the temp to rax for division
	movl  neghold(%rip), %r10d   #flag to see if it is negitive
	cmpw $0,%ax		#checks if temp is negitive if it is it jumps to a spot
	js .negate
.assemble2:
	cwtl           # sign extend ax to long word
    cltq           # sign extend eax to quad word
    cqto           # sign extend rax to rdx 
	movq $10,%rcx   # 
	idivw %cx						
	movb (%r11,%rdx,4),%r9b # everytime it is divieded by 10 it checks if it is negitive to indicate that it needs to stop and start assembling the mask into the display
	cmpw $1,%ax
	js .fin 
	inc %r8d
	
	shl $8,%r9d  # everytime it divides the mask is shifted 8 bites to the left to hold another mask
	cqto
	idivw %cx
	movb (%r11,%rdx,4),%r9b  # rdx holds the index for the mask the array of masks are held in r11 and it will move the mask into r9
	cmpw $1,%ax
	js .fin   # again checks if it is zero 
	shl $8,%r9d
	inc %r8d
	cqto	
	idivw %cx
	movb (%r11,%rdx,4),%r9b
	cmpw $1,%ax
	js .fin
	inc %r8d
	shl $8,%r9
	cqto
	idivw %cx
	movb (%r11,%rdx,4),%r9b
	cmpw $1,%ax
	js .fin
	inc %r8d
	
	orb %r9b, (%rsi)  # now that the mask is done it will begin putting it into the display
	cmpb $1,%r9b		#checks if mask is zero to avoid putting in junk in the display
	js .fin3
	shll $7,(%rsi)    #shifts the display left by 7 remember that there is an extra unused 0 bit at the end of every mask piece
	shr $8,%r9       #the r9 mask is in reverse order by inserting it in this way it reverses it to make it  the correct order
	
	cmpb $1,%r9b
	js .fin3    # fin3 just ret 0 if it is zero it needs to stop or else there will be a extra 7 bits of zero junk
	
	orb %r9b, (%rsi)
	cmpb $1,%r9b
	js .fin3
	shll $7,(%rsi)
	shr $8,%r9
	
	cmpb $1,%r9b
	js .fin3
	
	orb %r9b, (%rsi)
	cmpb $1,%r9b
	js .fin3
	shll $7,(%rsi)
	shr $8,%r9
	
	orb %r9b, (%rsi)
	jmp .check #check just adds the indicater that it is c or f
	movq $0, %rax
	ret
.negate:
	neg %ax   # ax is now good to divide
	inc %r10d   # trips the flag to tell it to go to an alternitive path
	jmp .assemble2
.fin:
	cmpl $1,%r10d
	jne .fin2   # r10 is the indication that we need to add a negitive sign
	
	shl $8, %r9
	movb $0b0000100,%r9b
	      # this function is to add the negitive sign at the end
	orb %r9b, (%rsi)
	shr $8,%r9
	cmpb $1,%r9b
	js .fin3  # all these functions jump to fin3 if there is nothing left to add to the display
	
	shll $7,(%rsi)
	orb %r9b, (%rsi)
	shr $8,%r9
	cmpb $1,%r9b
	js .fin3
	
	shll $7,(%rsi)
	orb %r9b, (%rsi)
	shr $8,%r9
	cmpb $1,%r9b
	js .fin3
	
	shll $7,(%rsi)
	orb %r9b, (%rsi)
		
	jmp .check
.fin2:
	
	cmpb $1,%r9b
	js .fin3
	
	orb %r9b, (%rsi)
	shr $8,%r9
	cmpb $1,%r9b
	js .fin3
	
	shll $7,(%rsi)
	orb %r9b, (%rsi)
	shr $8,%r9
	cmpb $1,%r9b
	js .fin3
	
	shll $7,(%rsi)
	orb %r9b, (%rsi)
	shr $8,%r9
	cmpb $1,%r9b
	js .fin3
	
	shll $7,(%rsi)
	orb %r9b, (%rsi)
	jmp .check

.check:
	
	movl %edi, %r10d
	shr $16, %r10			# shifts r10 to get the status
   cmpb $1,%r10b				#sees if it is one
   je .cf
   cmpb $2,%r10b				# sees if it is two
   je .ff
   movq $0, %rax
   ret
	
.fin3:
	jmp .check
.cf:
	 movq $0b001, %r8   #indicates fernenhight for the display	#shifts it to the last 4 bits
	 shl $28,%r8
	 or %r8d,(%rsi)
	 ret
.ff:
	 movq $0b0010, %r8   #indicates fernenhight for the display	#shifts it to the last 4 bits
	 shl $28,%r8
	 or %r8d,(%rsi)
	 ret
	 
#	; two useful techniques for this problem
 #       ; movl    an_int(%rip),%eax     load an_int into register eax
  #      ; leaq    an_array(%rip),%rdx   load pointer to beginning of an_array into edx
   #             ; ret                      eventually return from the function
#
.data
	temp_t:
		.short 0
		.short 0
 .text
  .global thermo_update
 thermo_update:
 
	leaq temp_t(%rip),%rdi  #rdi holds tempt this needs to happen because the first func needs a pointer
	subq $8,%rsp
	pushq %rbx # rbx and r12 hold the ret values for the functions
	pushq %r12
	call set_temp_from_ports
	movq temp_t(%rip),%rdi   # second function does not have a pointer
	movq %rax, %rbx
	leaq THERMO_DISPLAY_PORT(%rip), %rsi
	call set_display_from_temp
	movq %rax, %r12
	movq %rbx,%r8
	movq %r12,%r9   
	addq $8,%rsp
	pop %r12
	pop %rbx
	cmp $1,%r8
	je .fail
	cmp $1,%r9
	je .fail
	movq $0,%rax
	ret
	.fail:
	movq $1,%rax
	ret
	


