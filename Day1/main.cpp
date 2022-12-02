#include <stdio.h>
#include <fstream>
#include <cstdlib>
#include <cstring>

int main()
{
    std::ifstream input_file("input.txt");
    char buffer[64];

    const int n = 3;
    int top_n_calories[n];
    
    int calorie_count = 0;

    // zero out calorie counting array
    for(int i = 0; i < n; i++)
    {
        top_n_calories[i] = 0;
    }

    while(input_file.peek() != EOF)
    {
        input_file.getline(buffer, sizeof(buffer));
        int length = strlen(buffer);

        if(length > 0)
        {
            // update count for current elf
            int num_calories = atoi(buffer);
            calorie_count += num_calories;
        }
        else
        {
            // check if current calorie count beats out another in array
            for(int i = 0; i < n; i++)
            {
                if(calorie_count > top_n_calories[i])
                {
                    // push down lower counts and place in new count
                    for(int j = n - 1; j > i; j--)
                    {
                        int k = top_n_calories[j - 1];
                        top_n_calories[j - 1] = top_n_calories[j];
                        top_n_calories[j] = k;
                    }
                    top_n_calories[i] = calorie_count;
                    break;
                }
            }
            calorie_count = 0;
        }
    }


    // print out results
    int sum = 0;
    for(int i = 0; i < n; i++)
    {
        printf("[%d]: %d\n", i + 1, top_n_calories[i]);
        sum += top_n_calories[i];
    }

    printf("Sum: %d\n", sum);

    return 0;
}