.section .data
.str: 
	.ascii "%d\n\000"
.section .text
cs_totalnum_void: 
	mov ip, sp  
	stmfd sp!, {fp,ip,lr,pc}  
	sub fp, ip, #4 
	sub sp, sp, #4 
	str r1, [fp,#-16]  
	ldr r0, [fp,#-16]  
	ldr r0,[r0,# 4 ] 
	ldr r1, [fp,#-16]  
	ldr r1,[r1,# 8 ] 
	add r2, r0, r1 
	mov r0, r2  
	ldmea fp, {fp,sp,pc}  
cs_stunum_void: 
	mov ip, sp  
	stmfd sp!, {fp,ip,lr,pc}  
	sub fp, ip, #4 
	sub sp, sp, #4 
	str r1, [fp,#-16]  
	ldr r2,[r1,# 4 ] 
	cmp r2,#0   
	movgt r0, r2  
	ldmea fp, {fp,sp,pc}  
upc_upc_void: 
	mov ip, sp  
	stmfd sp!, {fp,ip,lr,pc}  
	sub fp, ip, #4 
	sub sp, sp, #4 
	str r1, [fp,#-16]  
	ldr r0, [fp,#-16]  
	ldr r1, =upc_totalnum_void  
	str r1, [r0]  
	ldr r2, [r0,#4]  
	ldr r3, [fp,#4]  
	str r3, [r0,#4]  
	ldr r2, [r0,#8]  
	ldr r3, [fp,#8]  
	str r3, [r0,#8]  
	ldmea fp, {fp,sp,pc}  
	.global main
main: 
	mov ip, sp  
	stmfd sp!, {fp,ip,lr,pc}  
	sub fp, ip, #4 
	sub sp, sp, #80 
	ldr r0,= -24  
	sub r1, fp, r0 
	ldr r0,= 3000  
	stmfd sp!, {r0}  
	ldr r0,= 20000  
	stmfd sp!, {r0}  
	bl upc_upc_void   
	add sp, sp, #8 
	ldr r0,= -24  
	sub r1, fp, r0 
	bl upc_stunum_void   
	str r0,[fp,# -28 ] 
	ldr r0, =.str  
	ldr r1,[fp,# -28 ] 
	bl printf   
	ldr r0,= -24  
	sub r1, fp, r0 
	bl upc_teanum_void   
	str r0,[fp,# -32 ] 
	ldr r0, =.str  
	ldr r1,[fp,# -32 ] 
	bl printf   
	ldr r0,= -36  
	sub r1, fp, r0 
	ldr r0,= 300  
	stmfd sp!, {r0}  
	ldr r0,= 2000  
	stmfd sp!, {r0}  
	bl cs_cs_void   
	add sp, sp, #8 
	ldr r0,= -36  
	sub r1, fp, r0 
	bl cs_stunum_void   
	str r0,[fp,# -52 ] 
	ldr r0, =.str  
	ldr r1,[fp,# -52 ] 
	bl printf   
	ldr r0,= -36  
	sub r1, fp, r0 
	bl upc_teanum_void   
	str r0,[fp,# -56 ] 
	ldr r0, =.str  
	ldr r1,[fp,# -56 ] 
	bl printf   
	ldr r0,= -24  
	sub r1, fp, r0 
	ldr r2, [r1,#0]  
	ldr r3,= upc_totalnum_void  
	cmp r2, r3  
	bleq upc_totalnum_void   
	str r0,[fp,# -60 ] 
	ldr r0, =.str  
	ldr r1,[fp,# -60 ] 
	bl printf   
	sub r1, fp,# -36 
	str r1, [fp,# -64 ]
	ldr r2, [r1]  
	ldr r3,= cs_totalnum_void  
	cmp r2, r3  
	bleq cs_totalnum_void   
	str r0,[fp,# -64 ] 
	ldr r0, =.str  
	ldr r1,[fp,# -64 ] 
	bl printf   
	ldmea fp, {fp,sp,pc}  
cs_cs_void: 
	mov ip, sp  
	stmfd sp!, {fp,ip,lr,pc}  
	sub fp, ip, #4 
	sub sp, sp, #4 
	str r1, [fp,#-16]  
	ldr r0, [fp,#-16]  
	ldr r1, =cs_totalnum_void  
	str r1, [r0]  
	ldr r2, [r0,#4]  
	ldr r3, [fp,#4]  
	str r3, [r0,#4]  
	ldr r2, [r0,#8]  
	ldr r3, [fp,#8]  
	str r3, [r0,#8]  
	ldmea fp, {fp,sp,pc}  
cs_teanum_void: 
	mov ip, sp  
	stmfd sp!, {fp,ip,lr,pc}  
	sub fp, ip, #4 
	sub sp, sp, #4 
	str r1, [fp,#-16]  
	ldr r2,[r1,# 8 ] 
	cmp r2,#0   
	movgt r0, r2  
	ldmea fp, {fp,sp,pc}  
upc_totalnum_void: 
	mov ip, sp  
	stmfd sp!, {fp,ip,lr,pc}  
	sub fp, ip, #4 
	sub sp, sp, #4 
	str r1, [fp,#-16]  
	ldr r0, [fp,#-16]  
	ldr r0,[r0,# 4 ] 
	ldr r1, [fp,#-16]  
	ldr r1,[r1,# 8 ] 
	add r2, r0, r1 
	mov r0, r2  
	ldmea fp, {fp,sp,pc}  
upc_teanum_void: 
	mov ip, sp  
	stmfd sp!, {fp,ip,lr,pc}  
	sub fp, ip, #4 
	sub sp, sp, #4 
	str r1, [fp,#-16]  
	ldr r2,[r1,# 8 ] 
	cmp r2,#0   
	movgt r0, r2  
	ldmea fp, {fp,sp,pc}  
upc_stunum_void: 
	mov ip, sp  
	stmfd sp!, {fp,ip,lr,pc}  
	sub fp, ip, #4 
	sub sp, sp, #4 
	str r1, [fp,#-16]  
	ldr r2,[r1,# 4 ] 
	cmp r2,#0   
	movgt r0, r2  
	ldmea fp, {fp,sp,pc}  

















