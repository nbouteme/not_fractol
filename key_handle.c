/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 16:52:16 by nbouteme          #+#    #+#             */
/*   Updated: 2016/02/05 02:12:52 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_defs.h"

int g_key_states[0x10000];
t_point g_mouse_pos;

const t_keybind g_binds[] =
{
	{'a', 0 }, {'s', 1 }, {'d', 2 }, {'f', 3 }, {'h', 4 }, {'g', 5 },
	{'z', 6 }, {'x', 7 }, {'c', 8 }, {'v', 9 }, {'\0', 10 }, {'b', 11},
	{'q', 12 }, {'w', 13 }, {'e', 14 }, {'r', 15 }, {'y', 16 },
	{'t', 17 }, {'1', 18 }, {'2', 19 }, {'3', 20 }, {'4', 21 }, {'6', 22 },
	{'5', 23 }, {'=', 24 }, {'9', 25 }, {'7', 26 }, {'-', 27 },
	{'8', 28 }, {'0', 29 }, {']', 30 }, {'o', 31 }, {'u', 32 },
	{'[', 33 }, {'i', 34 }, {'p', 35 }, {'\n', 36 }, {'l', 37 }, {'j', 38 },
	{'\'', 39 }, {'k', 40 }, {'\0', 41 }, {'\\', 42 }, {'\0', 43 },
	{'\0', 44 }, {'n', 45 }, {'m', 46 }
};

void		set_key_handlers(t_display *d)
{
	mlx_hook(d->win, KP, KPM, &disp_key_pressed, 0);
	mlx_hook(d->win, KR, KRM, &disp_key_released, 0);
	mlx_hook(d->win, MN, PMM, &disp_mouse_moved, 0);
}

t_point		get_mouse_pos(void)
{
	return (g_mouse_pos);
}

int			disp_mouse_moved(int x, int y)
{
	g_mouse_pos = (t_point){x, y};
	return (0);
}

int			disp_key_released(int key)
{
	g_key_states[key] = 0;
	return (0);
}

int			disp_key_pressed(int key)
{
	g_key_states[key] = 1;
	return (0);
}
