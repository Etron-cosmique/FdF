/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clvicent <clvicent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:25:59 by clvicent          #+#    #+#             */
/*   Updated: 2023/02/09 15:54:24 by clvicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// void	ratio(t_fdf *f)
// {
// 	while (!sizer(f))
// 	{
// 		f->m.size_p_x--;
// 		f->m.size_p_y--;
// 		// printf("coucou on est dans ratio\n");
// 		struct_filler(f);		
// 	}
// }

// int		sizer(t_fdf *f)
// {
// 	int a;
// 	int b;
// 	int c;
	
// 	a = f->l.true_y + ((f->m.size_x + f->m.size_y) * f->l.half_width);
// 	b = f->l.true_y + ((0 + f->m.size_y) * f->l.half_width);
// 	c = f->l.true_y + ((f->m.size_x + 0) * f->l.half_width);
// 	if (a > f->scy || b > f->scy || c > f->scy)
// 		return (0);
// 	a = f->l.true_x + ((f->m.size_x - f->m.size_y) * f->l.half_height);
// 	b = f->l.true_x + ((0 - f->m.size_y) * f->l.half_height);
// 	c = f->l.true_x + ((f->m.size_x - 0) * f->l.half_height);
// 	if (a < 0 || b > f->scx || c > f->scx)
// 		return (0);
// 	return (1);
// }

int		get_zoom(t_fdf *f)
{
	int i;

	i = 200;
	while (i)
	{
		if (f->l.true_y - (i * f->m.max_alt) < 0 ||
			(f->scy - f->l.true_y) - (i * f->m.min_alt) > f->scy)
			i--;
		else
			return (i);
	}
	return (0);
}

void	my_mlx_pixel_put(t_data *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->length + x * (img->bpp / 8));
	*(unsigned int *) dst = color;
}

// void	set_pix(t_fdf *f, int x, int y)
// {
// 	int color;

// 	get_pos(x, y, f);
// 	if (x_y(x, y, f) == 0)
// 		f->m.flag = 0;
// 	color = color_maker(f, x, y);
// 	if (f->m.c_alt > f->m.alt_0 && f->m.flag != 1)
// 		my_mlx_pixel_put(&f->img, x, y, get_rgb(255, splitter(color, 1), splitter(color, 2)));
// 	if (f->m.c_alt < f->m.alt_0 && f->m.flag != 1)
// 		my_mlx_pixel_put(&f->img, x, y, get_rgb(splitter(color, 2), splitter(color, 1), 255));
// 	if (f->m.c_alt > f->m.alt_0 && f->m.flag == 1)
// 		my_mlx_pixel_put(&f->img, x, y, get_rgb(splitter(color, 2), splitter(color, 1), 255));
// 	if (f->m.c_alt < f->m.alt_0 && f->m.flag == 1)
// 		my_mlx_pixel_put(&f->img, x, y, get_rgb(255, splitter(color, 1), splitter(color, 2)));
// 	if (f->m.c_alt == f->m.alt_0)
// 		my_mlx_pixel_put(&f->img, x, y, shade_zero(f, color));
// }
