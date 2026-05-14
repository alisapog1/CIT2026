#include <iostream>
#include <cmath>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;
};

void pushBack(Node*& head, Node*& tail, int val) {
    Node* newNode = new Node;
    newNode->data = val;
    newNode->next = NULL;
    newNode->prev = tail;
    
    if (tail) tail->next = newNode;
    else head = newNode;
    
    tail = newNode;
}

void clearList(Node*& head) {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

// проверка на простое число
bool isPrime(int n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

int main() {
    Node* head = NULL;
    Node* tail = NULL;
    
    int n;
    cout << "Введите количество элементов: ";
    cin >> n;
    cout << "Введите " << n << " чисел: ";
    
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        pushBack(head, tail, x);
    }
    
    // ищем первое составное число (не простое и не 1)
    Node* target = NULL;
    Node* curr = head;
    while (curr) {
        if (!isPrime(curr->data) && curr->data != 1) {
            target = curr;
            break;
        }
        curr = curr->next;
    }
    
    if (!target) {
        cout << "Составных чисел нет!" << endl;
        clearList(head);
        return 0;
    }
    
    // делаем target головой (циклический сдвиг)
    Node* newHead = target;
    Node* newTail = target->prev;
    if (newTail) newTail->next = NULL;
    
    // находим старый хвост
    Node* oldTail = tail;
    oldTail->next = head;
    head->prev = oldTail;
    
    // разрываем перед target
    if (target->prev) target->prev->next = NULL;
    target->prev = NULL;
    
    // вывод
    cout << "Результат: ";
    curr = newHead;
    while (curr) {
        cout << curr->data << " ";
        curr = curr->next;
    }
    cout << endl;
    
    clearList(newHead);
    return 0;
}