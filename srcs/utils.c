/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clvicent <clvicent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:42:48 by clvicent          #+#    #+#             */
/*   Updated: 2023/02/09 13:56:47 by clvicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	how_many_d(char *str)
{
	int	i;

	i = 0;
	while ((str[i] <= 13 && str[i] >= 9) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	return (i);
}

int	input_checker(char *str)
{
	int	i;

	i = 0;
	if (!ft_isdigit(str[0]))
		return (1);
	while (str[i] && str[i] != '\n')
	{
		if (!ft_isdigit(str[i]) && str[i] && str[i] != '\n'
			&& str[i] != ' ' && str[i] != '-' && str[i] != '+')
			return (1);
		else
			i++;
	}
	return (0);
}

int	input_converter(t_fdf *f)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	y = 0;
	f->tab = malloc(sizeof(int *) * f->m.size_y);
	if (f->tab == NULL)
		return (1);
	while (y < f->m.size_y)
	{
		x = 0;
		f->tab[y] = malloc(sizeof(int) * f->m.size_x);
		if (f->tab[y] == NULL)
			return (y);
		while (x < f->m.size_x)
		{
			f->tab[y][x] = ft_atoi(&f->str[i]);
			i += how_many_d(&(f->str[i]));
			x++;
		}
		y++;
	}
	free(f->str);
	return (0);
}

void	struct_filler(t_fdf *f)
{	
	f->m.start_x = (f->scx - f->m.size_p_x * (f->m.size_x - 1)) / 2;
	f->m.start_y = (f->scy - f->m.size_p_y * (f->m.size_y - 1)) / 2;
	f->l.true_x = f->scx / 2;
	f->l.true_y = f->m.start_y;
	f->l.half_height = f->m.size_p_x;
	f->l.half_width = f->m.size_p_x / 2;
}

void	set_alt(t_fdf *f)
{
	int	x;
	int	y;

	y = 0;
	f->m.min_alt = f->tab[0][0];
	f->m.max_alt = f->tab[0][0];
	while (y < f->m.size_y)
	{
		x = 0;
		while (x < f->m.size_x)
		{
			if (f->m.min_alt > f->tab[y][x])
				f->m.min_alt = f->tab[y][x];
			if (f->m.max_alt < f->tab[y][x])
				f->m.max_alt = f->tab[y][x];
			x++;
		}
		y++;
	}
	if (f->m.min_alt >= 0)
		f->m.alt_0 = f->m.min_alt;
	if (f->m.max_alt <= 0)
		f->m.alt_0 = f->m.max_alt;
	f->l.zoom = get_zoom(f);
	if (!f->l.zoom)
		ft_putstr_fd("ALT TOO HIGH/DEEP\n", 1);
}
