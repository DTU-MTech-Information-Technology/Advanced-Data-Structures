#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

const int MAX_LEVEL = 6;

class SkipListNode {
   public:
    int value;
    SkipListNode** forward;

    SkipListNode(int val, int level) {
        value = val;
        forward = new SkipListNode*[level + 1];
        for (int i = 0; i <= level; i++) forward[i] = nullptr;
    }

    ~SkipListNode() { delete[] forward; }
};

class SkipList {
   public:
    int level;
    SkipListNode* head;

    SkipList() {
        level = 0;
        head = new SkipListNode(-1, MAX_LEVEL);
        srand(time(0));
    }

    ~SkipList() {
        SkipListNode* current = head;
        while (current) {
            SkipListNode* next = current->forward[0];
            delete current;
            current = next;
        }
    }

    int randomLevel() {
        int lvl = 0;
        while (rand() % 2 && lvl < MAX_LEVEL) lvl++;
        return lvl;
    }

    void insert(int value) {
        SkipListNode* update[MAX_LEVEL + 1];
        SkipListNode* current = head;

        for (int i = level; i >= 0; i--) {
            while (current->forward[i] && current->forward[i]->value < value)
                current = current->forward[i];
            update[i] = current;
        }

        int newLevel = randomLevel();
        if (newLevel > level) {
            for (int i = level + 1; i <= newLevel; i++) update[i] = head;
            level = newLevel;
        }

        SkipListNode* newNode = new SkipListNode(value, newLevel);

        for (int i = 0; i <= newLevel; i++) {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
    }

    bool search(int value) {
        SkipListNode* current = head;
        for (int i = level; i >= 0; i--) {
            while (current->forward[i] && current->forward[i]->value < value)
                current = current->forward[i];
        }
        current = current->forward[0];
        return current && current->value == value;
    }
};

int main() {
    SkipList skiplist;

    skiplist.insert(3);
    skiplist.insert(26);
    skiplist.insert(7);
    skiplist.insert(9);
    skiplist.insert(19);
    skiplist.insert(22);
    skiplist.insert(21);
    skiplist.insert(6);
    skiplist.insert(17);
    skiplist.insert(12);

    int searchVal = 19;
    if (skiplist.search(searchVal))
        cout << searchVal << " found in skip list." << endl;
    else
        cout << searchVal << " not found in skip list." << endl;

    searchVal = 15;
    if (skiplist.search(searchVal))
        cout << searchVal << " found in skip list." << endl;
    else
        cout << searchVal << " not found in skip list." << endl;

    return 0;
}
