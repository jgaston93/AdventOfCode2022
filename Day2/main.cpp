#include <stdio.h>
#include <fstream>
#include <cstdlib>
#include <cstring>

enum Choice
{
    rock = 1,
    paper = 2,
    scissors = 3
};

enum Outcome
{
    win,
    lose,
    draw
};

// Part 1
Choice GetChoice(char input);

// Part 2
Choice GetMyChoice(Choice opponent_choice, Outcome outcome);
Outcome GetOutcome(char input);

int CalculateScore(Choice opponent_choice, Choice my_choice);

int main()
{
    bool part_1 = false; // switch between part 1 and 2

    std::ifstream input_file("input.txt");
    char buffer[64];

    int score = 0;

    while(input_file.peek() != EOF)
    {
        input_file.getline(buffer, sizeof(buffer));

        Choice opponent_choice = GetChoice(buffer[0]);
        Choice my_choice;
        
        if(part_1)
        {
            my_choice = GetChoice(buffer[2]);
        }
        else
        {
            Outcome outcome = GetOutcome(buffer[2]);
            my_choice = GetMyChoice(opponent_choice, outcome);
        }

        score += CalculateScore(opponent_choice, my_choice);
    }

    printf("Total Score: %d\n", score);

    input_file.close();

    return 0;
}

Choice GetChoice(char input)
{
    Choice choice;

    if(input == 'A' || input == 'X')
    {
        choice = rock;
    }
    else if(input == 'B' || input == 'Y')
    {
        choice = paper;
    }
    else if(input == 'C' || input == 'Z')
    {
        choice = scissors;
    }

    return choice;
}

Choice GetMyChoice(Choice opponent_choice, Outcome outcome)
{
    Choice choice = opponent_choice;

    if(outcome == lose)
    {
        int choice_number = opponent_choice - 1;
        if(choice_number < 1)
        {
            choice_number = 3;
        }
        choice = (Choice)choice_number;
        
    }
    else if(outcome == win)
    {
        int choice_number = opponent_choice + 1;
        if(choice_number > 3)
        {
            choice_number = 1;
        }
        choice = (Choice)choice_number;
    }

    return choice;
}

Outcome GetOutcome(char input)
{
    Outcome outcome;

    if(input == 'X')
    {
        outcome = lose;
    }
    else if(input == 'Y')
    {
        outcome = draw;
    }
    else if(input == 'Z')
    {
        outcome = win;
    }

    return outcome;
}

int CalculateScore(Choice opponent_choice, Choice my_choice)
{
    int score = (int)my_choice;

    // win
    if((my_choice > opponent_choice && my_choice - opponent_choice == 1) ||
        (my_choice == rock && opponent_choice == scissors))
    {
        score += 6;
    }
    // draw
    else if(my_choice == opponent_choice)
    {
        score += 3;
    }

    return score;
}