/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clvicent <clvicent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:30:07 by clvicent          #+#    #+#             */
/*   Updated: 2023/02/09 15:59:50 by clvicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	shut_fdf(t_fdf *f, char *message)
{
	printf("%s", message);
	mlx_destroy_image(f->mlx, f->img.img_ptr);
	mlx_destroy_window(f->mlx, f->win);
	mlx_destroy_display(f->mlx);
	free(f->mlx);
}

int	exit_cross(t_fdf *f)
{
	shut_fdf(f, "shut by exit cross");
	exit(0);
}

int	key_press(int keycode, t_fdf *f)
{
	printf("key_press()         : %i\n", keycode);
	if (keycode != 65307)
		return (0);
	shut_fdf(f, "shut by escape key");
	exit (0);
}

void	ft_init(t_fdf *f, char *filename)
{
	t_data	*img;

	img = &f->img;
	ft_bzero(&f->m, sizeof(t_math));
	ft_bzero(&f->l, sizeof(t_line));
	f->fd = open(filename, O_RDONLY);
	f->scx = SCX;
	f->scy = SCY;
	f->mlx = mlx_init();
	f->win = mlx_new_window(f->mlx, f->scx, f->scy, "fdf");
	img->img_ptr = mlx_new_image(f->mlx, f->scx, f->scy);
	img->addr = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->length, &img->endian);
}

int	main(int ac, char **av)
{
	t_fdf	f;

	if (ac != 2)
	{
		printf("Usage : ./fdf <filename.fdf>\n");
		return (1);
	}
	ft_init(&f, av[1]);
	if (-1 == width_and_length(&f))
	{
		printf("file is empty\n");
		return (1);
	}
	printf("f->m.size_y = %d\nf->m.size_x = %d\n", f.m.size_y, f.m.size_x);
	l_c_size(&f);
	struct_filler(&f);
	input_converter(&f);
	set_alt(&f);
	// printf("avant\n");
	// ratio(&f);
	// printf("apres\n");
	ft_grid(&f);
	mlx_put_image_to_window(f.mlx, f.win, f.img.img_ptr, 0, 0);
	mlx_key_hook(f.win, key_press, &f);
	mlx_hook(f.win, 17, 1L << 0, exit_cross, &f);
	mlx_loop(f.mlx);
}
