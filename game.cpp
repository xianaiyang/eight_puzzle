/* 
 * File:   game.cpp
 * Author: Administrator
 * 
 * Created on 2014年11月27日, 下午3:26
 */

#include "game.h"

game::game() {
}
game::game(const game& orig) {
}
 eight_puzzle& game::init(){
    cout <<"do you know the principle of eight puzzle game[y/n]?"<<endl;
    char choice;
    cin >> choice;
    if(choice == 'n' || choice == 'N'){
        eight_puzzle::principle();
    }
        cout <<"do you want to start at random station or you want to start"
                "a specific station you give[r/s]?";
        cin >> choice;
        if(choice = 'r' || choice == 'R'){
            eight_puzzle * start_state = new eight_puzzle();
            return *start_state;
        }
        else if(choice == 's' || choice == 'S'){
            cout << "please input your state from left top to right bottom"
                    " using escape to seperate each number and you use 0 to re"
                    "place blank. Thank you"<<endl;
            int num;
            vector <int> state_vector;
            int count = 0;
            while(cin >> num){
                state_vector.push_back(num);
                count++;
            }
            if(count!= 9){
                cerr <<"you should input 9 number"<<endl;
                exit -1;
            }
            else{
                 eight_puzzle* start = new eight_puzzle(state_vector);
                return *start;
            }
        }
        else{
            cerr << "wrong input"<<endl;
            exit -1;
        }

}
bool game::is_goal(const eight_puzzle & state){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(i + j != 4){
                if(state.cell[i][j] != 3*i + j + 1){
                    return false;
                }
            }
        }
    }
    return true;
}
bool game:: is_legal(const  eight_puzzle& state, const char direction){
    string legal_dirc;
    int row,col; // recommend the location of blank
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(state.cell[i][j] == 0){
                row = i;
                col = j;
                break;
            }
        }
    }
    if(row != 0){
        legal_dirc.push_back('s');
    }
    if(row != 2){
        legal_dirc.push_back('w');
    }
    if(col != 0){
        legal_dirc.push_back('d');
    }
    if(col != 2){
        legal_dirc.push_back('a');
    }
    if(legal_dirc.find(direction) != string::npos){
        return true;
    }
    else{
        return false;
    }
    
}
void game::move_one_step( eight_puzzle& state ,const char direction){
    int row,col; // recommend the location of blank
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(state.cell[i][j] == 0){
                row = i;
                col = j;
                break;
            }
        }
    }
    int new_row, new_col;
    if(direction == 'w'){
        new_row = row + 1;
        new_col = col;
    }
    if(direction == 'a'){
        new_row = row;
        new_col = col + 1;
    }
    if(direction == 's'){
        new_row = row - 1;
        new_col = col;
    }
    if(direction == 'd'){
        new_col = col - 1;
        new_row = row;
    }
    state.cell[row][col] = state.cell[new_row][new_col];
    state.cell[new_row][new_col] = 0;
}
void game::start_and_run(){
    eight_puzzle& puzzle_state = init();
    int try_num = 0;
    while(!is_goal(puzzle_state)){
        if(try_num == 0){
        cout <<"you can check the answer after you have try more than 30 times"<<endl;
        }
        if(try_num >= 3){
            cout <<"do you need to check the answer[y/n]"<<endl;
            char ans;
            cin >> ans;
            if(ans == 'y'|| ans == 'Y')
            {
                string solu = solution_greed_cut_DFS(puzzle_state);
                string::const_iterator seq_action = solu.begin();
                for(;seq_action != solu.end(); seq_action++)
                {
                    cout << puzzle_state<<endl;
                    cout << *seq_action<<endl;
                    move_one_step(puzzle_state,*seq_action);
                }
                cout << puzzle_state<<endl;
                return;
            }
        }
        cout << puzzle_state<<endl<<"please enter your move[a,s,w,d]"<<endl;
        char direction;
        cin >> direction;
        if(is_legal(puzzle_state,direction)){
            move_one_step(puzzle_state,  direction);
            try_num++;
        }
    }
    cout <<"恭喜你， 你赢了"<<endl;
}
const string& game::solution_cut_DFS(const eight_puzzle& state){
    string init_action("");
    stack<const eight_puzzle*> front_stack;
    stack<string*> action_seq;
    stack<int> depth;
    depth.push(0);
    front_stack.push(&state);
    action_seq.push(&init_action);
    int depth_cut = 1;
    const eight_puzzle* state_to_exploit = new eight_puzzle(*front_stack.top());
    const string* path = new string(*action_seq.top());
    int current_depth = depth.top();
    while(!is_goal(*state_to_exploit)){
        while(!is_goal(*state_to_exploit) ){
            front_stack.pop();
            action_seq.pop();
            depth.pop();
            string direct("aswd");
            if(current_depth < depth_cut){
                for(int i = 0; i < 4; i++){
                    if(is_legal(*state_to_exploit,direct[i])){
                        eight_puzzle * new_state = new eight_puzzle(*state_to_exploit);
                        string* action = new string();
                        action->assign(*path);
                        action->push_back(direct[i]);
                        move_one_step(*new_state,direct[i]);
                        front_stack.push(new_state);
                        action_seq.push(action);
                        depth.push(current_depth + 1);
                    }
                 }
            }
            if(state_to_exploit != NULL && state_to_exploit != &state){
                delete state_to_exploit;
            }
            if(path != NULL && path != &init_action){
                delete path;
            }
            if(front_stack.empty()){
                break;
            }
            state_to_exploit = front_stack.top();
            path = action_seq.top();
            current_depth = depth.top();
        }
        if(!action_seq.empty()){
            return *path;
        }
        depth_cut++;
        cout << "depth_cut"<<depth_cut<<endl;
        front_stack.push(&state);
        action_seq.push(&init_action);
        depth.push(0);
        state_to_exploit = front_stack.top();
        path = action_seq.top();
        current_depth = depth.top();
    }
}
string& game::solution_BFS(const class eight_puzzle& state){
    string* path = new string();
    queue<const eight_puzzle*> front_queue;
    queue<string*> action_seq;
    front_queue.push(&state);
    const  eight_puzzle* state_to_exploit;
    state_to_exploit = new eight_puzzle(*front_queue.front());
    int state_num = 0;
    while(!is_goal(*state_to_exploit)){
        cout <<"state number:"<<++state_num<<endl;
        front_queue.pop();
        if(!action_seq.empty()){
            action_seq.pop();
        }
        string direct("aswd");
        for(int i = 0; i < 4; i++){
            if(is_legal(*state_to_exploit,direct[i])){
                class eight_puzzle * new_state = new eight_puzzle();
                *new_state = *state_to_exploit;
                string* actions = new string();
                if(!path->empty()){
                    actions->assign(*path);
                }
                actions->push_back(direct[i]);
                move_one_step(*new_state,direct[i]);
                front_queue.push(new_state);
                action_seq.push(actions);
            } 
        }
        delete state_to_exploit;
        state_to_exploit = front_queue.front();
        delete path;
        path = action_seq.front();
    }
    string * result = new string();
    result->assign(*path);
    cout << *path;
    return *result;
}
const string& game::solution_greed_cut_DFS(const eight_puzzle& state){
    string init_action("");
    eight_puzzle* successor[4];
    string* successor_action[4];
    unsigned int distance[4];
    bool legal[4] = {false, false, false, false};
    stack<const eight_puzzle*> front_stack;
    stack<string*> action_seq;
    stack<int> depth;
    depth.push(0);
    front_stack.push(&state);
    action_seq.push(&init_action);
    int depth_cut = 1;
    const eight_puzzle* state_to_exploit = new eight_puzzle(*front_stack.top());
    const string* path = new string(*action_seq.top());
    int current_depth = depth.top();
    while(!is_goal(*state_to_exploit)){
        while(!is_goal(*state_to_exploit) ){
            front_stack.pop();
            action_seq.pop();
            depth.pop();
            string direct("aswd");
            if(current_depth < depth_cut){
                for(int i = 0; i < 4; i++){
                    if(is_legal(*state_to_exploit,direct[i])){
                        eight_puzzle * new_state = new eight_puzzle(*state_to_exploit);
                        string* action = new string();
                        action->assign(*path);
                        action->push_back(direct[i]);
                        move_one_step(*new_state,direct[i]);
                        successor[i] = new_state;
                        successor_action[i] = action;
                        legal[i] = true;
                        distance[i] = new_state->mahantann_distance();
                    }
                    else legal[i] = false;
                 }
                for(int i = 0;i < 4; i++ ){
                    unsigned int min_dis = 10000;
                    unsigned int index = 0;
                    for(int j = 0; j < 4; j++){
                        if(legal[j]){
                            if(min_dis > distance[j] ){
                                min_dis = distance[j];
                                index = j;
                            }
                        }
                    }
                    if(min_dis != 10000){
                        front_stack.push(successor[index]);
                        action_seq.push(successor_action[index]);
                        depth.push(current_depth + 1);
                        legal[index] = false;
                    }
                }
            }
            if(state_to_exploit != NULL && state_to_exploit != &state){
                delete state_to_exploit;
            }
            if(path != NULL && path != &init_action){
                delete path;
            }
            if(front_stack.empty()){
                break;
            }
            state_to_exploit = front_stack.top();
            path = action_seq.top();
            current_depth = depth.top();
        }
        if(!action_seq.empty()){
            return *path;
        }
        depth_cut++;
        cout << "depth_cut"<<depth_cut<<endl;
        front_stack.push(&state);
        action_seq.push(&init_action);
        depth.push(0);
        state_to_exploit = front_stack.top();
        path = action_seq.top();
        current_depth = depth.top();
    }
    
}
game::~game() {
}