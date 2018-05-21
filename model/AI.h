#ifndef TEEKO_AI_H
#define TEEKO_AI_H


#include "Player.h"

class AI : public Player {
private:
    int difficulty_; // 0 = easy ; 1 = normal ; 2 = hard
    vector<Space>* board_spaces_; // Not sure it will be useful, TODO remove if unused
public:
    AI(vector<Space>* board_spaces, int difficulty);
    int minimax(vector<Space> board, int depth, bool is_maximizing);
    int evaluate(vector<Space> *board);
    int FindBestMoveSpaceId(vector<Space> board);
};


#endif //TEEKO_AI_H
