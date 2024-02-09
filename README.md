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
- [ ] Parsing
	- [x] Linked List for Arguments:
		```c
		#define NONE -1 (none)
		#define PIPE 0 ( | )
		#defie OR 1 ( || )
		#define AND 2 ( && )
		#define REDIRECT_IN 3 ( < )
		#define REDIRECT_OUT 4 ( > )
		#define REDIRECT_OUT_APPEND 5 ( >> )
		#define REDIRECT_IN_DELIMITER 6 ( << )

		typedef struct s_command {
			char *command;
			char **args
			int pipe_dings;
			struct s_command *next;
			struct s_command *prev;
		} t_command;
		```
	- [x]  ft_split
		- split after operator
		- if no quote found -> print "not implemented" (for now)
	- [x] malloc for struct and when splitting just copy the content from old split pointer into the new struct pointer then free the split so that all thats malloc after parsing is the pointers in the struct
        - [ ] filter out the arguments and put them into the argument linked list
