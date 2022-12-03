#include <stdio.h>
#include <fstream>
#include <cstdlib>
#include <cstring>

int CheckCompartments(char* rucksack, int rucksack_size);
int CheckRucksacks(char* rs_1, int rs_1_size,
                    char* rs_2, int rs_2_size,
                    char* rs_3, int rs_3_size);

int GetDuplicates(char* set_1, int set_1_size, 
                    char* set_2, int set_2_size,
                    char* duplicates_list, int duplicates_list_size);
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

        int priority = 0;

        if(part_1)
        {
            // Check compartments in single rucksack
            priority = CheckCompartments(rucksack, rucksack_size);
        }
        else
        {
            // Get next two rucksacks and check all three for badges
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
    char* compartment_1 = rucksack;
    char* compartment_2 = rucksack + compartment_size;

    char duplicate_list[128];
    int num_duplicates = GetDuplicates(compartment_1, compartment_size, 
                                    compartment_2, compartment_size,
                                    duplicate_list, sizeof(duplicate_list));
    
    int priority = 0;
    if(num_duplicates > 0)
    {
        priority = GetPriority(duplicate_list[0]);
    }

    return priority;
}


int CheckRucksacks(char* rs_1, int rs_1_size,
                    char* rs_2, int rs_2_size,
                    char* rs_3, int rs_3_size)
{
    int priority = 0;
    bool duplicate_found = false;

    char duplicate_list_1[128];
    char duplicate_list_2[128];
    char duplicate_list_3[128];

    // Get duplicates between rucksacks 1 and 2
    int num_duplicates_1 = GetDuplicates(rs_1, rs_1_size,
                                            rs_2, rs_2_size,
                                            duplicate_list_1, sizeof(duplicate_list_1));
    // Get duplicates between rucksacks 2 adn 3
    int num_duplicates_2 = GetDuplicates(rs_2, rs_2_size,
                                            rs_3, rs_3_size,
                                            duplicate_list_2, sizeof(duplicate_list_2));

    // Get duplicates between sets of duplicates
    if(num_duplicates_1 > 0 && num_duplicates_2 > 0)
    {
        int num_duplicates_3 = GetDuplicates(duplicate_list_1, num_duplicates_1,
                                                duplicate_list_2, num_duplicates_2,
                                                duplicate_list_3, sizeof(duplicate_list_3));
        if(num_duplicates_3 > 0)
        {
            priority = GetPriority(duplicate_list_3[0]);
        }
    }

    return priority;
}


int GetDuplicates(char* set_1, int set_1_size, 
                    char* set_2, int set_2_size,
                    char* duplicates_list, int duplicates_list_size)
{
    int num_duplicates = 0;

    for(int i = 0; i < set_1_size; i++)
    {
        for(int j = 0; j < set_2_size; j++)
        {
            // check if duplicate and if duplicates list isn't full
            if(set_1[i] == set_2[j] && num_duplicates < duplicates_list_size)
            {
                // check if duplicate already exists in duplicates list
                bool already_exists = false;
                for(int k = 0; k < num_duplicates; k++)
                {
                    if(set_1[i] == duplicates_list[k])
                    {
                        already_exists = true;
                        break;
                    }
                }
                if(!already_exists)
                {
                    duplicates_list[num_duplicates++] = set_1[i];
                }
            }
        }
    }

    return num_duplicates;
}

int GetPriority(char item)
{
    int priority = 0;
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