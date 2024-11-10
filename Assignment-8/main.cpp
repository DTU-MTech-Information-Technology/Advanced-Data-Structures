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

    BinomialNode* findNode(BinomialNode* node, int value) {
        if (node == nullptr) return nullptr;
        if (node->key == value) return node;

        BinomialNode* found = findNode(node->child, value);
        if (found) return found;

        return findNode(node->sibling, value);
    }

   public:
    BinomialHeap() { head = nullptr; }

    void insert(int key) {
        BinomialNode* newNode = new BinomialNode(key);
        BinomialHeap tempHeap;
        tempHeap.head = newNode;
        head = unionHeaps(head, tempHeap.head);
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

    void decreaseKey(int oldKey, int newKey) {
        BinomialNode* node = findNode(head, oldKey);
        if (node == nullptr) {
            cout << "Key " << oldKey << " not found." << endl;
            return;
        }

        if (newKey > node->key) {
            cout << "New key is greater than current key." << endl;
            return;
        }

        node->key = newKey;
        BinomialNode* y = node;
        BinomialNode* z = node->parent;

        while (z && y->key < z->key) {
            swap(y->key, z->key);
            y = z;
            z = z->parent;
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

    cout << "Binomial Heap before decreaseKey:" << endl;
    heap.display();

    heap.decreaseKey(15, 2);
    cout << "\nBinomial Heap after decreaseKey(15, 2):" << endl;
    heap.display();

    return 0;
}
