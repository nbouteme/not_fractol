/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/05 01:32:48 by nbouteme          #+#    #+#             */
/*   Updated: 2016/03/24 01:23:54 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fracts.h"
#include <pthread.h>
#include <stdio.h>

void		*mandel2(const t_mandel_param *p)
{
	COMPLEX c;
	COMPLEX z;
	int		x;
	int		y;
	int		i;

	y = 105 * p->id - 1;
	while (++y < 105 * (p->id + 1) && (x = -1))
		while (++x < 420)
		{
			c = ((float)(x - 210) / (p->d->zoom * 210) + p->d->offset[0]) +
				((float)(y - 210) / (p->d->zoom * 210) + p->d->offset[1]) * I;
			z = p->params.ix + p->params.iy * I;
			i = -1;
			while (++i < p->d->n && cabsf(z) < 2.0)
			{
				z *= z;
				z += c;
			}
			p->d->g->color = i < p->d->n ? i_to_rgb(i) : 0;
			draw_point_bare(p->d->g, (t_point){x, y});
		}
	return (0);
}

void		mandel(t_display *d, t_fracparams params)
{
	t_mandel_param	p[4];
	pthread_t		th[3];
	int				i;

	i = 0;
	p[3] = (t_mandel_param){0, d, params};
	p[2] = p[3];
	p[1] = p[2];
	p[0] = p[1];
	p[1].id = 1;
	p[2].id = 2;
	p[3].id = 3;
	while (i < 3)
	{
		pthread_create(&th[i], 0, (void*)mandel2, p + i);
		++i;
	}
	mandel2(p + 3);
	i = 0;
	while (i < 3)
		pthread_join(th[i++], 0);
}
