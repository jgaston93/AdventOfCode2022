#include "Monkey.hpp"
#include <stdio.h>
#include <tgmath.h>

Monkey::Monkey() : m_num_inspections(0), m_num_items(0)
{
}

Monkey::~Monkey()
{
    delete m_operation;
}

void Monkey::SetOperation(Operation *operation)
{
    m_operation = operation;
}

void Monkey::SetTest(unsigned long long int value, Monkey *monkey_1, Monkey *monkey_2)
{
    m_test_value = value;
    m_monkey_1 = monkey_1;
    m_monkey_2 = monkey_2;
}

void Monkey::TakeTurn()
{
    for(int i = 0; i < m_num_items; i++)
    {
        printf("        Worry Level %i: %llu -> ", i, m_item_list[i]);
        unsigned long long int new_item = m_operation->PerformOperation(m_item_list[i]);
        printf("%llu\n", new_item);
        if(new_item < m_item_list[i])
        {
            printf("        !!!!Overflow!!!!\n");
        }
        m_item_list[i] = new_item;

        if(m_item_list[i] % m_test_value == 0)
        {
            m_monkey_1->GiveItem(m_item_list[i]);
        }
        else
        {
            m_monkey_2->GiveItem(m_item_list[i]);
        }
        m_num_inspections++;
    }
    m_num_items = 0;
}

void Monkey::GiveItem(unsigned long long int item)
{
    m_item_list[m_num_items++] = item;
}

int Monkey::GetItems(unsigned long long int* items)
{
    for(int i = 0; i < m_num_items; i++)
    {
        items[i] = m_item_list[i];
    }
    return m_num_items;
}

unsigned long long int Monkey::GetNumInspections()
{
    return m_num_inspections;
}