/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bato.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/05 01:32:48 by nbouteme          #+#    #+#             */
/*   Updated: 2016/02/05 01:49:03 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fracts.h"

void		bato(t_display *d, t_fracparams params)
{
	COMPLEX c;
	COMPLEX z;
	int		x;
	int		y;
	int		i;

	x = -1;
	while (++x < 420 && (y = -1))
		while (++y < 420)
		{
			c = ((float)(x - 210) / (d->zoom * 210) + d->offset[0]) +
				((float)(y - 210) / (d->zoom * 210) + d->offset[1]) * I;
			z = params.ix + params.iy * I;
			i = -1;
			while (++i < d->n && cabsf(z) < 2.0)
				z = ((fabsf(crealf(z)) + fabsf(cimagf(z)) * I) *
					 (fabsf(crealf(z)) + fabsf(cimagf(z)) * I)) + c;
			d->g->color = i < d->n ? i_to_rgb(i) : 0;
			draw_point(d->g, (t_point){x, y});
		}
}
