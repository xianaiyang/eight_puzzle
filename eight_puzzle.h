/* 
 * File:   eight_puzzle.h
 * Author: Administrator
 *
 * Created on 2014年11月27日, 下午12:53
 */

#ifndef EIGHT_PUZZLE_H
#define	EIGHT_PUZZLE_H
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include<math.h>
using namespace std;
class eight_puzzle {
public:
    eight_puzzle();
    eight_puzzle(vector<int> &);
    eight_puzzle(const eight_puzzle& orig);
    eight_puzzle& operator=(const eight_puzzle&);
    unsigned int mahantann_distance();
    static void principle();
    virtual ~eight_puzzle();
    friend ostream& operator<<(ostream &, const eight_puzzle &);
    friend class game;
private:
    void init(vector < int > &);
    int cell[3][3];

};

#endif	/* EIGHT_PUZZLE_H */

