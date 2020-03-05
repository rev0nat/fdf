/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 15:15:34 by aguillot          #+#    #+#             */
/*   Updated: 2018/10/22 15:15:37 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "../libft/libft.h"

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

typedef struct 	s_param
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_coordinates	*coordinates;
}				t_param;

#endif