/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 08:36:52 by marianfurni       #+#    #+#             */
/*   Updated: 2024/08/27 16:35:19 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

void	error(char *message, t_scene *scene)
{
	if (message != NULL)
	{
		write(1, "Error: ", 7);
		write(1, message, ft_strlen(message));
		write(1, "\n", 1);
	}
	if (scene != NULL)
	{
		free_scene(scene);
	}
	exit(1);
}
