/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clvicent <clvicent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:23:10 by clvicent          #+#    #+#             */
/*   Updated: 2023/02/13 16:42:16 by clvicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_grid(t_fdf *f)
{
	int	y;
	int	x;

	x = 0;
	while (x < f->scx)
	{
		y = 0;
		while (y < f->scy)
		{
			if (is_in_grid(x, y, f))
				draw_grid(x, y, f);
			y++;
		}	
		x++;
	}
	free_tab(f->tab, f->m.size_y);
}

int	is_in_grid(int x, int y, t_fdf *f)
{
	if (x < f->m.start_x || x > (f->scx + 1 - f->m.start_x) ||
		y < f->m.start_y || y > (f->scy + 1 - f->m.start_y))
		return (0);
	if (((y - f->m.start_y) % f->m.size_p_y == 0) &&
		((x - f->m.start_x) % f->m.size_p_x == 0))
		return (OK);
	if (x == (f->scx - f->m.start_x) && y == (f->scy - f->m.start_y))
		return (END);
	return (0);
}

#if 0
void	l_c_size(t_fdf *f)
{
	f->m.size_p_x = (f->scx - 1) / f->m.size_x;
	f->m.size_p_y = (f->scy - 1) / f->m.size_y;
	if (f->m.size_p_x > f->m.size_p_y)
		f->m.size_p_x = f->m.size_p_y;
	else
		f->m.size_p_y = f->m.size_p_x;
}
#else
void	l_c_size(t_fdf *f)
{
	int delta;

	delta = f->m.size_x + f->m.size_y;
	f->l.half_height = (f->scx - (f->scx / 10)) / delta;
	f->l.half_width = (f->scy - (f->scy / 10)) / delta;
	if (f->l.half_height * 2 > f->l.half_width)
		f->l.half_height = f->l.half_width / 2;
	else
		f->l.half_width = f->l.half_height * 2;
}
#endif
int	width_and_length(t_fdf *f)
{
	char	*line;

	line = NULL;
	LOG
	f->str = get_next_line(f->fd);
	if (f->str == NULL)
		return (-1);
	else
		f->m.size_y = 1;
	f->m.size_x = get_n_col(f->str);
	while (1)
	{
		line = get_next_line(f->fd);
		if (line == NULL || input_checker(line) == 1)
			return (0);
		f->m.size_y++;
		if (f->m.size_x != get_n_col(line))
			return (-1);
		f->str = ft_strjoin(f->str, line);
		free(line);
	}
	return (0);
}

int	get_n_col(char *str)
{
	int		i;
	char	**strs;

	i = 0;
	strs = ft_split(str, ' ');
	while (strs[i])
		i++;
	ft_exit(strs);
	return (i);
}
