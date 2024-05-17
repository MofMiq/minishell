# minishell
> This repository contains a "Minishell" project that is part of the École 42 curriculum.

This project is about recoding our own little bash. A program capable of parsing a prompt and launching executables with arguments, along with a few built-in functions.
The main goal is to have a good understanding of process creation and synchronisation using the C programming language.
This was probably the biggest project I've done so far, as well as the first one I did as a group -Investigating and working with Git is a must-.
This is a core project on our path as students within the 42 methodology, as it encompasses many different implementations and concepts, testing the knowledge we have acquired up to this point.

<div align="center">
  <img src="https://github.com/MofMiq/minishell/blob/main/imgs/builtins.gif" width="600"/>
</div>

### How to use it

Using ``make`` will create the ``minishell`` executable.

Simply run it with :

```
./minishell
```

### Mandatory part
1. Display a **prompt** when waiting for a new command and have a working **history**.

2. Minishell runs executables from an absolute, relative or environment **PATH** (``/bin/ls`` or ``ls``), including arguments or options. ``'`` and ``"`` work the same as bash, except for multiline commands.

<div align="center">
  <img src="https://github.com/MofMiq/minishell/blob/main/imgs/quotes.png" width="600"/>
</div>

3. You must redone **redirections** ``>`` ``>>`` ``<`` ``<<`` and pipes ``|``.

<div align="center">
  <img src="https://github.com/MofMiq/minishell/blob/main/imgs/redirections.png" width="600"/>
</div>

4. **Environment** variables are handled, like ``$HOME``, including the return code ``$?``.

5. A few of the functions are **"built-in"**, meaning we don't call the executable, we re-coded them directly. It's the case for ``echo``, ``pwd``, ``cd``, ``env``, ``export``, ``unset`` and ``exit``.

| Command | Description |
|---|---|
|`cd`| Changes the working directory of the current shell execution environment and updates the environment variables `PWD` and `OLDPWD`. <br>Without arguments it change the working directory to the home directory.  <br>`-` changes the directory to the `OLDPWD`. |
|`echo`| Displays a line of text<br>Optional flag `-n`: do not output the trailing newline|
|`env` | Displays the environment variables|
|`exit`| Terminates the shell.<br>Accepts optional argument `n`, which sets the exit status to `n`. |
|`export`| Accepts arguments `name[=value]`.<br>Adds name to the environment.  Set's value of name to `value`.<br>If no argument is given, displays list of exported variables.|
|`pwd`| Shows the current directory as an absolute path.|
|`unset`|Accepts argument `name`. <br> Removes the variable `name` from the environment.|

6. Finally, you can use ``Ctrl-C`` to interrupt and ``Ctrl-\`` to quit a program, as well as ``Ctrl-D`` to throw an EOF, same as in bash.

### What Is Bash and How Does It Work?
The shell is a program that the user can use to interact with an operating system's services. Bash is the GNU shell, and is currently the most common shell program. We took the challenge of recreating bash very literally, so the first thing we did was learn how bash actually works with the help of [this article](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf). Essentially it breaks down the process into 4 steps: lexer → parser → expander → executor, which we replicated in our project.

<div align="center">
  <img src="https://github.com/MofMiq/minishell/blob/main/imgs/bash.png" width="600"/>
</div>

I'll delve further into each step in the implementation section bellow.

### Implementation
#### Lexer
The lexer, also called the tokenizer, takes as the entered line as input. It then reads through the line word by word, using white space as delimiters.  First it checks wether or not the word is a token, ie: `|`, `<`, `<<`, `>`, or `>>`, and otherwise it assumes it is a word.  Which it then adds to the following linked list:

```C
typedef struct s_token
{
	char			*str;
	int			type;
	int			space;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;
```
Each node contains either a `char *` containing the word or a `t_token`.  We also assign each node an index so that we can easily delete them later.

#### The Parser
The lexer then gets sent to the parser which then groups the different nodes together based on the tokens. Basically, in this part, we need to process each token (redirections, pipes, environment variable expansion, etc.) so that when the executor part of the program receives them, it can execute them.

#### Executor
When the parser returns the tokens list back to the main loop and a simple check is done to determine how many commands there are, as they are handled by different functions. However, with the exception of a few builtins, the commands are ultimately executed by the function `execve`, which finds, and if successful, executes the command.

<div align="center">
  <img src="https://github.com/MofMiq/minishell/blob/main/imgs/exec.png" width="600"/>
</div>

### Credit

This project was done with [begarijo](https://github.com/begarijo).
