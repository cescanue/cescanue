/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 20:06:54 by cescanue          #+#    #+#             */
/*   Updated: 2024/11/02 20:45:41 by cescanue         ###   ########.fr       */
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