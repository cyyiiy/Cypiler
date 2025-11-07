## Welcome to the Cypiler!

The cypiler is a compiler written a C++ that compile a custom language (the cy++) into Linux 64 bit assembly. \
_As you can tell, the gimmick is that I take the "cy" from my name and put it everywhere I can._

The project is currently in development, and the list of features supported for the cy++ language will be expanded
with each release.
> Current version: 0.1.0


## The cy++ language

The language currently has a simple syntax, instructions are separated by semicolons `;`,
and instructions arguments are expected to be inside parenthesis `()`. \
Supported instructions are:
- `print("text");` The `print` instruction automatically sets a line break at the end of the text.
- `exit(exit_code);`

Example of a program written in cy++:
```
print("Hello from cy++");
print("You can try this at home!");
exit(3);
```


## How to use the compiler

You need to call the compiler with the cypp file you want to compile as the first (and only) argument.
Example: `compiler.exe test.cypp` on Windows.\
It will generate an assembly file (if the code compiles of course) next to the compiler executable.

### How to run the assembly code

As stated earlier, this compiler compiles into Linux 64 bit assembly. \
If you're on Linux, it should be pretty simple, just assemble and link it (you can do this with nasm and gcc)
then simply run the executable in the console. \
If you're on Windows, you will need to setup WSL to be able to have a Linux environment on your computer.
Once this is done, you can follow the same steps. \
If you're on Mac, I have absolutely no idea how it works, but you can surely find a way.


## Roadmap

Next features currently planned:
- Variables ("string" and "int" like types)
- Arithmetic operations (at least the addition)
- `if` and `else`