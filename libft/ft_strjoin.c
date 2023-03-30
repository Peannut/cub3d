/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 18:20:53 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/03/30 16:21:02 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// static	void	ft_strcpy(char *dst, const char *src, size_t size)
// {
// 	size_t	i;

// 	i = 0;
// 	if (size > 0)
// 	{
// 		while (src[i] && i < (size))
// 		{
// 			dst[i] = src[i];
// 			i++;
// 		}
// 	}
// }

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	char	*ptr;
// 	int		s1_len;
// 	int		s2_len;

// 	if (!s1 || !s2)
// 		return (NULL);
// 	s1_len = ft_strlen(s1);
// 	s2_len = ft_strlen(s2);
// 	ptr = (char *)malloc(s1_len + s2_len + 1);
// 	if (!ptr)
// 		return (NULL);
// 	ft_strcpy(ptr, s1, s1_len);
// 	ft_strcpy(ptr + s1_len, s2, s2_len);
// 	ptr[s1_len + s2_len] = 0;
// 	return (ptr);
// }

char	*ft_strjoin2(char *s1, char const *s2)
{
	char	*s;
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (!s1 || !s2)
	{
		free(s1);
		return (NULL);
	}
	s = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s)
		return (NULL);
	while (s1[++i])
		s[i] = s1[i];
	while (s2[++j])
		s[i + j] = s2[j];
	s[i + j] = '\0';
	free(s1);
	return (s);
}

char	*ft_strjoin2c(char *s, char c)
{
	int		i;
	char	*str;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
		i++;
	str = malloc(sizeof(char) * i + 2);
	if (!str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = c;
	str[i + 1] = '\0';
	free(s);
	return (str);
}
