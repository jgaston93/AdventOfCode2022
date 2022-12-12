#include <stdio.h>
#include <fstream>
#include <cstdlib>
#include <cstring>

struct Tile
{
    char height;
    bool visited;
};

struct Position
{
    int x;
    int y;
    int level;

    Position(int x=0, int y=0, int level=0) : x(x), y(y), level(level)
    {
    }    

    Position operator+(const Position a) const
    {
        return Position(a.x + x, a.y + y);
    }

    bool operator==(const Position a) const
    {
        return a.x == x && a.y == y;
    }
};

Position pop(Position* queue, int* size);
void push(Position* queue, int* size, Position pos);
bool can_visit(Tile* current_tile, Tile* proposed_tile);

int main()
{
    std::ifstream input_file("input.txt");
    const int height = 41;
    const int width = 113;

    Tile height_map[height][width];
    Position start;
    Position end;

    int row_index = 0;
    while(input_file.peek() != EOF)
    {
        char buffer[width + 1];
        input_file.getline(buffer, sizeof(buffer));
        for(int i = 0; i < width; i++)
        {
            if(buffer[i] == 'S')
            {
                height_map[row_index][i] = { 'a', false };
                start.x = i;
                start.y = row_index;
                printf("Start = height_map[%d][%d]\n", start.x, start.y);
            }
            else if(buffer[i] == 'E')
            {
                height_map[row_index][i] = { 'z', false };
                end.x = i;
                end.y = row_index;
                printf("End = height_map[%d][%d]\n", end.x, end.y);
            }
            else
            {
                height_map[row_index][i] = { buffer[i], false };
            }
        }
        row_index++;
    }
    
    input_file.close();

    int num_directions = 4;
    Position directions[] = { Position(-1, 0),      // Left
                                Position(1, 0),     // Right
                                Position(0, -1),    // Down
                                Position(0, 1) };   // Up

    int shortest_distance = width * height;

    for(int m = 0; m < height; m++)
    {
        for(int n = 0; n < width; n++)
        {
            if(height_map[m][n].height == 'a')
            {
                start.x = n;
                start.y = m;
            }
            else
            {
                continue;
            }

            const int max_queue_size = width * height * 1000;
            Position* queue = new Position[max_queue_size];
            int queue_size = 0;
            push(&queue[0], &queue_size, start);

            while(queue_size > 0)
            {
                Position pos = pop(&queue[0], &queue_size);
                        
                Tile* tile = &height_map[pos.y][pos.x];
                if(tile->visited)
                {
                    continue;
                }

                if(pos.x == end.x && pos.y == end.y)
                {
                    if(pos.level < shortest_distance)
                    {
                        shortest_distance = pos.level;
                    }
                    break;
                }
                tile->visited = true;

                for(int i = 0; i < num_directions; i++)
                {
                    Tile* new_tile = 0;
                    Position new_pos = pos + directions[i];
                    new_pos.level = pos.level + 1;
                    if(0 <= new_pos.x && new_pos.x < width &&
                        0 <= new_pos.y && new_pos.y < height)
                    {
                        new_tile = &height_map[new_pos.y][new_pos.x];
                    }
                    if(new_tile && can_visit(tile, new_tile))
                    {
                        push(&queue[0], &queue_size, new_pos);
                    }
                }

                if(queue_size > max_queue_size)
                {
                    printf("Exceeded queue length\n");
                }
            }

            for(int x = 0; x < height; x++)
            {
                for(int y = 0; y < width; y++)
                {
                    height_map[x][y].visited = false;
                }
            }
        }
    }

    printf("Shortest path: %d\n", shortest_distance);

    return 0;
}

bool can_visit(Tile* current_tile, Tile* proposed_tile)
{
    bool can_visit = false;
    if(proposed_tile->height <= current_tile->height || current_tile->height + 1 == proposed_tile->height)
    {
        can_visit = true;
    }
    return can_visit;
}

Position pop(Position* queue, int* size)
{
    Position position = queue[0];
    for(int i = 0; i < *size - 1; i++)
    {
        Position pos = queue[i];
        queue[i] = queue[i+1];
        queue[i+1] = pos;
    }
    *size -= 1;
    
    return position;
}

void push(Position* stack, int* size, Position crate)
{
    stack[*size] = crate;
    *size += 1;
}
