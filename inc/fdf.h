/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clvicent <clvicent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:54:02 by clvicent          #+#    #+#             */
/*   Updated: 2023/02/09 14:20:45 by clvicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define LOG    printf("%s:%d %s()\n", __FILE__,__LINE__, __FUNCTION__);
# define DEBUG 1
# define PAUSE    if (DEBUG) {getchar();};

# define SCX 1920
# define SCY 1080
# define OK 1
# define END 2

# include "libft.h"
# include "../mlx_linux/mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

typedef struct s_data {
	void 	*img_ptr;
	char 	*addr;
	int		bpp;
	int		length;
	int		endian;
}	t_data;

typedef struct s_line {
	int	x0;
	int	y0;
	int	x1;
	int	y1;
	int	dx;
	int dy;
	int	sx;
	int	sy;
	int	flag;
	int	true_x;
	int	true_y;
	int	half_height;
	int	half_width;
	int zoom;
}	t_line;

typedef struct s_math {
	int		index_x;
	int		index_y;
	int		size_x;
	int		size_y;
	int		size_p_x;
	int		size_p_y;
	int		start_x;
	int		start_y;
	int		max_alt;
	int		min_alt;
	int		alt_0;
	int		c_alt;
	int		next_alt;
	int		flag;
}	t_math;

typedef struct s_fdf {
	int		fd;
	int		**tab;
	char	*str;
	int		scx;
	int		scy;
	void	*mlx;
	void	*win;
	t_line	l;
	t_data	img;
	t_math	m;
}	t_fdf;

//grid_tools.c
void	ft_grid(t_fdf *f);
int		is_in_grid(int x, int y, t_fdf *f);
void	l_c_size(t_fdf *f);
int		width_and_length(t_fdf *f);
int		get_n_col(char *str);

//utils.c
int		how_many_d(char *str);
int		input_checker(char *str);
int		input_converter(t_fdf *f);
void	set_alt(t_fdf *f);
void	struct_filler(t_fdf *f);

//display_tools.c
void	ratio(t_fdf *f);
int		sizer(t_fdf *f);
int		get_zoom(t_fdf *f);
void	my_mlx_pixel_put(t_data *img, int x, int y, int color);

//tab_tools.c
void	get_pos(int x, int y, t_fdf *f);

//drawing_tools.c
void	draw_grid(int x, int y, t_fdf *f);
void	get_coord(int x, int y, t_fdf *f);
void	bresenham(t_fdf *f);
void	draw_line(t_fdf *f, t_line *l);

#endif
