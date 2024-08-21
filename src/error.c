/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 08:36:52 by marianfurni       #+#    #+#             */
/*   Updated: 2024/08/21 19:35:31 by marianfurni      ###   ########.fr       */
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
	if (scene == NULL)
		exit(1);
	if (message != NULL)
		exit(1);
	exit(0);
}
