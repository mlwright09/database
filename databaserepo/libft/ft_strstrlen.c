/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstrlen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jargote <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 08:58:23 by jargote           #+#    #+#             */
/*   Updated: 2016/11/11 15:53:33 by jargote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strstrlen(const char *big, const char *little)
{
	unsigned int	i;
	size_t			len;
	char			*ptr;

	i = 0;
	if (*little == '\0')
		return (-1);
	len = ft_strlen(little);
	if (ft_strlen(big) < len)
		return (-1);
	while (big[i] != '\0')
	{
		if (little[0] == big[i])
		{
			ptr = (char *)&big[i];
			if (ft_strnequ(little, &big[i], len))
				return (i);
		}
		i++;
	}
	return (-1);
}
