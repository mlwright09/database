/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_details.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwright <mlwright09@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 22:44:43 by mwright           #+#    #+#             */
/*   Updated: 2017/05/05 22:58:54 by mwright          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

void		update_detailfound(t_data_item **dataitem, int i)
{
	t_data_item	*details;
	char		new_dname[20];
	char		new_dvalue[50];

	details = *dataitem;
	ft_putstr("\x1b[36mPlease enter the new detail name for index ");
	ft_putnbr(i);
	ft_putstr(" (limit to 20 characters; do not include commas (,)):\n\33[0m");
	scanf(" %[^},\n]", new_dname);
	clear_stdin_buff();
	free(details->key);
	details->key = ft_strnew(ft_strlen(new_dname));
	ft_memcpy(details->key, new_dname, ft_strlen(new_dname));
	ft_putstr("\x1b[36mPlease enter the new detail value for index ");
	ft_putnbr(i);
	ft_putstr(" (limit to 50 characters; do not include commas (,)):\n\33[0m");
	scanf(" %[^},\n]", new_dvalue);
	clear_stdin_buff();
	free(details->value);
	details->value = ft_strnew(ft_strlen(new_dvalue));
	ft_memcpy(details->value, new_dvalue, ft_strlen(new_dvalue));
	ft_putstr("\x1b[36mEntry updated for detail at index ");
	ft_putnbr(i);
	ft_putstr(".\n");
	*dataitem = details;
}

void		update_nodedetail(t_data_item **dataitem, int i)
{
	t_data_item	*details;
	int			count;
	int			found;

	count = 1;
	found = 0;
	details = *dataitem;
	while (details && !found)
	{
		if (count == i)
			found = 1;
		else
			details = details->next;
		count++;
	}
	if (found)
	{
		update_detailfound(&details, i);
	}
	else
	{
		ft_putstr("Detail index ");
		ft_putnbr(i);
		ft_putstr(" not found.\n");
	}
	if (details)
		details = *dataitem;
	else
	{
		while (details->prev)
			details = details->prev;
		*dataitem = details;
	}
}

static void	validate_index(int **detail_index, int *i, char *istr, int amt)
{
	int		*d_i;

	*i = ft_atoi(ft_strtrim(istr));
	if (*i < 1 || *i > amt)
	{
		d_i = *detail_index;
		free(d_i);
		d_i = NULL;
		*detail_index = d_i;
	}
}

int			*update_detailsinput(int *strcount, int detailcount)
{
	char	detail_index[100];
	char	**d_i_split;
	int		*d_i;
	int		i;

	d_i = NULL;
	while (d_i == NULL)
	{
		ft_putendl("\x1b[36mPlease enter the index number of the details you wish to update (you may choose more than one in the following format excluding quotes: \"1, 3\"):\33[0m");
		scanf(" %[^\n]", detail_index);
		clear_stdin_buff();
		if (!(d_i_split = ft_strsplit(detail_index, ',')))
			return (NULL);
		*strcount = arrlen(d_i_split);
		if (!(d_i = (int *)malloc(sizeof(int) * *strcount)))
			return (NULL);
		i = -1;
		while (d_i_split[++i] && d_i)
			validate_index(&d_i, &d_i[i], d_i_split[i], detailcount);
		free(d_i_split);
	}
	return (d_i);
}

void		update_details(t_node **node)
{
	int		*d_i;
	int		i;
	int		strcount;
	t_node	*n;

	if (update_confirmprompt("details"))
	{
		n = *node;
		d_i = NULL;
		strcount = 0;
		d_i = update_detailsinput(&strcount, dataitem_count(n->details));
		i = 0;
		while (i < strcount)
		{
			update_nodedetail(&n->details, d_i[i]);
			i++;
		}
		*node = n;
	}
}
