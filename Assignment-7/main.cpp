#include <climits>
#include <iostream>

using namespace std;

class BinomialNode {
   public:
    int key;
    int degree;
    BinomialNode* parent;
    BinomialNode* child;
    BinomialNode* sibling;

    BinomialNode(int k) {
        key = k;
        degree = 0;
        parent = nullptr;
        child = nullptr;
        sibling = nullptr;
    }
};

class BinomialHeap {
   private:
    BinomialNode* head;

    void linkTree(BinomialNode* y, BinomialNode* z) {
        y->parent = z;
        y->sibling = z->child;
        z->child = y;
        z->degree++;
    }

    BinomialNode* mergeRootLists(BinomialNode* h1, BinomialNode* h2) {
        if (!h1) return h2;
        if (!h2) return h1;

        BinomialNode* head;
        if (h1->degree <= h2->degree) {
            head = h1;
            h1 = h1->sibling;
        } else {
            head = h2;
            h2 = h2->sibling;
        }

        BinomialNode* tail = head;

        while (h1 && h2) {
            if (h1->degree <= h2->degree) {
                tail->sibling = h1;
                h1 = h1->sibling;
            } else {
                tail->sibling = h2;
                h2 = h2->sibling;
            }
            tail = tail->sibling;
        }

        tail->sibling = h1 ? h1 : h2;

        return head;
    }

    BinomialNode* unionHeaps(BinomialNode* h1, BinomialNode* h2) {
        BinomialNode* newHead = mergeRootLists(h1, h2);
        if (!newHead) return nullptr;

        BinomialNode* prev = nullptr;
        BinomialNode* curr = newHead;
        BinomialNode* next = curr->sibling;

        while (next) {
            if ((curr->degree != next->degree) ||
                (next->sibling && next->sibling->degree == curr->degree)) {
                prev = curr;
                curr = next;
            } else {
                if (curr->key <= next->key) {
                    curr->sibling = next->sibling;
                    linkTree(next, curr);
                } else {
                    if (!prev) {
                        newHead = next;
                    } else {
                        prev->sibling = next;
                    }
                    linkTree(curr, next);
                    curr = next;
                }
            }
            next = curr->sibling;
        }

        return newHead;
    }

   public:
    BinomialHeap() { head = nullptr; }

    void insert(int key) {
        BinomialNode* newNode = new BinomialNode(key);
        BinomialHeap tempHeap;
        tempHeap.head = newNode;
        head = unionHeaps(head, tempHeap.head);
    }

    int getMin() {
        if (!head) return INT_MAX;

        BinomialNode* minNode = head;
        BinomialNode* curr = head->sibling;

        while (curr) {
            if (curr->key < minNode->key) {
                minNode = curr;
            }
            curr = curr->sibling;
        }
        return minNode->key;
    }

    void deleteMin() {
        if (!head) return;

        BinomialNode* minNode = head;
        BinomialNode* minNodePrev = nullptr;
        BinomialNode* prev = nullptr;
        BinomialNode* curr = head;

        while (curr->sibling) {
            if (curr->sibling->key < minNode->key) {
                minNode = curr->sibling;
                minNodePrev = curr;
            }
            curr = curr->sibling;
        }

        if (minNodePrev) {
            minNodePrev->sibling = minNode->sibling;
        } else {
            head = minNode->sibling;
        }

        BinomialNode* child = minNode->child;
        BinomialNode* revChild = nullptr;

        while (child) {
            BinomialNode* next = child->sibling;
            child->sibling = revChild;
            revChild = child;
            child->parent = nullptr;
            child = next;
        }

        BinomialHeap newHeap;
        newHeap.head = revChild;

        head = unionHeaps(head, newHeap.head);

        delete minNode;
    }

    void merge(BinomialHeap& other) {
        head = unionHeaps(head, other.head);
        other.head = nullptr;
    }

    void display() {
        if (!head) {
            cout << "Binomial Heap is empty." << endl;
            return;
        }

        cout << "Binomial Heap:" << endl;
        BinomialNode* curr = head;
        while (curr) {
            cout << "B" << curr->degree << ": ";
            displayTree(curr);
            cout << endl;
            curr = curr->sibling;
        }
    }

    void displayTree(BinomialNode* node) {
        if (!node) return;
        cout << node->key << " ";
        BinomialNode* child = node->child;
        while (child) {
            displayTree(child);
            child = child->sibling;
        }
    }
};

int main() {
    BinomialHeap heap;
    heap.insert(10);
    heap.insert(20);
    heap.insert(5);
    heap.insert(15);
    heap.insert(30);

    heap.display();
    cout << endl;
    cout << "Minimum element: " << heap.getMin() << endl;

    heap.deleteMin();
    cout << "After deleting the minimum element:" << endl;
    heap.display();
    cout << endl;

    BinomialHeap heap2;
    heap2.insert(3);
    heap2.insert(7);
    heap2.insert(25);

    cout << "Second Heap:" << endl;
    heap2.display();
    cout << endl;

    cout << "Merging second heap into first heap." << endl;
    heap.merge(heap2);

    cout << "First Heap after merging:" << endl;
    heap.display();
    cout << endl;

    return 0;
}
