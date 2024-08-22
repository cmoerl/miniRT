/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturm <csturm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 09:44:34 by csturm            #+#    #+#             */
/*   Updated: 2024/08/22 10:55:12 by csturm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

int	close_window(t_scene *scene)
{
	mlx_destroy_window(scene->mlx_ptr, scene->win_ptr);
	error(NULL, scene);
	return (0);
}

// 65307 = ESC
int	key_press(int keycode, t_scene *scene)
{
	if (keycode == 65307)
		close_window(scene);
	return (0);
}

void	event_loop(t_scene scene)
{
	mlx_hook(scene.win_ptr, 2, 1L << 0, key_press, &scene);
	mlx_hook(scene.win_ptr, 17, 1L << 17, close_window, &scene);
	mlx_loop(scene.mlx_ptr);
}
