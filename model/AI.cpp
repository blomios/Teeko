#include "AI.h"

AI::AI() : Player("Red") {}

int AI::minimax(vector<int> evaluated_board, int depth, bool is_maximizing, int node_index) {
    if(depth == 0)
        return evaluated_board[node_index];

    if(is_maximizing) {
        int best_eval = -INT32_MAX;
        for(Space* space : spaces_) {
            /*for(each possible moves) {
                
            }*/
        }
    } else {
        int best_eval = INT32_MAX;
    }
}
