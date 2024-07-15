/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturm <csturm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:56:02 by csturm            #+#    #+#             */
/*   Updated: 2024/07/15 09:46:53 by csturm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

// t_scene parse_scene(char *file, t_scene scene)
// {
//     char    *file_name;

//     file_name = file;
//     init_scene(&scene);
//     return (scene);
// }

int main(int argc, char **argv)
{
    t_scene scene;

    if (argc != 2)
    {
        write(1, "Error: Invalid number of arguments\n", 36);
        return (1);
    }
    // scene = parse_scene(argv[1], scene);
    render_scene(scene);
    event_loop(scene);
    return (0);
}