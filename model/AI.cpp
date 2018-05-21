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

    int count_mark_square = 1, count_mark_diago_d = 1, count_mark_diago_u = 1, count_mark_colu = 1 , count_mark_line = 1;

    /* Constant */
    // 1 marker alone, 2 marker, 3 marker and 1 far away, 3 marker and 1 close
    vector <int> coefRed { 1 , 4 , 10};
    int redScore=0, blackScore=0;

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

    //Check first red markers
    int space_id = red.at(0);
    for(int i = 1; i < 4; i++){
        if((space_id + 1) == red.at(i) && (red.at(0) + 5) == red.at(2)){
            /* Square */
            if(i == 2){
                space_id++;
            } else {
                space_id+=4;
            }
            count_mark_square++;
        } else if((space_id + 1) == red.at(i)){
            /* Line */
            space_id++;
            count_mark_line++;
        } else if((space_id + 5) == red.at(i)){
            /* Column */
            space_id+=5;
            count_mark_colu++;
        } else if((space_id + 6) == red.at(i)){
            /* Diagonal */
            space_id+=6;
            count_mark_diago_d++;
        } else if ((space_id + 4) == red.at(i)){
            /* Diagonal */
            space_id+=4;
            count_mark_diago_u++;
        }
    }

    count_mark_square == 3 || count_mark_diago_d == 3 || count_mark_line == 3
    || count_mark_colu == 3 ||  count_mark_diago_u == 3 ? redScore += 3*coefRed.at(2) : redScore += 0;

    count_mark_square == 2 ? redScore = 2*coefRed.at(1) : redScore += 0;
    count_mark_diago_d == 2 ? redScore = 2*coefRed.at(1) : redScore += 0;
    count_mark_line == 2 ? redScore = 2*coefRed.at(1) : redScore += 0;
    count_mark_colu == 2 ? redScore = 2*coefRed.at(1) : redScore += 0;
    count_mark_diago_u == 2 ? redScore = 2*coefRed.at(1) : redScore += 0;


    count_mark_square == 1 ? redScore = coefRed.at(0) : redScore += 0;
    count_mark_diago_d == 1 ? redScore = coefRed.at(0) : redScore += 0;
    count_mark_line == 1 ? redScore = coefRed.at(0) : redScore += 0;
    count_mark_colu == 1 ? redScore = coefRed.at(0) : redScore += 0;
    count_mark_diago_u == 1 ? redScore = coefRed.at(0) : redScore += 0;


    count_mark_square = 1, count_mark_diago_d = 1, count_mark_diago_u = 1, count_mark_colu = 1 , count_mark_line = 1;


    space_id = black.at(0);
    for(int i = 1; i < 4; i++){
        if((space_id + 1) == black.at(i) && (black.at(0) + 5) == black.at(2)){
            /* Square */
            if(i == 2){
                space_id++;
            } else {
                space_id+=4;
            }
            count_mark_square++;
        } else if((space_id + 1) == black.at(i)){
            /* Line */
            space_id++;
            count_mark_line++;
        } else if((space_id + 5) == black.at(i)){
            /* Column */
            space_id+=5;
            count_mark_colu++;
        } else if((space_id + 6) == black.at(i)){
            /* Diagonal */
            space_id+=6;
            count_mark_diago_d++;
        } else if ((space_id + 4) == black.at(i)){
            /* Diagonal */
            space_id+=4;
            count_mark_diago_u++;
        }
    }

    count_mark_square == 3 || count_mark_diago_d == 3 || count_mark_line == 3
    || count_mark_colu == 3 ||  count_mark_diago_u == 3 ? blackScore += -3*coefRed.at(2) : blackScore += 0;

    count_mark_square == 2 ? blackScore += -2*coefRed.at(1) : blackScore += 0;
    count_mark_diago_d == 2 ? blackScore += -2*coefRed.at(1) : blackScore += 0;
    count_mark_line == 2 ? blackScore += -2*coefRed.at(1) : blackScore += 0;
    count_mark_colu == 2 ? blackScore += -2*coefRed.at(1) : blackScore += 0;
    count_mark_diago_u == 2 ? blackScore += -2*coefRed.at(1) : blackScore += 0;


    count_mark_square == 1 ?  blackScore += -coefRed.at(0) : blackScore += 0;
    count_mark_diago_d == 1 ?  blackScore += -coefRed.at(0) : blackScore += 0;
    count_mark_line == 1 ?  blackScore += -coefRed.at(0) : blackScore += 0;
    count_mark_colu == 1 ?  blackScore += -coefRed.at(0) : blackScore += 0;
    count_mark_diago_u == 1 ?  blackScore += -coefRed.at(0) : blackScore += 0;



    return redScore - blackScore;
}
