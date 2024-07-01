/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturm <csturm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:56:02 by csturm            #+#    #+#             */
/*   Updated: 2024/07/01 10:00:17 by csturm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

int main(int argc, char **argv)
{
    t_scene scene;

    if (argc != 2)
    {
        printf(stderr, "Error: Wrong number of arguments\n");
        return (1);
    }
    scene = parse_scene(argv[1], scene);
    render_scene(scene);
    event_loop(scene);
    return (0);
}