```
                  _  __         _     
                 | |/ /__ _ ___| |__  
                 | ' // _` / __| '_ \ 
                 | . \ (_| \__ \ | | |
                 |_|\_\__,_|___/_| |_|
                            
                        a basic UNIX shell in C
```

# kash
Korn Again SHell for COP4600

### Authors

[Connor Jacobsen](https://github.com/connorjacobsen) && [Brett Swikle](https://github.com/bswike)

Although all of the commits (currently) belong to me, Brett was instrumental to completing this project, and many of the commits were a result of pair programming.

Some known bugs were left in, and speed was prioritized over completeness, as we needed to get everything (mostly) working by a deadline.

## About

Kash was the final assignment for COP4600 -- implementing a Unix shell with some Korn Shell features, and others that weren't.

## Features Implemented

- All built-in commands:
    - exiting
    - aliasing
    - set / unset env
    - printing aliases and environment
    - cd
- Basic (single) command execution
- Basic output file stdout redirection
- Appending to a file for stdout redirect
- Pipelines
- Input file redirection
- Stderr redirection
- Variable expansion
- Alias resolving
- background / foreground
- Wildcard matching

## Features Not Implemented

- tilde expansion
- tab completion

## Shell Types

| Type | Description |
| :----: | ----------- |
| __word__ | We will use *word* to refer to a sequence of characters which are treated as a logical unit, sometimes referred to as a *token*. *Words* are separated by white space, newlines, and metacharacters. Any other character is valid in a word. If you wish a *word* to contain white space, then you must put double quotes around it. For example, your scanner should interpret `echo test > foo` as 3 words and one metacharacter. However, the command `echo "test > foo"` would be interpreted by the scanner as 2 words, echo and `test > foo` (note that the “” have been removed from `"test > foo"`). |
| __white space__ | White space consists of the characters space and tab. |
| __metacharacters__ |  Metacharacters are characters which have special meaning to the shell, and stand only for themselves. Metacharacters cannot be part of a word unless they are preceded by a \ or are inside quotes. The following are metacharacters: < > \| " \ & |

## Built In Commands

| Command | Description |
| ----------------- | ----------- |
| __setenv variable word__ | This command sets the value of the variable *variable* to be *word*. |
| __printenv__ |  This command prints out the values of all the environment variables, in the format *variable=value*, one entry per line. |
| __unsetenv variable__ | This command will remove the binding of *variable*. If the variable is unbound, the command is ignored. |
| __cd word_directory_name__ | This command changes the current directory to the one named. You must handle *cd* with no arguments, to take you back to the home directory. |
| __alias name word__ | Adds a new alias to the shell. See the subsection on aliases for more information. |
| __unalias name__ | Remove the alias for *name* |
| __bye__ | Gracefully quit the shell. |

## Other Commands

`kash` can accept other commands of the following form:

`cmd [arg]* [|cmd [arg]*]* [ < fn1 ] [ >[>] fn2 ] [ 2>fn3 || 2>&1 ] [&]`

More on other commands:

Note that the I/O redirection can only appear at the end of the line in your shell. The construct 2>file redirects the standard error of the program to file, while 2>&1 connects the standard error of the program to its standard output. If cmd does not contain a /, the shell must check the directories on the path that is the value of the environment variable path for the commands. Only check those directories that are on the path, i.e., if the current directory is not in the path, do not look in the current directory. Only if the file exists and is executable, it should be run. You must also be able to handle piping and I/O redirection on builtin commands. If & exists at the end of the line, then the shell will execute this command in the backgound. If & doesn’t exist, then the shell will wait for this command to finish.

## Aliases

Implements a subset of the `ksh` alias mechanism. Only provides simple string substitutions.

| Command | Description |
| ------- | ----------- |
| __alias__ | The `alias` command with no arguments lists all of the current aliases. |
| __alias name word__ | This `alias` command adds a new alias to the shell. An alias is essentially a shorthand form of a long command. For example, you may have an alias `alias lf "/bin/ls -F"` set up so that whenever you type `lf` from the command line, the command that is executed is `/bin/ls -F`. Note that alias expansion is only performed on the *first* word of a command. However, aliases may be nested. |
| __unalias name__ | The `unalias` command is used to remove the alias for `name` from the alias list. |

## Environment Variable Expansion

It is also possible to include environment variables as part of words inside command lines. The shell reads all the characters from `${` to the next `}` and assumes it is the name of a variable. The value, if any, of the variable is substituted.

## Wildcard Matching

Many shells do filename generation with wildcarding. You will implement a subset of the functionality found in most shells. Before a command is executed, each command word should be scanned for the characters `*` and `?`. If one of these characters appears the word is regarded as a pattern. The word is replaced with alphabetically sorted filenames that match the pattern. If no filename is found that matches the pattern, the word is left unchanged. 

A `*` matches any string, including the null string. A `?` matches any single character. The character ‘.’ at the start of a filename or immediately following a ‘/’, as well as the character ‘/’ itself, must be matched explicitly

## Building and Running Kash

To build kash:

```bash
$ make
```

To run kash:

```
$ ./kash
```

To clean the directory before building again:

```
$ make clean
```

## Known Bugs

- Kash doesn't clean up after itself too well, so eventually it will probably consume all of your kernel memory if you let it, but that will probably take a long, long time.
    - Main offenders include:
        - `command_list_t`, `command_t`, `arglist_t`, and `arg_t` objects. These should be cleaned up after command execution, but are not.
- aliases resolve immediately, and for items other than the first word of a command.
- When environment variable values are smaller than the variable that represents them, and there are no quotations involved, we get some weird mash up of the two items, probably due to not pushing enough whitespace back onto the input stream.
