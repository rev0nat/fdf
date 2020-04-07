/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 15:15:34 by aguillot          #+#    #+#             */
/*   Updated: 2020/03/10 16:42:16 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <mlx.h>

typedef struct 	s_coordinates
{
	int 		x;
	int			y;
	int 		xx;
	int			yy;
	int			dx;
	int			dy;
	int			incre;
	int			incree;
	int			e;
}				t_coordinates;


typedef struct	s_point
{
	int			x;
	int			y;
	int			z;
}				t_point;

typedef struct	s_map
{
	t_point		*point;
	int			xmax;
	int			ymax;
}				t_map;

typedef struct 	s_param
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_map			*map;
}				t_param;

void		ft_map_reader(char *filepath, t_map *map);
void		ft_fdf(char *filepath);
void		ft_fatal_exit(void);
void		ft_fatal_exit_putendl(char *str);
void		ft_draw(t_param *params);

#endif
