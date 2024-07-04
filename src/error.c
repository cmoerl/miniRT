/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturm <csturm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 12:31:27 by csturm            #+#    #+#             */
/*   Updated: 2024/07/04 10:53:22 by csturm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

/* 
- print an error message
- exit the program (cleanly)
*/

// void    clean_exit(t_scene *scene)
// {
//     // close window etc if opened
//     // depends on what is initialised using malloc
// }

void    error(char *message, t_scene *scene)
{
    if (message != NULL)
    {
        write(1, "Error: ", 7);
        write(1, message, strlen(message));
        write(1, "\n", 1);
    }
    if (scene == NULL)
        exit(1);
    // clean_exit(scene);
    if (message != NULL)
        exit(1);
    exit(0);
}
