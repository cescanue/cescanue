/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 12:47:29 by cescanue          #+#    #+#             */
/*   Updated: 2023/05/02 16:44:49 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

# define MAX_FDS 4096
# define BUFFER_SIZE 4096

typedef struct s_list
{
	int				nbr;
	int				index;
	struct s_list	*next;
}	t_list;

typedef struct s_data
{
	t_list	**lsta;
	t_list	**lstb;
	int		lstsize;
	int		split;
	int		spsize;
	int		spsizel;
	int		maxc;
	int		maxlstsize;
	int		mov;
	int		print;
}	t_data;

typedef struct s_find
{
	int	index;
	int	pos;
}	t_find;

typedef struct s_toa
{
	int		index;
	int		index2;
	int		d;
	int		dd;
	t_find	f;
	t_find	l;
	t_find	f1;
	t_find	f2;
}	t_toa;

char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(const char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_split_g(int fd, char **pbuffers);
char	*get_next_line(int fd);
void	ft_toa_o1(t_data *data, t_toa *t);
void	ft_toa_o1_2(t_data *data, t_toa *t);
void	ft_dupdataint(t_data *d, t_data *dup);
t_data	ft_dupdata(t_data *d);
void	ft_toa_o2(t_data *data, t_toa *t);
void	ft_toa_o3(t_data *data, t_toa *t);
t_toa	ft_getdata(t_data *data);
int		ft_max(t_data *data);
t_find	ft_ffirst(int start, int end, t_list *lst);
t_find	ft_flast(int start, int end, t_list *lst);
void	ft_morder_tob(t_data *d);
void	ft_morder_toa(t_data *data);
void	ft_morder_split(t_data *data);
void	ft_morder(t_data *data);
void	ft_order3(t_data *data);
int		ft_findpos(int index, t_list *lst);
void	ft_order4(t_data *data);
void	ft_order5(t_data *data);
void	ft_interactive_choice(char *str, t_data *data);
void	ft_interactive_help(void);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_interactive(t_data *data);
int		ft_risordered(t_list *lst);
void	ft_radix(t_data	*data);
void	ft_generateindex(t_data	*data);
int		ft_rgetmaxbit(t_list *lst);
void	ft_rotate(t_list **lst);
void	ft_rrotate(t_list **lst);
void	ft_printlst(t_data	*data);
void	ft_swap(t_list *lst);
void	ft_sa(t_data *data);
void	ft_sb(t_data *data);
void	ft_ss(t_data *data);
void	ft_pa(t_data *data);
void	ft_pb(t_data *data);
void	ft_ra(t_data *data);
void	ft_rb(t_data *data);
void	ft_rr(t_data *data);
void	ft_rra(t_data *data);
void	ft_rrb(t_data *data);
void	ft_rrr(t_data *data);
void	ft_checkduplicateslsta(t_data *data);
void	ft_create_lst(t_data *data, int argc, char **argv);
void	ft_clearmem(t_data *data);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	ft_error(t_data *data, char *msg);
void	ft_putstr_fd(char *s, int fd);
int		ft_atoi(const char *str);
int		ft_isnbr(const char *str);
int		countwords(const char *s, char c);
char	**ft_split(char const *s, char c);
char	**ft_freea(char **astr);
void	*ft_memset(void *b, int c, size_t len);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstsecondlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst);
t_list	*ft_lstnew(int nbr, int index);
int		ft_lstsize(t_list *lst);

#endif