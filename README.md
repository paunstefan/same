# same
`same` is a command line utility for displaying the common components between two or more source code files

`same` uses lex/flex to split a file into tokens and will add the ones which are not part of the language syntax to a hash table. Then it will check the tokens from another files for matches.

It can be very useful when you want to quickly see what functions or data structures defined in one file are used in another.

## How to use

Requirements:
* GCC
* flex

First clone or download the repository. Then you must build and install the program.

```
make
make install
```

It will be installed by default in the `/usr/local/bin` directory. You might need root access for that.

To use it you must give a file to find the definitions, and one or more files to look for matches.

```
same <definitions file> <match file(s)>
```

## References

* https://www.lysator.liu.se/c/ANSI-C-grammar-l.html
* https://github.com/yui0/catc