; ft_read.s
; Lee datos de un descriptor de archivo.

global ft_read

section .text

ft_read:
    ; Entrada:
    ;   rdi - fd
    ;   rsi - buf
    ;   rdx - count
    ; Salida:
    ;   rax - número de bytes leídos o -1 en caso de error

    mov rax, 0            ; Número de syscall para read
    syscall               ; Invocar syscall

    test rax, rax         ; Verificar si hay error (rax < 0)
    jge read_success      ; Si rax >= 0, no hay error
    neg rax               ; Convertir código de error a positivo
    mov rcx, fs:0x18      ; Obtener dirección de errno desde TLS
    mov [rcx], eax        ; Establecer errno
    mov rax, -1           ; Devolver -1 en caso de error
read_success:
    ret                   ; Devolver número de bytes leídos
