#include <iostream>
#include <fstream>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

template <class T>
struct DynArr
{
    T *arr;
    size_t cap = 0;
    size_t pos = 0;
    DynArr()
    {
        arr = (T *)malloc(300);
        cap = 300;
    }
};

template <class T>
inline void AppendArr(DynArr<T> &arr, T data)
{
    if (arr.cap <= arr.pos)
    {
        T *temp = (T *)malloc(arr.cap * 4);
        memcpy(temp, arr.arr, arr.pos);
        arr.arr = temp;
        arr.cap *= 4;
    }
    arr.arr[arr.pos++] = data;
}

template <class T>
void TrashArr(DynArr<T> &arr)
{
    free(arr.arr);
}

bool run = true;
DynArr<char> characters;
DynArr<uint32_t> callstack;
DynArr<int32_t> stack;
DynArr<int8_t *> memory_cells;
int32_t workreg = 0;
int32_t basePointer = 0;
uint32_t position;

/* INTRINSIC FUNCTIONS ( empty the stack of their passed arguments ) */

void addition()
{
    workreg = stack.arr[stack.pos - 1] + stack.arr[stack.pos - 2];
    stack.pos -= 2;
}
void multiplication()
{
    workreg = stack.arr[stack.pos - 1] * stack.arr[stack.pos - 2];
    stack.pos -= 2;
}
void division()
{
    workreg = stack.arr[stack.pos - 2] / stack.arr[stack.pos - 1];
    stack.pos -= 2;
}
void subtraction()
{
    workreg = stack.arr[stack.pos - 2] - stack.arr[stack.pos - 1];
    stack.pos -= 2;
}
void modulo()
{
    workreg = stack.arr[stack.pos - 2] % stack.arr[stack.pos - 1];
    stack.pos -= 2;
}
void writeNum()
{
    std::cout << stack.arr[stack.pos - 1] << "\n";
    stack.pos -= 1;
}
void writeStr()
{
    puts(&characters.arr[stack.arr[stack.pos - 1]]);
    stack.pos -= 1;
}
void writeNl()
{
    std::cout << "\n";
}
void equal()
{
    workreg = (stack.arr[stack.pos - 2] == stack.arr[stack.pos - 1]) ? 1 : 0;
    stack.pos -= 2;
}
void enterNumber()
{
    std::cin >> workreg;
}
void stringcopy()
{
    // source, destination
    strcpy(&characters.arr[stack.arr[stack.pos - 1]], &characters.arr[stack.arr[stack.pos - 2]]);
    stack.pos -= 2;
}
void string_enter()
{
    scanf("%s", &characters.arr[stack.arr[stack.pos - 1]]);
    stack.pos -= 1;
}
void strcmpare()
{
    workreg = strcmp(&characters.arr[stack.arr[stack.pos - 1]], &characters.arr[stack.arr[stack.pos - 2]]) == 0 ? 1 : 0;
    stack.pos -= 2;
}
void allocateMemoryCell()
{ //takes as argument the size to allocate
    AppendArr(memory_cells, (int8_t *)malloc(stack.arr[stack.pos - 1]));
    workreg = memory_cells.pos - 1;
    stack.pos -= 1;
}
void freeMemoryCell()
{ //takes as argument the size to allocate
    free(memory_cells.arr[stack.arr[stack.pos - 1]]);
    stack.pos -= 1;
}
void getIntAt()
{
    workreg = *((int32_t *)(&characters.arr[stack.arr[stack.pos - 1] * 4]));
    stack.pos -= 1;
}
void getCharAt()
{
    workreg = characters.arr[stack.arr[stack.pos - 1]];
    stack.pos -= 1;
}
void setIntAt()
{ //position, data
    characters.arr[stack.arr[stack.pos - 2] * 4] = stack.arr[stack.pos - 1];
    stack.pos -= 1;
}
void setCharAt()
{
    workreg = characters.arr[stack.arr[stack.pos - 1]];
    stack.pos -= 1;
}
void stringCharAt()
{
    workreg = characters.arr[stack.arr[stack.pos - 2] + stack.arr[stack.pos - 1]];
    stack.pos -= 2;
}
void strconcat()
{
    workreg = (strcat(&characters.arr[stack.arr[stack.pos - 1]], &characters.arr[stack.arr[stack.pos - 2]]) - characters.arr);
    stack.pos -= 2;
}
void inversebool()
{
    workreg = (stack.arr[stack.pos - 1] == 0 ? 1 : 0);
    stack.pos -= 1;
}
void smaller()
{
    workreg = (stack.arr[stack.pos - 2] < stack.arr[stack.pos - 1]) ? 1 : 0;
    stack.pos -= 2;
}
void bigger()
{
    workreg = (stack.arr[stack.pos - 2] > stack.arr[stack.pos - 1]) ? 1 : 0;
    stack.pos -= 2;
}

constexpr void (*intrinsics[24])(void) = {
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
};

/* CLAIRVIC */

inline void throwFatal(std::string code)
{
    puts(("[CLV FATAL ERROR] " + code).c_str());
    exit(1);
}

char GetByte()
{
    return characters.arr[position++];
}

int32_t GetWordAt(size_t pos)
{
    return *((int32_t *)(&characters.arr[pos]));
}

void PutWordAt(size_t pos, int32_t word)
{
    *((int32_t *)(&characters.arr[pos])) = word;
}

inline int32_t GetWord()
{
    position += 4;
    return GetWordAt(position - 4);
}

void readCharacters(char *fileName)
{
    std::ifstream file(fileName);
    while (!file.eof())
        AppendArr<char>(characters, (char)file.get());
}

inline void handleIntrinsic(int id)
{
    intrinsics[id * -1 - 1]();
}

int main(int argc, char **argv)
{
    char temp;
    if (argc == 1)
        throwFatal("No CLAIRVIC bytecode to execute was specified.\n");
    else
    {
        readCharacters(argv[1]);
        while (run)
        {
            temp = GetByte();
            if (temp == 0)
            { //call function
                int funcID = GetWord();
                if (funcID < 0)
                    intrinsics[funcID * -1 - 1]();
                else
                {
                    AppendArr(stack, basePointer);
                    basePointer = stack.pos;
                    AppendArr(callstack, position);
                    position = funcID;
                }
            }
            else if (temp == 1)
            { //return from call
                position = callstack.arr[callstack.pos - 1];
                callstack.pos--;
                stack.pos = basePointer;
                basePointer = stack.arr[stack.pos - 1];
                stack.pos--;
            }
            else if (temp == 2)
            { //stop exec
                exit(GetByte());
            }
            else if (temp == 3)
            {
                AppendArr(stack, workreg);
            }
            else if (temp == 4)
            { // pop
                workreg = stack.arr[stack.pos - 1];
                stack.pos--;
            }
            else if (temp == 5)
            {
                workreg = stack.arr[basePointer + GetWord() - 1];
            }
            else if (temp == 6)
            {
                workreg = GetWord();
            }
            else if (temp == 7)
            {
                workreg = GetWordAt(GetWord());
            }
            else if (temp == 8)
            {
                PutWordAt(GetWord(), workreg);
            }
            else if (temp == 9)
            {
                stack.arr[basePointer + GetWord() - 1] = workreg;
            }
            else if (temp == 10)
            { //jump if not equal
                if (workreg != 0)
                {
                    position += 4;
                }
                else
                {
                    position = GetWord();
                }
            }
            else if (temp == 11)
            { //discard from stack
                stack.pos--;
            }
            else if (temp == 12)
            { // jump
                position = GetWord();
            }
            else if (temp == 13)
            { //jump if equal
                if (workreg == 0)
                {
                    position += 4;
                }
                else
                {
                    position = GetWord();
                }
            }
            else
            {
                throwFatal("Operation code " + std::to_string(temp) + " at position " + std::to_string(position) + " is invalid");
            }
        }
    }
    TrashArr(stack);
    TrashArr(callstack);
    TrashArr(characters);
}
