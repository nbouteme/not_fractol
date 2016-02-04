/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 19:17:17 by nbouteme          #+#    #+#             */
/*   Updated: 2016/01/27 16:50:56 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "gfx.h"
#include "mlx.h"
#include "key_defs.h"

int			disp_expose(t_display *d)
{
	present(d->g);
	mlx_do_sync(d->conn);
	return (0);
}

int			disp_handle_key(t_display *d)
{
	d->input(d);
	return (0);
}
