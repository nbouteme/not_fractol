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

static void	rotate(t_point *dir, float angle)
{
	int tmpx;

	tmpx = dir->w;
	dir->w = dir->w * cos(angle) + dir->h * sin(angle);
	dir->h = -tmpx * sin(angle) + dir->h * cos(angle);
}

t_dlisthead	*make_draw_list(t_lsys *self, char *r)
{
	t_point		dir;
	t_dlisthead	*ret;

	ret = ftext_lstnew();
	dir = (t_point) { 0, 10 };
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
						(t_point) {	self->pos.w + dir.w, self->pos.h + dir.h }
					}, sizeof(t_drawcall)));
			self->pos.w += dir.w;
			self->pos.h += dir.h;
		}
		++r;
	}
	return (ret);
}
