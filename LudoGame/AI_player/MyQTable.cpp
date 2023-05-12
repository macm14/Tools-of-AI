#include "MyQTable.h"

#include <iostream>
#include <exception>

#include <iostream>
#include <fstream>


using namespace std;

MyQTable::MyQTable()
{
    q_table = new long double *[STATES];
    for (int i = 0; i < STATES; i++)
    {
        q_table[i] = new long double[ACTIONS];
    }

    for (int i = 0; i < STATES; i++)
    {
        for (int j = 0; j < ACTIONS; j++)
        {
            q_table[i][j] = 0.0;
            //q_table[i][j] = (long double)rand() / RAND_MAX;
        }
    }

    reward_table = new long double[ACTIONS];
    
    reward_table[MOVE_OUT] = 0.25;
    reward_table[NORMAL] = 0.2;
    reward_table[IN_GOAL] = 0.8;
    reward_table[STAR] = 0.6;
    reward_table[GLOBE] = 0.4;
    reward_table[PROTECT] = 0.3;
    reward_table[KILL] = 0.3;
    reward_table[DIE] = 0.01;
    reward_table[GOAL_ZONE] = 0.4;
    reward_table[NOTHING] = 0;
}

long double MyQTable::get_value(int state, int action)
{
    return q_table[state][action];
}

void MyQTable::set_value(int state, int action, long double value)
{
    q_table[state][action] = value;
}

long double MyQTable::get_max_q(int state)
{
    long double max_value = -2;
    for (int i = 0; i < ACTIONS; i++) {
        if (q_table[state][i] > max_value) {
            max_value = q_table[state][i];
        }
    }
    return max_value;
}

void MyQTable::save(const std::string& name)
{
    ofstream myfile;
    myfile.open(name);
    if (myfile.is_open() == false)
        throw exception();

    for (int i = 0; i < STATES; i++)
    {
        for (int j = 0; j < ACTIONS; j++)
        {
            myfile << q_table[i][j] << "\n";
        }
    }
    myfile << 1.0 << "\n"; //ie. won state

    myfile.close();
}

bool MyQTable::load(const string& name)
{
    ifstream myfile;
    myfile.open(name);
    if (myfile.is_open() == false)
        std::cout << "Could not open file" << std::endl;

    double num = 0.0;
    for (int i = 0; i < STATES; i++)
    {
        for (int j = 0; j < ACTIONS; j++)
        {
            myfile >> num;
            q_table[i][j] = num;
        }
    }
    //for (int i = 0; i < STATES; i++)
    //{
    //    myfile >> num;
    //    q_table[i] = num;
    //}
    myfile.close();

   /* if (q_table[WON_STATE] != 1.0)
        throw exception();*/

    return true;
}

long double MyQTable::get_reward(int state)
{
    return reward_table[state];
}

//void MyQTable::record_visit(int index)
//{
//    usage_table[index]++;
//    total_visits++;
//}

//void MyQTable::report_visits()
//{
//    int one_time = 0;
//    int two_times = 0;
//    int teen_times = 0;
//    for (int i = 0; i < STATE_COUNT; i++)
//    {
//        if (usage_table[i] >= 1)  one_time++;
//        if (usage_table[i] >= 2)  two_times++;
//        if (usage_table[i] >= 10) teen_times++;
//    }
//
//    std::cout << one_time << "; " << two_times << "; " << teen_times << "; " << total_visits << std::endl;
//}

//void MyQTable::report_usage()
//{
//    int no_visit = 0;
//
//    int unused_goal[4] = { 0 };
//    int unused_pip[10] = { 0 };
//    int unused_unprotected[8] = { 0 };
//    int unused_threat[4] = { 0 };
//    int unused_best_opp[9] = { 0 };
//    int unused_second_opp[8] = { 0 };
//
//    int goal_pip[4][10] = { 0 };
//
//    for (int i = 0; i < STATE_COUNT; i++)
//    {
//        if (usage_table[i] == 0)
//        {
//            no_visit++;
//            int state = i;
//            int in_goal = state / GOAL_OFFSET;
//            state -= in_goal * GOAL_OFFSET;
//            int pip = state / PIP_OFFSET;
//            state -= pip * PIP_OFFSET;
//            int unprotected = state / UNPROTECTED_OFFSET;
//            state -= unprotected * UNPROTECTED_OFFSET;
//            int threat = state / THREAT_OFFSET;
//            state -= threat * THREAT_OFFSET;
//            int best_opp = state / BEST_OPP_OFFSET;
//            state -= best_opp * BEST_OPP_OFFSET;
//            int second_opp = state;
//
//            unused_goal[in_goal]++;
//            unused_pip[pip]++;
//            unused_unprotected[unprotected]++;
//            unused_threat[threat]++;
//            unused_best_opp[best_opp]++;
//            unused_second_opp[second_opp]++;
//
//            goal_pip[in_goal][pip]++;
//        }
//    }
//
//    std::cout << no_visit << " states was never visited" << std::endl;
//
//    std::cout << "unused_goal ";
//    for (int i = 0; i < 4; i++)
//        std::cout << unused_goal[i] << ", ";
//    std::cout << std::endl;
//
//    std::cout << "unused_pip ";
//    for (int i = 0; i < 10; i++)
//        std::cout << unused_pip[i] << ", ";
//    std::cout << std::endl;
//
//    std::cout << "unused_unprotected ";
//    for (int i = 0; i < 8; i++)
//        std::cout << unused_unprotected[i] << ", ";
//    std::cout << std::endl;
//
//    std::cout << "unused_threat ";
//    for (int i = 0; i < 4; i++)
//        std::cout << unused_threat[i] << ", ";
//    std::cout << std::endl;
//
//    std::cout << "unused_best_opp ";
//    for (int i = 0; i < 9; i++)
//        std::cout << unused_best_opp[i] << ", ";
//    std::cout << std::endl;
//
//    std::cout << "unused_second_opp ";
//    for (int i = 0; i < 8; i++)
//        std::cout << unused_second_opp[i] << ", ";
//    std::cout << std::endl;
//
//    //    std::cout << "goal_pip: " << std::endl;
//    //    for(int i = 0; i < 4; i++)
//    //    {
//    //        for(int j = 0; j < 10; j++)
//    //            std::cout << goal_pip[i][j] << ", ";
//    //            std::cout << std::endl;
//    //    }
//    //    std::cout << std::endl;
//}

void MyQTable::copy_values_to(MyQTable& destination)
{
    for (int i = 0; i < STATES; i++)
    {
        for (int j = 0; j < ACTIONS; j++)
        {
            destination.q_table[i][j] = this->q_table[i][j];
        }
    }

    //for (int i = 0; i < STATES; i++)
    //    destination.q_table[i] = this->q_table[i];

    //destination.q_table[WON_STATE] = 1.0;
}

double MyQTable::difference(MyQTable& other_table)
{
    double dif = 0;

    for (int i = 0; i < STATES; i++)
    {
        for (int j = 0; j < ACTIONS; j++)
        {
            dif += abs(other_table.q_table[i][j] - this->q_table[i][j]);
        }
    }
    /*for (int i = 0; i < STATE_COUNT; i++)
        dif += abs(other_table.q_table[i] - this->q_table[i]);*/

    return dif;
}

void MyQTable::print_q_table()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            std::cout << q_table[i][j] << "  ";
        }
        std::cout << std::endl;
    }
}

MyQTable::~MyQTable() {

    for (int i = 0; i < STATES; i++)
    {
        delete[] q_table[i];
    }

    delete q_table;
}


