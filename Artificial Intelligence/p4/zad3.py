from copy import deepcopy
from zad2 import Jungle, zad2Player, normalize

import random

def manhattanDifference(t1, t2):
    return abs(t1[0] - t2[0]) + abs(t1[1] - t2[1])

class zad3Player:

    def __init__(self, game) -> None:
        self.game : Jungle = game

    def h(self, board : Jungle, player):
        if board.winner == player:
            return 1000000

        enemyBase = self.game.dens[not player]
        ourBase = self.game.dens[player]
        enemyPieces = sum([board.PIECE_VALUES[piece] for piece in board.pieces[not player].keys()])
        ourPieces = sum([board.PIECE_VALUES[piece] for piece in board.pieces[player].keys()])

        score = ourPieces - enemyPieces
        score *= 3

        distOur = min([manhattanDifference(enemyBase, board.pieces[player][piece]) for piece in board.pieces[player]])
        distEnemy = min([manhattanDifference(ourBase, board.pieces[not player][piece]) for piece in board.pieces[not player]])
        score += -distOur + distEnemy

        return score

    def move(self):
        bestMoves = [(-10000, "")]

        for move in self.game.moves(self.game.curplayer):
            newBoard : Jungle = deepcopy(self.game)
            newBoard.update(newBoard.curplayer, normalize(move))
            res = self.h(newBoard, self.game.curplayer)

            if res > bestMoves[0][0]:
                bestMoves = [(res, move)]
            elif res == bestMoves[0][0]:
                bestMoves.append( (res, move) )

        return random.choice( bestMoves )[1]

def playGame(pA, pB):
    if random.randint(0, 1) == 1:
        f = pA
        s = pB
        aIsFirst = True
    else:
        f = pB
        s = pA
        aIsFirst = False
    game = Jungle()
    f = f(game)
    s = s(game)
    print(aIsFirst)
    i = 0
    while game.winner == None:
        i += 1
        game.update(game.curplayer, normalize(f.move()))
        game.draw()
        if game.winner != None:
            break
        i += 1
        game.update(game.curplayer, normalize(s.move()))
        game.draw()

    #print( aIsFirst, game.winner)
    if aIsFirst and (game.winner == 0):
        return True
    return (not aIsFirst) and (game.winner == 1)

def simulation(pA, pB, num):
    pAwon = 0
    for i in range(num):
        pAwon += playGame(pA, pB)
        print(pAwon, i)
    return pAwon

if __name__ == '__main__':
    print(simulation(zad3Player, zad2Player, 10))