#include <stdio.h>
#include <fstream>
#include <cstdlib>
#include <cstring>

enum InstructionType
{
    NOOP,
    ADDX
};

struct Instruction
{
    InstructionType type;
    int value;
    bool wait;
};

Instruction GetInstruction(std::ifstream* input_file);

int main()
{
    std::ifstream input_file("input.txt");
    
    // Signal checking 
    int cycles_to_check[] = { 20, 60, 100, 140, 180, 220 };
    int signal_strengths[] = { 0, 0, 0, 0, 0, 0 };
    int cycle_check_index = 0;

    // CRT screen
    const int screen_width = 40;
    const int screen_height = 6;
    char crt_screen[screen_height][screen_width];
    for(int i = 0; i < screen_height; i++)
    {
        memset(&crt_screen[i], ' ', screen_width);
    }
    int current_row = 0;

    // Clocks and registers
    int cycle_number = 1;
    int x_register = 1;

    Instruction instruction = GetInstruction(&input_file);

    while(input_file.peek() != EOF)
    {
        // Perform CRT draw
        int crt_position = (cycle_number - 1) % 40;
        if(crt_position <= x_register + 1 && crt_position >= x_register - 1)
        {
            crt_screen[current_row][crt_position] = '#';
        }

        if(cycle_number % 40 == 0)
        {
            current_row++;
        }

        // Handle CPU instructions
        if(instruction.type == NOOP)
        {
            instruction = GetInstruction(&input_file); 
        }
        else if (instruction.type == ADDX && instruction.wait)
        {
            instruction.wait = false;
        }
        else
        {
            x_register += instruction.value;
            instruction = GetInstruction(&input_file);
        }
        
        cycle_number++;

        // Check signal strength
        if(cycle_number == cycles_to_check[cycle_check_index])
        {
            signal_strengths[cycle_check_index++] = cycle_number * x_register;
        }

    }

    int sum = 0;
    for(int i = 0; i < cycle_check_index; i++)
    {
        sum += signal_strengths[i];
    }

    printf("Sum of signal strengths: %d\n", sum);

    for(int i = 0; i < screen_height; i++)
    {
        for(int j = 0; j < screen_width; j++)
        {
            printf("%c", crt_screen[i][j]);
        }
        printf("\n");
    }
    
    input_file.close();

    return 0;
}


Instruction GetInstruction(std::ifstream* input_file)
{
    char buffer[32];
    input_file->getline(buffer, sizeof(buffer));

    Instruction instruction;

    if(buffer[0] == 'n')
    {
        instruction.type = NOOP;
        instruction.value = 0;
        instruction.wait = false;
    }
    else
    {
        instruction.type = ADDX;

        if(buffer[5] == '-')
        {
            instruction.value = -atoi(&buffer[6]);
        }
        else
        {
            instruction.value = atoi(&buffer[5]);
        }

        instruction.wait = true;
    }

    return instruction;
}