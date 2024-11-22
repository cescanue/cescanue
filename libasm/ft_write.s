global ft_write

section .text

ft_write:
    ; Entrada:
    ;   rdi - fd
    ;   rsi - buf
    ;   rdx - count
    ; Salida:
    ;   rax - número de bytes escritos o -1 en caso de error

    mov rax, 1            ; Número de syscall para write
    syscall               ; Invocar syscall

    cmp rax, -4095        ; Verificar si hay error (-errno)
    jb write_success      ; Si rax >= -4095, no hay error
    neg rax               ; Convertir código de error a positivo
    mov rcx, fs:0x18      ; Obtener dirección de errno desde TLS
    mov [rcx], eax        ; Establecer errno
    mov rax, -1           ; Devolver -1 en caso de error
write_success:
    ret                   ; Devolver número de bytes escritos
