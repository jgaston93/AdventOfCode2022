#include <stdio.h>
#include <fstream>
#include <cstdlib>
#include <cstring>

#include "Monkey.hpp"
#include "AddOperation.hpp"
#include "MultiplyOperation.hpp"
#include "MultiplySelfOperation.hpp"

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
        input_file.getline(buffer, sizeof(buffer));

        // Starting Items
        printf("    Starting Items: ");
        input_file.getline(buffer, sizeof(buffer));
        int length = strlen(buffer);
        int item_index = item_offset_index;
        for(int i = item_offset_index; i < length; i++)
        {
            if(buffer[i] == ',')
            {
                buffer[i] = '\0';
                unsigned long long int item = atoi(&buffer[item_index]);
                monkeys[current_monkey_index]->GiveItem(item);
                item_index = i + 2;
                printf("%d ", item);
            }
            else if(i == length - 1)
            {
                unsigned long long int item = atoi(&buffer[item_index]);
                monkeys[current_monkey_index]->GiveItem(item);
                printf("%d ", item);
            }
        }
        printf("\n");

        // Operation
        input_file.getline(buffer, sizeof(buffer));
        Operation* operation;
        unsigned long long int operation_value = 0;

        if(buffer[operator_offset_index] == '+')
        {
            operation_value = atoi(&buffer[operation_value_offset_index]);
            operation = (Operation*)new AddOperation(operation_value);
            printf("    Add operation: %d\n", operation_value);
        }
        else if(buffer[operation_value_offset_index] != 'o')
        {
            operation_value = atoi(&buffer[operation_value_offset_index]);
            operation = (Operation*)new MultiplyOperation(operation_value);
            printf("    Multiply operation: %d\n", operation_value);
        }
        else
        {
            operation = (Operation*)new MultiplySelfOperation(operation_value);
            printf("    Multiply self operation\n");
        }

        monkeys[current_monkey_index]->SetOperation(operation);

        // Test
        input_file.getline(buffer, sizeof(buffer));
        unsigned long long int test_value = atoi(&buffer[test_value_offset_index]);
        input_file.getline(buffer, sizeof(buffer));
        int monkey_1_index = atoi(&buffer[monkey_1_offset_index]);
        input_file.getline(buffer, sizeof(buffer));
        int monkey_2_index = atoi(&buffer[monkey_2_offset_index]);

        printf("    Test value: %d Monkey indices: %d %d\n\n", test_value, monkey_1_index, monkey_2_index);

        monkeys[current_monkey_index]->SetTest(test_value, 
                        monkeys[monkey_1_index], monkeys[monkey_2_index]);

        current_monkey_index++;
        input_file.getline(buffer, sizeof(buffer));
    }
    printf("\n");
    
    input_file.close();

    const int num_rounds = 20;
    for(int i = 0; i < num_rounds; i++)
    {
        for(int j = 0; j < num_monkeys; j++)
        {
            monkeys[j]->TakeTurn();
        }
    }

    unsigned long long int max_1 = 0;
    unsigned long long int max_2 = 0;

    for(int i = 0; i < num_monkeys; i++)
    {
        unsigned long long int num_inspections = monkeys[i]->GetNumInspections();
        
        printf("Monkey %d inspections: %d\n", i, num_inspections);
        if(num_inspections > max_1)
        {
            max_2 = max_1;
            max_1 = num_inspections;
        }
        else if(num_inspections > max_2)
        {
            max_2 = num_inspections;
        }
    }

    unsigned long long int monkey_business = max_1 * max_2;
    printf("Monkey business: %lu\n", monkey_business);

    for(int i = 0; i < num_monkeys; i++)
    {
        delete monkeys[i];
    }
    delete[] monkeys;


    return 0;
}