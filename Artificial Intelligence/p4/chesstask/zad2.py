from typing import List
from random import randint, random
from copy import deepcopy

import chess
import chess.engine

defaultWeights = { "N" : 3, "B" : 3, "R" : 5, "Q" : 9, "K" : 0, "P" : 1 }

PLAYERS_NUM = 30
FULLMOVES_TERMINATION = 65

#engine = chess.engine.SimpleEngine.popen_uci("/usr/bin/stockfish")

class ChessAgent:

    def __init__(self, α, weights, board : chess.Board ) -> None:
        self.α = α
        self.weights = weights
        self.board : chess.Board = board
        self.gamesWon = 0

    def getPiecesOfColor(self, ifWhite):
        sum = 0
        for _, p in self.board.piece_map().items():
            if p.color == ifWhite:
                sum += self.weights[p.symbol().upper()]
        return sum

    def __getαMovePossibilitiesCount(self):
        return self.α * self.board.legal_moves.count()

    def __calculateHeuristic(self) -> int:        
        h = self.getPiecesOfColor(self.board.turn)
        h += -self.getPiecesOfColor(not self.board.turn)
        h += self.__getαMovePossibilitiesCount()
        self.board.turn = not self.board.turn
        h -= self.__getαMovePossibilitiesCount()
        self.board.turn = not self.board.turn
        return h

    def __calculateHeuristicWrapper(self, mv):
        self.board.push(mv)
        if self.board.is_checkmate():
            return 10000000

        self.board.turn = not self.board.turn
        h = self.__calculateHeuristic()
        self.board.pop()
        return h

    def move(self):
        max = [(-100000, "")]
        #print(self.board.legal_moves.count())
        for mv in self.board.legal_moves:
            #print(mv, self.board.legal_moves)
            #print("ale wszedłem")
            h = self.__calculateHeuristicWrapper(mv)
            if max[0][0] < h:
                max = [(h, mv)]
            if h == 10000000:
                return "M"
            elif max[0][0] == h:
                max.append( (h, mv) ) 
        self.board.push( max[randint(0, len(max) - 1)][1] )

def genRandomWeights():
    return { p : randint(3, 9) for p in ["N", "B", "R", "Q"] } | {"P" : 1, "K" : 0}

def playGame(pA : ChessAgent, pB : ChessAgent, gameBoard):
    gameBoard.reset()

    while ( not gameBoard.is_game_over() ) and gameBoard.fullmove_number < FULLMOVES_TERMINATION:
        
        #print(gameBoard, '\n')
        res = ( pA.move() == "M" )
        if res or gameBoard.is_game_over():
            break
        res = ( pB.move() == "M" )
        if res or gameBoard.is_game_over():
            break
        #print(gameBoard, '\n')

    if gameBoard.outcome() == None:
        weightsSaved = deepcopy(pA.weights)
        pA.weights = deepcopy(defaultWeights)
        aScore = pA.getPiecesOfColor(True)
        bScore = pA.getPiecesOfColor(False)
        pA.weights = weightsSaved
        if aScore > bScore:
            pA.gamesWon += 1
        if bScore > aScore:
            pB.gamesWon += 1
        
    else:
        if gameBoard.outcome().winner == True:
            pA.gamesWon += 1
        elif gameBoard.outcome().winner != None:
            pB.gamesWon += 1
    
    gameBoard.reset()
    while ( not gameBoard.is_game_over() ) and gameBoard.fullmove_number < FULLMOVES_TERMINATION:
        res = ( pB.move() == "M" )
        if res or gameBoard.is_game_over():
            break
        res = ( pA.move() == "M" )
        if res or gameBoard.is_game_over():
            break

    if gameBoard.outcome() == None:
        weightsSaved = deepcopy(pA.weights)
        pA.weights = deepcopy(defaultWeights)
        aScore = pA.getPiecesOfColor(False)
        bScore = pA.getPiecesOfColor(True)
        pA.weights = weightsSaved
        if aScore > bScore:
            pA.gamesWon += 1
        if bScore > aScore:
            pB.gamesWon += 1
        
    else:
        if gameBoard.outcome().winner == False:
            pA.gamesWon += 1
        elif gameBoard.outcome().winner != None:
            pB.gamesWon += 1

def genRandomPlayer(board) -> ChessAgent:
    return ChessAgent( random() * 1, genRandomWeights(), board )

def genRandomPlayers(board) -> List[ChessAgent]:
    return [ genRandomPlayer(board) for _ in range(PLAYERS_NUM) ]

def performSimulation():
    board = chess.Board()
    players : List[ChessAgent] = genRandomPlayers(board)
    for i in range(PLAYERS_NUM):
        for j in range(i + 1, PLAYERS_NUM):
            playGame( players[i], players[j], board )
    players.sort(key=lambda x : x.gamesWon)
    best : ChessAgent = players[0]
    print(best.weights)
    print(best.α)
    print(best.gamesWon)

performSimulation()