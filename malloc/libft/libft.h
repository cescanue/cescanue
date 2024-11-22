/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 11:41:44 by cescanue          #+#    #+#             */
/*   Updated: 2024/11/02 21:00:40 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int		ft_isalpha(int c);
int		ft_toupper(int c);
int		ft_isdigit(int c);
int		ft_tolower(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
size_t	ft_strlen(const char *s);
int		ft_isprint(int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void	*ft_lstfindcontent(t_list *lst, int (*find)(void *, int), int tofind);
void	*ft_lstfindlst(t_list *lst, int (*find)(void *, int), int tofind);
int		ft_isnbr(const char *str);

#endif

// Unified ft_printf declarations
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 20:06:54 by cescanue          #+#    #+#             */
/*   Updated: 2023/07/18 23:44:00 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include "libft.h"

//# define WRITEOUTPUT 2
# define MAX_MEM_VALUE 20480
# define BDECIMAL "0123456789"
# define BLHEXADECIMAL "0123456789abcdef"
# define BUHEXADECIMAL "0123456789ABCDEF"
# define TNIL "0x0"
# define TNULL "(null)"

typedef struct info
{
	int	flagminus;
	int	flagplus;
	int	flagspace;
	int	flagzero;
	int	flaghash;
	int	width;
	int	precision;
	int	setprecision;
	int	length;
	int	specifier;
	int	cprinted;
	int	sizevalue;
	int	ovalue;
	int	writeoutput;
}	t_info;

int		ft_printffd(int fd, char const *str, ...);
int		ft_printf(char const *str, ...);
void	ft_print(const char **str, t_info *info, va_list *ap);
void	ft_printvalue(char *value, t_info *info);
void	ft_initinfo(t_info *info);
int		ft_putstr(char *str, int size, t_info *info);
void	ft_parseinfo(const char **str, t_info *info);
void	ft_parseflag(const char **str, t_info *info);
void	ft_parsewidth(const char **str, t_info *info);
void	ft_parselength(const char **str, t_info *info);
void	ft_parseprecision(const char **str, t_info *info);	
void	ft_parsespecifier(const char **str, t_info *info);
char	*ft_getvalue(t_info *info, va_list *ap);
void	ft_valuetype(char *value, t_info *info, va_list *ap);
void	ft_getpercentage(char *value, t_info *info, va_list *ap);
void	ft_getc(char *value, t_info *info, va_list *ap);
void	ft_gets(char *value, t_info *info, va_list *ap);
void	ft_itoap2s(unsigned long nbr, char *base, char **value);
void	ft_itoa2s(long long nbr, char *base, char **value);
void	ft_itoaputchar(int nbr, char **value);
void	ft_getp(char *value, t_info *info, va_list *ap);
void	ft_getd(char *value, t_info *info, va_list *ap);
void	ft_getu(char *value, t_info *info, va_list *ap);
void	ft_getx(char *value, t_info *info, va_list *ap);
void	ft_formatgetsize(t_info *info, va_list *ap);
void	ft_format_width(char *value, t_info *info);
void	ft_format_hash(char *value, t_info *info);
void	ft_format_nprecision(char *value, t_info *info);
void	ft_format_nflags(char *value, t_info *info);
void	ft_format_nwidth(char *value, t_info *info);
void	ft_format_xwidth(char *value, t_info *info);

#endif