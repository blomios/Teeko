#include "Board.h"

Board::Board() {
    for(int &space : spaces_) {
        space = 0;
    }
}
