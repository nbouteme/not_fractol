/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 04:41:09 by nbouteme          #+#    #+#             */
/*   Updated: 2016/03/24 02:18:42 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <complex.h>
#include <tgmath.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#include <stdio.h>
#include "key_defs.h"
#include "vmath.h"

#include "lsys.h"
#include "fracts.h"

int			i_to_rgb(int x)
{
	return (x * 2654435761) & 0x00FFFFFF;
}

void		handle_input(t_display *d)
{
	if (is_key_pressed(ESCAPE))
		exit(42);
	d->offset[1] -= is_key_pressed(UP) ? (42.0 / 420) / d->zoom : 0;
	d->offset[1] += is_key_pressed(DOWN) ? (42.0 / 420) / d->zoom : 0;
	d->offset[0] -= is_key_pressed(LEFT) ? (42.0 / 420) / d->zoom : 0;
	d->offset[0] += is_key_pressed(RIGHT) ? (42.0 / 420) / d->zoom : 0;
	d->n += is_key_pressed(KP_ADD);
	d->n -= d->n > 2 ? is_key_pressed(KP_SUBTRACT) : 0;
	d->zoom *= is_key_pressed('p') ? 1.0f / 1.05f : 1.0f;
	d->zoom /= is_key_pressed('o') ? 1.0f / 1.05f : 1.0f;
	if (is_key_pressed('m'))
		d->sel = 0;
	if (is_key_pressed('j'))
		d->sel = 1;
	if (is_key_pressed('b'))
		d->sel = 3;
	if (d->system && is_key_pressed('c'))
	{
		d->n = 3;
		d->sel = 2;
	}
	d->paint(d);
	disp_expose(d);
}

int			handle_mouse(int button, int x, int y, t_display *d)
{
	float wx;
	float wy;

	wx = (float)x / 420 - 0.5f;
	wy = (float)y / 420 - 0.5f;
	d->can_move ^= button == 1;
	if (button == 5)
	{
		d->offset[0] += (wx / d->zoom) * 0.5f;
		d->offset[1] += (wy / d->zoom) * 0.5f;
		d->zoom *= 1.0f / 1.05f;
	}
	if (button == 4)
	{
		d->offset[0] += (wx / d->zoom) * 0.5f;
		d->offset[1] += (wy / d->zoom) * 0.5f;
		d->zoom /= 1.0f / 1.05f;
	}
	d->paint(d);
	disp_expose(d);
	return (0);
}

static void	init_lsys(t_display *d, char *fn)
{
	int		fd;
	char	*f;
	char	**array;

	fd = open(fn, O_RDONLY);
	if (fd == -1)
		print_help();
	f = readfile(fd, &check_input);
	if (!f)
		assert(0);
	array = ft_strsplit(f, '\n');
	d->system = parse_lsys(array);
}

int			main(int argc, char *argv[])
{
	t_display *d;

	if (argc > 2 || contains("-h", argv))
		print_help();
	d = new_display();
	if (argc == 2)
		init_lsys(d, argv[1]);
	d->paint = draw_fractal;
	d->input = handle_input;
	run_display(d);
	return (0);
}
