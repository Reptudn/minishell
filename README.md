# Minishell
The objective of this project is for you to create a simple shell.

# Resources
- [pipes](https://reactive.so/post/42-a-comprehensive-guide-to-pipex)
- [minishell guide](https://achrafbelarif.medium.com/42cursus-minishell-29cd25f972e6)

# Overview
## Parsing
Parsing bezieht sich auf den Prozess des Zerlegens oder Analysierens einer Eingabezeile oder eines Befehls in seine Bestandteile, um deren Struktur und Bedeutung zu verstehen.
Während des Parsings analysiert die Shell die Eingabezeile, um Befehle, Optionen, Argumente und andere Elemente zu identifizieren und zu interpretieren.
Dieser Prozess umfasst das Identifizieren von Schlüsselwörtern, Symbolen und Syntaxregeln, um den Befehl korrekt zu interpretieren und vorzubereiten.
Beim Parsen werden auch Variablenersetzung, Befehlsausführung und andere Funktionen berücksichtigt, die Teil der Shell-Syntax sind.

## Ausführung
Die Ausführungsphase tritt auf, nachdem der Parsing-Prozess abgeschlossen ist und die Shell den Befehl korrekt interpretiert hat.
In dieser Phase führt die Shell die Befehle und Aktionen aus, die durch den geparsten Befehl definiert sind.
Dies kann bedeuten, dass Programme gestartet, Dateien erstellt oder bearbeitet, Umgebungsvariablen gesetzt oder andere Aktionen ausgeführt werden, die vom Befehl angegeben sind.
Die Ausführung kann auch die Ausgabe von Text auf dem Bildschirm, das Lesen von Eingaben vom Benutzer oder andere interaktive Aktionen umfassen, die Teil des Befehls sind.

# Timeline
- [x] Endless loop for Commands
- [x] Parsing
	- [x] Linked List for Arguments:
		```c
		#define NONE 0 (none)
		#define PIPE 1 ( | )
		#define OR 2 ( || )
		#define AND 3 ( && )
		#define REDIRECT_IN 4 ( < )
		#define REDIRECT_OUT 5 ( > )
		#define REDIRECT_OUT_APPEND 6 ( >> )
		#define REDIRECT_IN_DELIMITER 7 ( << )

		typedef struct s_variable
		{
			char				*name;
			char				*value;
			struct s_variable	*next;
			struct s_variable	*prev;
		}			t_variable;

		typedef struct s_shell
		{
			bool		run;
			char		*path;
			char		**env;
			char		**envp;
			t_variable	*variables;
		}			t_shell;

		typedef struct s_command
		{
			char				*command;
			char				**args;
			int					*operator_type;
			int					priority;
			struct s_command	*next;
			struct s_command	*prev;
			t_shell				*shell;
		}			t_command;
		```
	- [x]  ft_split
		- split after operator
		- if no quote found -> print "not implemented" (for now)
	- [x] malloc for struct and when splitting just copy the content from old split pointer into the new struct pointer then free the split so that all thats malloc after parsing is the pointers in the struct
        - [x] filter out the arguments and put them into the argument linked list


# Components
## Command Handler
- make a function for any operator we got
	- && function
 	- || function
  	- ">>" function
  	- NONE is just the basic stuff run
	- ...
- the main command handler function should be recursive and return 0 when its over
- when only one command is given or only the one command is available and not cmd->next just run this command
- FIX DOUBLE FREE OR SEGV WHEN COMMAND IS BEING RUN AND IT HAS AN OPERATOR OTHER THAN "NONE"
```c
#defince SUCCESS_CMD 0
#define INVALID_TOKEN -1

int	run_command(t_command *cmd); // this runs only one command and that is basically like the old command handler we have but without a loop and we know there is no operator

int	command_hanlder(t_command *cmd1, t_command *cmd2) // or just cmd1 and we get the next one by cmd1->next
{
	if (!cmd1 || (!cmd1 && !cmd2)) // if the first command doesnt exits OR of both commands dont exist return 0 for done
		return (SUCCESS_CMD)
	if (cmd1 && ((*cmd1->operator_type != NONE) && !cmd2)) // if the first command does exist and it has an operator type but there is no operator return error for operator given but no second command (we might have to code completion for that too)
		reutrn (INVALID_TOKEN)
	if (!cmd2)
		run_command(cmd1); // supposed to run only one command -> is handling one command with no operator

	if (cmd1->operator_type == PIPE)
		run_pipe(cmd1, cmd2);
	else if (cmd1->operator_type == OR)
		run_or(cmd1, cmd2);
	else if (cmd1->operator_type == AND)
		run_and(cmd1, cmd2);
	else if (cmd1->operator_type == REDIRECT_IN)
		run_redirect_in(cmd1, cmd2);
	// the rest

	return (command_handler(cmd2, cmd2->next)); // recusively give it the next two commands
}
```

