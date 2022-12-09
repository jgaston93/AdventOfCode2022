#include <stdio.h>
#include <fstream>
#include <cstdlib>
#include <cstring>


struct Vec2
{
    int x = 0;
    int y = 0;

    Vec2(int x=0, int y=0) : x(x), y(y)
    {
    }

    void shorten()
    {
        if(x < -1) x = -1;
        if(x > 1) x = 1;
        if(y < -1) y = -1;
        if(y > 1) y = 1;
    }

    Vec2 operator+(const Vec2 a) const
    {
        return Vec2(a.x + x, a.y + y);
    }
    
    Vec2 operator-(const Vec2 a) const
    {
        return Vec2(x - a.x, y - a.y);
    }

    bool operator==(const Vec2 a) const
    {
        return a.x == x && a.y == y;
    }
};

int main()
{
    std::ifstream input_file("input.txt");
    char buffer[32];

    const int num_knots = 10;
    Vec2 knots[num_knots];

    Vec2 pos_list[100000];
    pos_list[0] = Vec2(0, 0); // add initial position
    int num_distinct_pos = 1;
    
    while(input_file.peek() != EOF)
    {
        input_file.getline(buffer, sizeof(buffer));

        // Create vector to move head
        Vec2 move_vec;
        char direction = buffer[0];
        int distance = atoi(&buffer[2]);
        
        switch(direction)
        {
            case 'U':
                move_vec.y = 1;
                break;
            case 'D':
                move_vec.y = -1;
                break;
            case 'L':
                move_vec.x = -1;
                break;
            case 'R':
                move_vec.x = 1;
                break;
        }

        for(int i = 0; i < distance; i++)
        {
            // Move head
            knots[0] = knots[0] + move_vec;

            // Move other knots
            for(int j = 1; j < num_knots; j++)
            {
                Vec2 pos_diff = knots[j - 1] - knots[j];

                // If not adjacent to previous knot move
                if(abs(pos_diff.x) > 1 || abs(pos_diff.y) > 1)
                {                    
                    pos_diff.shorten(); // Can only move 1 step in any direction
                    knots[j] = knots[j] + pos_diff;
                    
                    // Check position of last knot
                    if(j == num_knots - 1)
                    {
                        bool visited = false;
                        for(int k = 0; k < num_distinct_pos; k++)
                        {
                            if(pos_list[k] == knots[j])
                            {
                                visited = true;
                            }
                            if(visited)
                            {
                                break;
                            }
                        }
                        if(!visited)
                        {
                            pos_list[num_distinct_pos++] = knots[j];
                        }
                    }
                }
            }
        }
    }

    printf("Visited positions: %d\n", num_distinct_pos);
    
    input_file.close();

    return 0;
}
