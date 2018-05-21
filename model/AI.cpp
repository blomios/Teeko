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
 * Maximise Red player ( AI ), so minimize Black Player ( User )
 * @param board
 * @return
 */
int AI::evaluate(vector<Space> *board) {
    /* Constant */
    // 1 marker alone, 2 marker, 3 marker and 1 far away, 3 marker and 1 close
    vector <int> coef { 1 , 4 , 10};

    //Red player : AI      Black player User
    vector <int> red(4),black(4);

    for(int i = 0; i < 25; i ++){
        if( board->at(i).GetMarker()->GetColor() == "Red"){
            red.push_back(board->at(i).GetSpaceId());
        } else {
            black.push_back(board->at(i).GetSpaceId());
        }
    }

    sort(red.begin(),red.begin()+4);
    sort(black.begin(),black.begin()+4);

    return alignementMarker(red,coef,1) + alignementMarker(black,coef,-1);
}

int AI::alignementMarker(vector<int> markers_id, vector<int> coef,int player){

    int count_mark_square = 1, count_mark_diago_d = 1, count_mark_diago_u = 1, count_mark_colu = 1 , count_mark_line = 1;

    int score = 0;

    int space_id = markers_id.at(0);
    for(int i = 1; i < 4; i++){
        if((space_id + 1) == markers_id.at(i) && (markers_id.at(0) + 5) == markers_id.at(2)){
            /* Square */
            if(i == 2){
                space_id++;
            } else {
                space_id+=4;
            }
            count_mark_square++;
        } else if((space_id + 1) == markers_id.at(i)){
            /* Line */
            space_id++;
            count_mark_line++;
        } else if((space_id + 5) == markers_id.at(i)){
            /* Column */
            space_id+=5;
            count_mark_colu++;
        } else if((space_id + 6) == markers_id.at(i)){
            /* Diagonal */
            space_id+=6;
            count_mark_diago_d++;
        } else if ((space_id + 4) == markers_id.at(i)){
            /* Diagonal */
            space_id+=4;
            count_mark_diago_u++;
        }
    }

    count_mark_square == 3 || count_mark_diago_d == 3 || count_mark_line == 3
    || count_mark_colu == 3 ||  count_mark_diago_u == 3 ? score += 3*coef.at(2) * player : score += 0;

    count_mark_square == 2 ? score += 2*coef.at(1) * player : score += 0;
    count_mark_diago_d == 2 ? score += 2*coef.at(1) * player : score += 0;
    count_mark_line == 2 ? score += 2*coef.at(1) * player : score += 0;
    count_mark_colu == 2 ? score += 2*coef.at(1) * player : score += 0;
    count_mark_diago_u == 2 ? score += 2*coef.at(1) * player : score += 0;


    count_mark_square == 1 ? score += coef.at(0) * player : score += 0;
    count_mark_diago_d == 1 ? score += coef.at(0) * player : score += 0;
    count_mark_line == 1 ? score += coef.at(0) * player : score += 0;
    count_mark_colu == 1 ? score += coef.at(0) * player : score += 0;
    count_mark_diago_u == 1 ? score += coef.at(0) * player : score += 0;

    return score;
}
