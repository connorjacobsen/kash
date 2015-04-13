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
- background / foreground
- Wildcard matching

## Features Not Implemented

- Extra credit:
    - tilde expansion
    - tab completion

## Building and Running Kash

To build kash:

```bash
$ make
```

To run kash:

```
$ ./shell
```

To clean the directory before building again:

```
$ make clean
```
