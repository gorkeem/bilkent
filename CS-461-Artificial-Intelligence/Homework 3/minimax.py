import random

BOARD_SIZE = 4

def printBoard(board):
    divider = ''.join(["-+"]*(BOARD_SIZE - 1))
    for i in (range(BOARD_SIZE)):
        for j in (range(BOARD_SIZE - 1)):
            print(board[i][j], end="|")
        print(board[i][BOARD_SIZE - 1], end="")
        print('\n' + divider + "-")

def getWinnerText(winnerValue):
    if winnerValue == 1:
        return "X Won"
    elif winnerValue == -1:
        return "O Won"
    else:
        return "Tie"

def checkWinner(board):
    '''Return the winner of the given board
        1 if X won
        -1 if O won
        0 if tie
    '''
    # Horizontal
    for i in range(BOARD_SIZE):
        if(all(x == board[i][0] for x in board[i]) and board[i][0] is not ' '):
            return 1 if board[i][0] == 'X' else -1

    # Vertical
    for i in range(BOARD_SIZE):
        column = [x[i] for x in board]
        if(all(x == column[i] for x in column) and column[0] is not ' '):
            return 1 if column[0] == 'X' else -1

    # Diagonal
    diagonal1 = []
    diagonal2 = []
    for i in range(BOARD_SIZE):
        diagonal1.append(board[i][i])
        diagonal2.append(board[i][BOARD_SIZE - 1 - i])

    if(all(x == diagonal1[0] for x in diagonal1) and diagonal1[0] is not ' '):
        return 1 if diagonal1[0] == 'X' else -1

    if(all(x == diagonal2[0] for x in diagonal2) and diagonal2[0] is not ' '):
        return 1 if diagonal2[0] == 'X' else -1

    # tie
    hasAvailableSpot = False
    for i in range(BOARD_SIZE):
        if ' ' in board[i]:
            hasAvailableSpot = True
            break

    if not hasAvailableSpot:
        return 0

    return None

class Node:
    def __init__(self, board, isMaxPlayersTurn, depth):
        self.board = board
        self.isMaxPlayersTurn = isMaxPlayersTurn
        self.depth = depth

class TicTacToeGame:
    def __init__(self):
        board = [[" "] * BOARD_SIZE for i in range(BOARD_SIZE)]
        # board = [
        #     [" ", " ", " "],
        #     [" ", " ", " "],
        #     [" ", " ", " "],
        # ]
        self.root = Node(board, True, 0)
        self.recordedGames = {}
        self.cache = {}
        self.trace = True

    def cacheBoard(self, board, value):
        self.cache[str(board)] = value

    def getValueForNode(self, node, alpha=-float("inf"), beta=float("inf")):
        if self.trace:
            print("Calculating virtual value for the board below:")
            printBoard(node.board)
            val = input(
                "Press enter to continue tracing or \'q\' to end tracing")
            if val.strip() == 'q':
                self.trace = False
                print("Printing board situations immediately under the original board")
        result = checkWinner(node.board)
        if result is not None:
            if result not in self.recordedGames.keys():
                self.recordedGames[result] = [row[:] for row in node.board]
            return result

        for child in self.play(node):
            value = self.cache.get(str((child.board)))
            if value is None:
                value = self.getValueForNode(child, alpha, beta)
                self.cacheBoard(child.board, value)
            if node.isMaxPlayersTurn:
                alpha = max(alpha, value)
            else:
                beta = min(beta, value)
            if alpha >= beta:
                break

        # Print nodes immediately under the root i.e. nodes with depth 1
        if node.depth == 1:
            printBoard(node.board)
            if node.isMaxPlayersTurn:
                print("Virtual value", alpha)
            else:
                print("Virtual value", beta)
            print()

        if node.isMaxPlayersTurn:
            return alpha
        else:
            return beta

    def play(self, node):
        '''Depending on whose turn is it, places the player's symbol on the next available spot'''
        for i in range(BOARD_SIZE):
            for j in range(BOARD_SIZE):
                if node.board[i][j] == ' ':
                    childBoard = [row[:] for row in node.board]
                    if node.isMaxPlayersTurn:
                        childBoard[i][j] = 'X'
                    else:
                        childBoard[i][j] = 'O'
                    childNode = Node(
                        childBoard, not node.isMaxPlayersTurn, node.depth + 1)
                    yield childNode

    def printRecordedGames(self):
        '''Print recorded three arbitrary games'''
        for result in self.recordedGames:
            print(getWinnerText(result))
            printBoard(self.recordedGames[result])
            print()

game = TicTacToeGame()
print("Virtual Value of the root node: ",
      game.getValueForNode(game.root), '\n')
print("Three arbitary games:")
game.printRecordedGames()
print("4x4 TicTacToe is futile because the root node has a value of 0")