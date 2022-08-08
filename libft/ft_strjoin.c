/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 18:20:53 by zoukaddo          #+#    #+#             */
/*   Updated: 2021/11/17 22:04:50 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	ft_strcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while (src[i] && i < (size))
		{
			dst[i] = src[i];
			i++;
		}
	}
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	int		s1_len;
	int		s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ptr = (char *)malloc(s1_len + s2_len + 1);
	if (!ptr)
		return (NULL);
	ft_strcpy(ptr, s1, s1_len);
	ft_strcpy(ptr + s1_len, s2, s2_len);
	ptr[s1_len + s2_len] = 0;
	return (ptr);
}

/*int    main()
{
    char s1[] = "ayo";
    char s2[] = "klo";
    printf("%s",ft_strjoin(,));

}*/
