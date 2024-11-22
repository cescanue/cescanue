; ft_strcpy.s
; Copia una cadena de origen a destino.

global ft_strcpy
section .text

ft_strcpy:
    ; Entrada:
    ;   rdi - puntero al destino
    ;   rsi - puntero al origen
    ; Salida:
    ;   rax - puntero al destino

    push rdi              ; Guardar rdi para devolverlo después

strcpy_loop:
    mov al, [rsi]         ; Cargar byte del origen en al
    mov [rdi], al         ; Almacenar byte en el destino
    inc rsi               ; Avanzar origen
    inc rdi               ; Avanzar destino
    cmp al, 0             ; ¿Es el carácter nulo?
    jne strcpy_loop       ; Si no es nulo, continuar copiando

    pop rax               ; Restaurar puntero al destino en rax
    ret                   ; Devolver
