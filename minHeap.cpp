#include <iostream>
#include <climits>

using namespace std;

class minHeap {
    int *hArr;
    int capacity;
    int heapSize;
    
public:
    minHeap(int cap); //constructor
    ~minHeap();
    
    void minHeapify(int i);
    
    int parent(int i) {
        return ((i-1)/2);
    }
    
    int left(int i) {
        return (2*i + 1);
    }
    
    int right(int i) {
        return (2*i + 2);
    }
    
    int extractMin();
    void decreaseKey(int i, int newVal);
    
    int getMin() {
        return hArr[0];
    }
    
    void deleteKey(int i);
    void insertKey(int i);
    void printHeap();
    
};

//constructor
minHeap::minHeap(int cap) {
    heapSize = 0;
    capacity = cap;
    hArr = new int[cap];
}

minHeap::~minHeap() {
    delete[] hArr;
}

void minHeap::printHeap() {
    cout << "Printing heap values" << endl;
    for(int i=0; i<heapSize; i++) {
        cout << hArr[i] << endl;
    }
}

int minHeap::extractMin() {
    if(heapSize <= 0) {
        return INT_MAX;
    } else if(heapSize == 1) {
        heapSize--;
        return hArr[0];
    }
    
    int minVal = hArr[0];
    hArr[0] = hArr[heapSize-1];
    heapSize--;
    
    minHeap::minHeapify(0);
    return minVal;
}

void minHeap::decreaseKey(int i, int newVal) {
    if(i < heapSize) {
        hArr[i] = newVal;
        
        while((i != 0) && (hArr[i] < hArr[parent(i)])) {
            int temp = hArr[i];
            hArr[i] = hArr[parent(i)];
            hArr[parent(i)] = temp;
            
            //go to parent and check values again
            i = parent(i);
        }
    }
}

void minHeap::deleteKey(int i) {
    decreaseKey(i, INT_MIN);
    extractMin();
}

void minHeap::insertKey(int i) {
    if(heapSize == capacity) {
        return;
    }
    heapSize++;
    int idx = heapSize - 1;
    hArr[idx] = i;
    while((idx != 0) && (hArr[idx] < hArr[parent(idx)])) {
        int temp = hArr[idx];
        hArr[idx] = hArr[parent(idx)];
        hArr[parent(idx)] = temp;
        
        //go to parent and check values again
        idx = parent(idx);
    }
}

void minHeap::minHeapify(int idx) {
    int l = left(idx);
    int r = right(idx);
    int smallest = idx;

    if (l < heapSize && hArr[l] < hArr[smallest])
        smallest = l;
    if (r < heapSize && hArr[r] < hArr[smallest])
        smallest = r;

    if (smallest != idx) {
        int temp = hArr[idx];
        hArr[idx] = hArr[smallest];
        hArr[smallest] = temp;
        minHeapify(smallest);
    }
}

// Driver program to test above functions
int main()
{
    minHeap h(11);
    h.insertKey(3);
    h.insertKey(2);
    h.deleteKey(1);
    h.insertKey(15);
    h.insertKey(5);
    h.insertKey(4);
    h.insertKey(45);
    h.printHeap();
    cout << h.extractMin() << " ";
    cout << h.getMin() << " ";
    h.decreaseKey(2, 1);
    cout << h.getMin();
    
    return 0;
}
