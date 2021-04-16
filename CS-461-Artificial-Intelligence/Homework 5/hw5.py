from collections import defaultdict

"""
Group Klue

Reference:
This topological sort implementation is taken from geeks for geeks : https://www.geeksforgeeks.org/topological-sorting/
We did some modifications. We changed defaultdict as dict instead of list to make process string based. Hence, we changed
some check points as dictionary keys instead of integers.
"""
# Class to represent a graph
class Graph:
    def __init__(self, vertices):
        self.graph = defaultdict(dict)  # dictionary containing adjacency List
        self.V = vertices  # No. of vertices
        self.keys = self.graph.keys()
    # function to add an edge to graph
    def addEdge(self, u, v):
        self.graph[u] = v

        # A recursive function used by topologicalSort

    def topologicalSortUtil(self, v, visited, stack):

        # Mark the current node as visited.
        visited[v] = True
        # Recur for all the vertices adjacent to this vertex
        for i in self.keys:
            if visited[i] == False:
                self.topologicalSortUtil(i, visited, stack)

                # Push current vertex to stack which stores result
        stack.insert(0, v)

        # The function to do Topological Sort. It uses recursive

    # topologicalSortUtil()
    def topologicalSort(self):
        # Mark all the vertices as not visited
        #visited = [False] * self.V
        visited = {}

        stack = []
        for i in self.keys:
            visited[i] = False

        # Call the recursive helper function to store Topological
        # Sort starting from all vertices one by one
        for i in self.keys:
            if visited[i] == False:
                self.topologicalSortUtil(i, visited, stack)

                # Print contents of the stack
        return (stack)

    def solve_problem(self,list,element):
        precedence_list = []
        index = 0
        while list[index] is not element:
            precedence_list.append(list[index])
            index +=1
        precedence_list.append(element)
        precedence_list.reverse()
        print(precedence_list)

g1 = Graph(8)
g1.addEdge("ios_base",None)
g1.addEdge("ios","ios_base")

g1.addEdge("istream","ios")
g1.addEdge("ostream","ios")

g1.addEdge("istream_withassign(cin)","istream")
g1.addEdge("iostream","istream")

g1.addEdge("iostream","ostream")
g1.addEdge("ostream_withassign(cout,cerr,clog)","ostream")

g1.addEdge("iosstream_withassign","iostream")

print("\nPrecedence list for elements. Clarification:  left to right  == top to bottom as in the book page 195. The Rightest side is parent('everything' in book example)")

print ("Graph 1")
print("---------------------------------------------------------------------------------------------------------------")
list1 = g1.topologicalSort()
print("\nprecedence list of istream_withassign(cin)")
g1.solve_problem(list1,"istream_withassign(cin)")
print("\nprecedence list of iosstream_withassign")
g1.solve_problem(list1,"iosstream_withassign")
print("\nprecedence list of ostream_withassign(cout,cerr,clog)")
g1.solve_problem(list1,"ostream_withassign(cout,cerr,clog)")


g2 = Graph(7)
g2.addEdge("Graph",None)
g2.addEdge("GraphWrapper","Graph")
g2.addEdge("Astar","GraphWrapper")
g2.addEdge("GraphLBwrapper","GraphWrapper")
g2.addEdge("BaseSequenceSpaceGraphLBwrapper","GraphLBwrapper")
g2.addEdge("RotamerToSequenceGraphLBwrapper","BaseSequenceSpaceGraphLBwrapper")
g2.addEdge("SequenceSpaceGraphLBwrapper","BaseSequenceSpaceGraphLBwrapper")


print ("Graph 2")
print("---------------------------------------------------------------------------------------------------------------")
list2 = g2.topologicalSort()
print("\nprecedence list of Astar")
g2.solve_problem(list2,"Astar")
print("\nprecedence list of RotamerToSequenceGraphLBwrapper")
g2.solve_problem(list2,"RotamerToSequenceGraphLBwrapper")
print("\nprecedence list of SequenceSpaceGraphLBwrapper")
g2.solve_problem(list2,"SequenceSpaceGraphLBwrapper")

g3 = Graph(9)
g3.addEdge("puddle::MetaObject",None)
g3.addEdge("puddle::MetaNamedObject","puddle::MetaObject")
g3.addEdge("puddle::MetaScopedObject","puddle::MetaObject")
g3.addEdge("puddle::MetaNamedScopedObject","puddle::MetaNamedObject")
g3.addEdge("puddle::MetaNamedScopedObject","puddle::MetaScopedObject")
g3.addEdge("puddle::MetaType","puddle::MetaNamedScopedObject")
g3.addEdge("puddle::MetaScope","puddle::MetaNamedScopedObject")
g3.addEdge("puddle::MetaTemplatedType","puddle::MetaType")
g3.addEdge("puddle::MetaClass","puddle::MetaType")
g3.addEdge("puddle::MetaClass","puddle::MetaScope")
g3.addEdge("puddle::MetaTemplatedClass","puddle::MetaTemplatedType")
g3.addEdge("puddle::MetTemplatedClass","puddle::MetaClass")

print ("Graph 3")
print("---------------------------------------------------------------------------------------------------------------")
list3 = g3.topologicalSort()
print("\nprecedence list of puddle::MetTemplatedClass ")
g3.solve_problem(list3,"puddle::MetTemplatedClass")