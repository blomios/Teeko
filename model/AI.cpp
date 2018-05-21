#include "AI.h"

AI::AI(vector<Space>* board_spaces, int difficulty) : Player("Red") {
    board_spaces_ = board_spaces;
    difficulty_ = difficulty;
}

// TODO Finish this method then add alpha/beta pruning
int AI::minimax(vector<Space> board, int depth, bool is_maximizing) {
    // If we are at the bottom of the tree, evaluate the board ; TODO Add condition : if there isn't any possible move
    if(depth == 0)
        return evaluate(&board);

    if(is_maximizing) {
        // Best eval is -inf for now
        int best_eval = -INT32_MAX;
        // For each space on the board
        for(Space current_space : board) {
            // Check whether there is a valid move and for each valid moves, make the move
            for(int move_space_id : current_space.GetValidMoves(&board)) {
                if(move_space_id!=-1 && current_space.GetMarker() != nullptr && current_space.GetMarker()->GetColor() == "Red") {
                    board.at(move_space_id - 1).SetMarker(current_space.GetMarker()); // Add the marker to the new space
                    board.at(current_space.GetSpaceId() - 1).SetMarker(nullptr); // Remove the marker
                    best_eval = max(best_eval, minimax(board, depth--, false)); // Let's go deeper
                }
            }
        }
    } else {
        // Best eval is +inf for now
        int best_eval = INT32_MAX;
        // For each space on the board
        for(Space current_space : board) {
            // Check whether there is a valid move and for each valid moves, make the move
            for(int move_space_id : current_space.GetValidMoves(&board)) {
                if(move_space_id!=-1 && current_space.GetMarker() != nullptr && current_space.GetMarker()->GetColor() == "Black") {
                    board.at(move_space_id - 1).SetMarker(current_space.GetMarker()); // Add the marker to the new space
                    board.at(current_space.GetSpaceId() - 1).SetMarker(nullptr); // Remove the marker
                    best_eval = min(best_eval, minimax(board, depth--, true)); // Let's go deeper
                }
            }
        }
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
