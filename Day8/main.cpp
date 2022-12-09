#include <stdio.h>
#include <fstream>
#include <cstdlib>
#include <cstring>


int main()
{
    std::ifstream input_file("input.txt");
    char buffer[1024];

    const int num_rows = 99;
    const int num_columns = 99;
    int forest[99][99];
    
    int row = 0;
    while(input_file.peek() != EOF)
    {
        input_file.getline(buffer, sizeof(buffer));
        
        for(int col = 0; col < num_columns; col++)
        {
            forest[row][col] = buffer[col] - '0';
        }
        row++;
    }

    int num_visible_trees = 0;
    int max_scenic_score = 0;

    for(int i = 0; i < num_rows; i++)
    {
        for(int j = 0; j < num_columns; j++)
        {
            bool visible_left = true;
            bool visible_right = true;
            bool visible_up = true;
            bool visible_down = true;
            int left_score = 0;
            int right_score = 0;
            int up_score = 0;
            int down_score = 0;

            // look left
            for(int k = j - 1; k >= 0; k--)
            {
                left_score++;
                if(forest[i][k] >= forest[i][j])
                {
                    visible_left = false;
                }
                if(!visible_left)
                {
                    break;
                }
            }
            // look right
            for(int k = j + 1; k < num_columns; k++)
            {
                right_score++;
                if(forest[i][k] >= forest[i][j])
                {
                    visible_right = false;
                }
                if(!visible_right)
                {
                    break;
                }
            }

            // look up
            for(int k = i - 1; k >= 0; k--)
            {
                up_score++;
                if(forest[k][j] >= forest[i][j])
                {
                    visible_up = false;
                }
                if(!visible_up)
                {
                    break;
                }
            }
            
            // look down
            for(int k = i + 1; k < num_rows; k++)
            {
                down_score++;
                if(forest[k][j] >= forest[i][j])
                {
                    visible_down = false;
                }
                if(!visible_down)
                {
                    break;
                }
            }

            int scenic_score = left_score * right_score * up_score * down_score;
            if(scenic_score > max_scenic_score)
            {
                max_scenic_score = scenic_score;
            }

            if(visible_left || visible_right || visible_up || visible_down)
            {
                num_visible_trees++;
            }
        }
    }

    printf("Num visible trees: %d\n", num_visible_trees);
    printf("Max scenic score: %d\n", max_scenic_score);
    
    input_file.close();

    return 0;
}
