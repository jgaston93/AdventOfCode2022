#include "Monkey.hpp"

Monkey::Monkey() : m_num_items(0)
{
}

Monkey::~Monkey()
{
    delete[] m_item_list;
    delete m_operation;
}

void Monkey::SetOperation(Operation *operation)
{
    m_operation = operation;
}

void Monkey::SetTest(int value, Monkey *monkey_1, Monkey *monkey_2)
{
    m_test_value = value;
    m_monkey_1 = monkey_1;
    m_monkey_2 = monkey_2;
}

void Monkey::TakeTurn()
{


}

void Monkey::GiveItem(int item)
{
    m_item_list[m_num_items++] = item;
}