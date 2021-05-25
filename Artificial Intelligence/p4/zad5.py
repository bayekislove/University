from copy import deepcopy

from typing import List
from zad1 import RandomPlayer, Board, simulation
from math import sqrt, log

MCTS_ITERATIONS = 50 

class MCTSPlayer:

    def __init__(self, color, board) -> None:
        self.color = color
        self.board : Board = board
        self.moveHistory = []

        #we represent state as two sets of player's positions
        self.__rememberedValues = dict() #{ (whitePlayerPos, blackPlayerPos) : (whiteWon, blackWon) }

    def __calculate( self, winratio, parentTimesChosen, timesChosen, C = sqrt(2) ):
        return winratio + ( C * sqrt( log(parentTimesChosen) / timesChosen ) )

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
            #else:
                #moveHistory.append( (frozenset(cBrd.getPositions(True)), frozenset(cBrd.getPositions(False))) )

            sRes = s.move()
            if( sRes == False ):
                SContinues = False
            #else:
                #moveHistory.append( (frozenset(cBrd.getPositions(True)), frozenset(cBrd.getPositions(False))) )

        (b, w) = cBrd.calculate()

        (wWon, bWon) =  (1, 0) if w > b else ( (0, 1) if b > w  else (0.5, 0.5) )
        while( len(moveHistory) > 0 ):
            move = moveHistory.pop()
            if move not in self.__rememberedValues:
                self.__rememberedValues[move] = (wWon, bWon)
            else:
                (wW, bW) = self.__rememberedValues[move]
                self.__rememberedValues[move] = (wW + wWon, bW + bWon)

    def returnBoardAfterMove( self, board, rM, cM ):
        newBoard : Board = deepcopy(board)
        newBoard.addDisk(rM, cM)

        return newBoard

    def move(self):
        possibilities = self.board.getAllPossibilitiesToMove()
        if len(possibilities) == 0:
            return False

        self.moveHistory.append( (frozenset(self.board.whites), frozenset(self.board.blacks)) )

        for (rP, cP) in possibilities:
            newPos = self.returnBoardAfterMove(self.board, rP, cP)
            if (frozenset(newPos.whites), frozenset(newPos.blacks)) not in self.__rememberedValues:
                tup = (frozenset(newPos.whites), frozenset(newPos.blacks))
                
                newMoveHistory = deepcopy(self.moveHistory)
                newMoveHistory.append( tup )
                self.simulation(deepcopy(self.board), newMoveHistory )
            
        for _ in range(MCTS_ITERATIONS):
            toMove = (-10000, "")
            for (rP, cP) in possibilities:
                parentDictVal = self.__rememberedValues[ (frozenset(self.board.whites), frozenset(self.board.blacks)) ]
                parentTimesChosen = parentDictVal[0] + parentDictVal[1]

                newPosition = self.returnBoardAfterMove(self.board, rP, cP)
                childDictVal = self.__rememberedValues[ (frozenset(newPosition.whites), frozenset(newPosition.blacks)) ]
                childTimesChosen = childDictVal[0] + childDictVal[1]

                wins = childDictVal[0] if self.board.whiteTurn else childDictVal[1]
                winratio = wins / childTimesChosen

                cVal = self.__calculate(winratio, parentTimesChosen, childTimesChosen)
                if toMove[0] < cVal:
                    toMove = (cVal, (rP, cP))
            nH = deepcopy(self.moveHistory)
            nB = self.returnBoardAfterMove(self.board, toMove[1][0], toMove[1][1])
            nH.append( (frozenset(nB.whites), frozenset(nB.blacks)) )
            self.simulation( deepcopy(self.board), nH )

        toMove = (-1, "")
        for (rP, cP) in possibilities:
            nB = self.returnBoardAfterMove(self.board, rP, cP)
            childDictVal = self.__rememberedValues[(frozenset(nB.whites), frozenset(nB.blacks))]
            childTimesChosen = childDictVal[0] + childDictVal[1]
            if childTimesChosen > toMove[0]:
                toMove = (rP, cP)
        
        self.board.addDisk(toMove[0], toMove[1])
        

###############################################################################################

def playGame(playerW, playerB):
    brd = Board()
    black = playerB(False, brd)
    white = playerW(True, brd)
    blackContinues = True
    whiteContinues = True
    
    while(blackContinues or whiteContinues):
        brd.movesMade += 1
        #print(brd.calculate())
        if(black.move() == False):
            blackContinues = False
            brd.movesMade -= 1
        brd.movesMade += 1
        if(white.move() == False):
            whiteContinues = False
            brd.movesMade -= 1

    (b, w) = brd.calculate()
    return "B" if b > w else ("W" if w > b else "D")

def simulation(pA, pB, num):
    pAWon = 0
    pBWon = 0

    for _ in range(num):
        res = playGame(pA, pB)
        if( res == 'W' ):
            pAWon += 1
        if( res == 'B' ):
            pBWon += 1
        print(pAWon, pBWon)
        res = playGame(pB, pA)

        if( res == 'W' ):
            pBWon += 1
        if( res == 'B' ):
            pAWon += 1
        print(pAWon, pBWon)

    print(f"Gracz A wygrał {pAWon} razy, gracz B {pBWon}")

if __name__ == '__main__':    
    simulation(MCTSPlayer, RandomPlayer, 5)