#include "lexer.h"
/*
void delete_space_node(t_token **t)
{
	t_token *tmp;
	
	if ((*t)->data && (*t)->data[0] == ' ')
	{
		tmp = *t;
		t->next_token = tmp->next_token;
		*t = tmp;
		free(tmp);
	}
}
*/
bool n_parser(t_token_list *lst)
{
	t_token *t;
	char	prev_token;

	if (!lst)
		return 1;
	t = lst->all; 
	while (t)
	{
		//delete_space_node(&t);
		if (t->data == NULL)
			return (printf("Parse Error, Uncolsed quote\n"));
		if (t->is_key && (!t->next_token || !t->next_token->data))
			return (printf("syntax error unexpected token after 'newline'\n"));
		if (t->is_key && (t->next_token && t->next_token->is_key))
			return (printf("syntax error unexpected token '%s'\n", t->next_token->data));
				
		t = t->next_token;
	}
	return (0);
}
