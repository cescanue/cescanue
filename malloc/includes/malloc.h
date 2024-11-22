/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 21:26:03 by cescanue          #+#    #+#             */
/*   Updated: 2024/11/07 12:51:22 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <pthread.h>
# include <sys/mman.h>
# include <unistd.h>
# include "../libft/libft.h"

# define TINY        1024UL
# define SMALL       15360UL
# define ALIGNMENT   16UL
# define ALIGN(size) (((size) + (ALIGNMENT - 1UL)) & ~(ALIGNMENT - 1UL))
# define MINBOOK     100UL

# define BLOCK_SIGNATURE 0xDEADBEEFCAFEBABEUL

typedef struct s_block
{
    size_t    signature;   
    size_t    size;        
    size_t    num;
    char      free;
    void      *next;
}   t_block;

typedef struct s_zones
{
    void    *tiny;
    void    *small;
    void    *large;
}   t_zone;

extern t_zone            g_zone;
extern pthread_mutex_t   g_mutex;

void    *malloc(size_t size);
void    free(void *ptr);
void    *realloc(void *ptr, size_t size);
void    show_alloc_mem(void);
void	show_alloc_mem_hex(void);

#endif
