from typing import List
from zad1 import RandomPlayer, Board
from math import sqrt, log

class MCTSPlayer:
    #we represent state as two sets of player's positions
    __rememberedValues = dict() #{ (whitePlayerPos, blackPlayerPos) : (whiteWon, blackWon) }
    __totRemValuesCount = 0

    def __init__(self, color, board) -> None:
        self.color = color
        self.board = board

    def __calculate( winratio, timesChosen, C = sqrt(2) ):
        return winratio + ( C * sqrt( log(MCTSPlayer.__totRemValuesCount) / timesChosen ) )

    def simulation( self, cBrd : Board, moveHistory : List ):
        if cBrd.whiteTurn:
            f = RandomPlayer(True, cBrd) 
            s = RandomPlayer(False, cBrd)
        else:
            f = RandomPlayer(False, cBrd)
            s = RandomPlayer(True, cBrd)

        fContinues, SContinues = True, True
        while(fContinues or SContinues):
            fRes = f.move()
            if( fRes == False ):
                fContinues = False
            else:
                moveHistory.append( (frozenset(cBrd.getPositions(True)), frozenset(cBrd.getPositions(False))) )

            sRes = s.move()
            if( sRes == False ):
                SContinues = False
            else:
                moveHistory.append( (frozenset(cBrd.getPositions(True)), frozenset(cBrd.getPositions(False))) )

        (b, w) = cBrd.calculate()

        (wWon, bWon) = (1, 0) if w > b else ( (0, 1) if b > w  else (0, 0) )
        while( len(moveHistory) > 0 ):
            move = moveHistory.pop()
            if move not in MCTSPlayer.__rememberedValues:
                MCTSPlayer.__rememberedValues[move] = (wWon, bWon)
            else:
                (wW, bW) = MCTSPlayer.__rememberedValues[move]
                MCTSPlayer.__rememberedValues[move] = (wW + wWon, bW + bWon)

    def move(self):
        best = (-1000000, 0, 0)
        for (rP, cP) in self.board.getAllPossibilitiesToMove():
            

        self.board.addDisk( best[1], best[2] )
        

if __name__ == '__main__':    
    print()