/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturm <csturm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 09:44:34 by csturm            #+#    #+#             */
/*   Updated: 2024/08/19 10:37:44 by csturm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

int     close_window(t_scene *scene)
{
    error(NULL, scene);
    return (0);
}

int    key_press(int keycode, t_scene *scene)
{
    if (keycode == 53) // ESC
        close_window(scene);
    // if (keycode == 61) // +
    //     increase_resolution(scene);
    // if (keycode == 45) // -
    //     decrease_resolution(scene);
    return (0);
}

void    event_loop(t_scene scene)
{
    mlx_hook(scene.win_ptr, 2, 1L << 0, key_press, &scene);
    mlx_hook(scene.win_ptr, 17, 1L << 17, close_window, &scene);
    mlx_loop(scene.mlx_ptr);
}
