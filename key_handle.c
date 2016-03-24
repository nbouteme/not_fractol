/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 16:52:16 by nbouteme          #+#    #+#             */
/*   Updated: 2016/03/24 01:29:54 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_defs.h"

void		set_key_handlers(t_display *d)
{
	mlx_hook(d->win, KP, KPM, &disp_key_pressed, 0);
	mlx_hook(d->win, KR, KRM, &disp_key_released, 0);
	mlx_hook(d->win, MN, PMM, &disp_mouse_moved, d);
	mlx_mouse_hook(d->win, &handle_mouse, d);
}

t_point		get_mouse_pos(void)
{
	return (*get_mousepos());
}

int			disp_mouse_moved(int x, int y, t_display *d)
{
	(void)d;
	if (d->can_move)
		*get_mousepos() = (t_point){x, y};
	else
		*get_mousepos() = (t_point){0, 0};
	return (0);
}

int			disp_key_released(int key)
{
	get_states()[key] = 0;
	return (0);
}

int			disp_key_pressed(int key)
{
	get_states()[key] = 1;
	return (0);
}
