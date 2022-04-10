void	open_deocument(char *eof)
{
	char *buffer;
	
	while (1)
	{
		buffer = readline("heredoc> ");
		if (!ft_strcmp(buffer, eof))
			break;
		write(0, buffer,ft_strlen(buffer));
		free(buffer);
	}
}
