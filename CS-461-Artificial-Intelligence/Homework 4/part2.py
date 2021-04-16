# Greatest Common Divisor Algorithm
def gcd(x, y): 
    while(y): 
        x, y = y, x % y 
    return x

# Implementation of the first algorithm
def algorithm1(capacity1=3, capacity2=7, target=5):

    divisor = gcd(capacity1, capacity2)

    # If both jugs are smaller than target, there is no solution.
    if target > capacity1 and target > capacity2:  
        print("No solution.")

    # If greatest common divisor does not divide the target, there is no solution.
    elif target % divisor != 0:  
        print("No solution.")
    else:
        print("Solution 1 - Pouring from 1 to 2\n")
        
        # Initial state of the jugs
        jug1 = 0
        jug2 = 0
        
        # Variables
        m = capacity1
        n = capacity2
        d = target
        k = 0  
        steps1 = 0
        
        # x and y of the algorithm
        additions = 0
        substractions = 0
        
        print("Initial State")
        print("( 0 , 0 )") 
        while k != d:
            # If k is not equal d, then repeat adding m to k and assign the result to k until k = d or k > n.
            if k < n:    
                k = k + m
                additions = additions + 1
                
                if jug1 != d and jug2 != d:
                    print("Fill jug 1")
                    jug1 = m
                    print("(", jug1 , ",", jug2, ")")
                    steps1 = steps1 + 1
                    print("Pour 1 to 2")
                    temp = jug1
                    jug1 = max(0, jug1 - (n - jug2))
                    jug2 = min(jug2 + temp, n)
                    print("(", jug1 , ",", jug2, ")")
                    steps1 = steps1 + 1

            # If k > n, then subtract n from k and assign the result to k
            elif k > n: 
                k = k - n
                substractions = substractions + 1

                if jug1 != d and jug2 != d:
                    print("Empty jug 2")
                    jug2 = 0
                    print("(", jug1 , ",", jug2, ")")
                    steps1 = steps1 + 1
                    print("Pour 1 to 2")
                    temp = jug1
                    jug1 = max(0, jug1 - (n - jug2))
                    jug2 = min(jug2 + temp, n)
                    print("(", jug1 , ",", jug2, ")")
                    steps1 = steps1 + 1
        print("x =", additions, " , y =", substractions)
        print("Total Steps", steps1)
        print("\n")
        
        # Initial state of the jugs
        jug1 = 0
        jug2 = 0
        
        # m and n will be swapped to find a different solution
        m = capacity2
        n = capacity1
        k = 0
        steps2 = 0
        
        # x and y of the algorithm
        additions = 0
        substractions = 0
        
        print("Solution 2 - Pouring from 2 to 1\n")

        print("Initial State")
        print("( 0 , 0 )") 
        while k != d:

            # If k is not equal d, then repeat adding m to k and assign the result to k until k = d or k > n.
            if k < n:    
                k = k + m
                additions = additions + 1

                if jug1 != d and jug2 != d:
                    print("Fill jug 2")
                    jug2 = m
                    print("(", jug1 , ",", jug2, ")")
                    steps2 = steps2 + 1
                    print("Pour 2 to 1")
                    temp = jug2
                    jug2 = max(0, jug2 - (n - jug1))
                    jug1 = min(jug1 + temp, n)
                    print("(", jug1 , ",", jug2, ")")
                    steps2 = steps2 + 1

            # If k > n, then subtract n from k and assign the result to k
            elif k > n: 
                k = k - n
                substractions = substractions + 1

                if jug1 != d and jug2 != d:
                    print("Empty jug 1")
                    jug1 = 0
                    print("(", jug1 , ",", jug2, ")")
                    steps2 = steps2 + 1
                    print("Pour 2 to 1")
                    temp = jug2
                    jug2 = max(0, jug2 - (n - jug1))
                    jug1 = min(jug1 + temp, n)
                    print("(", jug1 , ",", jug2, ")")
                    steps2 = steps2 + 1
        print("x =", additions, " , y =", substractions)
        print("Total Steps", steps2)
        
        if steps1 > steps2:
            print("Solution 2 is the shortest solution.\n")
        elif steps2 > steps1:
            print("Solution 1 is the shortest solution.\n")
        else:
            print("Solution 1 and 2 are both shortest solutions.\n")

# Implementation of the second algorithm
def algorithm2(capacity1=11, capacity2=2, target=5):
    divisor = gcd(capacity1, capacity2)

    # If both jugs are smaller than target, there is no solution.
    if target > capacity1 and target > capacity2:  
        print("no solution.")
    # If greatest common divisor does not divide the target, there is no solution.
    elif target % divisor != 0:  
        print("no solution.")
    else:
        print("Solution 1 - Pouring from 1 to 2")
        
        # Initial state of the jugs
        jug1 = 0
        jug2 = 0
        
        # Variables
        m = capacity1
        n = capacity2
        d = target
        k = 0  
        steps1 = 0
        
        # x and y of the algorithm
        additions = 0
        substractions = 0
        
        print("Initial State")
        print("( 0 , 0 )") 
        while k != d:

            # If k != d, then add n to k and assign the result to k.
            if k < m:   
                k = k + n
                additions = additions + 1
           
                if jug1 != d and jug2 != d:
                    print("Fill jug 1")
                    jug1 = n
                    print("(", jug1 , ",", jug2, ")")
                    steps1 = steps1 + 1
                    print("Pour 1 to 2")
                    temp = jug1
                    jug1 = max(0, jug1 - (m - jug2))
                    jug2 = min(jug2 + temp, m)
                    print("(", jug1 , ",", jug2, ")")
                    steps1 = steps1 + 1

            # If k > d, then repeat subtracting m from k and assign the result to k until k = d or k < m. 
            elif k > m:  
                k = k - m
                substractions = substractions + 1
               
                if jug1 != d and jug2 != d:
                    print("Empty jug 2")
                    jug2 = 0
                    print("(", jug1 , ",", jug2, ")")
                    steps1 = steps1 + 1
                    print("Pour 1 to 2")
                    temp = jug1
                    jug1 = max(0, jug1 - (m - jug2))
                    jug2 = min(jug2 + temp, m)
                    print("(", jug1 , ",", jug2, ")")
                    steps1 = steps1 + 1
        print("x =", additions, " , y =", substractions)
        print("Total Steps", steps1)
        print("\n")
        
        # Initial state of the jugs
        jug1 = 0
        jug2 = 0
        
        # m and n will be swapped to find a different solution
        m = capacity2
        n = capacity1
        d = target
        k = 0
        steps2 = 0
        
        # x and y of the algorithm
        additions = 0
        substractions = 0
        
        print("Solution 2 - Pouring from 2 to 1")

        print("Initial State")
        print("( 0 , 0 )") 
        while k != d:

            # If k != d, then add n to k and assign the result to k.
            if k < m:   
                k = k + n
                additions = additions + 1
              
                if jug1 != d and jug2 != d:
                    print("Fill jug 2")
                    jug2 = n
                    print("(", jug1 , ",", jug2, ")")
                    steps2 = steps2 + 1
                    print("Pour 2 to 1")
                    temp = jug2
                    jug2 = max(0, jug2 - (m - jug1))
                    jug1 = min(jug1 + temp, m)
                    print("(", jug1 , ",", jug2, ")")
                    steps2 = steps2 + 1

            # If k > d, then repeat subtracting m from k and assign the result to k until k = d or k < m.
            elif k > m:  
                k = k - m
                substractions = substractions + 1
             
                if jug1 != d and jug2 != d:
                    print("Empty jug 1")
                    jug1 = 0
                    print("(", jug1 , ",", jug2, ")")
                    steps2 = steps2 + 1
                    print("Pour 2 to 1")
                    temp = jug2
                    jug2 = max(0, jug2 - (m - jug1))
                    jug1 = min(jug1 + temp, m)
                    print("(", jug1 , ",", jug2, ")")
                    steps2 = steps2 + 1
        print("x =", additions, " , y =", substractions)
        print("Total Steps", steps2)
        
        if steps1 > steps2:
            print("Solution 2 is the shortest solution.\n")
        elif steps2 > steps1:
            print("Solution 1 is the shortest solution.\n")
        else:
            print("Solution 1 and 2 are both shortest solutions.\n")


""" Running the algorithms """
algorithm1(3, 7, 5)
# algorithm2(3, 7, 5)
# algorithm1(11, 2, 5)
algorithm2(11, 2, 5)