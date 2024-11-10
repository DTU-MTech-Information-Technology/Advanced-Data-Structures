#include <climits>
#include <cmath>
#include <iostream>
using namespace std;

class FibonacciNode {
   public:
    int key;
    int degree;
    bool mark;
    FibonacciNode* parent;
    FibonacciNode* child;
    FibonacciNode* left;
    FibonacciNode* right;

    FibonacciNode(int k) {
        key = k;
        degree = 0;
        mark = false;
        parent = nullptr;
        child = nullptr;
        left = right = this;
    }
};

class FibonacciHeap {
   private:
    FibonacciNode* minNode;
    int nodeCount;

    void link(FibonacciNode* y, FibonacciNode* x) {
        y->left->right = y->right;
        y->right->left = y->left;
        y->parent = x;
        if (x->child) {
            y->right = x->child;
            y->left = x->child->left;
            x->child->left->right = y;
            x->child->left = y;
        } else {
            x->child = y;
            y->right = y;
            y->left = y;
        }
        x->degree++;
        y->mark = false;
    }

    void consolidate() {
        int maxDegree = static_cast<int>(log2(nodeCount)) + 1;
        FibonacciNode* A[maxDegree + 1];
        for (int i = 0; i <= maxDegree; ++i) {
            A[i] = nullptr;
        }

        FibonacciNode* start = minNode;
        FibonacciNode* x = start;
        do {
            FibonacciNode* next = x->right;
            int d = x->degree;
            while (A[d]) {
                FibonacciNode* y = A[d];
                if (x->key > y->key) swap(x, y);
                link(y, x);
                A[d] = nullptr;
                d++;
            }
            A[d] = x;
            x = next;
        } while (x != start);
        minNode = nullptr;
        for (int i = 0; i <= maxDegree; i++) {
            if (A[i]) {
                if (!minNode) {
                    minNode = A[i];
                    minNode->left = minNode->right = minNode;
                } else {
                    A[i]->left = minNode;
                    A[i]->right = minNode->right;
                    minNode->right->left = A[i];
                    minNode->right = A[i];
                    if (A[i]->key < minNode->key) minNode = A[i];
                }
            }
        }
    }

    void cut(FibonacciNode* x, FibonacciNode* y) {
        if (y->child == x) y->child = (x->right != x) ? x->right : nullptr;
        y->degree--;
        x->right->left = x->left;
        x->left->right = x->right;
        x->parent = nullptr;
        x->mark = false;
        x->right = minNode;
        x->left = minNode->left;
        minNode->left->right = x;
        minNode->left = x;
    }

    void cascadingCut(FibonacciNode* y) {
        FibonacciNode* z = y->parent;
        if (z) {
            if (!y->mark)
                y->mark = true;
            else {
                cut(y, z);
                cascadingCut(z);
            }
        }
    }

   public:
    FibonacciHeap() : minNode(nullptr), nodeCount(0) {}

    void insert(int key) {
        FibonacciNode* node = new FibonacciNode(key);
        if (!minNode) {
            minNode = node;
        } else {
            node->right = minNode;
            node->left = minNode->left;
            minNode->left->right = node;
            minNode->left = node;
            if (key < minNode->key) minNode = node;
        }
        nodeCount++;
    }

    int findMin() { return minNode ? minNode->key : INT_MAX; }

    void deleteMin() {
        if (!minNode) return;
        FibonacciNode* child = minNode->child;
        if (child) {
            do {
                FibonacciNode* next = child->right;
                child->left->right = child->right;
                child->right->left = child->left;
                child->right = minNode;
                child->left = minNode->left;
                minNode->left->right = child;
                minNode->left = child;
                child->parent = nullptr;
                child = next;
            } while (child != minNode->child);
        }
        minNode->left->right = minNode->right;
        minNode->right->left = minNode->left;
        FibonacciNode* oldMin = minNode;
        if (minNode == minNode->right) {
            minNode = nullptr;
        } else {
            minNode = minNode->right;
            consolidate();
        }
        delete oldMin;
        nodeCount--;
    }

    void merge(FibonacciHeap& other) {
        if (!other.minNode) return;
        if (!minNode) {
            minNode = other.minNode;
        } else {
            minNode->left->right = other.minNode;
            other.minNode->left->right = minNode;
            FibonacciNode* tmp = minNode->left;
            minNode->left = other.minNode->left;
            other.minNode->left = tmp;
            if (other.minNode->key < minNode->key) minNode = other.minNode;
        }
        nodeCount += other.nodeCount;
        other.minNode = nullptr;
        other.nodeCount = 0;
    }

    void display() {
        if (!minNode) {
            cout << "Fibonacci Heap is empty" << endl;
            return;
        }
        cout << "Fibonacci Heap:" << endl;
        FibonacciNode* start = minNode;
        FibonacciNode* node = start;
        do {
            displayTree(node);
            node = node->right;
        } while (node != start);
        cout << endl;
    }

    void displayTree(FibonacciNode* node, int depth = 0) {
        FibonacciNode* child = node->child;
        for (int i = 0; i < depth; ++i) cout << "  ";
        cout << node->key << endl;
        if (child) {
            do {
                displayTree(child, depth + 1);
                child = child->right;
            } while (child != node->child);
        }
    }
};

int main() {
    FibonacciHeap heap;
    heap.insert(10);
    heap.insert(20);
    heap.insert(5);
    heap.insert(15);
    heap.insert(30);

    heap.display();

    cout << "Minimum element: " << heap.findMin() << endl;
    heap.deleteMin();

    cout << "After deleting minimum element:" << endl;
    heap.display();

    FibonacciHeap heap2;
    heap2.insert(3);
    heap2.insert(7);
    heap2.insert(25);

    cout << "Second Heap:" << endl;
    heap2.display();
    heap.merge(heap2);

    cout << "First Heap after merging with second heap:" << endl;
    heap.display();

    return 0;
}
