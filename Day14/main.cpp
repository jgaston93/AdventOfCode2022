#include <stdio.h>
#include <fstream>
#include <cstdlib>
#include <cstring>

struct Coordinate
{
    int x;
    int y;

    Coordinate(int x=0, int y=0) : x(x), y(y)
    {
    }

    Coordinate operator+(const Coordinate a) const
    {
        return Coordinate(x + a.x, y + a.y);
    }

    Coordinate operator-(const Coordinate a) const
    {
        return Coordinate(x - a.x, y - a.y);
    }

    bool operator==(const Coordinate a) const
    {
        return a.x == x && a.y == y;
    }

    bool operator!=(const Coordinate a) const
    {
        return a.x != x || a.y != y;
    }
};

int main()
{
    std::ifstream input_file("input.txt");
    char buffer[1024];

    const int cave_size = 1024;
    char cave[cave_size][cave_size];
    for(int i = 0; i < cave_size; i++)
    {
        memset(cave[i], '.', cave_size);
    }

    int max_x = 0;
    int min_x = 0xFFFF;
    int max_y = 0;
    int min_y = 0xFFFF;
    

    while(input_file.peek() != EOF)
    {
        input_file.getline(buffer, sizeof(buffer));
        int buffer_size = strlen(buffer);

        int buffer_index = 0;
        int x_index = 0;
        int y_index = 0;
        bool coordinate_found = false;
        int num_coordinates = 0;
        Coordinate prev_coord;

        while(buffer_index < buffer_size + 1)
        {
            if(!coordinate_found)
            {
                if(buffer[buffer_index] == ',')
                {
                    buffer[buffer_index] = '\0';
                    y_index = buffer_index + 1;
                }
                else if(buffer[buffer_index] == ' ' || 
                        buffer[buffer_index] == '\0')
                {
                    buffer[buffer_index] = '\0';
                    coordinate_found = true;
                }

            }
            if(coordinate_found)
            {
                int x_value = atoi(&buffer[x_index]);
                int y_value = atoi(&buffer[y_index]);
                Coordinate coord(x_value, y_value);
                num_coordinates++;

                if(num_coordinates > 1)
                {
                    Coordinate diff = coord - prev_coord;
                    if(diff.x > 0) diff.x = 1;
                    else if(diff.x < 0) diff.x = -1;
                    if(diff.y > 0) diff.y = 1;
                    else if(diff.y < 0) diff.y = -1;

                    while(prev_coord != coord)
                    {
                        cave[prev_coord.y][prev_coord.x] = '#';
                        prev_coord = prev_coord + diff;
                    }
                }
                prev_coord = coord;
                cave[prev_coord.y][prev_coord.x] = '#';

                if(x_value < min_x) min_x = x_value;
                if(x_value > max_x) max_x = x_value;
                if(y_value < min_y) min_y = y_value;
                if(y_value > max_y) max_y = y_value;
                coordinate_found = false;

                buffer_index += 4;
                x_index = buffer_index;
            }
            buffer_index++;
        }
    }
    
    input_file.close();

    for(int i = 0; i < cave_size; i++)
    {
        cave[max_y + 2][i] = '#';
    }

    printf("Min X: %d Max X: %d\n", min_x, max_x);
    printf("Min Y: %d Max Y: %d\n", min_y, max_y);

    bool reached_abyss = false;
    int num_sand_particles = 0;

    Coordinate start(500, 0);

    int num_directions = 3;
    Coordinate directions[] = {
        Coordinate(0, 1),
        Coordinate(-1, 1),
        Coordinate(1, 1)
    };

    int cant_move_count = 0;

    while(!reached_abyss && cant_move_count < 2)
    {
        num_sand_particles++;
        Coordinate sand = start;
        bool can_move = true;
        while(can_move)
        {
            bool moved = false;
            for(int i = 0; i < num_directions; i++)
            {
                Coordinate new_coord = sand + directions[i];
                if(cave[new_coord.y][new_coord.x] == '.')
                {
                    sand = new_coord;
                    moved = true;
                    cant_move_count = 0;
                    break;
                }
            }
            if(!moved)
            {
                can_move = false;
                cant_move_count++;
            }
            if(sand.y > max_y + 3)
            {
                reached_abyss = true;
            }
        }
        cave[sand.y][sand.x] = 'o';
    }


    for(int i = min_y - 5; i < max_y + 5; i++)
    {
        for(int j = min_x - 5; j < max_x + 5; j++)
        {
            printf("%c", cave[i][j]);
        }
        printf("\n");
    }

    printf("Num Particles = %d\n", num_sand_particles - 1);
    if(reached_abyss)
    {
        printf("Reached abyss\n");
    }

    return 0;
}