/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 11:50:04 by cescanue          #+#    #+#             */
/*   Updated: 2023/06/29 21:20:56 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../mlx/includes/mlx.h"
# include "../mlx/ft_printf/includes/ft_printf.h"
# include "../mlx/ft_printf/libft/includes/libft.h"
# include <fcntl.h>

# define MAX_FDS 4096
# define BUFFER_SIZE 1024
# define SS 32
# define SPEED 8
# define NUMBERSW 8
# define NUMBERSH 32
# define TIMEL 250
# define NENEMIES 35
# define LIVES 4
# define NFIRES 6

typedef struct s_point
{
	int	y;
	int	x;
}	t_point;	

typedef struct s_gimg
{
	void	*img;
	int		y;
	int		x;
	int		d;
}	t_gimg;

typedef struct s_img
{
	void	*img;
	void	*mlx;
	int		w;
	int		h;
}	t_img;

typedef struct s_data
{
	void			*mlx;
	void			*mlx_win;
	char			**map;
	char			**mapcheck;
	int				mapx;
	int				mapy;
	int				maperror;
	int				maperrorway;
	int				mapc;
	int				mape;
	int				mapp;
	int				py;
	int				px;
	int				pmv;
	long			ets;
	long			etns;
	unsigned long	seed;
	unsigned long	cpuc;
	int				lives;
	int				tlives;
	int				tawards;
	t_list			**awards;
	t_list			**enemy;
	t_list			**exit;
	t_list			**ground;
	t_list			**ostacles;
	t_list			**fire;
	t_list			**pup;
	t_list			**pdown;
	t_list			**pright;
	t_list			**pleft;
	t_list			**heart;
	t_list			**gground;
	t_list			**gawards;
	t_list			**gostacles;
	t_list			**gexit;
	t_list			**gp;
	t_list			**genemies;
	t_list			**gfire;
	t_list			**numbers;
}	t_data;

char			*get_next_line(int fd);
void			ft_error(char *error, t_data *d);
void			ft_loadmap(char *map, t_data *d);
void			ft_loadmapcheck(char *map, t_data *d);
void			ft_map_count_lines(char *map, t_data *d);
void			ft_clearmem(t_data *data);
void			ft_printmap(t_data *d);
void			ft_checkmapwallsud(t_data *d);
void			ft_checkmapwallsm(t_data *d);
void			ft_checkmapmin(t_data *d);
void			ft_checkmap(t_data *d);
void			ft_initdata(t_data *d);
void			ft_loadimgs(char *path, t_list **lst, t_data *d);
void			ft_putimgtolst(char *file, t_list **lst, t_data *d);
void			ft_dellsti(void *img);
void			ft_dellstg(void *img);
void			ft_clearlsti(t_list **lst);
void			ft_clearlstg(t_list **lst);
void			ft_loadallimgs(t_data *data);
void			ft_init_windows(t_data *d);
void			ft_game(t_data *d);
void			ft_printglst(t_list *lg, t_data *d);
void			ft_generateglst(char type, t_list **lg, t_list *li, t_data *d);
int				key_hook(int key, t_data *d);
int				keyrelease_hook(int key, t_data *d);
int				exit_hook(t_data *d);
int				hook_loop(t_data *d);
void			ft_clearmemlsts1(t_data *data);
void			ft_clearmemlsts(t_data *data);
void			ft_generateallglst(t_data *d);
void			ft_printallglst(t_data *d);
void			ft_move_p(int key, t_data *d);
void			ft_move_prelease(int key, t_data *d);
t_list			*ft_checkcolisionlst(t_gimg *p, t_list *o, int precision);
int				ft_checkcolision(t_gimg *p, t_gimg *o, int precision);
void			ft_checkawards(t_data *d);
void			ft_lstdelonem(t_list **head, t_list *lst, void (*del)(void*));
void			ft_checkexit(t_data *d);
void			ft_checkmapway(int y, int x, t_data *d);
void			ft_printmo(t_data *d);
unsigned int	ft_rand(unsigned long *seed);
void			ft_generateenemies(t_data *d);
void			ft_moveenemies(t_data *d);
void			ft_print_lives(t_data *d);
t_img			*ft_getimglst(int pos, t_list *lst);
void			ft_print_awardsn(t_data *d);
void			ft_generafirelst(t_data *d);
void			ft_animationfire(t_data *d);
void			ft_nextsp(t_gimg *p, t_list *pi);
void			ft_checkfire(t_data *d);

#endif