#include <stdio.h>
#include <fstream>
#include <cstdlib>
#include <cstring>

struct File
{
    char* name = 0;
    int size = 0;
};

struct Directory
{
    char* name = 0;
    Directory* parent_directory = 0;
    int num_directories = 0;
    int num_files = 0;
    Directory** directories = 0;
    File** files = 0;
};

int main()
{
    std::ifstream input_file("input.txt");
    char buffer[64];
    
    input_file.getline(buffer, sizeof(buffer));

    struct Directory* root = new Directory();
    root->name = strdup("/");

    struct Directory* current_dir = root;

    while(input_file.peek() != EOF)
    {
        input_file.getline(buffer, sizeof(buffer));

        if(buffer[2] == 'l')
        {
            int num_directories = 0;
            int num_files = 0;
            struct Directory** directories = new Directory*[64];
            struct File** files = new File*[64];
            while(input_file.peek() != '$')
            {
                input_file.getline(buffer, sizeof(buffer));
                if(buffer[0] == 'd')
                {
                    struct Directory* directory = new Directory();
                    directory->name = strdup(&buffer[4]);
                    directory->parent_directory = current_dir;
                    directories[num_directories++] = directory;
                }
                else
                {
                    struct File* file = new File();

                }
            }
        }
        else if(buffer[2] == 'c')
        {

        }
    }

    input_file.close();

    return 0;
}
