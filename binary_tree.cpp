#include <stdio.h>
#include <iostream>
#include <random>
#include <QDebug>
#include <QTime>
using namespace std;

class BSTtreeNode {
    friend class BSTtree;

public:
    int element;
    char tab[10];

private:
    BSTtreeNode(int element);
    BSTtreeNode* leftChild;
    BSTtreeNode* rightChild;
};

class BSTtree {
public:
    BSTtree();
    BSTtreeNode* head;
    bool addNode(int index);
    void addRandom(int amount);
    BSTtreeNode* findNode(int index);
    bool removeNode(int index);
    void displayPreorder(BSTtreeNode* head);
    void displayPostorder(BSTtreeNode* head);
    void displayInorder(BSTtreeNode* head);

private:
    default_random_engine generator;
};

bool mejn();

BSTtreeNode::BSTtreeNode(int element) {
    this->element = element;
    this->leftChild = nullptr;
    this->rightChild = nullptr;
}

BSTtree::BSTtree() {
    this->head = nullptr;
    this->generator.seed(QTime::currentTime().msec());
}

bool BSTtree::addNode(int element) {
    if (this->head == nullptr) {
        this->head = new BSTtreeNode(element);
        return true;
    }

    BSTtreeNode* temp = this->head;
    BSTtreeNode* prev = nullptr;

    while (temp != nullptr) {
        prev = temp;
        if (temp->element == element)
            return false;
        else if (temp->element > element)
            temp = temp->leftChild;
        else if (temp->element < element)
            temp = temp->rightChild;
    }

    if (prev->element > element)
        prev->leftChild = new BSTtreeNode(element);
    else
        prev->rightChild = new BSTtreeNode(element);
    return true;
}

void BSTtree::addRandom(int amount) {
    uniform_int_distribution<int> distribution(-100, 100);
    for (int i = 0; i < amount; i++)
        if (!addNode(distribution(generator)))
            i--;
}

BSTtreeNode* BSTtree::findNode(int element) {
    BSTtreeNode* temp = head;

    while (temp != nullptr && temp->element != element)
 
        if (temp->element > element)
            temp = temp->leftChild;
        else (temp->element < element)
            temp = temp->rightChild;

    return temp;
}

bool BSTtree::removeNode(int element) {
    BSTtreeNode* prevNode = nullptr;
    BSTtreeNode* temp = head;

    while (temp != nullptr) {
        if (head == nullptr)
            return false;
        else if (temp->element == element) {
            if (temp->leftChild == nullptr && temp->rightChild == nullptr) {
                delete temp;
                return true;
            }
            else if (temp->leftChild == nullptr) {
                if (temp == head) {
                    head = head->rightChild;
                    delete temp;
                    return true;
                }
                if (prevNode->leftChild == temp)
                    prevNode->leftChild = temp->rightChild;
                else
                    prevNode->rightChild = temp->rightChild;
                delete temp;
                return true;
            }
            else if (temp->rightChild == nullptr) {
                if (temp == head) {
                    head = head->leftChild;
                    delete temp;
                    return true;
                }
                if (prevNode->leftChild == temp)
                    prevNode->leftChild = temp->leftChild;
                else
                    prevNode->rightChild = temp->leftChild;
                delete temp;
                return true;
            }
            else {
                BSTtreeNode* prev = temp;
                BSTtreeNode* temp1 = temp->leftChild;

                while (temp1->rightChild != nullptr) {
                    prev = temp1;
                    temp1 = temp1->rightChild;
                }

                BSTtreeNode* predecesor = nullptr;
                if (prev == temp) {
                    predecesor = prev->leftChild;
                    temp->element = predecesor->element;
                    strcpy(temp->tab, predecesor->tab);
                    prev->leftChild = predecesor->leftChild;
                    delete predecesor;
                    return true;
                }
                else {
                    predecesor = prev->rightChild;
                    if (predecesor->leftChild == nullptr) {
                        temp->element = predecesor->element;
                        strcpy(temp->tab, predecesor->tab);
                        prev->rightChild = nullptr;
                        delete predecesor;
                        return true;
                    }
                    else {
                        temp->element = predecesor->element;
                        strcpy(temp->tab, predecesor->tab);
                        prev->rightChild = predecesor->leftChild;
                        delete predecesor;
                        return true;
                    }
                }
            }
        }
        else if (temp->element > element) {
            prevNode = temp;
            temp = temp->leftChild;
        }
        else if (temp->element < element) {
            prevNode = temp;
            temp = temp->rightChild;
        }
    }

    return false;
}

void BSTtree::displayPreorder(BSTtreeNode* node1) {
    int counter = -1;

    function<void(BSTtreeNode*)> recursive = [&](BSTtreeNode* node)->void {
        if (!node)
            return;

        counter++;
        printf("%d ", node->element);
        recursive(node->leftChild);
        recursive(node->rightChild);
    };

    recursive(node1);
    qDebug() << "\nLiczba odwiedzonych wezlow: " << counter << "\n";
}

void BSTtree::displayPostorder(BSTtreeNode* node1) {
    int counter = -1;

    function<void(BSTtreeNode*)> recursive = [&](BSTtreeNode* node)->void {
        if (!node)
            return;

        counter++;
        recursive(node->leftChild);
        recursive(node->rightChild);
        printf("%d ", node->element);
    };

    recursive(node1);
    qDebug() << "\nLiczba odwiedzonych wezlow:" << counter << "\n";
}

void BSTtree::displayInorder(BSTtreeNode* node1) {
    int counter = -1;

    function<void(BSTtreeNode*)> recursive = [&](BSTtreeNode* node)->void {
        if (!node)
            return;

        counter++;
        recursive(node->leftChild);
        printf("%d ", node->element);
        recursive(node->rightChild);
    };

    recursive(node1);
    qDebug() << "\nLiczba odwiedzonych wezlow:" << counter << "\n";
}



bool mejn() {
    QTime t;
    int X, k1, k2, k3, k4;

    FILE* fp = fopen("BSTDrzewo.txt", "r");
    if (!fp)
        return false;

    fscanf(fp, "%d %d %d %d %d", &X, &k1, &k2, &k3, &k4);
    fclose(fp);

    t.start();
    BSTtree* tree = new BSTtree();
    tree->removeNode(k1);
    tree->addNode(k1);
    tree->addRandom(X);
    tree->displayInorder(tree->head);
    tree->displayPreorder(tree->head);
    tree->addNode(k2);
    tree->displayInorder(tree->head);
    tree->addNode(k3);
    tree->addNode(k4);
    tree->removeNode(k1);
    tree->displayPreorder(tree->head);
    tree->findNode(k1);
    tree->removeNode(k2);
    tree->displayInorder(tree->head);
    tree->removeNode(k3);
    tree->removeNode(k4);

    printf("Uplynelo: ", t.elapsed(), "[ms]");
    return true;
}
