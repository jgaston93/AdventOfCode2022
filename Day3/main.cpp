#include <stdio.h>
#include <fstream>
#include <cstdlib>
#include <cstring>

int CheckCompartments(char* rucksack, int rucksack_size);
int CheckRucksacks(char* rs_1, int rs_1_size,
                    char* rs_2, int rs_2_size,
                    char* rs_3, int rs_3_size);

char GetDuplicate(char* set_1, int set_1_size, char* set_2, int set_2_size);
int GetPriority(char item);

int main()
{
    bool part_1 = false;

    std::ifstream input_file("input.txt");
    char rucksack[128];

    int priority_sum = 0;

    while(input_file.peek() != EOF)
    {
        input_file.getline(rucksack, sizeof(rucksack));
        int rucksack_size = strlen(rucksack);

        int priority;

        if(part_1)
        {
            priority = CheckCompartments(rucksack, rucksack_size);
        }
        else
        {
            char rucksack_2[128];
            char rucksack_3[128];
            input_file.getline(rucksack_2, sizeof(rucksack_2));
            int rucksack_2_size = strlen(rucksack_2);
            input_file.getline(rucksack_3, sizeof(rucksack_3));
            int rucksack_3_size = strlen(rucksack_3);

            priority = CheckRucksacks(rucksack, rucksack_size,
                                        rucksack_2, rucksack_2_size,
                                        rucksack_3, rucksack_3_size);
        }

        priority_sum += priority;
    }

    printf("Sum: %d\n", priority_sum);

    return 0;
}


int CheckCompartments(char* rucksack, int rucksack_size)
{
    int compartment_size = rucksack_size / 2;
    
    char duplicate = GetDuplicate(rucksack, compartment_size, 
                                    rucksack + compartment_size, compartment_size);
    int priority = GetPriority(duplicate);

    return priority;
}


int CheckRucksacks(char* rs_1, int rs_1_size,
                    char* rs_2, int rs_2_size,
                    char* rs_3, int rs_3_size)
{
    int priority = 0;
    bool duplicate_found = false;

    for(int i = 0; i < rs_1_size; i++)
    {
        for(int j = 0; j < rs_2_size; j++)
        {
            if(rs_1[i] == rs_2[j])
            {
                for(int k = 0; k < rs_3_size; k++)
                {
                    if(rs_2[j] == rs_3[k])
                    {
                        priority = GetPriority(rs_3[k]);
                        duplicate_found = true;
                        break;
                    }
                }
            }
            if(duplicate_found)
            {
                break;
            }
        }
        if(duplicate_found)
        {
            break;
        }
    }

    return priority;
}


char GetDuplicate(char* set_1, int set_1_size, char* set_2, int set_2_size)
{
    char duplicate;
    bool duplicate_found = false;

    for(int i = 0; i < set_1_size; i++)
    {
        for(int j = 0; j < set_2_size; j++)
        {
            if(set_1[i] == set_2[j])
            {
                duplicate = set_1[i];
                duplicate_found = true;
                break;
            }
        }
        if(duplicate_found)
        {
            break;
        }
    }
}

int GetPriority(char item)
{
    int priority;
    if(item >= 'a')
    {
        priority = item - 'a' + 1;
    }
    else
    {
        priority = item - 'A' + 27;
    }
    return priority;
}