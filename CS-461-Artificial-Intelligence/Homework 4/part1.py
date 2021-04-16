JUG1_CAPACITY = 7
JUG2_CAPACITY = 3

class Node:
    def __init__(self, jug1=0, jug2=0, children=[]):
        self.jug1 = jug1
        self.jug2 = jug2
        self.children = children

def rule1(x, y):
    '''If x < JUG1_CAPACITY then (x,y) -> (JUG1_CAPACITY,y)'''
    if x < JUG1_CAPACITY:
        return Node(JUG1_CAPACITY, y)
    return None

def rule2(x, y):
    '''If y < JUG2_CAPACITY then (x,y) -> (x,JUG2_CAPACITY)'''
    if y < JUG2_CAPACITY:
        return Node(x, JUG2_CAPACITY)
    return None

def rule3(x, y):
    '''If x > 0 then (x,y) -> (0,y)'''
    if x > 0:
        return Node(0, y)
    return None

def rule4(x, y):
    '''If y > 0 then (x,y) -> (x,0)'''
    if y > 0:
        return Node(x, 0)
    return None

def rule5(x, y):
    '''If x + y <= JUG1_CAPACITY and y > 0 then (x,y) -> (x+y,0)'''
    if x + y <= JUG1_CAPACITY and y > 0:
        return Node(x+y, 0)
    return None

def rule6(x, y):
    '''If x + y > JUG1_CAPACITY and x < JUG1_CAPACITY then (x,y) -> (JUG1_CAPACITY,x+y-JUG1_CAPACITY)'''
    if x + y > JUG1_CAPACITY and x < JUG1_CAPACITY:
        return Node(JUG1_CAPACITY, x+y-JUG1_CAPACITY)
    return None

def rule7(x, y):
    '''If x + y <= JUG2_CAPACITY and x > 0 then (x,y) -> (0,x+y)'''
    if x + y <= JUG2_CAPACITY and x > 0:
        return Node(0, x+y)
    return None

def rule8(x, y):
    '''If x + y > JUG2_CAPACITY and y < JUG2_CAPACITY then (x,y) -> (x+y - JUG2_CAPACITY,JUG2_CAPACITY)'''
    if x + y > JUG2_CAPACITY and y < JUG2_CAPACITY:
        return Node(x+y - JUG2_CAPACITY, JUG2_CAPACITY)
    return None

def printPath(stack):
    for i in range(len(stack) - 1):
        print(stack[i], end=" -> ")
    print(stack[-1], '\n')


def applyRules(node, seen, path=[]):
    # print((node.jug1, node.jug2))
    if (node.jug1, node.jug2) in seen:
        return

    path.append((node.jug1, node.jug2))
    if node.jug1 == 5 and node.jug2 == 0:
        printPath(path)
        return

    seen.add((node.jug1, node.jug2))

    for rule in rules:
        child = rule(node.jug1, node.jug2)
        if child is not None:
            applyRules(child, seen, path)

    path.pop()

rules = [rule1, rule2, rule3, rule4, rule5, rule6, rule7, rule8]
tree = Node(0, 0)
path = []
applyRules(tree, set(), path)
