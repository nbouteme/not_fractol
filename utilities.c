/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/05 01:39:12 by nbouteme          #+#    #+#             */
/*   Updated: 2016/02/05 02:11:04 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fracts.h"

int			contains(const char *rhs, char **args)
{
	while (*args)
		if (ft_strcmp(rhs, *args) == 0)
			return (1);
		else
			++args;
	return (0);
}

void		print_help(void)
{
	ft_putstr(
		"Usage: ./fractol [-h | lsystemfile]\n" "O/P: Zoom in/out\n"
		"Arrows: Move the camera\n" "+/-: Increase/Decrease the number"
		"of iterations\n" "m: Displays the mandelbrot fractal\n" "j:"
		"Displays the julia fractal\n" "c: displays the custom fractal,"
		"as defined by the file " "given as an argument to this"
		"program\n" "Camera movements may not be available in custom"
		"mode" "lsystemfile should be the path to a valid lsystem"
		"description\n" "A valid file is a file whose first line is an"
		"axiom, " "and subsequent lines are rules\n");
	exit(1);
}

int			check_input(char *s)
{
	const char *auth = "\n=1234567890ABCDEFGHIJJKLMNOPQRSTUVWXYZ+-";

	while (*s)
		if (ft_strindexof(auth, *s) == -1)
			return (0);
		else
			++s;
	return (1);
}

char		*readfile(int fd, int (*check)(char *))
{
	char	*buf;
	char	*tmp;
	char	*ret;
	int		n;

	ret = ft_strnew(1);
	buf = ft_strnew(B_SIZE + 1);
	while ((n = read(fd, buf, B_SIZE)) > 0)
	{
		if (!check(buf))
			return (0);
		tmp = ret;
		ft_bzero(buf + n, B_SIZE - n);
		ret = ft_strjoin(ret, buf);
		free(tmp);
	}
	free(buf);
	return (ret);
}

void		assert(int b)
{
	if (b)
		return ;
	write(2, "Error.\n", 7);
	exit(2);
}
