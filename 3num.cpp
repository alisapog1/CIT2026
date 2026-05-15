#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

int main() {
    int N, K;
    cout << "Введите N (количество людей): ";
    cin >> N;
    cout << "Введите K (каждого K-го удаляем): ";
    cin >> K;
    
    if (N <= 0 || K <= 0) {
        cout << "Неверные данные!" << endl;
        return 0;
    }
    
    // создаем кольцевой список
    Node* head = NULL;
    Node* tail = NULL;
    
    for (int i = 1; i <= N; i++) {
        Node* newNode = new Node;
        newNode->data = i;
        newNode->next = NULL;
        
        if (!head) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    // замыкаем кольцо
    tail->next = head;
    
    // удаляем каждый K-ый
    Node* curr = head;
    Node* prev = tail;
    int count = N;
    
    while (count > 1) {
        // делаем K-1 шагов
        for (int i = 1; i < K; i++) {
            prev = curr;
            curr = curr->next;
        }
        // удаляем curr
        prev->next = curr->next;
        cout << "Удален: " << curr->data << endl;
        delete curr;
        curr = prev->next;
        count--;
    }
    
    cout << "Остался: " << curr->data << endl;
    
    // чистим память
    delete curr;
    
    return 0;
}