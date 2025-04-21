# C - Simple Shell

## Description
A pedagogical exercise in recreating shell's essential mechanisms, following Holberton's project-based learning approach.

## Progression
Our shell can handle the commands existing in the "PATH" envrionnement variable, and the following built-ins : ```exit```, ```env```.

It could be improved by :
- Handleing ```Ctrl+c```, the shell should not quit when the input is ```^C```,
- Implementing more built-ins functions like ```setenv```, ```unsetenv```, ```cd```, ```help```, ```alias``` and the ```history```,
- Handleing the command separator ```;```,
- Handleing the ```&&``` and ```||``` logical operators,
- Handleing variables remplacement,
- Handleing ```$$``` and ```$?``` variables,
- Handleing comments with ```#```,
- Handleing files for input.

## Compilation Command
```gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh```

## Requirements
- Editors: ```vi``` using VSCODE,
- Compile on Ubuntu 20.04 LTS,
- To compile we will use ```gcc``` using the options ```-Wall -Werror -Wextra -pedantic -std=gnu89```,
- Our code should use the Betty style. It will be checked using betty-style.pl and betty-doc.pl,
- No more than 5 functions per file,
- All our header files should be include guarded,
- We use system calls only when we need to.
- The output and error output must be the same as ```sh``` in most cases.

## Exemples and testing
Here are some exemples of the use of our shell :

```valentin@Valou-PC:~/holbertonschool-simple_shell$ ./hsh
$ ls
README.md  Shared_diagram-VD.jpg  VD_tests  builtin.c  exec.c  generate-authors.sh  helper.c  hsh  main.c  path.c  read.c  shell  shell.h  split.c
$ pwd
/home/valentin/holbertonschool-simple_shell
$ exit
valentin@Valou-PC:~/holbertonschool-simple_shell$ ```

## Man page
The man page provides a detailed explanation of the function. To see the full documentation, run our man page like this: ```man hsh```

## Testing
We have made a testing script .
Here are some exemples:

```c

```

We also used valgrind to be sure there is no memory leaks or issues :
```valgrind ./hsh```

## Flowchart
![alt text](Shared_diagram-VD.jpg)

## Authors
* 
* 
* Valentin Dumont https://github.com/proser-v