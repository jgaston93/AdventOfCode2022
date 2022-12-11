#ifndef MONKEY_HPP
#define MONKEY_HPP

#include "Operation.hpp"

class Monkey
{
    public:
        Monkey();
        ~Monkey();
        void SetOperation(Operation *operation);
        void SetTest(int value, Monkey *monkey_1, Monkey *monkey_2);
        void TakeTurn();
        void GiveItem(int item);

    private:
        int m_item_list[64];
        int m_num_items;
        Operation *m_operation;
        int m_test_value;
        Monkey *m_monkey_1;
        Monkey *m_monkey_2;
};

#endif // MONKEY_HPP