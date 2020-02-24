/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro_paint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekindomb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:08:29 by ekindomb          #+#    #+#             */
/*   Updated: 2020/02/24 17:44:42 by ekindomb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "micro_paint.h"

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

void    putstr(char *str, int len)
{
    write(1, str, len);
}

int     first_line(t_res *res, FILE *fd)
{
    if ((fscanf(fd, "%d %d %c\n", &(res->width), &(res->heigth), &(res->bg)) != 3))
        return (1);
    if ((res->width <= 0 && res->width > 300) || (res->heigth <= 0 && res->width > 300))
        return (1);
    return(0);
}

void    display_map(char **map, int width, int heigth)
{
    int i;

    i = 0;
    while (map[i])
    {
        putstr(map[i], ft_strlen(map[i]));
        write(1, "\n", 1);
        i++;
    }
}

int     ft_draw(FILE *fd, char **map, t_res res)
{
    char type;
    float x;
    float y;
    int ymax;
    int xmax;
    char draw;
    int i;
    int j;
    float width;
    float heigth;

    i = 0;
    if (fscanf(fd, "%c %f %f %f %f %c", &type, &x, &y, &width, &heigth, &draw) == 6)
    {
        ymax = (int)y + heigth;
        xmax = (int)x + width;

        while (i < res.width)
        {
            j = 0;
            while (j < res.heigth)
            {
                if ((j >= (int)x && j <= xmax) && (i >= (int)y && i <= ymax))
                {
                    if (type == 'R')
                        map[i][j] = draw;
                    else if (type == 'r')
                    {
                        if (j == x || j == xmax || i == y || i == ymax)
                            map[i][j] = draw;
                    }
                }
                j++;
            }
            i++;
        }
    }
    return (0);
}

int main(int ac, char **av)
{
    FILE *fd;
    t_res res;
    char **map;
    int i;
    char *error = "Error: argument\n";
    char *error1 = "Error: Operation file corrupted\n";
    if (ac != 2)
    {
        putstr(error, ft_strlen(error));
        return (1);
    }
    fd = fopen(av[1], "r");
    if (!fd)
    {
        putstr(error1, ft_strlen(error1));
        return (1);
    }
    if (first_line(&res, fd) == 1)
    {
        putstr(error1, ft_strlen(error1));
        return (1);
    }
    if (!(map = malloc(sizeof(char *) * (res.heigth + 1))))
        return (1);
    i = 0;
    printf ("width %d and heigth %d\n", res.width, res.heigth);
    while (i < res.heigth)
    {
        if (!(map[i] = (char *)malloc(sizeof(char) * (res.width + 1))))
            return (1);
        map[i][res.width] = '\0';
        i++;
    }
    i = 0;
    map[res.heigth] = 0;
    while (i < res.heigth)
    {
        memset(map[i], res.bg, res.width);
        i++;
    }
    ft_draw(fd, map, res);
    display_map(map, res.width, res.heigth);
}
