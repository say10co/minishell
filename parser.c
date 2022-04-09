#include "lexer.h"

bool n_parser(t_token_list *lst)
{
	t_token *t;
	char	prev_token;

	if (!lst)
		return 1;
	t = lst->all; 
	while (t)
	{
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
