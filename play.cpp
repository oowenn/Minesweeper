#include <iostream>
#include <vector>
#include <stdlib.h>
#include <deque>
#include <string>

using namespace std;

class tile
{
    public:
        // (x, y)
        pair<int, int> coords;
        // 0-8 means bomb around it, mine =💣
        int val;
        char visible;
        vector<pair<int, int>> surroundingCoords;
        tile(pair<int, int> p, int value, vector<pair<int, int>> SC){
            visible = '+';
            coords = p;
            val = value;
            surroundingCoords = SC;
        }
        
    bool isMine(){
        if(val >= 0){
            return false;
        }
        return true;
    }
    //Make a method that will update a vector<pair<int, int>> (x, y) coordinates that surround the tile and are in bounds
    
    void setCoords(pair<int, int> p) {
        coords = p;
    }
    void setVal(int v) {
        val = v;
    }
    void setSurroundingCoords(vector<pair<int, int>> sc) {
        surroundingCoords = sc;
    }
    void setVisible(int v){
        if(v = -1) {
            visible = '*';
        }
        else {
            visible = '0' + v;
        }
    }
    pair<int, int> getCoords() {
        return coords;
    }
    int getVal() {
        return val;
    }
    vector<pair<int, int>> getSurroundingCoords() {
        return surroundingCoords;
    }

    bool inRange(pair<int,int> p, int h, int w){
        if (p.first < 0 || p.first >= w || p.second < 0 || p.second >= h) {
            return false;
        }
        
        return true;
    }
    vector<pair<int, int>> findSurroundingTiles(int h, int w) {
        vector<pair<int, int>> out;
        int x = coords.first;
        int y = coords.second;
        int cou = 0;
        for(int i = -1; i <= 1; i++){
            for(int j = -1; j <= 1; j++){
                if(i == 0 && j == 0){
                    continue;
                }
                pair<int, int> p = {x + i, y + j};
                if (inRange(p, h, w)) {
                    
                    out.push_back(p);
                }
            }
        }
        return out;

    }
    
    
};


/*
h = height, w = width, m = mines
Use a 1-D vector of all the indices and then randomly pop elements from the vector to put a mine in the corresponding location in the seed. 
*/
vector<vector<int>> makeGame(int h, int w, int m, pair<int, int> p) {
    
    //These are my coords!!!!!!!! X represents the x coord and y respresnts the y coord
    int x = p.first;
    int y = p.second;
    // 2-D int vector to be outputted initialized with height h, width w; all 0s
    vector<vector<int>> game(h, vector<int>(w, 0));
    int size = h * w;

    // 1-D int vector to be [0, 1, 2, 3, ...]
    vector<int> indices(size, 0);
    for (int i = 0; i < size; i++) {
        indices[i] = i;
    }
    // remove surrounding tiles around the initial position
    for (int k = 0; k < 9; k++) {
        int i = x - 1 + (k / 3);
        int j = y - 1 + (k % 3);
        if ((i >= 0 && i < h) && (j >= 0 && j < w)) {
            indices.erase(indices.begin() + i*h + j - k);
        }
    }
    while (m > 0) {
        // choose a random index from the remaining indices
        srand(time(0));
        int ran = rand()%indices.size();
        int r = indices[ran];

        // remove the index from the vector and then find the corresponding coordinates from the 1-D vector to 2-D vector using height and width;
        indices.erase(indices.begin() + ran);
        int i = r / w; // height
        int j = r % w; // width
        game[i][j] = -1;
        // in the game board: add 1 to surrounding tiles of the mine that are within bounds and not mines
        if ((i - 1 >= 0) && (j - 1 >= 0) && (game[i-1][j-1] > -1)) {
            game[i-1][j-1]++;
        }
        if ((i - 1 >= 0) && (game[i-1][j] > -1)) {
            game[i-1][j]++;
        }
        if ((i - 1 >= 0) && (j + 1 < w) && (game[i-1][j+1] > -1)) {
            game[i-1][j+1]++;
        }
        if ((j - 1 >= 0) && (game[i][j-1] > -1)) {
            game[i][j-1]++;
        }
        if ((j + 1 < w) && (game[i][j+1] > -1)) {
            game[i][j+1]++;
        }
        if ((i + 1 < h) && (j - 1 >= 0) && (game[i+1][j-1] > -1)) {
            game[i+1][j-1]++;
        }
        if ((i + 1 < h) && (game[i+1][j] > -1)) {
            game[i+1][j]++;
        }
        if ((i + 1 < h) && (j + 1 < w) && (game[i+1][j+1] > -1)) {
            game[i+1][j+1]++;
        }
        m--;
    }
    return game;
}

/*
Print the 2-D vector game
*/
void printGame(vector<vector<int>> seed, int h, int w) {
    for(int i = 0; i < h; i++){
        for(int j = 0; j < w; j++){
            cout << seed[i][j] << '\t';
        }
        cout << endl;
    }   
    return;
}

void clickTile(vector<vector<int>> seed, vector<vector<char>> &board, pair<int, int> p) {
    deque<pair<int, int>> q;
    q.push_back(p);
    while (q.size() > 0) {
        pair<int, int> tile = q.back();
        int y = tile.first;
        int x = tile.second;
        q.pop_back();
        

    }
    
}

//Wait, JAVA
void playGame(vector<vector<int>> seed, vector<vector<char>> board, int h, int w, pair<int, int> p) {
}


int main() {
    // h * w >= 9 + m
    int h = 10;
    int w = 10;
    int m = 10;
    // starting coordinates (x, y)
    pair<int, int> p = {5, 5};
    vector<vector<int>> seed = makeGame(h, w, m, p);
    vector<vector<char>> board(h, vector<char>(w, '+'));
    printGame(seed, h, w);
    
    return 0;
}