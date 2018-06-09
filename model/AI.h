#ifndef TEEKO_AI_H
#define TEEKO_AI_H

#include "Player.h"
#include "Utils.h"

class AI : public Player {
private:
    // The AI's difficulty, 0=easy, 1=normal, 2=hard
    int difficulty_;
public:
    // AI's constructor
    AI(int difficulty);
    // The main algorithm determining a board's evaluation to a certain depth
    int minimax(vector<Space> board, int depth, bool is_maximizing, int alpha, int beta);
    // Evaluates the board and returns a score
    int evaluate(vector<Space> *board);
    int evaluate_Easy(vector<Space> *board,vector<int>red,vector<int>black);
    int evaluate_Medium(vector<Space> *board,vector<int>red,vector<int>black);
    int evaluate_Hard(vector<Space> *board,vector<int>red,vector<int>black);
    int evaluatePotential(vector<int> markers,int player);
    // Finds the best best move possible
    vector<int> FindBestMoveSpacesId(vector<Space> board);
    // Finds the best space to place a marker
    int FindBestPlacementSpaceId(vector<Space> board);
    int alignementMarker(vector<int> markers_id, int coef,int player);
    int distanceMarker(vector<int> space_id, int coef,int player);
};


#endif //TEEKO_AI_H
