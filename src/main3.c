/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 13:06:42 by aguillot          #+#    #+#             */
/*   Updated: 2018/10/22 14:48:30 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "../include/fdf.h"
#include <math.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>



int TraceSegmentMouseGeneral(t_param *params)
{
	t_coordinates *coor = params->coordinates;
	int dx = coor->dx;
	int dy = coor->dy;
	int incx = (dx > 0) ? 1 : -1;
	int incy = (dy > 0) ? 1 : -1;
	dx = abs(dx);
	dy = abs(dy);
	int cumul = 0;
	int i = 1;

	mlx_pixel_put(params->mlx_ptr, params->win_ptr, coor->x, coor->y, 0xb5f7b4);
	if (dx > dy)
	{
		cumul = dx / 2;
		while (i <= dx)
		{
			coor->x += incx;
			cumul += dy;
			if (cumul >= dx)
			{
				cumul -= dx;
				coor->y += incy;
			}
			mlx_pixel_put(params->mlx_ptr, params->win_ptr, coor->x, coor->y, 0xb5f7b4);
			i++;
		}
	}
	else
	{
		cumul = dy /2;
		while (i <= dy)
		{
			coor->y += incy;
			cumul += dx;
			if (cumul >= dy)
			{
				cumul -= dy;
				coor->x += incx;
			}
			mlx_pixel_put(params->mlx_ptr, params->win_ptr, coor->x, coor->y, 0xb5f7b4);
			i++;
		}
	}
	return (0);
}

void TracerLigne(t_param *params)
{
  	int 			dx;
	int				dy;
	int				i;
	int 			xinc;
	int 			yinc;
	int 			cumul;
	int 			x;
	int 			y;
	t_coordinates 	*coor;
	void			*mlx_ptr = params->mlx_ptr;
	void			*win_ptr = params->win_ptr;
	coor = params->coordinates;
  	x = coor->x;
 	y = coor->y ;
  	dx = coor->xx - coor->x ;
  	dy = coor->yy - coor->y ;
 	xinc = ( dx > 0 ) ? 1 : -1 ;
  	yinc = ( dy > 0 ) ? 1 : -1 ;
  	dx = abs(dx) ;
  	dy = abs(dy) ;
	mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0x32a8a8);
  	if ( dx > dy )
	{
    	cumul = dx / 2 ;
    	for ( i = 1 ; i <= dx ; i++ )
		{
      		x += xinc;
      		cumul += dy;
      		if ( cumul >= dx )
			{
        		cumul -= dx;
        		y += yinc;
			}
			mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0x32a8a8);
		}
	}
    else
	{
    	cumul = dy / 2 ;
    	for ( i = 1 ; i <= dy ; i++ )
		{
     		y += yinc ;
      		cumul += dx ;
      		if ( cumul >= dy )
			{
        		cumul -= dy ;
        		x += xinc ;
			}
			mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0x32a8a8);
		}
	}
}

//fonction qui va tracer un trait d'un clic à l'autre
int FillMouseParams(int x, int y, t_param *params)
{
	if (!(params->coordinates->x) && !(params->coordinates->y))
	{
		params->coordinates->x = x;
		params->coordinates->y = y;
		printf("c->x: %d, c->y: %d\n", params->coordinates->x, params->coordinates->y);
		return (1);
	}
	params->coordinates->xx = x;
	params->coordinates->yy = y;
	printf("c->XX: %d, c->YY: %d\n", params->coordinates->xx, params->coordinates->yy);
	params->coordinates->dx = (params->coordinates->xx) - (params->coordinates->x);
	params->coordinates->dy = (params->coordinates->yy) - (params->coordinates->y);
	params->coordinates->incre = 2 * (params->coordinates->dy);
	params->coordinates->incree = 2 * (params->coordinates->dx - params->coordinates->dy);
	params->coordinates->e = 2 * (params->coordinates->dx) - (params->coordinates->dy);
	//TracerLigne(params);
	TraceSegmentMouseGeneral(params);
	return (0);
}

//Faire une fonction qui va tracer une droite d'un clic de la souris à l'autre
int ft_mouse_hook(int button, int x,int y, t_param *params)
{
	(void)button;
	if (FillMouseParams(x, y, params) == 0)
	{
		ft_bzero(params->coordinates, sizeof(t_coordinates));
	}
	return (0);
}

int	main()
{
	void			*mlx_ptr;
	void			*win_ptr;
	int 			sx;
	t_param			*params;
	t_coordinates 	*coordinates;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 1000, 1000, "fdf");
	//LEAK

	if (!(coordinates = (t_coordinates*)malloc(sizeof(t_coordinates))))
	{
		perror("");
		exit(1);
		//errors_controller(MALLOC_ERROR);
	}
	ft_bzero(coordinates, sizeof(t_coordinates));
	if (!(params = (t_param*)malloc(sizeof(t_param))))
	{
		perror("");
		exit(1);
		//errors_controller(MALLOC_ERROR);
	}
	ft_bzero(params, sizeof(t_param));
	params->mlx_ptr = mlx_ptr;
	params->win_ptr = win_ptr;
	params->coordinates = coordinates;
	sx = mlx_string_put(mlx_ptr, win_ptr, 0, 0, 2392020, "tm");
	mlx_mouse_hook(win_ptr, ft_mouse_hook, params);
	mlx_loop(mlx_ptr);

	return (0);
}