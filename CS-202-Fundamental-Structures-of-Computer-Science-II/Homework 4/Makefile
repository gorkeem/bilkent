avlfreq: main.o AVLTree.o AVLTreeNode.o
	g++ main.o AVLTree.o AVLTreeNode.o -o avlfreq

main.o: main.cpp
	g++ -c main.cpp

AVLTree.o: AVLTree.cpp
	g++ -c AVLTree.cpp

AVLTreeNode.o: AVLTreeNode.cpp
	g++ -c AVLTreeNode.cpp

clean: clean-custom
	rm* output