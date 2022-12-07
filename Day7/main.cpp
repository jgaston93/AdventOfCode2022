#include <stdio.h>
#include <fstream>
#include <cstdlib>
#include <cstring>

bool CheckDuplicates(char* sub_stream, int sub_stream_size);

int main()
{
    std::ifstream input_file("input.txt");
    char buffer[4096];
    input_file.getline(buffer, sizeof(buffer));
    int stream_size = strlen(buffer);
    
    int marker_position = 0;
    const int marker_size = 14;

    for(int i = 0; i < stream_size - marker_size; i++)
    {
        if(!CheckDuplicates(&buffer[i], marker_size))
        {
            marker_position = i + marker_size;
            break;
        }
    }

    printf("Marker Position: %d\n", marker_position);

    input_file.close();

    return 0;
}


bool CheckDuplicates(char* sub_stream, int sub_stream_size)
{
    bool duplicate_found = false;

    for(int i = 0; i < sub_stream_size - 1; i++)
    {
        for(int j = i + 1; j < sub_stream_size; j++)
        {
            if(sub_stream[i] == sub_stream[j])
            {
                duplicate_found = true;
            }
        }
        if(duplicate_found)
        {
            break;
        }
    }

    return duplicate_found;
}