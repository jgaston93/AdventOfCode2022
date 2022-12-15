#include <stdio.h>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <tgmath.h>

int get_value(char* packet, int size);
int get_num_elements(char* packet, int size);
int get_number_size(char* packet, int size);
int get_list_size(char* packet, int size);
int compare(char* packet_1, int packet_1_size, char* packet_2, int packet_2_size, int indentation);

int main()
{
    std::ifstream input_file("input.txt");
    char packet_1[1024];
    char packet_2[1024];
    char buffer[1024];

    int index = 1;
    int sum = 0;
    
    while(input_file.peek() != EOF)
    {
        input_file.getline(packet_1, sizeof(packet_1)); // get packet 1
        input_file.getline(packet_2, sizeof(packet_2)); // get packet 2
        input_file.getline(buffer, sizeof(buffer));     // skip line

        int size_1 = strlen(packet_1);
        int size_2 = strlen(packet_2);

        int indentation = 0;

        char buffer1[1024];
        char buffer2[1024];
        strncpy(buffer1, packet_1, size_1);
        strncpy(buffer2, packet_2, size_2);
        buffer1[size_1] = '\0';
        buffer2[size_2] = '\0';
        for(int i = 0; i < indentation; i++)
        {
            printf("  ");
        }
        printf("-Compare %s vs %s\n", buffer1, buffer2);

        int difference = compare(packet_1, size_1, packet_2, size_2, indentation + 1);
        if(difference <= 0)
        {
            sum += index;
        }
        index++;
    }
    
    input_file.close();

    printf("Sum: %d\n", sum);

    return 0;
}

int get_value(char* packet, int size)
{
    int value = 0;
    int exponent = 0;
    for(int i = size - 1; i >=0; i--)
    {
        value += (packet[i] - '0') * pow(10, exponent++);
    }
    return value;
}

int get_number_size(char* packet, int size)
{
    int number_size = 0;
    while(packet[number_size] != ',' && packet[number_size] != ']')
    {
        number_size++;
    }
    return number_size;
}

int get_list_size(char* packet, int size)
{
    int list_size = 1;
    int bracket_count = 1;
    while(bracket_count > 0)
    {
        if(packet[list_size] == '[')
        {
            bracket_count++;
        }
        else if(packet[list_size] == ']')
        {
            bracket_count--;
        }
        list_size++;
    }
    return list_size;
}

int get_num_elements(char* packet, int size)
{
    int num_items = 0;
    int packet_index = 1;

    bool number_found = false;
    bool list_found = false;
    int bracket_count = 0;

    while(packet_index < size)
    {
        if(number_found)
        {
            if(packet[packet_index] == ',')
            {
                number_found = false;
            }
        }
        else if(list_found)
        {
            if(bracket_count == 0)
            {
                list_found = false;
            }
            else if(packet[packet_index] == '[')
            {
                bracket_count++;
            }
            else if(packet[packet_index] == ']')
            {
                bracket_count--;
            }
        }
        else if(packet[packet_index] == '[')
        {
            bracket_count = 1;
            list_found = true;
            num_items++;
        }
        else if('0' <= packet[packet_index] && packet[packet_index] <= '9')
        {
            number_found = true;
            num_items++;
        }
        packet_index++;
    }
    return num_items;
}

int compare(char* p_1, int size_1, char* p_2, int size_2, int indentation)
{
    int difference = 0;

    int num_elements_1 = get_num_elements(p_1, size_1);
    int num_elements_2 = get_num_elements(p_2, size_2);

    int index_1 = 1;
    int index_2 = 1;

    while(difference == 0 && num_elements_1 > 0 && num_elements_2 > 0)
    {
        int element_1_size;
        int element_2_size;

        bool is_element_1_number = false;
        bool is_element_2_number = false;

        if(p_1[index_1] == '[')
        {
            element_1_size = get_list_size(p_1 + index_1, size_1 - index_1);
        }
        else
        {
            element_1_size = get_number_size(p_1 + index_1, size_1 - index_1);
            is_element_1_number = true;
        }

        if(p_2[index_2] == '[')
        {
            element_2_size = get_list_size(p_2 + index_2, size_2 - index_2);
        }
        else
        {
            element_2_size = get_number_size(p_2 + index_2, size_2 - index_2);
            is_element_2_number = true;
        }

        if(is_element_1_number && is_element_2_number)
        {
            int value_1 = get_value(p_1 + index_1, element_1_size);
            int value_2 = get_value(p_2 + index_2, element_2_size);

            for(int i = 0; i < indentation; i++)
            {
                printf("  ");
            }
            printf("-Compare %d vs %d\n", value_1, value_2);

            difference = value_1 - value_2;

            if(difference > 0)
            {
                for(int i = 0; i < indentation + 1; i++)
                {
                    printf("  ");
                }
                printf("-Right side is smaller, incorrect\n\n");
            }
            else if(difference < 0)
            {
                for(int i = 0; i < indentation + 1; i++)
                {
                    printf("  ");
                }
                printf("-Left side is smaller, correct\n\n");
            }
        }
        else if(!is_element_1_number && is_element_2_number)
        {
            char* new_p_2 = new char[element_2_size + 2];
            for(int i = 0; i < element_2_size; i++)
            {
                new_p_2[i + 1] = p_2[index_2 + i];
            }
            new_p_2[0] = '[';
            new_p_2[element_2_size + 2 - 1] = ']';

            char buffer1[1024];
            char buffer2[1024];
            strncpy(buffer1, p_1 + index_1, element_1_size);
            strncpy(buffer2, new_p_2, element_2_size + 2);
            buffer1[element_1_size] = '\0';
            buffer2[element_2_size + 2] = '\0';
            for(int i = 0; i < indentation; i++)
            {
                printf("  ");
            }
            printf("-Mixed types; convert right to %s\n", buffer2);
            for(int i = 0; i < indentation; i++)
            {
                printf("  ");
            }
            printf("-Compare %s vs %s\n", buffer1, buffer2);

            difference = compare(p_1 + index_1, element_1_size, new_p_2, element_2_size + 2, indentation + 1);

            delete[] new_p_2;

        }
        else if(is_element_1_number && !is_element_2_number)
        {
            char* new_p_1 = new char[element_1_size + 2];
            for(int i = 0; i < element_1_size; i++)
            {
                new_p_1[i + 1] = p_1[index_1 + i];
            }
            new_p_1[0] = '[';
            new_p_1[element_1_size + 2 - 1] = ']';

            char buffer1[1024];
            char buffer2[1024];
            strncpy(buffer1, new_p_1, element_1_size + 2);
            strncpy(buffer2, p_2 + index_2, element_2_size);
            buffer1[element_1_size + 2] = '\0';
            buffer2[element_2_size] = '\0';
            for(int i = 0; i < indentation; i++)
            {
                printf("  ");
            }
            printf("-Mixed types; convert left to %s\n", buffer1);
            for(int i = 0; i < indentation; i++)
            {
                printf("  ");
            }
            printf("-Compare %s vs %s\n", buffer1, buffer2);

            difference = compare(new_p_1, element_1_size + 2, p_2 + index_2, element_2_size, indentation + 1);

            delete[] new_p_1;
        }
        else
        {
            char buffer1[1024];
            char buffer2[1024];
            strncpy(buffer1, p_1 + index_1, element_1_size);
            strncpy(buffer2, p_2 + index_2, element_2_size);
            buffer1[element_1_size] = '\0';
            buffer2[element_2_size] = '\0';
            for(int i = 0; i < indentation; i++)
            {
                printf("  ");
            }
            printf("-Compare %s vs %s\n", buffer1, buffer2);

            difference = compare(p_1 + index_1, element_1_size, p_2 + index_2, element_2_size, indentation + 1);
        }

        index_1 += element_1_size + 1;
        index_2 += element_2_size + 1;
        num_elements_1--;
        num_elements_2--;
    }

    if(difference == 0)
    {
        if(num_elements_1 > 0)
        {
            difference = 1;
            
            for(int i = 0; i < indentation + 1; i++)
            {
                printf("  ");
            }
            printf("-Right side ran out of elements, incorrect\n\n");
        }
        else if (num_elements_2 > 0)
        {
            
            for(int i = 0; i < indentation + 1; i++)
            {
                printf("  ");
            }
            printf("-Left side ran out of elements, correct\n\n");
        }
    }

    return difference;
}