#include <stdio.h>
#include <fstream>
#include <cstdlib>
#include <cstring>

int main()
{

    std::ifstream input_file("input.txt");
    char buffer[128];

    int num_overlaps = 0;
    int num_total_overlaps = 0;

    while(input_file.peek() != EOF)
    {
        input_file.getline(buffer, sizeof(buffer));
        int bytes_read = strlen(buffer);
        
        int start_1, end_1, start_2, end_2;

        sscanf(buffer, "%d-%d,%d-%d", &start_1, &end_1, &start_2, &end_2);

        if((start_1 <= start_2 && end_1 >= start_2) ||
            (start_2 <= start_1 && end_2 >= start_1))
        {
            num_overlaps++;
            if(start_1 <= start_2 && end_1 >= end_2 ||
                start_2 <= start_1 && end_2 >= end_1)
            {
                num_total_overlaps++;   
            }
        }
    }

    printf("Num Overlaps: %d Total Overlaps: %d\n", num_overlaps, num_total_overlaps);

    return 0;
}
