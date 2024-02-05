# minishell

42 project, recoding our own little bash. A program capable of parsing a prompt and launching executables with arguments, along with a few built-in functions.

### How to use it

Using ``make`` will create the ``minishell`` executable.

Simply run it with :

```
./minishell
```

### Mandatory part

Minishell runs executables from an absolute, relative or environment PATH (``/bin/ls`` or ``ls``), including arguments or options. ``'`` and ``"`` work the same as bash, except for multiline commands.

You can use redirections ``>`` ``>>`` ``<`` ``<<`` and pipes ``|``.

Environment variables are handled, like ``$HOME``, including the return code ``$?``.

Finally, you can use ``Ctrl-C`` to interrupt and ``Ctrl-\`` to quit a program, as well as ``Ctrl-D`` to throw an EOF, same as in bash.

A few of the functions are "built-in", meaning we don't call the executable, we re-coded them directly. It's the case for ``echo``, ``pwd``, ``cd``, ``env``, ``export``, ``unset`` and ``exit``.

### Credit

This project was done with [begarijo](https://github.com/begarijo).
