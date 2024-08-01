/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 12:18:53 by csturm            #+#    #+#             */
/*   Updated: 2024/08/01 12:13:22 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"
#include <stdio.h>

/* 
- check if the file is valid
- initialise a t_scene struct
- read the file (get_next_line)
- parse the file into structs defined in minirt.h
- return a t_scene struct that holds all other structs
*/


void check_file(char *file)
{
    // Check if file is accessible
    if (!file || access(file, F_OK) == -1)
    {
        perror("Error accessing file");
        exit(EXIT_FAILURE);
    }

    // Check if file has .rt extension
    char *extension = ft_strrchr(file, '.');
    if (!extension || ft_strcmp(extension, ".rt") != 0)
    {
        printf("Error: Incorrect file format. Expected .rt\n");
        exit(EXIT_FAILURE);
    }
}

t_scene init_scene(t_scene scene)
{
    scene.objects = malloc(sizeof(t_object));
    if (!scene.objects)
        error("Memory allocation failed", &scene);
    scene.objects->spheres = NULL;
    scene.objects->planes = NULL;
    scene.objects->cylinders = NULL;
    return scene;
}

t_scene parse_scene(char *file, t_scene scene)
{
    int fd;
    char *line = NULL;

    scene = init_scene(scene);
    check_file(file);
    fd = open(file, O_RDONLY);
    if (fd < 0)
        error("Could not open file", &scene);
    while ((line = get_next_line(fd)) != NULL)
    {
        // Print each line for testing
        printf("Read line: %s\n", line);
        free(line);
    }
    close(fd);
    return scene;
}