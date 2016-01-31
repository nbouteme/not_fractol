/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useless_as_heck.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 19:28:59 by nbouteme          #+#    #+#             */
/*   Updated: 2016/01/27 16:51:53 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "mlx.h"

void		run_display(t_display *d)
{
	d->paint(d->g);
	mlx_loop(d->conn);
}

int			disp_loop(t_display *d)
{
	d->paint(d->g);
	return (0);
}

int			event_loop(t_display *d)
{
	disp_handle_key(d);
	return (0);
}

t_display	*new_display()
{
	t_display *ret;

	ret = malloc(sizeof(*ret));
	ret->conn = mlx_init();
	ret->dim.w = 420;
	ret->dim.h = 420;
	ret->win = mlx_new_window(ret->conn, ret->dim.w, ret->dim.h, "fractol");
	ret->g = new_graphics(ret);
	set_key_handlers(ret);
	mlx_loop_hook(ret->conn, &event_loop, ret);
	mlx_expose_hook(ret->win, &disp_expose, ret);
	mlx_do_key_autorepeaton(ret->conn);
	return (ret);
}
