#include "AI.h"

AI::AI(vector<Space>* board_spaces, int difficulty) : Player("Red") {
    board_spaces_ = board_spaces;
    difficulty_ = difficulty;
}

// TODO Finish this method then add alpha/beta pruning
int AI::minimax(vector<Space> board, int depth, bool is_maximizing, int node_index) {
    // If we are at the bottom of the tree, evaluate the board ; TODO Add condition : if there isn't any possible move
    if(depth == 0)
        return evaluate(&board);

    if(is_maximizing) {
        int best_eval = -INT32_MAX;
        for(Space* space : spaces_) {
            for(space->GetValidMoves(board_spaces_)) {
                // TODO Update the board with the move using whatever function from Game class
                best_eval = max(best_eval, minimax(/* TODO new board */, depth--, false, node_index++));
            }
        }
    } else {
        int best_eval = INT32_MAX;
        // TODO Follow the same steps as maximizer
    }
}

/**
 * TODO This function returns an evaluation of the passed board
 * https://en.wikipedia.org/wiki/Evaluation_function
 * @param board
 * @return
 */
int AI::evaluate(vector<Space> *board) {
    return 0;
}
