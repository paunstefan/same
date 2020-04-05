# same
`same` is a command line utility for displaying the common components between two or more source code files

`same` uses lex/flex to split a file into tokens and will add the ones which are not part of the language syntax to a hash table. Then it will check the tokens from another files for matches.

It can be very useful when you want to quickly see what functions or data structures defined in one file are used in another.

## How to use

Requirements:
* GCC
* flex

First clone or download the repository. Then run `make` to build the program.

To use it you must give a file to find the definitions, and one or more files to look for matches.

```
same <source file> <destination files(s)>
```

## References

* https://www.lysator.liu.se/c/ANSI-C-grammar-l.html
* https://github.com/yui0/catc