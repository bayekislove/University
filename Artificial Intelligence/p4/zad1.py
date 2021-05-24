from random import randint
from time import time
from copy import deepcopy

class Board:
    __dirs  = [ (0,1), (1,0), (-1,0), (0,-1), (1,1), (-1,-1), (1,-1), (-1,1) ]

    def __init__(self):
        self.board = [[-1 for _ in range(8)] for _ in range(8) ]
        self.whites = {(3,3), (4,4)}
        self.blacks = {(3,4), (4,3)}
        self.board[3][3] = True #if white player
        self.board[3][4] = False
        self.board[4][3] = False
        self.board[4][4] = True
        self.whiteTurn = False
        self.movesMade = 0

    #this adds new disk and flips all other oponent's pieces
    #when new disk is added we need to check all directions
    def addDisk(self, r, c):
        color = self.whiteTurn
        setToAdd = self.whites if color else self.blacks #we will be removing 
        setToRemove = self.blacks if color else self.whites

        setToAdd.add( (r, c) )
        self.board[r][c] = color
        pomAdd = set()
        for (rD, cD) in Board.__dirs:
            pom = set()
            eR = r + rD
            eC = c + cD
            while(  eR < 8 and eR > -1 and eC < 8 and eC > -1 and
                    self.board[eR][eC] == (not color) ):
                    pom.add( (eR, eC) )
                    eR += rD
                    eC += cD
                    if( eR < 8 and eR > -1 and eC < 8 and eC > -1 and self.board[eR][eC] == color ):
                        for x in pom:
                            pomAdd.add(x)
                        break

        for x in pomAdd:
            self.board[x[0]][x[1]] = color
            setToAdd.add(x)
            setToRemove.remove(x)
        self.whiteTurn = not self.whiteTurn
        
    def __inBounds(self, r, c):
        return r < 8 and r > -1 and c < 8 and c > -1

    def __getPossibilityInDirection(self, sR, sC, dR, dC):
        while(  self.__inBounds(sR + dR, sC + dC) and 
                self.board[sR + dR][sC + dC] == (not self.whiteTurn) ):
            sR += dR
            sC += dC
            if( self.__inBounds(sR + dR, sC + dC) and
                self.board[sR + dR][sC + dC] == -1 ):
                return (sR + dR, sC + dC)

        return False

    def getAllPossibilitiesToMove(self):
        allPoss = set()
        for (r, c) in self.getPositions(self.whiteTurn):
            for (dR, dC) in self.__dirs:
                res = self.__getPossibilityInDirection(r, c, dR, dC )
                if res != False:
                    allPoss.add( res )
        return list(allPoss)
    
    def getPositions(self, color):
        toClone = self.whites if color else self.blacks
        return {x for x in toClone}
    
    def printBoard(self):
        for x in self.board:
            line = ""
            for i in x:
                if(i == -1):
                    line += '.'
                if(i == True):
                    line += 'o'
                if(i == False):
                    line += '#'
            print(line)
        print()

    def calculate(self):
        return (len(self.blacks), len(self.whites))

    def copy(self):
        ret = Board()
        ret.board = deepcopy(self.board)
        ret.whites = deepcopy(self.whites)
        ret.blacks = deepcopy(self.blacks)
        ret.whiteTurn = self.whiteTurn
        ret.movesMade = self.movesMade
        return ret

class RandomPlayer:   
    def __init__(self, color, board):
        self.board = board
        self.color = color

    def move(self):
        allPosssibilities = self.board.getAllPossibilitiesToMove()
        if(len(allPosssibilities) == 0):
            return False
        ra = len(allPosssibilities) - 1
        k = randint(0, ra)
        (r, c) = allPosssibilities[k]
        self.board.addDisk(r, c)

class CleverPlayer:
    __priority = [[30, -10,   11,   8,   8,   11,  -10,   30],
    	         [-10,  -7,   -4,   1,   1,   -4,   -7,  -10],
    	         [11,  - 4,    2,   2,   2,    2,   -4,   11],
    	         [8,     1,    2,   0,   0,    2,    1,    8],
    	         [8,     1,    2,   0,   0,    2,    1,    8],
    	         [11,   -4,    2,   2,   2,    2,   -4,   11],
    	         [-10,  -7,   -4,   1,   1,   -4,   -7,  -10],
    	         [30,  -10,   11,   8,   8,   11,  -10,   30]]

    __ePriority = [[100, -50,   55,   40,   40,   55,  -50,  100],
    	          [-10,  -20,   -4,   1,   1,   -4,   -20,  -10],
    	          [11,   -20,    2,   2,   2,    2,   -4,    11],
    	          [ 40,     1,    2,   0,   0,    2,    1,     40],
    	          [ 40,     1,    2,   0,   0,    2,    1,     40],
    	          [11,   -4,    2,   2,   2,    2,   -4,   11],
    	          [-10,  -20,   -4,   1,   1,   -4,   -20,  -10],
    	          [100,  -50,   55,   40,   40,   55,  -50,   100]]

    def __init__(self, color, board):
        self.board = board

        self.color = color
        self.boardPos = board.getPositions(self.color)

    def __calculateScore(self, board, priorities):
        score = 0
        for r in range(8):
            for c in range(8):
                if( board[r][c] == self.color ):
                    score += priorities[r][c]
                if( board[r][c] == (not self.color) ):
                    score -= priorities[r][c]
        return score

    # def __getMobility(self):
    #     cur = len(self.board.getAllPossibilitiesToMove())
    #     self.board.whiteTurn = not self.board.whiteTurn
    #     nex = len(self.board.getAllPossibilitiesToMove())
    #     self.board.whiteTurn = not self.board.whiteTurn
    #     return cur - nex

    def __h(self):

        score = 0
        score += 0.5 * self.__calculateScore(self.board.board, self.__priority)

        # if self.board.movesMade > 30:
        #     score += 0.5 * self.__calculateScore(self.board.board, self.__ePriority)

        (b, w) = self.board.calculate()

        if self.board.movesMade > 53:
            if self.color:
                score += 3*(w - b)
            else:
                score += 3*(b - w) 

        return score

    def moveB(self):
        poss = self.board.getAllPossibilitiesToMove()
        if( len(poss) == 0 ):
            return False

        maxScore = (-10000, 0, 0)
        for (rP, cP) in poss:
            backupBoard = deepcopy(self.board.board)
            backupWhites = self.board.getPositions(True)
            backupBlacks = self.board.getPositions(False)
    
            self.board.addDisk(rP, cP)
            self.board.whiteTurn = not self.board.whiteTurn

            score = self.__h()

            self.board.board = backupBoard
            self.board.whites = backupWhites
            self.board.blacks = backupBlacks

            if( score >= maxScore[0] ):
                maxScore = (score, rP, cP)
        self.board.addDisk( maxScore[1], maxScore[2] )

    def move(self):
        poss = self.board.getAllPossibilitiesToMove()
        if( len(poss) == 0 ):
            return False

        (_, r, c) = self.__alphaBetaSearch(3, toReturn=True)
        self.board.addDisk(r, c)

    def __alphaBetaSearch(self, d, α = -10000, ϐ = 10000, toReturn = False):
        if d == 0:
            return self.__h()
        if self.board.whiteTurn == self.color: #szukamy najlepszej opcji dla siebie
            best = (-10000, 0, 0)
            for (r, c) in self.board.getAllPossibilitiesToMove():
                backupBoard = deepcopy(self.board.board)
                backupWhites = self.board.getPositions(True)
                backupBlacks = self.board.getPositions(False)

                self.board.addDisk(r, c)
                ret = self.__alphaBetaSearch(d-1, α, ϐ)

                self.board.whiteTurn = not self.board.whiteTurn
                self.board.board = backupBoard
                self.board.whites = backupWhites
                self.board.blacks = backupBlacks

                if best[0] < ret:
                    best = (ret, r, c)
                α = max(α, best[0])
                if α >= ϐ:
                    break

            return best if toReturn else best[0]

        else: #szukamy najlepszej opcji dla siebie
            best = (10000, 0, 0)
            for (r, c) in self.board.getAllPossibilitiesToMove():
                backupBoard = deepcopy(self.board.board)
                backupWhites = self.board.getPositions(True)
                backupBlacks = self.board.getPositions(False)

                self.board.addDisk(r, c)
                ret = self.__alphaBetaSearch(d-1, α, ϐ)

                self.board.whiteTurn = not self.board.whiteTurn
                self.board.board = backupBoard
                self.board.whites = backupWhites
                self.board.blacks = backupBlacks

                if ret < best[0]:
                    best = (ret, r, c)

                ϐ = min(ϐ, best[0])
                if α >= ϐ:
                    break
            return best if toReturn else best[0]

###############################################################################################

def playGame(playerW, playerB):
    brd = Board()
    black = playerB(False, brd)
    white = playerW(True, brd)
    blackContinues = True
    whiteContinues = True
    
    while(blackContinues or whiteContinues):
        brd.movesMade += 1
        if(black.move() == False):
            blackContinues = False
            brd.movesMade -= 1
        brd.movesMade += 1
        if(white.move() == False):
            whiteContinues = False
            brd.movesMade -= 1

    (b, w) = brd.calculate()
    return "B" if b > w else ("W" if w > b else "D")

def simulation(num, pA, pB):
    pAWon = 0
    pBWon = 0
    essa = {'W' : 0, 'B' : 0, 'D' : 0}
    for i in range(num):
        res = playGame(pA, pB)
        essa[res] += 1
        if( res == 'W' ):
            pAWon += 1
        if( res == 'B' ):
            pBWon += 1
        res = playGame(pB, pA)
        essa[res] += 1
        if( res == 'W' ):
            pBWon += 1
        if( res == 'B' ):
            pAWon += 1

    print(f"Gracz A wygrał {pAWon} razy, gracz B - {pBWon}")
    print(f"Biały {essa['W']}, czarny {essa['B']}")


if __name__ == '__main__':
    start = time()
    simulation(500, CleverPlayer, RandomPlayer)
    print(f"Czas trwania - {time() - start}")