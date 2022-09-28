// #include "header.h"

// int check_if_next_quote(t_lexer *lexer)
// {
//     if(lexer->c + 1 == '\'')
//     {
//         return (1);
//     }
//     return(0);
// }

// char	*collect_string_2(t_lexer *lexer, char *join)
// {
// 	char *value;
// 	char *s;
// 	value = ft_calloc(1, sizeof(char));
// 	value[0] = '\0';
// 	while(lexer->c != '\0')
// 	{
// 		if(lexer->c == '\'' || lexer->c == '"')
// 			lexer_advance(lexer);
// 		s = get_current_char_as_string(lexer);
// 		join = ft_strjoin(join, s);
// 		free(s);
// 		lexer_advance(lexer);
// 	}
// 	return (value);
// }