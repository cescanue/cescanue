; ft_strlen.s
; Calcula la longitud de una cadena terminada en nulo.

global ft_strlen
section .text

ft_strlen:
    ; Entrada:
    ;   rdi - puntero a la cadena
    ; Salida:
    ;   rax - longitud de la cadena

    xor rax, rax          ; rax = 0 (contador)

strlen_loop:
    cmp byte [rdi], 0     ; ¿Es el carácter actual nulo?
    je strlen_end         ; Si es nulo, terminar
    inc rax               ; Incrementar contador
    inc rdi               ; Avanzar al siguiente carácter
    jmp strlen_loop       ; Repetir

strlen_end:
    ret                   ; Devolver longitud en rax
