// NEEDS HEADER

#include "ft_db.h"

int		node_count(t_node *nodes)
{
	int		count;

	count = 0;
	while (nodes)
	{
		count++;
		nodes = nodes->next;
	}
	return (count);
}

void	writetofile(FILE *f, t_node *node)
{
	int		i;
	int		detailscount;
	int		tagcount;

	fprintf(f, "{\n");
	fprintf(f, "\t\"ID\": \"%i\",\n", node->id);
	fprintf(f, "\t\"label\": \"%s\",\n", node->label);
	fprintf(f, "\t\"details\":\n");
	i = 0;
	detailscount = dataitem_count(node->details);
	while (node->details)
	{
		fprintf(f, "\t\t\"%s\" = \"%s\"", node->details->key, node->details->value);
		if (++i < detailscount)
			fprintf(f, ",");
		fprintf(f, "\n");
		node->details = node->details->next;
	}
	fprintf(f, "\t\"tags\":[");
	i = -1;
	tagcount = arrlen(node->tags);
	while (node->tags[++i])
	{
		fprintf(f, "\"%s\"", node->tags[i]);
		if (i < tagcount - 1)
			fprintf(f, ",");
	}
	fprintf(f, "]\n");
	fprintf(f, "}\n");
}

int		nodestofile(t_node *nodes, char *fname)
{
	FILE	*f;

printf("%s\n", fname);
	if (!(f = fopen(fname, "w+")))
		return (0);
	while (nodes)
	{
		writetofile(f, nodes);
		nodes = nodes->next;
	}
	fclose(f);
	return (1);
}
