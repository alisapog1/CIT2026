#include <iostream>
using namespace std;

// структура двусвязного списка
struct Node {
    int data;
    Node* next;
    Node* prev;
};

// вставка в конец (для создания списка)
void pushBack(Node*& head, Node*& tail, int val) {
    Node* newNode = new Node;
    newNode->data = val;
    newNode->next = NULL;
    newNode->prev = tail;
    
    if (tail != NULL) tail->next = newNode;
    else head = newNode;
    
    tail = newNode;
}

// удаление всего списка
void clearList(Node*& head) {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    Node* head = NULL;
    Node* tail = NULL;
    
    // ввод данных
    int n;
    cout << "Введите количество элементов: ";
    cin >> n;
    cout << "Введите " << n << " чисел: ";
    
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        pushBack(head, tail, x);
    }
    
    if (!head) {
        cout << "Список пуст" << endl;
        return 0;
    }
    
    // находим первое число
    int firstVal = head->data;
    
    // находим максимальное число
    int maxVal = head->data;
    Node* curr = head->next;
    while (curr) {
        if (curr->data > maxVal) maxVal = curr->data;
        curr = curr->next;
    }
    
    // вставляем после каждого элемента, равного первому
    curr = head;
    while (curr) {
        if (curr->data == firstVal) {
            // создаем новый узел
            Node* newNode = new Node;
            newNode->data = maxVal;
            newNode->next = curr->next;
            newNode->prev = curr;
            
            // связываем с правым соседом
            if (curr->next) curr->next->prev = newNode;
            else tail = newNode; // если вставляем в конец, обновляем хвост
            
            // связываем с левым соседом (текущим)
            curr->next = newNode;
            
            // сдвигаем текущий на вставленный элемент, чтобы не зациклиться
            curr = newNode;
        }
        curr = curr->next;
    }
    
    // вывод результата
    cout << "Результат: ";
    curr = head;
    while (curr) {
        cout << curr->data << " ";
        curr = curr->next;
    }
    cout << endl;
    
    clearList(head);
    return 0;
}