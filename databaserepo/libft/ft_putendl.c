/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jargote <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 14:58:39 by jargote           #+#    #+#             */
/*   Updated: 2016/11/11 15:44:52 by jargote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl(char const *s)
{
	int		len;

	if (s)
	{
		len = 0;
		while (s[len] != '\0')
			len++;
		write(1, s, len);
		write(1, "\n", 1);
	}
}