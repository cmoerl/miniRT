/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturm <csturm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 12:31:27 by csturm            #+#    #+#             */
/*   Updated: 2024/06/21 12:55:54 by csturm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

/* 
- print an error message
- exit the program (cleanly)
*/

void    clean_exit(t_scene *scene)
{
    free(scene->spheres);
    free(scene->planes);
    free(scene->cylinders);
}

void    error(char *message, t_scene *scene)
{
    printf(stderr, "Error: %s\n", message);
    clean_exit(scene);
    exit(1);
}
