#ifndef TEEKO_AI_H
#define TEEKO_AI_H

#include "Player.h"
#include "Utils.h"

class AI : public Player {
private:
    int difficulty_; // 0 = easy ; 1 = normal ; 2 = hard
    vector<Space>* board_spaces_; // Not sure it will be useful, TODO use that instead of passing the board in findBestMove
public:
    AI(vector<Space> *board_spaces, int difficulty, std::string color);
    int minimax(vector<Space> board, int depth, bool is_maximizing, int alpha, int beta);
    int evaluate(vector<Space> *board);
    int evaluate_Easy(vector<Space> *board,vector<int>red,vector<int>black);
    int evaluate_Medium(vector<Space> *board,vector<int>red,vector<int>black);
    int evaluate_Hard(vector<Space> *board,vector<int>red,vector<int>black);
    int evaluatePotential(vector<int> markers,int player);
    vector<int> FindBestMoveSpacesId(vector<Space> board);
    // Find the best space to place a marker
    int FindBestPlacementSpaceId(vector<Space> board);
    int alignementMarker(vector<int> markers_id, int coef,int player);
    int distanceMarker(vector<int> space_id, int coef,int player);
};


#endif //TEEKO_AI_H
