/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 18:50:11 by nbouteme          #+#    #+#             */
/*   Updated: 2016/01/13 18:53:27 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft/std.h>
#include "mlx.h"
#include "gfx.h"

t_graphics	*new_graphics(t_display *d)
{
	int			osef;
	t_graphics	*g;

	g = malloc(sizeof(t_graphics));
	g->d = d;
	g->int_img = mlx_new_image(d->conn, d->dim.w, d->dim.h);
	g->fb = (int*)mlx_get_data_addr(g->int_img, &osef, &osef, &osef);
	g->dim.w = d->dim.w;
	g->dim.h = d->dim.h;
	g->color = 0x00FFFFFF;
	return (g);
}
