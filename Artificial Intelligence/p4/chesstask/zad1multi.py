from typing import List
from random import randint
from time import time

import chess
import multiprocessing


pawnEval = [0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
            5.0,  5.0,  5.0,  5.0,  5.0,  5.0,  5.0,  5.0,
            1.0,  1.0,  2.0,  3.0,  3.0,  2.0,  1.0,  1.0,
            0.5,  0.5,  1.0,  2.5,  2.5,  1.0,  0.5,  0.5,
            0.0,  0.0,  0.0,  2.0,  2.0,  0.0,  0.0,  0.0,
            0.5, -0.5, -1.0,  0.0,  0.0, -1.0, -0.5,  0.5,
            0.5,  1.0, 1.0,  -2.0, -2.0,  1.0,  1.0,  0.5,
            0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0]

knightEval = [-5.0, -4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0,
              -4.0, -2.0,  0.0,  0.0,  0.0,  0.0, -2.0, -4.0,
              -3.0,  0.0,  1.0,  1.5,  1.5,  1.0,  0.0, -3.0,
              -3.0,  0.5,  1.5,  2.0,  2.0,  1.5,  0.5, -3.0,
              -3.0,  0.0,  1.5,  2.0,  2.0,  1.5,  0.0, -3.0,
              -3.0,  0.5,  1.0,  1.5,  1.5,  1.0,  0.5, -3.0,
              -4.0, -2.0,  0.0,  0.5,  0.5,  0.0, -2.0, -4.0,
              -5.0, -4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0
              ]

bishopEval = [
    -2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0,
    -1.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -1.0,
    -1.0,  0.0,  0.5,  1.0,  1.0,  0.5,  0.0, -1.0,
    -1.0,  0.5,  0.5,  1.0,  1.0,  0.5,  0.5, -1.0,
    -1.0,  0.0,  1.0,  1.0,  1.0,  1.0,  0.0, -1.0,
    -1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0, -1.0,
    -1.0,  0.5,  0.0,  0.0,  0.0,  0.0,  0.5, -1.0,
    -2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0]

rookEval = [
    0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
    0.5,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  0.5,
    -0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5,
    -0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5,
    -0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5,
    -0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5,
    -0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5,
    0.0,   0.0, 0.0,  0.5,  0.5,  0.0,  0.0,  0.0]

queenEval = [
    -2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0,
    -1.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -1.0,
    -1.0,  0.0,  0.5,  0.5,  0.5,  0.5,  0.0, -1.0,
    -0.5,  0.0,  0.5,  0.5,  0.5,  0.5,  0.0, -0.5,
    -0.5,  0.0,  0.5,  0.5,  0.5,  0.5,  0.0, -0.5,
    -1.0,  0.0,  0.5,  0.5,  0.5,  0.5,  0.0, -1.0,
    -1.0,  0.0,  0.5,  0.0,  0.0,  0.0,  0.0, -1.0,
    -2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0
]

processes = []


def tB(board) -> List[List[int]]:  # transposeBoard
    return [board[63-i] for i in range(64)]


evalDict = {True: {"N": knightEval, "B": bishopEval, "R": rookEval, "Q": queenEval, "P": pawnEval},
            False: {"N": tB(knightEval), "B": tB(bishopEval), "R": tB(rookEval), "Q": tB(queenEval), "P": tB(pawnEval)}}


class RandomPlayer:

    def __init__(self, board: chess.Board) -> None:
        self.board: chess.Board = board

    def move(self) -> None:
        moves = list(self.board.legal_moves)
        self.board.push(moves[randint(0, len(moves) - 1)])


class CleverPlayer:
    weights = {"N": 30, "B": 30, "R": 50, "Q": 90, "K": 0, "P": 10}

    def __init__(self, board) -> None:
        self.board: chess.Board = board

    def getPiecesOfColor(self, ifWhite):
        sum = 0
        for idx, p in self.board.piece_map().items():
            if p.color == ifWhite:
                sum += CleverPlayer.weights[p.symbol().upper()]
                if p.symbol().upper() != 'K':
                    sum += evalDict[ifWhite][p.symbol().upper()][idx]
        return sum

    def h(self, color):
        ours = self.getPiecesOfColor(color)
        theirs = self.getPiecesOfColor(not color)
        return ours - theirs

    def hWrapper(self, mv):
        self.board.push(mv)
        self.board.turn = not self.board.turn
        if self.board.is_checkmate():
            return 100000 if self.board.outcome().winner else -100000
            # wiemy że gramy białym graczem, można to uprościć
        if self.board.is_stalemate():
            return -100000

        ret = self.h(self.board.turn)
        self.board.pop()
        return ret

    def alphabeta(self, d, α, β, toMax):
        if toMax:
            val = (-1000000, "")
            if d == 1:  # czyli na następnym etapie kończymy przeszukiwanie
                for mv in self.board.legal_moves:
                    ret = self.hWrapper(mv)
                    if ret >= val[0]:
                        val = (ret, mv)
            else:
                for mv in self.board.legal_moves:
                    # wrobimy ruch i patrzymy co się stanie
                    self.board.push(mv)
                    ret = self.alphabeta(d - 1, α, β, False)

                    if ret[0] >= val[0]:
                        val = (ret[0], mv)
                    α = max(α, ret[0])

                    self.board.turn = not self.board.turn  # trzeba odwołać ruch w tej turze
                    self.board.pop()
                    if α >= β:
                        break
            return val
        else:  # minimalizujemy wartość
            val = (1000000, "")
            if d == 1:  # czyli na następnym etapie kończymy przeszukiwanie
                for mv in self.board.legal_moves:
                    ret = self.hWrapper(mv)
                    if ret <= val[0]:
                        val = (ret, mv)
            else:
                for mv in self.board.legal_moves:
                    # wrobimy ruch i patrzymy co się stanie
                    self.board.push(mv)
                    ret = self.alphabeta(d - 1, α, β, True)

                    if ret[0] <= val[0]:
                        val = (ret[0], mv)

                    self.board.turn = not self.board.turn  # trzeba odwołać ruch w tej turze
                    self.board.pop()

                    β = min(β, ret[0])
                    if β >= α:
                        break
            return val

    def moveBasic(self):
        max = [(-100000, "")]
        for mv in self.board.legal_moves:
            heur = self.hWrapper(mv)
            if heur > max[0][0]:
                max = [(heur, mv)]
            elif heur == max[0][0]:
                max.append((heur, mv))
        self.board.push(max[randint(0, len(max) - 1)][1])

    def move(self):
        return self.board.push(self.alphabeta(3, -1000000, 1000000, True)[1])


def playGame(pA, pB, board: chess.Board, score: multiprocessing.Array):
    board = chess.Board()
    pA = pA(board)
    pB = pB(board)

    board.push(chess.Move.from_uci('e2e4'))
    pB.move()
    while (not board.is_game_over()) and board.fullmove_number < 100:
        # print(board.fullmove_number)
        pA.move()
        # print(board, '\n')
        if board.is_game_over():
            break
        pB.move()
        # print(board, '\n')
    # print(board)
    score[1] += board.fullmove_number
    if board.outcome() is None or board.outcome().winner == None:
        score[0] += -100
    else:
        score[0] += -1000 if board.outcome().winner == False else (100 -
                                                                      board.fullmove_number)

def simulation(pA, pB, board: chess.Board):
    score = multiprocessing.Array('i', [0, 0])
    for _ in range(50):
        res = multiprocessing.Process(
            target=playGame, args=(pA, pB, board, score))
        res.start()
        processes.append(res)
    for process in processes:
        process.join()
    return score[0], score[1]


if __name__ == '__main__':
    start = time()
    (score, movesNo) = simulation(CleverPlayer, RandomPlayer, chess.Board)
    print( score )
    print( movesNo, time() - start )
