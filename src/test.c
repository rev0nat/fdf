static void	ft_draw_line(t_param *params, t_point start, t_point finish)
{
    int tx = start.x - (params->map->xmax / 2);
    int txx = finish.x - (params->map->xmax / 2);
    int ty = start.y - (params->map->ymax / 2);
    int tyy = finish.y - (params->map->ymax / 2);
    int tmpx = (1000 / (params->map->xmax * 2.f)) * tx;
    int tmpxx = (1000 / (params->map->xmax * 2.f)) * txx;
    int tmpy = (1000 / (params->map->ymax * 2.f)) * ty;
    int tmpyy = (1000 / (params->map->ymax * 2.f)) * tyy;
	int x = sqrt(2)/2 * (tmpx - tmpy);
	int xx = sqrt(2)/2 * (tmpxx - tmpyy);
	int y = (sqrt(2/3) * start.z) - (1 / sqrt(6)) * (tmpx + tmpy);
	int yy = (sqrt(2/3) * finish.z) - (1 / sqrt(6)) * (tmpxx + tmpyy);
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
	printf(“x: %d, y: %d, xx: %d, yy: %d\n”, x, y, xx, yy);
	printf(“dx: %d, dy: %d\n”, dx, dy);
	//mlx_pixel_put(params->mlx_ptr, params->win_ptr, x, y, 0xb5f7b4);
	if (dx > dy)
	{
		cumul = dx / 2;
		//printf(“dans le if (dx > dy): dx: %f, dy: %f\n”, dx, dy);
		while (i <= dx)
		{
			x += incx;
			cumul += dy;
			if (cumul >= dx)
			{
				cumul -= dx;
				y += incy;
			}
			printf(“x: %d, y: %d\n”, x, y);
			mlx_pixel_put(params->mlx_ptr, params->win_ptr, x + 500, y + 500, 0xb5f7b4);
			i++;
		}
	}
	else
	{
		cumul = dy /2;
		//printf(“toto\n”);
		//printf(“i: %d, dx: %f\n”, i, dx);
		while (i <= dy)
		{
			y += incy;
			cumul += dx;
			if (cumul >= dy)
			{
				cumul -= dy;
				x += incx;
			}
			printf(“x: %d, y: %d\n”, x, y);
			mlx_pixel_put(params->mlx_ptr, params->win_ptr, x + 500, y + 500, 0xb5f7b4);
			i++;
		}
	}
}