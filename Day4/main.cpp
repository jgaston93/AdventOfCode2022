#include <stdio.h>
#include <fstream>
#include <cstdlib>
#include <cstring>

int main()
{

    std::ifstream input_file("input.txt");
    char buffer[128];

    int num_partial_overlaps = 0;
    int num_total_overlaps = 0;

    while(input_file.peek() != EOF)
    {
        input_file.getline(buffer, sizeof(buffer));
        int bytes_read = strlen(buffer);
        
        int lower_1, upper_1, lower_2, upper_2;

        sscanf(buffer, "%d-%d,%d-%d", &lower_1, &upper_1, &lower_2, &upper_2);
        
        if(upper_1 >= lower_2 && upper_2 >= lower_1)
        {
            num_partial_overlaps++;
            if(lower_1 >= lower_2 && upper_2 >= upper_1 ||
                lower_2 >= lower_1 && upper_1 >= upper_2)
            {
                num_total_overlaps++;
            }   
        }
    }

    printf("Partial Overlaps: %d Total Overlaps: %d\n", num_partial_overlaps, num_total_overlaps);

    return 0;
}
