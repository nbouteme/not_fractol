/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useless_as_heck.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 19:28:59 by nbouteme          #+#    #+#             */
/*   Updated: 2016/02/05 02:10:04 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "mlx.h"

void		run_display(t_display *d)
{
	d->paint(d);
	mlx_loop(d->conn);
}

int			disp_loop(t_display *d)
{
	d->paint(d);
	return (0);
}

int			event_loop(t_display *d)
{
	disp_handle_key(d);
	return (0);
}

t_display	*new_display(void)
{
	t_display *ret;

	ret = malloc(sizeof(*ret));
	ret->conn = mlx_init();
	ret->dim.w = 420;
	ret->dim.h = 420;
	ret->win = mlx_new_window(ret->conn, ret->dim.w, ret->dim.h, "fractol");
	ret->g = new_graphics(ret);
	ret->n = 30;
	ret->offset[0] = -0.5f;
	ret->offset[1] = -0.5f;
	ret->zoom = 2;
	ret->sel = 1;
	set_key_handlers(ret);
	mlx_loop_hook(ret->conn, &event_loop, ret);
	mlx_expose_hook(ret->win, &disp_expose, ret);
	mlx_do_key_autorepeaton(ret->conn);
	return (ret);
}
