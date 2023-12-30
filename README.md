# avr-shell-cmd
Small helper library for creating shell commands on an AVR, when using avr-gcc.
Requires a small addition to the linker script. A full script isn't included here, as it changes depending on which AVR is used.

## Linker script modifications
Find the linker script suitable for the AVR in question, then add these four lines somewhere in the .text section:
```
PROVIDE (__cmdtable_start = .) ;
*(SORT_BY_NAME(.cmdtable*))
PROVIDE (__cmdtable_end = .) ;
KEEP(*(.cmdtable*))
```
The recommended placement is after .ctors and .dtors, and before .init0

Then just tell the linker to use the modified linker script (use the -T command line option). In Atmel/Microchip Studio this is done in the project properties (Alt+F7), Toolchain, AVR/GNU Linker, Miscellaneous, Other Linker Flags. Add the line:
```
-T $(ProjectDir)\avrxmega4.x
```
Change the path and filename to match your modified linker script.

If you don't use Atmel/Microchip Studio, add the linker option in your makefile.

## Using avr-shell-cmd
First, include the files here in your build. This repo can be included as a submodule.

### Creating a shell command
Wherever you want a shell command, include cmd.h. Then make a static function with the command you want (name it the command followed by "Cmd"), and then put it in a CMD macro. Here is a command called "example":
```
static void exampleCmd(uint8_t argc, char *argv[])
{
    // Your command code goes here
}

CMD(example, "Put helptext here");
```
That is all that's needed.

### Executing a shell command
Collect input from a serial port (or anywhere else you want to expose a shell). Once a full line has been read, call *cmd_split_exec* with the line.
The correct command function will be called.

One command is already provided: *help*. It will print a list of all commands and their helptext.
