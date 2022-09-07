alias: alias
       Define or display aliases.

    Without arguments, `alias' prints the list of aliases in the reusable
    form `alias NAME=VALUE' on standard output.

    Otherwise, an alias is defined for each NAME whose VALUE is given.
    A trailing space in VALUE causes the next word to be checked for
    alias substitution when the alias is expanded.

    Options:
	NONE
    Exit Status:
    alias returns true unless a NAME is supplied for which no alias has been
    defined.

cd: cd
    Change the shell working directory.

    Change the current directory to DIR.  The default DIR is the value of the
    HOME shell variable.

    The variable CDPATH defines the search path for the directory containing
    DIR.  Alternative directory names in CDPATH are separated by a colon (:).
    A null directory name is the same as the current directory.  If DIR begins
    with a slash (/), then CDPATH is not used.

    Exit Status:
    Returns 0 if the directory is changed, and if $PWD is set successfully when
    -P is used; non-zero otherwise.

env: env
    Print environment

    Options:
	NONE

      Return environment to standard output.

help: help
    Display information about builtin commands.

    Displays brief summaries of builtin commands.  If PATTERN is
    specified, gives detailed help on all commands matching PATTERN,
    otherwise the list of help topics is printed.

    Exit Status:
    Returns success unless PATTERN is not found or an invalid option is given.

history: history
    Display or manipulate the history list.

    Display the history list with line numbers, prefixing each modified
    entry with a `*'.  An argument of N lists only the last N entries.

    Exit Status:
    Returns success unless an invalid option is given or an error occurs.

setenv: setenv
    Set values of environment variables.

    Exit Status:
    Returns success unless an invalid option is given.

unalias: unalias
    Remove each NAME from the list of defined aliases.

    Return success unless a NAME is not an existing alias.

unsetenv: unsetenv
	Remove each NAME from the list of defined environment variables.

	Options:
	NONE. I mean, really, who do you think wrote this? Ken Thompson or Dennis Ritchie?


	No...
	Return success unless a NAME is not an existing alias.

unset: unset
    Unset values and attributes of shell variables and functions.

    For each NAME, remove the corresponding variable or function.
    Without options, unset first tries to unset a variable, and if that fails,

    Exit Status:
    Returns success unless an invalid option is given or a NAME is read-only.
