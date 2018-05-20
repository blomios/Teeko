#include "AI.h"

AI::AI(vector<Space>* board_spaces, int difficulty) : Player("Red") {
    board_spaces_ = board_spaces;
    difficulty_ = difficulty;
}

int AI::minimax(vector<int> evaluated_board, int depth, bool is_maximizing, int node_index) {
    if(depth == 0)
        return evaluated_board[node_index];

    if(is_maximizing) {
        int best_eval = -INT32_MAX;
        for(Space* space : spaces_) {
            for(space->GetValidMoves(board_spaces_)) {
            }
        }
    } else {
        int best_eval = INT32_MAX;
    }
}
