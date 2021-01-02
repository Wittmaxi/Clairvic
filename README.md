# Clairvic
ByteCode language aimed at fast cross-platform execution and minimal executable-sizes

FULL DISCLAIMER: This is some pretty old code I wrote in an entirely experimental manner, 
trying to avoid caveats of the STL - the code might not be clean, in fact it might not even work. 
I'm uploading this for a friend of mine who is going to use it.
## Basics
Clairvic only has a single memory and a stack. Most of the "computing" only ever happens in intrinsic thus reducing the size of the executable by a lot. 
The first three bytes contain the magic number 'CLV', from then on everything is executed, starting at the 4th byte. 

## Operation Codes 
|     | ASM-equivalent | Arguments (if any)         |                                                                                                                                                                               |
| --- | -------------- | -------------------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| 0   | call           | <Word> Location            | Sets the InstructionPointer to the location Negative values refer to Intrinsics Automatically creates stackframes Pass arguments through the stack, first in is the first out |
| 1   | ret            |                            | like ret in assembler                                                                                                                                                         |
| 2   | hlt            | <1 Byte> error Code        |                                                                                                                                                                               |
| 3   | push           |                            | Pushes workreg into stack                                                                                                                                                     |
| 4   | pop            |                            | Pops the top entry in the stack to workreg                                                                                                                                    |
| 5   | mov            | <Word> index in stackframe | Gets the item from the stackframe at that index into workreg                                                                                                                  |
| 6   | mov            | <Word>                     | sets workreg to <Word>                                                                                                                                                        |
| 7   | mov            | <Word> pointer             | Moves a word-value in the program code pointed to by <arg> into workreg                                                                                                       |
| 8   | mov            | <Word> pointer             | Puts the current value of workreg into the program code at a position pointed by <argu>                                                                                       |
| 9   | mov            | <Word> index in stackframe | Sets the item from the stackframe at that index to workreg                                                                                                                    |
| 10  | jne            | <Word> pointer             | if workreg is zero, continues, else jumps (no stackframe created) to <pointer>                                                                                                |
| 11  |                |                            | Discards the top value from the stack                                                                                                                                         |
| 12  | jmp            | <word> Pointer             |                                                                                                                                                                               |
| 13  | je             | <word> Pointer             | inverse of jne                                                                                                                                                                |

## Intrinsic functions

    addition,           // -1
    subtraction,        // -2
    division,           // -3
    multiplication,     // -4
    modulo,             // -5
    writeNum,           // -6
    writeNl,            //-7
    equal,              // -8
    enterNumber,        // -9
    writeStr,           //-10
    stringcopy,         //-11
    string_enter,       //-12
    strcmpare,          //-13
    allocateMemoryCell, //-14
    freeMemoryCell,     //-15
    getIntAt,           //-16
    getCharAt,          //-17
    setIntAt,           //-18
    setCharAt,          //-19
    stringCharAt,       //-20
    strconcat,          //-21
    inversebool,        //-22
    smaller,            //-23
    bigger,             //-24

    This has to be enough for now, I'll update this list eventually

# FEEL FREE TO ASK
This project is honestly just me quickly putting my things together. I currently do not have the time to make it better. 
If you have any requests, ask me on Telegram @BinaryByter or contact me through an E-Mail
maximilian.Wittmer@gmx.de