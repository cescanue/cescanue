; ft_strdup.s
; Duplica una cadena de caracteres usando malloc
global ft_strdup
extern ft_strlen
extern ft_strcpy
extern malloc

section .text

ft_strdup:
    ; Entrada:
    ;   rdi - puntero a la cadena original
    ; Salida:
    ;   rax - puntero a la nueva cadena o NULL en caso de error
    
    push rbp              ; Establecer stack frame
    mov rbp, rsp
    push rbx             ; Guardar rbx (callee-saved register)
    
    mov rbx, rdi         ; Guardar el puntero original en rbx
    
    ; Calcular longitud de la cadena
    call ft_strlen       ; Llamar a ft_strlen
    ; rax = longitud de la cadena
    inc rax              ; Añadir 1 para el carácter nulo
    
    ; Llamar a malloc
    mov rdi, rax         ; Primer argumento: tamaño para malloc
    call malloc wrt ..plt ; Llamar a malloc usando PLT
    ; rax = puntero a la nueva cadena
    
    test rax, rax        ; Verificar si malloc devolvió NULL
    je strdup_error      ; Si es NULL, saltar al manejo de error
    
    ; Copiar la cadena
    mov rdi, rax         ; Primer argumento: destino (malloc pointer)
    mov rsi, rbx         ; Segundo argumento: origen (cadena original)
    call ft_strcpy       ; Llamar a ft_strcpy
    
    pop rbx              ; Restaurar rbx
    leave               ; Restaurar stack frame
    ret                 ; Devolver rax (puntero a la nueva cadena)

strdup_error:
    mov rcx, fs:0x18     ; Obtener dirección de errno desde TLS
    mov dword [rcx], 12  ; Código de error ENOMEM
    xor rax, rax         ; Devolver NULL
    pop rbx              ; Restaurar rbx
    leave               ; Restaurar stack frame
    ret                 ; Retornar