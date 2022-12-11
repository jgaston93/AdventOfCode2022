#include <stdio.h>
#include <fstream>
#include <cstdlib>
#include <cstring>

#include "Monkey.hpp"
#include "AddOperation.hpp"
#include "MultiplyOperation.hpp"

int main()
{
    std::ifstream input_file("input.txt");

    int num_monkeys = 0;
    Monkey** monkeys;
    
    while(input_file.peek() != EOF)
    {
        char buffer[64];
        input_file.getline(buffer, sizeof(buffer));
        if(buffer[0] == 'M')
        {
            num_monkeys++;
        }
    }
    input_file.clear();
    input_file.seekg(std::ios::beg);

    monkeys = new Monkey*[num_monkeys];
    for(int i = 0; i < num_monkeys; i++)
    {
        monkeys[i] = new Monkey();
    }

    const int item_offset_index = 18;
    const int operator_offset_index = 23;
    const int operation_value_offset_index = 25;
    const int test_value_offset_index = 21;
    const int monkey_1_offset_index = 29;
    const int monkey_2_offset_index = 30;

    int current_monkey_index = 0;
    while(input_file.peek() != EOF)
    {
        printf("Monkey[%d]:\n", current_monkey_index);
        char buffer[64];

        // Starting Items
        input_file.getline(buffer, sizeof(buffer));
        int length = strlen(buffer);
        int item_index = item_offset_index;
        for(int i = item_offset_index; i < length; i++)
        {
            if(buffer[i] == ',')
            {
                buffer[i] = '\0';
                int item = atoi(&buffer[item_index]);
                monkeys[current_monkey_index]->GiveItem(item);
                item_index = i + 2;
            }
        }

        // Operation
        input_file.getline(buffer, sizeof(buffer));
        Operation* operation;
        int operation_value = atoi(&buffer[operation_value_offset_index]);

        if(buffer[operator_offset_index] == '+')
        {
            operation = (Operation*)new AddOperation(operation_value);
        }
        else
        {
            operation = (Operation*)new MultiplyOperation(operation_value);
        }

        monkeys[current_monkey_index]->SetOperation(operation);

        // Test
        input_file.getline(buffer, sizeof(buffer));
        int test_value = atoi(&buffer[test_value_offset_index]);
        int monkey_1_index = atoi(&buffer[monkey_1_offset_index]);
        int monkey_2_index = atoi(&buffer[monkey_2_offset_index]);

        monkeys[current_monkey_index]->SetTest(test_value, 
                        monkeys[monkey_1_index], monkeys[monkey_2_index]);

        current_monkey_index++;
    }
    
    input_file.close();




    return 0;
}