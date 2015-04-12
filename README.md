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

## Features Not Implemented

- background / foreground
- Wildcard matching
- Extra credit:
    - tilde expansion
    - tab completion

## Known Bugs

- find all char* memory leaks...
    - args
    - arglists
    - after command execution
