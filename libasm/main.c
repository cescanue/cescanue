// main.c
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

// Declaraciones de las funciones en ensamblador
size_t  ft_strlen(const char *s);
char    *ft_strcpy(char *dst, const char *src);
int     ft_strcmp(const char *s1, const char *s2);
ssize_t ft_write(int fd, const void *buf, size_t count);
ssize_t ft_read(int fd, void *buf, size_t count);
char    *ft_strdup(const char *s);

int main()
{
    // Prueba de ft_strlen
    const char *str = "Hola, mundo!";
    printf("ft_strlen: %zu\n", ft_strlen(str));
    printf("strlen: %zu\n", strlen(str));

    // Prueba de ft_strcpy
    char dest[50];
    ft_strcpy(dest, str);
    printf("ft_strcpy: %s\n", dest);

    // Prueba de ft_strcmp
    printf("ft_strcmp: %d\n", ft_strcmp("abc", "abd"));
    printf("strcmp: %d\n", strcmp("abc", "abd"));

    // Prueba de ft_write
    ssize_t ret = ft_write(1, "Escribiendo con ft_write\n", 25);
    printf("ft_write returned: %zd, errno: %d\n", ret, errno);

    // Prueba de ft_read
    char buffer[100];
    ret = ft_read(0, buffer, 10);
    if (ret >= 0)
    {
        buffer[ret] = '\0';
        printf("ft_read: %s\n", buffer);
    }
    else
    {
        perror("ft_read error");
    }

    // Prueba de ft_strdup
    char *dup = ft_strdup(str);
    if (dup)
    {
        printf("ft_strdup: %s\n", dup);
        free(dup);
    }
    else
    {
        perror("ft_strdup error");
    }

    return 0;
}
