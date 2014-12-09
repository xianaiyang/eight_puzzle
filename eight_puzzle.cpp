/* 
 * File:   eight_puzzle.cpp
 * Author: Administrator
 * 
 * Created on 2014年11月27日, 下午12:53
 */

#include "eight_puzzle.h"


eight_puzzle::eight_puzzle() {
    vector<int> eight_number(9);
    for(int i = 0; i < 9; i++)
    {
        eight_number[i] = i;
    }
    random_shuffle(eight_number.begin(), eight_number.end());
    init(eight_number);
}
eight_puzzle::eight_puzzle(vector<int> & eight_number) {
    init(eight_number);
}
eight_puzzle::eight_puzzle(const eight_puzzle& orig) {
    for(int m = 0; m < 3; m++)
    {
        for(int n = 0; n < 3; n++)
        {
            cell[m][n] = orig.cell[m][n];
        }
    }
}
eight_puzzle& eight_puzzle::operator=(const eight_puzzle& source){
    for(int m = 0; m < 3; m++)
    {
        for(int n = 0; n < 3; n++)
        {
            cell[m][n] = source.cell[m][n];
        }
    }
    return *this;
}
ostream& operator <<(ostream & os, const eight_puzzle & puzzle){
    for(int i = 0; i < 13; i++)
    {
        os << '-';
    }
    os << endl;
    for(int m = 0; m < 3; m++)
    {
        for(int n = 0; n < 3; n++)
        {
            if(puzzle.cell[m][n] == 0)
            {
                os <<"|   ";
            }
            else
            {
                os <<"| " << puzzle.cell[m][n] << ' ';
            }
            if(n == 2)
            {
                os << '|' << endl;
            }
        }
    }
    for(int i = 0; i < 13; i++)
    {
        os << '-';
    }
    os << endl;
    return os;
}
unsigned int eight_puzzle::mahantann_distance(){
    unsigned int distance = 0;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            switch(cell[i][j]){
                case 0: break;
                case 1: distance += i + j; break;
                case 2: distance += i + abs(j - 1);break;
                case 3: distance += i + 2 -j; break;
                case 4: distance += abs(i - 1) + j;break;
                case 5: distance += abs(i - 1) + abs(j - 1); break;
                case 6: distance += abs(i - 1) + 2 - j ; break;
                case 7: distance += 2 -i + j;break;
                case 8: distance += 2 -i + abs(j - 1);break;
                default:break;
            }
        }
    }
    return distance;
}
void eight_puzzle::init(vector<int> &eight_number){
    for(int m = 0; m < 3; m++)
    {
        for(int n = 0; n < 3; n++)
        {
            cell[m][n] = eight_number[m*3 + n];
        }
    }
}
void eight_puzzle::principle(){
    cout <<"There are eight number from 1 to eight locate in a 3*3 cubic "
            "and with one blank. You can move one number arround the blank to it"
            "and at end you should get the state that the number arrange in order "
            "from top left to right bottom and the blank locat at bottom left. Have"
            "a fun and good luck"<<endl;
}
eight_puzzle::~eight_puzzle() {
}

