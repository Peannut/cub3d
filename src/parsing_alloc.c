/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_alloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 00:04:56 by abouhaga          #+#    #+#             */
/*   Updated: 2023/03/25 16:43:35 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// to count the number of lines in a 2D array
int count_lines(char **map)
{
    int i;
    i = 0;
    while (map[i] != NULL)
        i++;
    return i;
}

//to get the length of the longest line in a 2D array
int get_longest_line(char **map)
{
    int len;
    int i;
    int longest;
    i = 0;
    longest = 0;
    while (map[i] != NULL)
    {
        len = strlen(map[i]);
        if (len > longest)
            longest = len;
        i++;
    }
    return longest;
}

//to allocate memory for a 2D array and copy its contents
char **allocate(char **map, int num_lines, int longest_line)
{
    char **mapv;
    int i;

    mapv = malloc(sizeof(char *) * (num_lines + 1));
    if (mapv == NULL)
        ft_error("Error: malloc failed\n");
    i = 0;
    while (i < num_lines)
    {
        mapv[i] = malloc(sizeof(char) * (longest_line + 1));
        if (mapv[i] == NULL)
            ft_error("Error: malloc failed\n");
        ft_strlcpy(mapv[i], map[i], longest_line + 1);
        mapv[i][longest_line] = '\0';
        i++;
    }
    mapv[num_lines] = NULL;
    return mapv;
}

//to free memory allocated 
void free_map(char **map, int num_lines)
{
    int i = 0;
    while (i < num_lines)
    {
        free(map[i]);
        i++;
    }
    free(map);
}

//to allocate memory for and copy a subset of the map
char **copy_lines(char **map, int start, int end)
{
    int i;
    int num_lines;
    char **subset;
    num_lines = end - start + 1;
    subset = malloc(sizeof(char *) * (num_lines + 1));
    if (subset == NULL)
        ft_error("Error: malloc failed\n");
    i = 0;
    while (i < num_lines)
    {
        subset[i] = ft_strdup(map[start + i]);
        i++;
    }
    subset[num_lines] = NULL;
    return subset;
}

char **allocate_map(char **map, int i)
{
    int num_lines;
    int longest_line;
    char **subset;
    char **allocated;
    num_lines = count_lines(map) - i;
    longest_line = get_longest_line(&map[i]);
    subset = copy_lines(map, i, i + num_lines - 1);
    allocated = allocate(subset, num_lines, longest_line);
    free_map(subset, num_lines);
    return allocated;
}
