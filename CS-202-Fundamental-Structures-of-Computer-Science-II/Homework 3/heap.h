class Heap {
public:
	Heap();				// default constructor
	Heap(int elementSize);
	~Heap();
	// copy constructor and destructor are supplied by the compiler

	bool heapIsEmpty() const;
	void heapInsert(const int& newItem);
	void heapDelete(int& rootItem);

    // extra homework functions
    void insert(const int a); // same as heapInsert
    int maximum();
    int popMaximum();
	void heapRebuild(int root, int size);		// Converts the semiheap rooted at 
					        // index root into a heap

	int getCompCount();

	

	int* items;	// array of heap items
	int size;            	// number of heap items
	int maxNumOfElements;
	int compCount;
};
