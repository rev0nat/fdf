/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 17:56:00 by aguillot          #+#    #+#             */
/*   Updated: 2020/03/10 18:19:43 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


//test de wikipedia via stackoverflow.
/*int toIsometric2D(double x, double y,double z, double *u, double*v){
    *u=(x-z)/sqrt(2);
    *v=(x+2*y+z)/sqrt(6);
    return 0;
}*/

static void	ft_draw_line(t_param *params, t_point start, t_point finish)
{
	int x = sqrt(2)/2 * (start.x - start.y);
	int xx = sqrt(2)/2 * (finish.x - finish.y);
	int y = (sqrt(2/3) * start.z) - (1 / sqrt(6)) * (start.x + start.y);
	int yy = (sqrt(2/3) * finish.z) - (1 / sqrt(6)) * (finish.x + finish.y);

	/*int x = start.x;
	int y = start.y;
	int xx = finish.x;
	int yy = finish.y;*/
	int dx = xx - x;
	int dy = yy - y;
	int incx = (dx > 0) ? 1 : -1;
	int incy = (dy > 0) ? 1 : -1;
	dx = abs(dx);
	dy = abs(dy);
	int cumul = 0;
	int i = 1;

	/*printf("x: %f, y: %f, xx: %f, yy: %f\n", x, y, xx, yy);
	printf("dx: %f\n", dx);
	printf("dy: %f\n", dy);*/
	printf("dx: %d, dy: %d\n", dx, dy);
	mlx_pixel_put(params->mlx_ptr, params->win_ptr, x + 500, y + 500, 0xb5f7b4);
	if (dx > dy)
	{
		cumul = dx / 2;
		//printf("dans le if (dx > dy): dx: %f, dy: %f\n", dx, dy);
		while (i <= dx)
		{
			x += incx;
			cumul += dy;
			if (cumul >= dx)
			{
				cumul -= dx;
				y += incy;
			}
			//printf("x: %f, y: %f\n", x, y);
			mlx_pixel_put(params->mlx_ptr, params->win_ptr, x + 500, y + 500, 0xb5f7b4);
			i++;
		}
	}
	else
	{
		cumul = dy /2;
		//printf("toto\n");
		//printf("i: %d, dx: %f\n", i, dx);
		while (i <= dy)
		{
			y += incy;
			cumul += dx;
			if (cumul >= dy)
			{
				cumul -= dy;
				x += incx;
			}
			//printf("x: %f, y: %f\n", x, y);
			mlx_pixel_put(params->mlx_ptr, params->win_ptr, x + 500, y + 500, 0xb5f7b4);
			i++;
		}
	}
}

void		ft_draw(t_param *params)
{
	t_point	*points;
	int		i;

	points = params->map->point;
	i = 1;
	while (i < params->map->xmax)
	{
		ft_draw_line(params, points[i - 1], points[i]);
		i++;
	}
}
