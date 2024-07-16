/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 12:18:53 by csturm            #+#    #+#             */
/*   Updated: 2024/07/16 21:51:20 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

/* 
- check if the file is valid
- initialise a t_scene struct
- read the file (get_next_line)
- parse the file into structs defined in minirt.h
- return a t_scene struct that holds all other structs
*/

void    check_file(char *file)
{
// check if right format and accessible
}

t_scene init_scene(t_scene scene)
{
    scene.spheres = NULL;
    scene.planes = NULL;
    scene.cylinders = NULL;
    return (scene);
}
t_scene parse_scene(char *file, t_scene scene)
{
    int fd;
    char *line;

    scene = init_scene(scene);
    check_file(file);
    fd = open(file, O_RDONLY);
    if (fd < 0)
        error("Could not open file", &scene);
    while (get_next_line(fd, &line))
    {
        // parse line into structs
        free(line);
    }
    return (scene);
}