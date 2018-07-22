/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   labels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwright <mlwright09@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 21:23:11 by mwright           #+#    #+#             */
/*   Updated: 2017/05/05 22:30:50 by mwright          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

void	tag_it(int res, FILE *f)
{
	char	tag[50];

	if (res > 0)
	{
		fprintf(f, "\t\"tags\":[");
		while (res > 0)
		{
			printf("Type one tag, then press enter\n");
			scanf(" %[^},\n]", tag);
			clear_stdin();
			fprintf(f, "\"%s\"", tag);
			if (res > 1)
				fprintf(f, ",");
			res--;
		}
		fprintf(f, "]");
	}
	fprintf(f, "\n}");
}

void	create_tag(FILE *f)
{
	int	res;

	res = 0;
	printf("\x1b[36mHow many tags would you like to add for this entry?\n");
	if (!scanf("%i", &res))
	{
		printf("That was not an integer...\n");
		clear_stdin();
		fprintf(f, "\t\"tags\":[\"no tag\"]\n}");
		return ;
	}
	if (res == 0)
	{
		fprintf(f, "\t\"tags\":[\"no tag\"]\n}");
		return ;
	}
	tag_it(res, f);
}

int		end_id(FILE *f)
{
	int		r;
	char	*str;

	r = 0;
	f = fopen("db.txt", "r");
	str = (char *)malloc(5);
	if (fgets(str, 3, f) != NULL)
		r = atoi(str);
	return (r);
}

void	detail_entry(int detail_lines, FILE *f)
{
	char	detail_name[50];
	char	detail_val[50];
	int		count;

	count = 1;
	while (detail_lines > 0)
	{
		printf("%i Enter detail field name:\n", count);
		scanf(" %[^},\n]", detail_name);
		clear_stdin();
		printf("%i Enter detail value:\n", count);
		scanf(" %[^},\n]", detail_val);
		clear_stdin();
		fprintf(f, "\n\t\t \"%s\" = \"%s\"", detail_name, detail_val);
		if (detail_lines > 1)
			fprintf(f, ",");
		detail_lines--;
		count++;
	}
	fprintf(f, "\n");
}

int		create_label(FILE *f)
{
	char		label[50];
	int			detail_lines;
	static int	id;

	detail_lines = 0;
	id = end_id(f);
	printf("\x1b[36mEnter a label for the new node ('}'',' are not recognized)\n");
	scanf(" %[^},\n]", label);
	clear_stdin();
	printf("\x1b[32mHow many details do you want to enter for this node (int)\n");
	if (!(scanf("%i", &detail_lines)) || detail_lines == 0)
	{
		printf("Error, invalid entry...Try again\n");
		return (id);
	}
	fprintf(f, "    \n{\n\t\"ID\": \"%i\",\n", id++);
	fprintf(f, "\t\"label\": \"%s\",\n", label);
	if (detail_lines > 0)
		fprintf(f, "\t\"details\":");
	detail_entry(detail_lines, f);
	create_tag(f);
	return (id);
}
