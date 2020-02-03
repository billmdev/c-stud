#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define SSHELL_RL_BUFSIZE 1024
char *sshell_read_line(void)
{
  int bufsize = SSHELL_RL_BUFSIZE;
  int position = 0;
  char *buffer = malloc(sizeof(char) * bufsize);
  int c;

  if (!buffer) {
    fprintf(stderr, "sshell: allocation error\n");
    exit(EXIT_FAILURE);
  }

  while (1) {
    c = getchar();

    if (c == EOF || c == '\n') {
      buffer[position] = '\0';
      return buffer;
    } else {
      buffer[position] = c;
    }
    position++;

    if (position >= bufsize) {
      bufsize += SSHELL_RL_BUFSIZE;
      buffer = realloc(buffer, bufsize);
      if (!buffer) {
        fprintf(stderr, "sshell: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
  }
}

#define SSHELL_TOK_BUFSIZE 64
#define SSHELL_TOK_DELIM " \t\r\n\a"
char **sshell_split_line(char *line)
{
  int bufsize = SSHELL_TOK_BUFSIZE, position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token;

  if (!tokens) {
    fprintf(stderr, "sshell: allocation error\n");
    exit(EXIT_FAILURE);
  } 

  token = strtok(line, SSHELL_TOK_DELIM); 
  while (token != NULL) {
    position++;

    if (position >= bufsize) {
      bufsize += SSHELL_TOK_BUFSIZE;
      tokens = realloc(tokens, bufsize * sizeof(char*));
      if (!tokens) {
        fprintf(stderr, "sshell: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, SSHELL_TOK_DELIM);
  }
  tokens[position] = NULL;
  return tokens;
}

int sshell_launch(char **args)
{
  pid_t pid, wpid;
  int status;

  pid = fork();
  if (pid == 0) {
    if (execvp(args[0], args) == -1) {
      perror("sshell");
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    perror("sshell");
  } else {
    do {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}

int sshell_cd(char **args);
int sshell_help(char **args);
int sshell_exit(char **args);

/*
  List of builtin commands, followed by their corresponding functions.
 */
char *builtin_str[] = {
  "cd",
  "help",
  "exit"
};

int (*builtin_func[]) (char **) = {
  &sshell_cd,
  &sshell_help,
  &sshell_exit
};

int sshell_num_builtins() {
  return sizeof(builtin_str) / sizeof(char *);
}

/*
  Builtin function implementations.
*/
int sshell_cd(char **args)
{
  if (args[1] == NULL) {
    fprintf(stderr, "sshell: expected argument to \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("sshell");
    }
  }
  return 1;
}

int sshell_help(char **args)
{
  int i;
  printf("Billy's shell\n");
  printf("Type program names and arguments, and hit enter.\n");
  printf("The following are built in:\n");

  for (i = 0; i < sshell_num_builtins(); i++) {
    printf("  %s\n", builtin_str[i]);
  }

  printf("Use the man command for information on other programs.\n");
  return 1;
}

int sshell_exit(char **args)
{
  return 0;
}

int sshell_execute(char **args)
{
  int i;

  if (args[0] == NULL) {
    // An empty command was entered.
    return 1;
  }

  for (i = 0; i < sshell_num_builtins(); i++) {
    if (strcmp(args[0], builtin_str[i]) == 0) {
      return (*builtin_func[i])(args);
    }
  }

  return sshell_launch(args);
}

void sshell_loop(void)
{
	char *line;
	char **args;
	int status;
	
	do {
	  printf("$ ");
	  line = sshell_read_line(); //Will use Prof's suggestion later
	  args = sshell_split_line(line);
	  status = sshell_execute(args);
		
	  free(line);
	  free(args);
	} while (status);
}

int main(int argc, char **argv)
{
  // Load config files, if any.

  // Run command loop.
  sshell_loop();

  // Perform any shutdown/cleanup.

  return EXIT_SUCCESS;
}

