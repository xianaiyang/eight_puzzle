/* 
 * File:   game.h
 * Author: Administrator
 *
 * Created on 2014年11月27日, 下午3:26
 */

#ifndef GAME_H
#define	GAME_H
#include "eight_puzzle.h"
#include <string>
#include <queue>
#include<stack>
using namespace std;
class game {
public:
    game();
    game(const game& orig);
    void start_and_run();
    virtual ~game();
private:
    bool is_goal(const eight_puzzle&);
    bool is_legal(const eight_puzzle&, const char );
    eight_puzzle& init();
    void move_one_step(eight_puzzle&,const char);
    string& solution_BFS(const eight_puzzle&);
    const string& solution_cut_DFS(const eight_puzzle&);
    const string& solution_greed_cut_DFS(const eight_puzzle&);
    void help();

};

#endif	/* GAME_H */

