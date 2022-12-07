#include <stdio.h>
#include <fstream>
#include <cstdlib>
#include <cstring>

typedef struct File
{
    char* name = 0;
    int size = 0;
} File;

typedef struct Directory
{
    char* name = 0;
    Directory* parent_directory = 0;
    int num_directories = 0;
    int num_files = 0;
    Directory** directories = 0;
    File** files = 0;
    int size = 0;
} Directory;

const int max_size = 4096;
Directory* fifo_pop(Directory** stack, int* size);
Directory* lifo_pop(Directory** stack, int* size);
void push(Directory** stack, int* size, Directory* crate);
int calculate_sum(Directory* directory);

int main()
{
    std::ifstream input_file("input.txt");
    char buffer[64];
    
    input_file.getline(buffer, sizeof(buffer));

    Directory* root = new Directory();
    root->name = strdup("/");

    Directory* current_dir = root;

    while(input_file.peek() != EOF)
    {
        input_file.getline(buffer, sizeof(buffer));

        if(buffer[2] == 'l')
        {
            int num_directories = 0;
            int num_files = 0;
            Directory** directories = new Directory*[64];
            File** files = new File*[64];
            while(input_file.peek() != '$' && input_file.peek() != EOF)
            {
                input_file.getline(buffer, sizeof(buffer));
                if(buffer[0] == 'd')
                {
                    Directory* directory = new Directory();
                    directory->name = strdup(&buffer[4]);
                    directory->parent_directory = current_dir;
                    directories[num_directories++] = directory;
                }
                else
                {
                    File* file = new File();
                    int index = strcspn(buffer, " ");
                    file->name = strdup(&buffer[index + 1]);
                    buffer[index] = '\0';
                    file->size = atoi(buffer);
                    files[num_files++] = file;
                }
            }
            if(num_directories > 0)
            {
                Directory** directory_list = new Directory*[num_directories];
                memcpy(directory_list, directories, sizeof(Directory*) * num_directories);
                current_dir->directories = directory_list;
                delete[] directories;
                current_dir->num_directories = num_directories;
            }
            if(num_files > 0)
            {
                File** file_list = new File*[num_files];
                memcpy(file_list, files, sizeof(File*) * num_files);
                current_dir->files = file_list;
                delete[] files;
                current_dir->num_files = num_files;
            }
        }
        else if(buffer[2] == 'c')
        {
            if(buffer[5] == '.')
            {
                current_dir = current_dir->parent_directory;
            }
            else
            {
                for(int i = 0; i < current_dir->num_directories; i++)
                {
                    if(strcmp(&buffer[5], current_dir->directories[i]->name) == 0)
                    {
                        current_dir = current_dir->directories[i];
                        break;
                    }
                }
            }
        }
    }

    int total_space = 70000000;
    int target_free_space = 30000000;
    int used_space = calculate_sum(root);
    int current_free_space = total_space - used_space;

    Directory* stack[max_size];
    int size = 0;
    push(stack, &size, root);

    int sum = 0;
    int minimum = total_space;
    int space_to_delete = 0;

    while(size > 0)
    {
        Directory* dir = lifo_pop(stack, &size);
        if(dir->size <= 100000 && dir->name[0] != '/')
        {
            printf("%s: %d\n", dir->name, dir->size);
            sum += dir->size;
        }

        int new_free_space = current_free_space + dir->size;
        if(new_free_space > target_free_space)
        {
            int difference = target_free_space - new_free_space;
            if(difference < minimum)
            {
                minimum = difference;
                space_to_delete = dir->size;
            }
        }

        for(int i = 0; i < dir->num_directories; i++)
        {
            push(stack, &size, dir->directories[i]);
        }
    }

    printf("Total Sum: %d\n", sum);
    printf("Space to Delete: %d\n", space_to_delete);

    input_file.close();

    return 0;
}

int calculate_sum(Directory* directory)
{
    int sum = 0;
    for(int i = 0; i < directory->num_files; i++)
    {
        sum += directory->files[i]->size;
    }
    if(directory->num_directories > 0)
    {
        for(int i = 0; i < directory->num_directories; i++)
        {
            sum += calculate_sum(directory->directories[i]);
        }
    }
    
    directory->size = sum;
    return sum;
}

Directory* lifo_pop(Directory** stack, int* size)
{
    Directory* directory = 0;
    if(*size > 0)
    {
        directory = stack[*size - 1];
        *size -= 1;
    }
    return directory;
}

Directory* fifo_pop(Directory** stack, int* size)
{
    Directory* directory = 0;
    if(*size > 0)
    {
        directory = stack[0];
        for(int i = 0; i < *size - 1; i++)
        {
            Directory* dir = stack[i];
            stack[i] = stack[i+1];
            stack[i+1] = dir;
        }
        *size -= 1;
    }
    return directory;
}

void push(Directory** stack, int* size, Directory* crate)
{
    if(*size < max_size)
    {
        stack[*size] = crate;
        *size += 1;
    }
}