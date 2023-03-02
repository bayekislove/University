import chess
import chess.engine
import multiprocessing

from random import randint
from time import time

engine = chess.engine.SimpleEngine.popen_uci("/usr/games/stockfish")
processes = []

class RandomPlayer:

    def __init__(self, board: chess.Board) -> None:
        self.board: chess.Board = board

    def move(self) -> None:
        moves = list(self.board.legal_moves)
        self.board.push(moves[randint(0, len(moves) - 1)])

class StockfishPlayer:

    def __init__(self, board):
        self.board = board

    def move(self):
        #print("A")
        res = engine.play(self.board, chess.engine.Limit(time=0.8))
        #print(res)
        self.board.push(res.move)

def playGame(pA, pB, board: chess.Board):
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
    if board.outcome() is None or board.outcome().winner == None:
        return -100
    else:
        return -1000 if board.outcome().winner == False else (100 - board.fullmove_number)

def simulation(pA, pB, board: chess.Board):
    score = 0
    for _ in range(10):
        score += playGame(pA, pB, board)

    return score

if __name__ == '__main__':
    print(simulation(StockfishPlayer, RandomPlayer, chess.Board))

engine.quit()