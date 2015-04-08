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

## ToDo:

File redirection should be handled by `kash_exec`, it is simpler than trying to pass the input, output, error, and bg/fg information to each `command_t`.

Need to change `make_command` for this. Can also remove `pipe_command_t` and use only `command_t`.

## Features Implemented

- All built-in commands:
    - exiting
    - aliasing
    - set / unset env
    - printing aliases and environment
    - cd
- Basic (single) command execution
- Basic output file stdout redirection
- Pipelines
- Input file redirection

## Features Not Implemented

The only basic infrastructure not yet implemented is support for pipes. Once this is done, all of the other unimplemented features should come together fairly easily.

- Alias resolving
    - Function exists, but is not yet hooked up.
- Stderr redirection
- background / foreground
- Appending to a file for stdout redirect
- Wildcard matching
- Variable expansion
- Excluding metacharacters from `words` (except when escaped)
- Extra credit:
    - tilde expansion
    - tab completion

## Known Bugs

- find all char* memory leaks...
    - args
    - arglists
    - after command execution

cmd_list_ety: /* empty */ { $$ = NULL; }
    | cmd_list { $$ = $1; }
    ;

cmd_list:
    cmd { $$ = make_command_list($1, NULL); }
    | cmd_list PIPE cmd {
        $$ = make_command_list($3, $1);
      }
    ;
