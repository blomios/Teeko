#ifndef TEEKO_AI_H
#define TEEKO_AI_H

#include "../Core/Player.h"
#include "../Utils/Utils.h"

class AI : public Player {
private:
    // The AI's difficulty, 0=easy, 1=normal, 2=hard
    int difficulty_;
public:
    // AI's constructor
    AI(int difficulty, std::string color);
    // The main algorithm determining a board's evaluation to a certain depth
    int Minimax(vector<Space> board, int depth, bool is_maximizing, int alpha, int beta);
    // Evaluates the board and returns a score
    int Evaluate(vector<Space> *board);
    int EvaluateEasy(vector<int> red, vector<int> black);
    int EvaluateNormal(vector<int> red, vector<int> black);
    int EvaluateHard(vector<int> red, vector<int> black);
    int EvaluatePotential(vector<int> markers, int player);
    // Finds the best best move possible
    vector<int> FindBestMoveSpacesId(vector<Space> board);
    // Finds the best space to place a marker
    int FindBestPlacementSpaceId(vector<Space> board);
    int MarkerAlignment(vector<int> markers_id, int coef, int player);
    int MarkerDistance(vector<int> space_id, int coef, int player);
};


#endif //TEEKO_AI_H
