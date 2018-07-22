/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_record.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwright <mlwright09@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 22:44:22 by mwright           #+#    #+#             */
/*   Updated: 2017/05/05 22:54:05 by mwright          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

void	clear_stdin_buff(void)
{
	int		c;

	while ((c = getchar()) != '\n')
		continue;
}

t_node	*find_node_by_id(t_node *nodes, int id)
{
	while (nodes)
	{
		if (nodes->id == id)
			return (nodes);
		nodes = nodes->next;
	}
	return (NULL);
}

int		update_confirmprompt(char *type)
{
	char	update_details;

	update_details = 42;
	while (update_details != 'y' && update_details != 'n')
	{
		ft_putstr("\x1b[36mDo you want to update the ");
		ft_putstr(type);
		ft_putendl(" for this node? (y/n)\33[0m");
		scanf(" %c", &update_details);
		clear_stdin_buff();
	}
	if (update_details == 'y')
		return (1);
	else
		return (0);
}

t_node	*update_record(t_node *nodes)
{
	int		node_id;
	int		nodecount;
	t_node	*node;

	if (!nodes)
	{
		ft_putstr("Database is currently empty.  Try CREATE first.");
		return (NULL);
	}
	node_id = -1;
	nodecount = node_count(nodes);
	while (node_id == -1 || !find_node_by_id(nodes, node_id))
	{
		ft_putendl("\x1b[36mPlease enter the ID of the node you would like to update (integer only):\33[0m");
		scanf("%i", &node_id);
		clear_stdin_buff();
	}
	node = find_node_by_id(nodes, node_id);
	print_node(node, 1);
	update_details(&node);
	ft_putendl("Update complete.");
	return (nodes);
}
