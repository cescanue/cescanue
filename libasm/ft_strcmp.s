; ft_strcmp.s
; Compara dos cadenas de caracteres.

global ft_strcmp
section .text

ft_strcmp:
    ; Entrada:
    ;   rdi - puntero a la primera cadena
    ;   rsi - puntero a la segunda cadena
    ; Salida:
    ;   rax - resultado de la comparación

strcmp_loop:
    mov al, [rdi]         ; Cargar byte de s1 en al
    mov bl, [rsi]         ; Cargar byte de s2 en bl
    cmp al, bl            ; Comparar bytes
    jne strcmp_diff       ; Si son diferentes, saltar
    cmp al, 0             ; ¿Es fin de cadena?
    je strcmp_equal       ; Si ambos son nulos, cadenas iguales
    inc rdi               ; Avanzar en s1
    inc rsi               ; Avanzar en s2
    jmp strcmp_loop       ; Repetir

strcmp_diff:
    movzx eax, al         ; Extender al a 32 bits sin signo
    movzx ebx, bl         ; Extender bl a 32 bits sin signo
    sub eax, ebx          ; Calcular diferencia
    ret                   ; Devolver resultado

strcmp_equal:
    xor eax, eax          ; Cadenas iguales, devolver 0
    ret
