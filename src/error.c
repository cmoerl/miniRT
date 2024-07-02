/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturm <csturm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 12:31:27 by csturm            #+#    #+#             */
/*   Updated: 2024/07/02 12:23:51 by csturm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

/* 
- print an error message
- exit the program (cleanly)
*/

void    clean_exit(t_scene *scene)
{
    // depends on what is initialised using malloc
}

void    error(char *message, t_scene *scene)
{
    printf(stderr, "Error: %s\n", message);
    clean_exit(scene);
    exit(1);
}
