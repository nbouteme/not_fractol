/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/05 01:33:26 by nbouteme          #+#    #+#             */
/*   Updated: 2016/03/24 02:14:12 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fracts.h"

void		draw_fractal(t_display *d)
{
	const t_dfrac	fractals[] = { &mandel, &julia, &custom, &bato };

	fractals[d->sel](d, (t_fracparams)
	{
		(float)get_mouse_pos().w / 420,
		(float)get_mouse_pos().h / 420
	});
}

t_dlist		*transform_dcs(t_dlist *elem, t_mat3 m)
{
	t_drawcall	*v;
	t_drawcall	ret;
	t_cvec3		t;

	v = elem->content;
	t = mat3_m_vec3(m, &(float[]) {v->from.w, v->from.h, 1.0});
	ret.from.w = (*t)[0];
	ret.from.h = (*t)[1];
	mat3_m_vec3(m, &(float[]) {v->to.w, v->to.h, 1.0});
	ret.to.w = (*t)[0];
	ret.to.h = (*t)[1];
	return (ftext_lstnewelem(&ret, sizeof(ret)));
}

static void	draw_list(t_dlisthead *dcs, t_display *d)
{
	t_dlist *s;
	t_dlist *e;

	s = dcs->next;
	e = dcs->next->prev;
	clear_graphics(d->g);
	while (s != e)
	{
		draw_line(d->g,
				((t_drawcall*)s->content)->from,
				((t_drawcall*)s->content)->to);
		s = s->next;
	}
	present(d->g);
	mlx_do_sync(d->conn);
}

void		custom(t_display *d, t_fracparams params)
{
	static t_dlisthead	*dcs = 0;
	static int			oldn = 0;
	char				*r;
	t_dlisthead			*tdcs;

	(void)params;
	d->g->color = 0x00FFFFFF;
	if (oldn != d->n)
	{
		oldn = d->n;
		free(dcs);
		r = get_command_string(d->system, d->n / 10 + 1);
		dcs = make_draw_list(d->system, r);
		free(r);
	}
	tdcs = ftext_lstmapup(dcs, (void*)&transform_dcs, &(float[3][3])
						{
							{d->zoom / 42, 0, -d->offset[0] * 21},
							{0, d->zoom / 42, -d->offset[1] * 21},
							{0, 0, 1}
						});
	draw_list(tdcs, d);
	ftext_lstdel(&tdcs, 0);
}
