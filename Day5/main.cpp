#include <stdio.h>
#include <fstream>
#include <cstdlib>
#include <cstring>

const int num_stacks = 9;
const int max_stack_height = 64;

char pop(char* stack, int* stack_height);
void push(char* stack, int* stack_height, char crate);
void print_stack(char* stack, int stack_height);

int main()
{
    std::ifstream input_file("input.txt");
    char buffer[128];

    // Stacks
    char stacks[num_stacks][max_stack_height];
    int stack_heights[num_stacks];

    // Initialize all stack heights to 0
    for(int i = 0; i < num_stacks; i++)
    {
        stack_heights[i] = 0;
    }

    // Beging reading initial stack information
    input_file.getline(buffer, sizeof(buffer));

    while(buffer[1] != '1')
    {
        int buffer_index = 1;
        for(int i = 0; i < num_stacks; i++)
        {
            if(buffer[buffer_index] >= 65 && buffer[buffer_index] <= 90)
            {
                stacks[i][stack_heights[i]++] = buffer[buffer_index];
            }
            buffer_index += 4;
        }
        input_file.getline(buffer, sizeof(buffer));
    }

    // Reverse arrays 
    for(int i = 0; i < num_stacks; i++)
    {
        for(int j = 0; j < stack_heights[i] / 2; j++)
        {
            int k = stacks[i][j];
            stacks[i][j] = stacks[i][stack_heights[i] - 1 - j];
            stacks[i][stack_heights[i] - 1 - j] = k;
        }
    }

    // Skip blank line
    input_file.getline(buffer, sizeof(buffer));

    while(input_file.peek() != EOF)
    {
        input_file.getline(buffer, sizeof(buffer));

        int quantity, source, destination;
        sscanf(buffer, "move %d from %d to %d", &quantity, &source, &destination);

        for(int i = 0; i < quantity; i++)
        {
            int crate = pop(stacks[source - 1], &stack_heights[source - 1]);
            push(stacks[destination - 1], &stack_heights[destination - 1], crate);
        }
    }

    printf("Top Crates: ");
    for(int i = 0; i < num_stacks; i++)
    {
        printf("%c", stacks[i][stack_heights[i] - 1]);
    }
    printf("\n");

    input_file.close();

    return 0;
}

char pop(char* stack, int* stack_height)
{
    int value = ' ';
    if(*stack_height > 0)
    {
        value = stack[*stack_height - 1];
        *stack_height -= 1;
    }
    return value;
}

void push(char* stack, int* stack_height, char crate)
{
    if(*stack_height < max_stack_height)
    {
        stack[*stack_height] = crate;
        *stack_height += 1;
    }
}


void print_stack(char* stack, int stack_height)
{
    for(int i = 0; i < stack_height; i++)
    {
        printf("[%c] ", stack[i]);
    }
    printf("\n");
}
