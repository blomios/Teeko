#ifndef TEEKO_AI_H
#define TEEKO_AI_H


#include "Player.h"

class AI : public Player {
private:
    int difficulty_; // 0 = easy ; 1 = normal ; 2 = hard
    vector<Space>* board_spaces_;
public:
    AI(vector<Space>* board_spaces, int difficulty);
    int minimax(vector<int> evaluated_board, int depth, bool is_maximizing, int node_index);
};


#endif //TEEKO_AI_H
