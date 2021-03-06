#include "AI.h"

/**
*AI's constructor
 * @param difficulty of theAI*/
AI::AI(int difficulty, std::string color) : Player(color) {
    difficulty_ = difficulty;
}

/**
 * The minimax algorithm used to determine a move's quality
 * @param board
 * @param depth at which the algorithm is going to go
 * @param is_maximizing, true if called by the maximizer
 * @param alpha value, used for pruning
 * @param beta, used for pruning
 * @return
 */
int AI::Minimax(vector<Space> board, int depth, bool is_maximizing, int alpha, int beta) {
    // Counters for the number of marker for each player
    int black_count = 0;
    int red_count = 0;
    // Counts the number of marker on the board
    // Also retrieves the spaces' ID of both Black and Red players
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
    if (depth == 0 || (!black.empty() && MarkerAlignment(black, 1, -1) == -3) || (!red.empty() &&
            MarkerAlignment(red, 1, 1) == 3))
        return Evaluate(&board);

    // Maximizer
    if (is_maximizing) {
        // Best eval is -inf for now
        int best_eval = -INT32_MAX;
        // Maximizer already has 4 markers placed
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
                            best_eval = max(best_eval, Minimax(new_board, depth - 1, false, alpha,
                                                               beta)); // Let's go deeper
                            // Alpha-beta pruning
                            alpha = max(alpha, best_eval);
                            if (beta <= alpha) {
                                break;
                            }
                        }
                    }
                }
            }
        }
        // Maximizer doesn't have 4 markers placed
        else {
            // For each space on the board
            for (Space current_space : board) {
                // If there isn't any marker on the space
                if (current_space.GetMarker() == nullptr) {
                    // Creates a new board and place a marker on that space
                    vector<Space> new_board(board);
                    new_board.at(current_space.GetSpaceId() - 1).SetMarker(new Marker("Red", 0));
                    best_eval = max(best_eval, Minimax(new_board, depth - 1, false, alpha,
                                                       beta)); // Let's go deeper
                    // Alpha-beta pruning
                    alpha = max(alpha, best_eval);
                    if (beta <= alpha) {
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
        // Minimizer already has 4 markers placed
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
                                            Minimax(new_board, depth - 1, true, alpha, beta)); // Let's go deeper
                            // Alpha-beta pruning
                            beta = min(beta, best_eval);
                            if (beta <= alpha) {
                                break;
                            }
                        }
                    }
            }
        }
        // Minimizer doesn't have 4 placed markers
        else {
            // For each space on the board
            for (Space current_space : board) {
                // If there isn't any marker on the space
                if (current_space.GetMarker() == nullptr) {
                    // Creates a new board and place a marker on that space
                    vector<Space> new_board(board);
                    new_board.at(current_space.GetSpaceId() - 1).SetMarker(new Marker("Black", 0));
                    best_eval = min(best_eval, Minimax(new_board, depth - 1, true, alpha,
                                                       beta)); // Let's go deeper
                    // Alpha-beta pruning
                    beta = min(beta, best_eval);
                    if (beta <= alpha) {
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
int AI::Evaluate(vector<Space> *board) {
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
            score = EvaluateEasy(red, black);
            break;
        case 1:
            score = EvaluateNormal(red, black);
            break;
        case 2:
            score = EvaluateHard(red, black);
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
int AI::EvaluateEasy(vector<int> red, vector<int> black) {
    int score = 0;

    sort(red.begin(),red.begin()+red.size());
    sort(black.begin(),black.begin()+black.size());

    score+= MarkerAlignment(red, 25, 1)+ MarkerAlignment(black, 25, -1);
    score+= MarkerDistance(red, 1, 1)+ MarkerDistance(black, 1, -1);
    return score;
}

/**
 * This function returns an evaluation of the passed board, using a medium evaluation
 * Maximise Red player ( AI ), so minimize Black Player ( User )
 * @param board
 * @return
 */
int AI::EvaluateNormal(vector<int> red, vector<int> black) {
    int score=0;

    sort(red.begin(),red.begin()+red.size());
    sort(black.begin(),black.begin()+black.size());

    score+= MarkerAlignment(red, 20, 1)+ MarkerAlignment(black, 20, -1);
    score+=(0.5)* EvaluatePotential(red, 1)+(0.5)* EvaluatePotential(black, -1);

    return score;
}


/**
 * This function returns an evaluation of the passed board, it's the best evaluation
 * Maximise Red player ( AI ), so minimize Black Player ( User )
 * @param board
 * @return
 */
int AI::EvaluateHard(vector<int> red, vector<int> black) {

    int score=0;

    sort(red.begin(),red.begin()+red.size());
    sort(black.begin(),black.begin()+black.size());

    score+= MarkerAlignment(red, 15, 1)+ MarkerAlignment(black, 15, -1);
    score+= MarkerDistance(red, 1, 1)+ MarkerDistance(black, 1, -1);
    score+=(0.25)* EvaluatePotential(red, 1)+(0.25)* EvaluatePotential(black, -1);
    return score;

}

/**
 * This function returns an evaluation of the position of each marker on the board (for a color)
 * @param board
 * @return
 */
int AI::EvaluatePotential(vector<int> markers, int player){
    int score = 0;
    vector<int>coin = {1,5,21,25}; // les coins du board | 4 coups gagnants possibles
    vector<int>bMilieu = {3,11,15,23}; // les bords du board qui sont au milieu| 5 coups gagnants possibles
    vector<int>bCoin = {2,4,6,10,16,20,22,24}; // les milieux des bords du board | 6 coups gagnant possibles
    vector<int>milieuC = {7,9,17,19}; // les coins du carré intérieur | 10 coups gagnant possibles
    vector<int>milieuB = {8,12,14,18}; // les bords du carré intérieur | 10 coups gagnants possibles



    // On parcourt tout nos markers
    for (int i = 0; i < markers.size(); ++i) {
        int ourMarker = markers[i];
        if(find(coin.begin(),coin.end(),ourMarker)!=coin.end()){
            score+=0;
        }else if(find(bCoin.begin(),bCoin.end(),ourMarker)!=bCoin.end()){
            score+=2;
        }else if(find(bMilieu.begin(),bMilieu.end(),ourMarker)!=bMilieu.end()) {
            score += 1;
        }else if(find(milieuC.begin(),milieuC.end(),ourMarker)!=milieuC.end()) {
            score += 3;
        }else if(find(milieuB.begin(),milieuB.end(),ourMarker)!=milieuB.end()) {
            score += 3;
        }else{
            score+=4;
        }

    }
    
    return score*player;
}


int AI::MarkerDistance(vector<int> space_id, int coef, int player){
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
                score += (3 - Utils::GetDistance(ptA, ptB)) * player * coef;
            }
        }
    }
    return score;
}


/**
 * This function returns a score if an alignment is found else, it returns 0
 * @param markers_id Vector contains spaces where are markers of the player
 * @param coef, the number we want to multiply to the score
 * @param player If equal to 1 is the red player ( maximizer)
 *               Else -1 is the black player ( minimiser)
 * @return score the score of the solution
 */
int AI::MarkerAlignment(vector<int> markers_id, int coef, int player){

    int count_mark_square = 1, count_mark_diago_d = 1, count_mark_diago_u = 1, count_mark_colu = 1 , count_mark_line = 1;

    int score = 0;

    int space_id = markers_id.at(0);
    for(int i = 1; i < markers_id.size(); i++){
        if(markers_id.size() == 4 &&(space_id + 1) == markers_id.at(i) && (markers_id.at(0) + 5) == markers_id.at(2)){
            // Scare condition
            if(i == 2){ // If we are on the third space, we need to add one because the fourth is next to the third
                space_id++;
            } else { // Other solution, second space, for the next step we need to add four
                space_id+=4;
            }
            count_mark_square++;

        } else if((space_id + 1) == markers_id.at(i) && (space_id % 5 != 0 && space_id + 1 % 5 != 1)){
            // Line condition and check if there isn't one marker on the first column and the last
            space_id++;
            count_mark_line++;

        } else if((space_id + 5) == markers_id.at(i)){
            // Column condition
            space_id+=5;
            count_mark_colu++;

        } else if((space_id + 6) == markers_id.at(i) && (space_id % 5 != 0 && space_id +6 % 5 != 5 )){
            // Diagonal condition down and check if the diagonal is in single piece
            space_id+=6;
            count_mark_diago_d++;

        } else if ((space_id + 4) == markers_id.at(i) && (space_id % 5 != 1 && space_id +4 % 5 != 0 )){
            // Diagonal condition up and check if the diagonal is in single piece
            space_id+=4;
            count_mark_diago_u++;
        }
    }


    if (count_mark_square == 4 || count_mark_diago_d == 4 || count_mark_line == 4
        || count_mark_colu == 4 || count_mark_diago_u == 4)
        score += 3 * coef * player;

    return score;
}


/**
 * Find the best move to make
 * @param board
 * @return a vector of two int, the first being the space's ID where the marker is
 * and the second being the space's ID where the marker will be moved
 */
vector<int> AI::FindBestMoveSpacesId(vector<Space> board) {
    int best_eval;
    int move_eval;
    bool maximizing;
    // Red player is the maximizer, black player is the minimizer
    if(color_ == "Black") {
        best_eval = +INT32_MAX;
        maximizing = true;
    }
    else {
        best_eval = -INT32_MAX;
        maximizing = false;
    }

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

    // Vector containing the spaces' IDs involved in the move
    vector<int> best_move_spaces_id;
    for (Space current_space : board) {
        // Check whether there is a valid move and for each valid moves, make the move
        for (int move_space_id : current_space.GetValidMoves(&board)) {
            if (move_space_id != -1 && current_space.GetMarker() != nullptr &&
                current_space.GetMarker()->GetColor() == color_) {
                vector<Space> new_board(board);
                new_board.at(move_space_id - 1).SetMarker(current_space.GetMarker()); // Add the marker to the new space
                new_board.at(current_space.GetSpaceId() - 1).SetMarker(nullptr); // Remove the marker

                // Gets the move evaluation
                move_eval = Minimax(new_board, depth, maximizing, -INT32_MAX, +INT32_MAX);
                // If the move is better than the best move found so far, it becomes the best move
                if (move_eval > best_eval && color_ == "Red") {
                    best_move_spaces_id.clear();
                    best_move_spaces_id.push_back(current_space.GetSpaceId());
                    best_move_spaces_id.push_back(move_space_id);
                    best_eval = move_eval;
                }
                else if (move_eval < best_eval && color_ == "Black") {
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

/**
 * Find the best placement
 * @param board
 * @return a vector of two int, the first being the space's ID where the marker is
 * and the second being the space's ID where the marker will be moved
 */
int AI::FindBestPlacementSpaceId(vector<Space> board) {
    // Best evaluation so far
    int best_eval;
    // Evaluation of the tested move
    int move_eval;
    // The best placement space's ID
    int best_placement_space_id;
    //
    bool maximizing;

    // Red player is the maximizer, black player is the minimizer
    if(color_ == "Black") {
        best_eval = +INT32_MAX;
        maximizing = true;
    }
    else {
        best_eval = -INT32_MAX;
        maximizing = false;
    }

    // Check whether there is a valid move and for each valid moves, make the move
    for (Space space : board) {
        if (space.GetMarker() == nullptr) {
            vector<Space> new_board(board);
            // Adds the marker to the new space
            new_board.at(space.GetSpaceId() - 1).SetMarker(
                   new Marker(color_, 0));
            // Gets the evaluation of the placement
            move_eval = Minimax(new_board, 4, maximizing, -INT32_MAX, +INT32_MAX);
            // If it's better than the best placement so far, replaces it
            if (move_eval > best_eval && color_ == "Red") {
                best_placement_space_id = space.GetSpaceId();
                best_eval = move_eval;
            }
            else if (move_eval < best_eval && color_ == "Black") {
                best_placement_space_id = space.GetSpaceId();
                best_eval = move_eval;
            }
        }
    }
    return best_placement_space_id;
}
