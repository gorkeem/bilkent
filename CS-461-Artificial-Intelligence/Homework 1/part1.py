import random
import operator
initial_state = (4,4,0,0,0)
goal_state = (0,0,1,4,4)

# 1 m 1 c left to right  and reverse
possible_expansion1 = (-1,-1,1,1,1)
possible_expansion2 = (1,1,-1,-1,-1)

# 2 m 0 c left to right  and reverse
possible_expansion3 = (-2,0,1,2,0)
possible_expansion4 = (2,0,-1,-2,0)
# 0 m 2 c left to right  and reverse
possible_expansion5 = (0,-2,1,0,2)
possible_expansion6 = (0,2,-1,0,-2)

# 1 m 0 c left to right  and reverse
possible_expansion7 = (-1,0,1,1,0)
possible_expansion8 = (1,0,-1,-1,0)
# 0 m 1 c left to right  and reverse
possible_expansion9 = (0,-1,1,0,1)
possible_expansion10 = (0,1,-1,0,-1)


path = []
past_states = []

path.append(initial_state)
past_states.append(initial_state)


def check_no_failure(state):
    if state[0] <0 or state[1]<0 or state[2]<0 or state[3]<0 or state[4] < 0:
        return False
    elif state[0] + state[3] > 4 or state[1] + state[4] > 4:
        return False
    elif (state[0] < state[1] and state[0] is not 0)or (state[3] < state[4] and state[3] is not 0):
        return False
    else:
        return True
def check_no_loop(state):
    for i in range(0,len(past_states)):
        if past_states[i] == state:
            return False
    return True

def expansion(state):
    expanded_states = []
    if state[2] == 0:
        expanded_state1 = tuple(map(operator.add, state, possible_expansion1))
        expanded_state3 = tuple(map(operator.add, state, possible_expansion3))
        expanded_state5 = tuple(map(operator.add, state, possible_expansion5))
        expanded_state7 = tuple(map(operator.add, state, possible_expansion7))
        expanded_state9 = tuple(map(operator.add, state, possible_expansion9))

        if check_no_failure(expanded_state1) and check_no_loop(expanded_state1):
            expanded_states.append(expanded_state1)
        if check_no_failure(expanded_state3) and check_no_loop(expanded_state3):
            expanded_states.append(expanded_state3)
        if check_no_failure(expanded_state5) and check_no_loop(expanded_state5):
            expanded_states.append(expanded_state5)
        if check_no_failure(expanded_state7) and check_no_loop(expanded_state7):
            expanded_states.append(expanded_state7)
        if check_no_failure(expanded_state9) and check_no_loop(expanded_state9):
            expanded_states.append(expanded_state9)

    elif state[2] == 1:
        expanded_state2 = tuple(map(operator.add,state , possible_expansion2))
        expanded_state4 = tuple(map(operator.add,state , possible_expansion4))
        expanded_state6 = tuple(map(operator.add,state , possible_expansion6))
        expanded_state8 = tuple(map(operator.add,state , possible_expansion8))
        expanded_state10 = tuple(map(operator.add, state, possible_expansion10))

        if check_no_failure(expanded_state2) and check_no_loop(expanded_state2):
            expanded_states.append(expanded_state2)
        if check_no_failure(expanded_state4) and check_no_loop(expanded_state4):
            expanded_states.append(expanded_state4)
        if check_no_failure(expanded_state6) and check_no_loop(expanded_state6):
            expanded_states.append(expanded_state6)
        if check_no_failure(expanded_state8) and check_no_loop(expanded_state8):
            expanded_states.append(expanded_state8)
        if check_no_failure(expanded_state10) and check_no_loop(expanded_state10):
           expanded_states.append(expanded_state10)

    return expanded_states


def solution():

    while len(path) != 0 :
        print(path)

        expanded_states = expansion(path[-1])

         # no possible way. All fringes has loop or failed
        if len(expanded_states) == 0:
            path.remove(path[-1])

        else:
            new_state = random.choice(expanded_states)
            path.append(new_state)
            past_states.append(new_state)

            if new_state == goal_state:
                print (path)
                return path
    print("No solution!")


solution()