## Welcome to the Cypiler!

The cypiler is a compiler written a C++ that compile a custom language (the cy++) into Linux 64 bit assembly. \
_As you can tell, the gimmick is that I take the "cy" from my name and put it everywhere I can._

The project is currently in development, and the list of features supported for the cy++ language will be expanded
with each release.
> Current version: 0.2.0


## The cy++ language

The language currently has a simple syntax, instructions are separated by semicolons `;`,
and instructions arguments are expected to be inside parenthesis `()`. \
Supported instructions are:
- `print("text");` The `print` instruction automatically sets a line break at the end of the text.
- `exit(exit_code);`
- `const int name = val;` Declare a numeric constant that can later be used with the `exit` instruction,
or in the declaration of another numeric constant.
- `const string name = "val";` Declare a text constant that can later be used with the `print` instruction,
or in the declaration of another text constant.

Example of a program written in cy++:
```
const string print_val = "Hello from cy++";
const int exit_val = 3;

print(print_val);
print("You can try this at home!");

exit(exit_val);
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
- Comments (auto-generated comments in the asm, and comments in cypp)
- Integer variables
- Addition operation for integer variables
- `if` and `else`