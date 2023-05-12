#include "../inc/minishell.h"

void	error_message(char *message, int exit_status, ...)
{
	va_list	arg;

	va_start(arg, exit_status);
	ft_printf(ERR, message, arg);
	va_end(arg);
	g_shell->exit_status = exit_status;
}
