//We always have to include the library
#include "LedControl.h"

void step();
int getNeighborsWrap(int cell);
int getNeighborsBound(int cell);
void printCurrentBoard();
void newBoard();
bool boardIsStale();

/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn 
 pin 11 is connected to the CLK 
 pin 10 is connected to LOAD 
 We have only a single MAX72XX.
 */
LedControl lc=LedControl(12,11,10,1);
// Globals
bool a [64], b [64];
bool *board = a;
bool *temp = b;
bool wrap = true;
int generation = 1;

/* we always wait a bit between updates of the display */
unsigned long delaytime=200;

void setup() {
  Serial.begin(9600);
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,8);
  /* and clear the display */
  lc.clearDisplay(0);
  Serial.println("Start game");
  newBoard();
}

void step() {  
    for(int i=0; i<64; i++){
        int neighbors = 0;
        if(wrap) {
            neighbors = getNeighborsWrap(i);
        } else {
            neighbors = getNeighborsBound(i);
        }
        if(neighbors > 3) {
            temp[i] = 0;
        } else if(neighbors == 3) {
            temp[i] = 1;
        } else if(neighbors == 2) {
            temp[i] = board[i];
        } else if(neighbors <= 1) {
            temp[i] = 0;
        }
    }
    // Serial.println();
    bool *swap = board;
    board = temp;
    temp = swap;
}

int getNeighborsWrap(int cell) {
    if(cell > 7 && cell < 56 && cell%8 != 0 && (cell+1)%8 != 0){ // cell is somewhere in the middle
        return 
        board[cell-9] + board[cell-8] + board[cell-7] + 
        board[cell-1] +                 board[cell+1] + 
        board[cell+7] + board[cell+8] + board[cell+9];
    } else if( cell%8 == 0 && cell != 0 && cell != 56 ){ //cell is on the left edge, not on a corner
        return  
        board[cell-1] +  board[cell-8] + board[cell-7] + 
        board[cell+7] +                  board[cell+1] + 
        board[cell+15] + board[cell+8] + board[cell+9];
    } else if( cell > 0 && cell < 7 ){ //cell is on the top edge, not on a corner
        return 
        board[cell+55] + board[cell+56] + board[cell+57] +
        board[cell-1] +                   board[cell+1] +
        board[cell+7] +  board[cell+8] +  board[cell+9];
    } else if( (cell+1)%8 == 0 && cell != 7 && cell != 63 ){ //cell is on the right edge, not on a corner
        return
        board[cell-9] + board[cell-8] + board[cell-15] + 
        board[cell-1] +                 board[cell-7] + 
        board[cell+7] + board[cell+8] + board[cell+1];
    } else if( cell > 56 && cell < 63 ){ //cell is on the bottom edge, not on a corner
        return 
        board[cell-9] +  board[cell-8] +  board[cell-7] + 
        board[cell-1] +                   board[cell+1] + 
        board[cell-57] + board[cell-56] + board[cell-55];
    } else if ( cell == 0 ) { //  top-left 
        return 
        board[63] + board[56] + board[57] +
        board[7] +            + board[1] +
        board[15] + board[8] +  board[9];
    } else if ( cell == 7 ) { // top-right
        return
        board[62] + board[63] + board[56] +
        board[6] +            + board[0] +
        board[14] + board[15] +  board[8];
    } else if ( cell == 56 ) { // bottom-left
        return
        board[55] + board[48] + board[49] +
        board[63] +            + board[57] +
        board[7] + board[0] +  board[1];
    } else if ( cell == 63 ) { // bottom-right
        return
        board[54] + board[55] + board[48] +
        board[62] +            + board[56] +
        board[6] + board[7] +  board[0];
    } else { // other
        Serial.println("Something is very wrong. cell = " + cell);
    }
}

int getNeighborsBound(int cell) {
    if(cell > 7 && cell < 56 && cell%8 != 0 && (cell+1)%8 != 0){ // cell is somewhere in the middle
        return board[cell-8] + board[cell-7] + board[cell+1] + board[cell+9] + board[cell+8] + board[cell+7] + board[cell-1] + board[cell-9];
    } else if( cell%8 == 0 && cell != 0 && cell != 56 ){ //cell is on the left edge, not on a corner
        return  board[cell-8] + board[cell-7] + board[cell+1] + board[cell+9] + board[cell+8];
    } else if( cell > 0 && cell < 7 ){ //cell is on the top edge, not on a corner
        return board[cell+1] + board[cell+9] + board[cell+8] + board[cell+7] + board[cell-1];
    } else if( (cell+1)%8 == 0 && cell != 7 && cell != 63 ){ //cell is on the right edge, not on a corner
        return board[cell-8] + board[cell+8] + board[cell+7] + board[cell-1] + board[cell-9];
    } else if( cell > 56 && cell < 63 ){ //cell is on the bottom edge, not on a corner
        return board[cell-8] + board[cell-7] + board[cell+1] + board[cell-1] + board[cell-9];
    } else if ( cell == 0 ) { //  top-left 
        return board[1] + board[9] + board[8];
    } else if ( cell == 7 ) { // top-right
        return board[15] + board[14] + board[6];
    } else if ( cell == 56 ) { // bottom-left
        return board[48] + board[49] + board[57];
    } else if ( cell == 63 ) { // bottom-right
        return board[55] + board[62] + board[54];
    } else { // other
        Serial.println("Something is very wrong. cell = " + cell);
    }
}

void printCurrentBoard() {
    for(int y=0; y<8; y++){
        for(int x=0; x<8; x++){
            bool state = false;
            if(board[x+y*8] == 1){
                state = true;
            } else {
                state = false;
            }
            lc.setLed(0, y, x, state);
        }
    }
}

void newBoard() {
    const int seed = analogRead(0);
    Serial.print("New Seed: ");
    Serial.println(seed);
    randomSeed(seed);
    // Set each light to a 1 or 0
    for(int i=0; i<64; i++){
        board[i] = random(0,2);
    }
}

bool boardIsStale() {
    // TODO: This does not account for oscillators
    for(int i=0; i<64; i++){
        if (board[i] != temp[i]) {
            return false;
        }
    }
    return true;
}

void loop() {
    printCurrentBoard();
    delay(delaytime);
    step();
    if (boardIsStale()) {
        generation++;
        newBoard();
        Serial.println("Game #" + String(generation));
    }
}