/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsys_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/31 23:54:42 by nbouteme          #+#    #+#             */
/*   Updated: 2016/02/01 04:11:11 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsys.h"
#include <math.h>

typedef struct	s_fpoint
{
	float w;
	float h;
}				t_fpoint;

static void	rotate(t_fpoint *dir, float angle)
{
	float x;
	float y;
	float tmpx;
	float n;

	x = dir->w;
	y = dir->h;
	tmpx = x;
	x = x * cos(angle) + y * sin(angle);
	y = -tmpx * sin(angle) + y * cos(angle);
	n = sqrt(x * x + y * y);
	x /= n;
	x *= 420;
	y /= n;
	y *= 420;
	dir->w = x;
	dir->h = y;
}

t_dlisthead	*make_draw_list(t_lsys *self, char *r)
{
	t_fpoint	dir;
	t_dlisthead	*ret;

	ret = ftext_lstnew();
	dir = (t_fpoint) { 0, 420 };
	while (*r)
	{
		if (*r == '+')
			rotate(&dir, -self->angle);
		else if (*r == '-')
			rotate(&dir, self->angle);
		else
		{
			ftext_lstpush_back(ret, ftext_lstnewelem(&(t_drawcall) {
						self->pos,
						(t_point) { dir.w + self->pos.w, dir.h + self->pos.h }
					}, sizeof(t_drawcall)));
			self->pos.w += round(dir.w);
			self->pos.h += round(dir.h);
		}
		++r;
	}
	self->pos = (t_point){0, 0};
	return (ret);
}
