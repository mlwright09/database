/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   query_record.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwright <mlwright09@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 23:02:55 by mwright           #+#    #+#             */
/*   Updated: 2017/05/05 23:38:55 by mwright          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

int			arrlen(char **arr)
{
	int		len;

	if (arr == NULL)
		return (0);
	len = 0;
	while (arr[len])
		len++;
	return (len);
}

int			dataitem_count(t_data_item *dataitem)
{
	int		count;

	count = 0;
	while (dataitem)
	{
		dataitem = dataitem->next;
		count++;
	}
	return (count);
}

void		print_dataitem(t_data_item *data, int index)
{
	int		i;
	int		count;

	i = 1;
	count = dataitem_count(data);
	while (data)
	{
		if (data->key && data->value)
		{
			if (index)
			{
				ft_putstr("\t\t");
				ft_putnbr(i);
				ft_putstr(") ");
				ft_putstr(data->key);
				ft_putstr(" = ");
				ft_putstr(data->value);
			}
			else
			{
				ft_putstr("\t\t");
				ft_putstr(data->key);
				ft_putstr(" = ");
				ft_putstr(data->value);
			}
			if (i < count)
				ft_putstr("\n");
			i++;
		}
		data = data->next;
	}
}

void		print_tags(char **tags)
{
	int		i;
	int		total;

	if (tags)
	{
		total = arrlen(tags);
		i = 0;
		while (tags[i])
		{
			ft_putstr(tags[i]);
			if (i < total - 1)
				ft_putstr(", ");
			i++;
		}
	}
}

void		print_node(t_node *node, int detail_index)
{
	ft_putstr("\tID: ");
	ft_putnbr(node->id);
	ft_putstr("\n\tLabel: ");
	ft_putendl(node->label);
	ft_putstr("\tDetails:\n");
	if (node->details)
	{
		if (detail_index)
			print_dataitem(node->details, detail_index);
		else
			print_dataitem(node->details, detail_index);
		ft_putstr("\n");
	}
	ft_putstr("\tTags: ");
	if (node->tags)
		print_tags(node->tags);
	ft_putstr("\n\n");
}

void		add_dataitem(t_data_item **head, t_data_item *new)
{
	t_data_item	*h;

	h = *head;
	if (!h)
		*head = new;
	else
	{
		while (h->next)
			h = h->next;
		h->next = new;
		new->prev = h;
		while (h->prev)
			h = h->prev;
		*head = h;
	}
}

t_data_item	*init_dataitem(char *data)
{
	t_data_item		*data_item;
	int				len;

	if (!(data_item = (t_data_item *)malloc(sizeof(t_data_item))))
		return (NULL);
	len = ft_memchrlen(ft_strtrim(data), '=', ft_strlen(data));
	if (!(data_item->key = ft_strnew(len - 1)))
		return (NULL);
	if (!(data_item->value = ft_strnew(ft_strlen(&data[len]))))
		return (NULL);
	data_item->key = ft_strsub(data, 1, len - 3);
	data_item->value = ft_strsub(&data[len], 3, ft_strlen(&data[len]) - 4);
	data_item->next = NULL;
	data_item->prev = NULL;
	return (data_item);
}

char		*strremove_dquotes(char *str)
{
	int		i;
	int		j;
	char	*no_dquotes;
	int		len;

	no_dquotes = NULL;
	if (str)
	{
		i = 0;
		len = 0;
		while (str[i++])
			if (str[i] != '\"')
				len++;
		if (!(no_dquotes = ft_strnew(len)))
			return (NULL);
		i = 0;
		j = 0;
		while (str[i++])
		{
			if (str[i] != '\"')
				no_dquotes[j++] = str[i];
		}
	}
	return (no_dquotes);
}

t_node		*init_node(char *data)
{
	int			i;
	char		*res;
	char		**details;
	char		**tags;
	t_node		*node;
	int			j;
	t_data_item	*dataitem;
	char		*temp;

	if (!(node = (t_node *)malloc(sizeof(t_node))))
		return (NULL);
	i = 0;
	res = ft_strstr(data, "\"ID\": ");
	res = ft_strsub(res, 7, ft_strstrlen(res, "\",") - 7);
	node->id = ft_atoi(res);
	res = ft_strstr(data, "\"label\": ");
	res = ft_strsub(res, 10, ft_strstrlen(res, "\",") - 10);
	if (!(node->label = ft_strnew(ft_strlen(res))))
		return (NULL);
	node->label = ft_strcpy(node->label, res);
	res = ft_strstr(data, "\"details\":");
	if (res)
	{
		res = ft_strsub(res, 12, ft_strstrlen(res, "\n\t\"tags\":") - 12);
		if (!(details = ft_strsplit(res, ',')))
			return (NULL);
		j = 0;
		node->details = NULL;
		while (details[j])
		{
			if (!node->details)
			{
				node->details = init_dataitem(ft_strtrim(details[j]));
			}
			else
			{
				dataitem = NULL;
				dataitem = init_dataitem(ft_strtrim(details[j]));
				add_dataitem(&node->details, dataitem);
			}
			j++;
		}
	}
	else
		node->details = NULL;
	res = ft_strstr(data, "\"tags\":[");
	if (res)
	{
		res = ft_strsub(res, 8, ft_strstrlen(res, "]") - 8);
		temp = res;
		res = strremove_dquotes(res);
		free(temp);
		if (!(tags = ft_strsplit(ft_strtrim(res), ',')))
			return (NULL);
		node->tags = tags;
	}
	else
		node->tags = NULL;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void		add_node(t_node **head, t_node *new)
{
	t_node	*h;

	h = *head;
	if (!h)
		*head = new;
	else
	{
		while (h->next)
			h = h->next;
		h->next = new;
		new->prev = h;
		while (h->prev)
			h = h->prev;
		*head = h;
	}
}

int		lstfindval(t_list *lst, char *val)
{
	while (lst)
	{
		if (!ft_memcmp(lst->content, val, lst->content_size))
			return (1);
		lst = lst->next;
	}
	return (0);
}

t_list		*unique_tags(t_node *nodes)
{
	t_list	*tags;
	t_list	*t;
	int		unique;
	int		i;

	tags = NULL;
	while (nodes)
	{
		if (nodes->tags)
		{
			i = 0;
			while (nodes->tags[i])
			{
				unique = 1;
				if (lstfindval(tags, nodes->tags[i]))
					unique = 0;
				if (unique)
				{
					if (!tags)
					{
						if (!(tags = ft_lstnew(nodes->tags[i], ft_strlen(nodes->tags[i]))))
							return (NULL);
					}
					else
					{
						t = NULL;
						if (!(t = ft_lstnew(nodes->tags[i], ft_strlen(nodes->tags[i]))))
							return (NULL);
						ft_lstadd(&tags, t);
					}
				}
				i++;
			}
		}
		nodes = nodes->next;
	}
	return (tags);
}

t_list		*unique_labels(t_node *nodes)
{
	t_list	*labels;
	t_node	*n;
	int		unique;
	t_list	*t;

	labels = NULL;
	while (nodes)
	{
		n = nodes->next;
		unique = 1;
		while (n && unique)
		{
			if (!n || !ft_strcmp(nodes->label, n->label))
				unique = 0;
			n = n->next;
		}
		if (unique)
		{
			if (!labels)
			{
				if (!(labels = ft_lstnew(nodes->label, ft_strlen(nodes->label))))
					return (NULL);
			}
			else
			{
				t = NULL;
				if (!(t = ft_lstnew(nodes->label, ft_strlen(nodes->label))))
					return (NULL);
				ft_lstadd(&labels, t);
			}
		}
		nodes = nodes->next;
	}
	return (labels);
}

int			lstcount(t_list *lst)
{
	int		count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

void		lstprintcontent_indexed(t_list *lst)
{
	int		count;
	char	*content;
	int		i;

	count = 1;
	while (lst)
	{
		content = (char *)lst->content;
		printf("%d) ", count);
		i = 0;
		while (i < (int)lst->content_size)
		{
			printf("%c", ((char *)lst->content)[i]);
			i++;
		}
		printf("\n");
		lst = lst->next;
		count++;
	}
}

void		*lstfindnth(t_list *lst, int index)
{
	int		count;

	count = 1;
	while (lst)
	{
		if (count == index)
			return (lst->content);
		lst = lst->next;
		count++;
	}
	return (NULL);
}

char		*prompt_searchfor(t_list *values, char *type)
{
	int		s;
	int		count;
	char	*searchfor;

	s = 0;
	count = lstcount(values);
	while (s == 0 || s > count)
	{
		ft_putstr("\x1b[32mPlease enter the ");
		ft_putstr(type);
		ft_putendl(" you want to search by (enter integer only):\033[0m");
		lstprintcontent_indexed(values);
		scanf("%i", &s);
	}
	searchfor = (char *)lstfindnth(values, s);
	return (searchfor);
}

void		query_data(t_node *nodes, char *label, char *tag)
{
	int		i;
	int		count;

	if (!nodes)
		ft_putendl("The database is currently empty.  Try creating data first.");
	else
	{
		count = 0;
		printf("\x1b[32mQUERY RESULTS:\n\033[0m");
		while (nodes)
		{
			if (label && tag)
			{
				if (nodes->label && !ft_strcmp(nodes->label, label))
				{
					i = 0;
					while (nodes->tags[i])
					{
						if (!ft_strcmp(nodes->tags[i], tag))
						{
							count++;
							print_node(nodes, 0);
						}
						i++;
					}
				}
			}
			else if (!tag && label && nodes->label && !ft_strcmp(nodes->label, label))
			{
				print_node(nodes, 0);
				count++;
			}
			else if (!label && tag && nodes->tags)
			{
				i = 0;
				while (nodes->tags[i])
				{
					if (!ft_strcmp(nodes->tags[i], tag))
					{
						count++;
						print_node(nodes, 0);
					}
					i++;
				}
			}
			nodes = nodes->next;
		}
		if (label && tag)
		{
			printf("\nFOUND %d OBJECTS LABELLED AS ", count);
			i = 0;
			while (i < (int)ft_strlen((char *)label))
			{
				printf("%c", ((char *)label)[i]);
				i++;
			}
			i = 0;
			printf(" AND TAGGED AS ");
			while (i < (int)ft_strlen((char *)tag))
			{
				printf("%c", ((char *)tag)[i]);
				i++;
			}
			printf("\n");
		}
		else if (label)
		{
			printf("\nFOUND %d OBJECTS LABELLED AS ", count);
			i = 0;
			while (i < (int)ft_strlen((char *)label))
			{
				printf("%c", ((char *)label)[i]);
				i++;
			}
			printf("\n");
		}
		else if (tag)
		{
			printf("\nFOUND %d OBJECTS TAGGED AS ", count);
			i = 0;
			while (i < (int)ft_strlen((char *)tag))
			{
				printf("%c", ((char *)tag)[i]);
				i++;
			}
			printf("\n");
		}
		printf("\n\n");
	}
}

t_node		*read_db(char *fname)
{
	int		f;
	t_node	*nodes;
	t_node	*n;
	int		status;
	char	*line;

	if ((f = open(fname, O_RDONLY, S_IREAD)) < 0)
	{
		printf("file does not exist");
		exit(0);
	}
	line = NULL;
	nodes = NULL;
	while ((status = get_next_line(f, &line)) && ft_strlen(line) > 22)
	{
		if (status == -1)
			exit(1);
		n = init_node(line);
		add_node(&nodes, n);
	}
	close(f);
	return (nodes);
}

t_node		*query_record(char *fname)
{
	t_node	*nodes;
	int		searchby;
	t_list	*labels;
	t_list	*tags;
	char	*label;
	char	*tag;

	nodes = read_db(fname);
	searchby = 0;
	while (searchby == 0)
	{
		ft_putendl("\x1b[32mPlease enter by what you want to search by (enter integer only):\033[0m");
		ft_putendl("1) Label");
		ft_putendl("2) Tag");
		ft_putendl("3) Both");
		scanf("%i", &searchby);
	}
	label = NULL;
	tag = NULL;
	if (searchby == 1 || searchby == 3)
	{
		labels = unique_labels(nodes);
		label = prompt_searchfor(labels, "label");
	}
	if (searchby == 2 || searchby == 3)
	{
		tags = unique_tags(nodes);
		tag = prompt_searchfor(tags, "tag");
	}
	query_data(nodes, label, tag);
	return (nodes);
}
