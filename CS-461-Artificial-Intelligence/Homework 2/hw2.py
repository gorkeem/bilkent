from numpy import copy
import random

PUZZLE_LIMIT = 30


def printPuzzle(puzzle):
    for row in puzzle:
        for item in row:
            if item is None:
                print(" ", end=" ")
            else:
                print(item, end=" ")
        print()


class Solver:
    def __init__(self, init_state, goal_state=[[1, 2, 3], [4, 5, 6], [7, 8, None]]):
        """
        priority_queue is sorted by fval in ascending order
        seen holds the all previous states
        """
        self.init_state = init_state
        self.goal_state = goal_state
        self.priority_queue = []
        self.seen = []

    def calc_fval(self, node):
        """
        Calculate the f() = h() + g()
        g() value is the number of nodes from the current node to the initial node
        """
        return self.calc_hval(node) + node.g

    def calc_hval(self, node):
        """
        Calculate the h() using the Hamming Distance, number of displaced tiles
        """
        hval = 0
        for i in range(3):
            for j in range(3):
                if node.puzzle[i][j] != self.goal_state[i][j] and node.puzzle[i][j] != None:
                    hval += 1
        return hval

    def is_loop(self, node):
        """
        If the puzzle is already seen before returns True
        """
        if node.puzzle in [o.puzzle for o in self.seen]:
            return True
        return False

    def solve(self, show_trace=False):
        """ 
        Initializes the tree with the node containing the initial state and calculates the fval of it
        Adds the inital node to the priority queue
        Inside the loop,
        Checks if the node with the lowest fval, first item in priority queue, is the goal state
        If it is, loop terminates
        Else, generates all the children of the current node, calculates their fval and
        adds it to the priority queue if it is not a loop.
        After adding new nodes, priority queue is sorted again by fval.
        """
        start_node = Node(self.init_state, 0)
        start_node.fval = self.calc_fval(start_node)
        self.priority_queue.append(start_node)
        while True:
            current_node = self.priority_queue[0]
            if self.calc_hval(current_node) == 0:
                break
            children = current_node.get_all_blank_swaps()
            for child_node in children:
                if not self.is_loop(child_node):
                    child_node.fval = self.calc_fval(child_node)
                    self.priority_queue.append(child_node)
            self.seen.append(current_node)
            self.priority_queue.pop(0)
            self.priority_queue.sort(key=lambda x: x.fval, reverse=False)

        if show_trace:
            self.print_solution_trace(current_node)

    def print_solution_trace(self, node):
        solution_path = node.get_path()
        print("Solved in:", len(solution_path) - 1, "step")
        for i in range(len(solution_path) - 1):
            solution_path[i].print()
            print()
            print(solution_path[i+1].last_move)
            print("  | ")
            print(" \|/")
            print()
        solution_path[-1].print()
        print()


class Node:
    def __init__(self, puzzle, fval=0, parent=None, last_move=""):
        """ 
        Initialize the node with the 
        puzzle data, 
        g value of the node
        and the calculated fvalue 
        """
        self.puzzle = puzzle
        self.parent = parent
        self.fval = fval
        self.last_move = last_move
        if self.parent is None:
            self.g = 0
        else:
            self.g = self.parent.g + 1

    def print(self):
        printPuzzle(self.puzzle)

    def get_path(self):
        """
        Reconstruct a path from to the root 'parent'
        """
        node = self
        path = []
        while node:
            path.append(node)
            node = node.parent
        path.reverse()
        return path

    def find_blank(self):
        """
        Find the x,y coordinates of the blank square
        i: y coordinate
        j: x coordinate
        For this puzzle,
            1 2 3 
            4 5   
            7 8 6
        i = 1, j = 2
        """
        for i in range(len(self.puzzle)):
            for j in range(len(self.puzzle[i])):
                if self.puzzle[i][j] is None:
                    return (i, j)

    def move_blank(self, blank_x, blank_y, swap_x, swap_y):
        """
        Swap the blank square with given x,y
        Returns swapped puzzle
        """
        new_puzzle = None
        if swap_y >= 0 and swap_y <= 2 and swap_x >= 0 and swap_x <= 2:
            new_puzzle = copy(self.puzzle).tolist()
            new_puzzle[blank_y][blank_x], new_puzzle[swap_y][swap_x] = new_puzzle[swap_y][swap_x], new_puzzle[blank_y][blank_x]
        return new_puzzle

    def get_all_blank_swaps(self):
        """
        Return all the child nodes of the current puzzle
        Child nodes are puzzles with only one move away from the current puzzle
        """
        blank_y, blank_x = self.find_blank()
        possible_swap_locations = [
            ("DOWN", [blank_y-1, blank_x]),
            ("UP", [blank_y+1, blank_x]),
            ("RIGHT", [blank_y, blank_x-1]),
            ("LEFT", [blank_y, blank_x+1]),
        ]
        children = []
        for swap_location in possible_swap_locations:
            new_puzzle = self.move_blank(
                blank_x, blank_y, swap_location[1][1], swap_location[1][0])
            if new_puzzle is not None:
                last_move = str(new_puzzle[blank_y]
                                [blank_x]) + " " + swap_location[0]
                children.append(Node(new_puzzle, 0, self, last_move))
        return children


class PuzzleGenerator:
    def __init__(self):
        """
        Initialize the generator with the goal state and an empty puzzle pool
        """
        self.node = Node([[1, 2, 3], [4, 5, 6], [7, 8, None]])
        self.puzzles = []

    def generate(self):
        """
        Children of the initial puzzle are added to a pool, then all the children of those children
        are added to the pool. In each loop, a puzzle is added to the puzzles pool if it isn't already
        in the puzzles pool.
        """
        pool = self.node.get_all_blank_swaps()
        for child_node in pool:
            if child_node.puzzle not in self.puzzles:
                self.puzzles.append(child_node.puzzle)
                pool += child_node.get_all_blank_swaps()
                if len(self.puzzles) >= PUZZLE_LIMIT:
                    break


"Generate unique puzzles"
generator = PuzzleGenerator()
generator.generate()

# i = 1
# print("Initial States")
# for puzzle in generator.puzzles:
#     print("Puzzle", i)
#     printPuzzle(puzzle)
#     i += 1
#     print()

"""
Randomly pick two numbers between 0 and 30 to decide which puzzles show their solution trace
"""
i = 1
random_puzzle_numbers = random.sample(range(1, PUZZLE_LIMIT), 2)
for puzzle in generator.puzzles:
    show_trace = True if i in random_puzzle_numbers else False
    solver = Solver(puzzle)
    if show_trace:
        print("Puzzle", i)
    solver.solve(show_trace)
    i += 1
