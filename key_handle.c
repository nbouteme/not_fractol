/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 16:52:16 by nbouteme          #+#    #+#             */
/*   Updated: 2016/02/01 01:05:31 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef __linux__
# include <X11/Xlib.h>
# include <X11/Xutil.h>
# include <X11/extensions/XShm.h>
# define KRM KeyReleaseMask
# define KR KeyRelease
# define KPM KeyPressMask
# define KP KeyPress
# define PMM PointerMotionMask
# define MN MotionNotify
#else
# define KRM 2
# define KR 3
# define KPM 1
# define KP 2
# define PMM (1 << 6)
# define MN 6
#endif

#include "mlx.h"

static int g_key_states[0x10000];
static t_point mouse_pos;

void		set_key_handlers(t_display *d)
{
	mlx_hook(d->win, KP, KPM, &disp_key_pressed, 0);
	mlx_hook(d->win, KR, KRM, &disp_key_released, 0);
	mlx_hook(d->win, MN, PMM, &disp_mouse_moved, 0);
}

t_point get_mouse_pos()
{
	return (mouse_pos);
}

int			disp_mouse_moved(int x, int y)
{
	mouse_pos = (t_point){x, y};
	return (0);
}

int			disp_key_released(int key)
{
	g_key_states[key] = 0;
	return (0);
}

typedef struct	s_keybind
{
	char c;
	int idx;
}				t_keybind;

t_keybind g_binds[] =
{
	{'a', 0 }, {'s', 1 }, {'d', 2 }, {'f', 3 }, {'h', 4 }, {'g', 5 },
	{'z', 6 }, {'x', 7 }, {'c', 8 }, {'v', 9 }, {'\0', 10 }, {'b', 11},
	{'q', 12 }, {'w', 13 }, {'e', 14 }, {'r', 15 }, {'y', 16 },
	{'t', 17 }, {'1', 18 }, {'2', 19 }, {'3', 20 }, {'4', 21 }, {'6', 22 },
	{'5', 23 }, {'=', 24 }, {'9', 25 }, {'7', 26 }, {'-', 27 },
	{'8', 28 }, {'0', 29 }, {']', 30 }, {'o', 31 }, {'u', 32 },
	{'[', 33 }, {'i', 34 }, {'p', 35 }, {'\n',36 }, {'l', 37 }, {'j', 38 },
	{'\'', 39 }, {'k', 40 }, {'\0', 41 }, {'\\', 42 }, {'\0', 43 },
	{'\0', 44 }, {'n', 45 }, {'m', 46 }
};
#include <stdio.h>
int			disp_key_pressed(int key)
{
	g_key_states[key] = 1;
	return (0);
}

#ifndef __linux__
static int key_idx(int k)
{
	int i;

	i = 0;
	while (i < 47)
		if (g_binds[i].c == k)
			return (g_binds[i].idx);
		else
			++i;
	return (-1);
}
#endif

int			is_key_pressed(int key)
{
#ifndef __linux__
	if (ft_isalpha(key) && (key = key_idx(key)) != -1)
		return (g_key_states[i]);
#endif
	return (g_key_states[key]);
}
