#include "AI.h"


AI::AI(vector<Space>* board_spaces, int difficulty) : Player("Red") {
    board_spaces_ = board_spaces;
    difficulty_ = difficulty;
}

int AI::minimax(vector<Space> board, int depth, bool is_maximizing, int alpha, int beta) {
    // Counters the number of marker for each player
    int black_count = 0;
    int red_count = 0;
    // Retrieves the spaces' ID of both Black and Red players
    // They will be used to determine if a player has aligned 4 markers and has won
    vector<int> red, black;
    for (Space space : board) {
        if (space.GetMarker() != nullptr && space.GetMarker()->GetColor() == "Red") {
            red.push_back(space.GetSpaceId());
            red_count++;
        } else if (space.GetMarker() != nullptr && space.GetMarker()->GetColor() == "Black") {
            black.push_back(space.GetSpaceId());
            black_count++;
        }
    }

    // If we are at a leaf of the tree (2 cases : win or depth reached)
    if (depth == 0 || alignementMarker(black, 1, -1) == -3 || alignementMarker(red, 1, 1) == 3)
        return evaluate(&board);

    if (is_maximizing) {
        // Best eval is -inf for now
        int best_eval = -INT32_MAX;
        // Minimizer already has 4 markers placed
        if (red_count == 4) {
            // For each space on the board
            for (Space current_space : board) {
                // Checks whether there is a valid move and for each valid moves, makes that move
                if (current_space.GetMarker() != nullptr && current_space.GetMarker()->GetColor() == "Red") {
                    for (int move_space_id : current_space.GetValidMoves(&board)) {
                        if (move_space_id != -1) {
                            // Creates a new board and moves the marker
                            vector<Space> new_board(board);
                            new_board.at(move_space_id - 1).SetMarker(
                                    current_space.GetMarker()); // Adds the marker to the new board
                            new_board.at(current_space.GetSpaceId() - 1).SetMarker(
                                    nullptr); // Removes the marker from the board
                            best_eval = max(best_eval, minimax(new_board, depth - 1, false, alpha,
                                                               beta)); // Let's go deeper
                            alpha = max(alpha, best_eval);
                            if (beta <= alpha) {
                                //cout << "Pruning..." << endl;
                                break;
                            }
                        }
                    }
                }
            }
        }
            // Minimizer doesn't have 4 markers placed
        else {
            // For each space on the board
            for (Space current_space : board) {
                // If there isn't any marker on the space
                if (current_space.GetMarker() == nullptr) {
                    // Creates a new board and place a marker on that space
                    vector<Space> new_board(board);
                    new_board.at(current_space.GetSpaceId() - 1).SetMarker(new Marker("Red", 0));
                    best_eval = max(best_eval, minimax(new_board, depth - 1, false, alpha,
                                                       beta)); // Let's go deeper
                    alpha = max(alpha, best_eval);
                    if (beta <= alpha) {
                        //cout << "Pruning..." << endl;
                        break;
                    }
                }
            }
        }
        return best_eval;
    }

    // Minimizer
    else {
        // Best eval is +inf for now
        int best_eval = INT32_MAX;
        // Maximizer already has 4 markers placed
        if (black_count == 4) {
            // For each space on the board
            for (Space current_space : board) {
                // Checks whether there is a valid move and for each valid moves, makes that move
                if (current_space.GetMarker() != nullptr && current_space.GetMarker()->GetColor() == "Black")
                    for (int move_space_id : current_space.GetValidMoves(&board)) {
                        if (move_space_id != -1) {
                            // Creates a new board and moves the marker
                            vector<Space> new_board(board);
                            new_board.at(move_space_id - 1).SetMarker(
                                    current_space.GetMarker()); // Adds the marker to the new space
                            new_board.at(current_space.GetSpaceId() - 1).SetMarker(nullptr); // Removes the marker
                            best_eval = min(best_eval,
                                            minimax(new_board, depth - 1, true, alpha, beta)); // Let's go deeper
                            beta = min(beta, best_eval);
                            if (beta <= alpha) {
                                //cout << "Pruning..." << endl;
                                break;
                            }
                        }
                    }
            }
        }
            // Maximizer doesn't have 4 placed markers
        else {
            // For each space on the board
            for (Space current_space : board) {
                // If there isn't any marker on the space
                if (current_space.GetMarker() == nullptr) {
                    // Creates a new board and place a marker on that space
                    vector<Space> new_board(board);
                    new_board.at(current_space.GetSpaceId() - 1).SetMarker(new Marker("Black", 0));
                    best_eval = min(best_eval, minimax(new_board, depth - 1, true, alpha,
                                                       beta)); // Let's go deeper
                    beta = min(beta, best_eval);
                    if (beta <= alpha) {
                        //cout << "Pruning..." << endl;
                        break;
                    }
                }
            }
        }
        return best_eval;
    }
}

/**
 * This function returns an evaluation of the passed board depending on the difficulty chosen by the user
 * Maximise Red player ( AI ), so minimize Black Player ( User )
 * @param board
 * @return
 */
int AI::evaluate(vector<Space> *board) {
    int score = 0;

    //Red player : AI      Black player User (1/-1)
    vector <int> red,black;

    // We put this code here to avoid redundancy
    for(int i = 0; i < 25; i ++){
        if(board->at(i).GetMarker() != nullptr && board->at(i).GetMarker()->GetColor() == "Red"){
            red.push_back(board->at(i).GetSpaceId());
        } else if(board->at(i).GetMarker() != nullptr && board->at(i).GetMarker()->GetColor() == "Black"){
            black.push_back(board->at(i).GetSpaceId());
        }
    }

    switch (this->difficulty_){
        case 0:
            score =evaluate_Easy(board,red,black);
            break;
        case 1:
            score =evaluate_Medium(board,red,black);
            break;
        case 2:
            score = evaluate_Hard(board,red,black);
            break;
    }

    return score;
}


/**
 * This function returns an evaluation of the passed board, it's the "worse" evaluation
 * Maximise Red player ( AI ), so minimize Black Player ( User )
 * @param board
 * @return
 */
int AI::evaluate_Easy(vector<Space> *board,vector<int>red,vector<int>black) {
    int score = 0;

    score+=alignementMarker(red,30,1)+ alignementMarker(black,30,-1);
    score+=distanceMarker(red,1,1)+ distanceMarker(black,1,-1);
    return score;
}

/**
 * This function returns an evaluation of the passed board, using a medium evaluation
 * Maximise Red player ( AI ), so minimize Black Player ( User )
 * @param board
 * @return
 */
int AI::evaluate_Medium(vector<Space> *board,vector<int>red,vector<int>black) {
    int score=0;
    score+=alignementMarker(red,20,1)+ alignementMarker(black,20,-1);
    score+=evaluatePotential(red,1)+evaluatePotential(black,-1);

    return score;
}


/**
 * This function returns an evaluation of the passed board, it's the best evaluation
 * Maximise Red player ( AI ), so minimize Black Player ( User )
 * @param board
 * @return
 */
int AI::evaluate_Hard(vector<Space> *board,vector<int>red,vector<int>black) {
    /* Constant */
    // 1 marker alone, 2 markers, 3 markers and 1 far away, 3 markers and 1 close
    vector <int> coef { 1 , 4 , 10};
    int score=0;

    sort(red.begin(),red.begin()+red.size());
    sort(black.begin(),black.begin()+black.size());

    score+=alignementMarker(red,20,1)+ alignementMarker(black,20,-1);
    score+=distanceMarker(red,1,1)+ distanceMarker(black,1,-1);
    score+=evaluatePotential(red,1)+evaluatePotential(black,-1);
    return score;

}

/**
 * This function returns an evaluation of the position of each
 * @param board
 * @return
 */
int AI::evaluatePotential(vector<int> markers,int player){
    int score = 0;
    vector<int>coin = {1,5,21,25}; // les coins du board | 4 coups gagnants possibles
    vector<int>bCoin = {3,11,15,23}; // les bords du board qui sont vers les coins | 5 coups gagnants possibles
    vector<int>bMilieu = {2,4,6,10,16,20,22,24}; // les milieux des bords du board | 6 coups gagnant possibles
    vector<int>milieuC = {7,9,17,19}; // les coins du carré intérieur | 10 coups gagnant possibles
    vector<int>milieuB = {8,12,14,18}; // les bords du carré intérieur | 10 coups gagnants possibles



    // On parcourt tout nos markers
    for (int i = 0; i < markers.size(); ++i) {
        int ourMarker = markers[i];
        if(find(coin.begin(),coin.end(),ourMarker)!=coin.end()){
            score+=1;
        }else if(find(bCoin.begin(),bCoin.end(),ourMarker)!=bCoin.end()){
            score+=3;
        }else if(find(bMilieu.begin(),bMilieu.end(),ourMarker)!=bMilieu.end()) {
            score += 2;
        }else if(find(milieuC.begin(),milieuC.end(),ourMarker)!=milieuC.end()) {
            score += 4;
        }else if(find(milieuB.begin(),milieuB.end(),ourMarker)!=milieuB.end()) {
            score += 4;
        }else{
            score+=5;
        }

    }
    
    return score*player;
}


int AI::distanceMarker(vector<int> space_id, int coef,int player){
    int score=0;

    // Explore the board
    for(int i=0; i<space_id.size(); i++){
        // Get the actual point we're looking at
        int ptA=space_id.at(i);
        // Explore the board once again
        for(int j=0; j<space_id.size(); j++){
            // If we're not looking at our current point
            if(j>i){
                // Get the other point we are looking at
                int ptB=space_id.at(j);
                // Increments the score through our first point's distance to the other point we're looking at
                        // time the player (1/-1) and the coefficient
                score += (3 - Utils::getDistance(ptA,ptB)) * player * coef;
            }
        }
    }
    return score;
}

int AI::alignementMarker(vector<int> markers_id, int coef,int player){

    int count_mark_square = 1, count_mark_diago_d = 1, count_mark_diago_u = 1, count_mark_colu = 1 , count_mark_line = 1;

    int score = 0;

    int space_id = markers_id.at(0);
    for(int i = 1; i < markers_id.size(); i++){
        if(markers_id.size() == 4 &&(space_id + 1) == markers_id.at(i) && (markers_id.at(0) + 5) == markers_id.at(2)){
            /* Square */
            if(i == 2){
                space_id++;
            } else {
                space_id+=4;
            }
            count_mark_square++;
        } else if((space_id + 1) == markers_id.at(i) && (space_id % 5 != 0 && space_id + 1 % 5 != 1)){
            /* Line */
            space_id++;
            count_mark_line++;
        } else if((space_id + 5) == markers_id.at(i)){
            /* Column */
            space_id+=5;
            count_mark_colu++;
        } else if((space_id + 6) == markers_id.at(i) && (space_id % 5 != 0 && space_id +6 % 5 != 5 )){
            /* Diagonal */
            space_id+=6;
            count_mark_diago_d++;
        } else if ((space_id + 4) == markers_id.at(i) && (space_id % 5 != 1 && space_id +4 % 5 != 0 )){
            /* Diagonal */
            space_id+=4;
            count_mark_diago_u++;
        }
    }


    count_mark_square == 4 || count_mark_diago_d == 4 || count_mark_line == 4
    || count_mark_colu == 4 ||  count_mark_diago_u == 4 ? score +=  3*coef * player: score += 0;

    return score;
}

vector<int> AI::FindBestMoveSpacesId(vector<Space> board) {
    int best_eval = -INT32_MAX;

    int depth=0;

    switch (difficulty_){
        case 0:
            depth = 2;
            break;
        case 1:
            depth = 3;
            break;
        case 2:
            depth = 4;
            break;
        default:
            depth = 4;
            break;
    }

    vector<int> best_move_spaces_id;
    for (Space current_space : board) {
        // Check whether there is a valid move and for each valid moves, make the move
        for (int move_space_id : current_space.GetValidMoves(&board)) {
            if (move_space_id != -1 && current_space.GetMarker() != nullptr &&
                current_space.GetMarker()->GetColor() == "Red") {
                vector<Space> new_board(board);
                new_board.at(move_space_id - 1).SetMarker(current_space.GetMarker()); // Add the marker to the new space
                new_board.at(current_space.GetSpaceId() - 1).SetMarker(nullptr); // Remove the marker

                int move_eval = minimax(new_board, depth, false, -INT32_MAX, INT32_MAX);
                if (move_eval > best_eval) {
                    best_move_spaces_id.clear();
                    best_move_spaces_id.push_back(current_space.GetSpaceId());
                    best_move_spaces_id.push_back(move_space_id);
                    best_eval = move_eval;
                }
            }
        }
    }
    return best_move_spaces_id;
}

int AI::FindBestPlacementSpaceId(vector<Space> board) {
    int best_eval = -INT32_MAX;
    int move_eval;
    int best_placement_space_id;
    // Check whether there is a valid move and for each valid moves, make the move
    for (Space space : board) {
        if (space.GetMarker() == nullptr) {
            vector<Space> new_board(board);
            new_board.at(space.GetSpaceId() - 1).SetMarker(
                   new Marker("Red", 0)); // Add the marker to the new space
            move_eval = minimax(new_board, 4, false, -INT32_MAX, INT32_MAX);
            if (move_eval > best_eval) {
                best_placement_space_id = space.GetSpaceId();
                best_eval = move_eval;
            }
        }
    }
    return best_placement_space_id;
}
