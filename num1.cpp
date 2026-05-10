#include <iostream>
using namespace std;

// структуры
struct Node {
    int data;
    Node* next;
};

struct Queue {
    Node* head;
    Node* tail;
};

// базовые функции
void initQueue(Queue& q) {
    q.head = NULL;
    q.tail = NULL;
}
// Инициализация: голова и хвост = NULL (очередь пуста)

bool isEmpty(Queue& q) {
    return q.head == NULL;
}
// Проверка: пуста ли очередь

void push(Queue& q, int x) {
    Node* newNode = new Node;
    newNode->data = x;
    newNode->next = NULL;
    if (isEmpty(q)) {
        q.head = newNode;
        q.tail = newNode;
    } else {
        q.tail->next = newNode;
        q.tail = newNode;
    }
}
// Добавление элемента в конец очереди

int pop(Queue& q) {
    Node* temp = q.head;
    int value = temp->data;
    q.head = q.head->next;
    if (q.head == NULL) q.tail = NULL;
    delete temp;
    return value;
}
// Удаление элемента из начала очереди, возвращаем его значение

void clearQueue(Queue& q) {
    while (!isEmpty(q)) pop(q);
}
// Очистка всей очереди (освобождение памяти)

// основная функция
int main() {
    Queue original;
    initQueue(original);
    // Создали и инициализировали исходную очередь

    // ввод данных 
    cout << "Введите количество элементов: ";
    int n;
    cin >> n;
    cout << "Введите " << n << " целых чисел через пробел: ";
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        push(original, x);
    }
    // Все числа добавлены в очередь

    // первый проход: находим максимум и последний нечётный 
    int maxVal = -1e9;
    int lastOdd = -1;
    
    Queue temp1;
    initQueue(temp1);
    // Создаём временную очередь для хранения элементов
    
    while (!isEmpty(original)) {
        int val = pop(original);
        push(temp1, val);
        // Перекладываем элемент из original в temp1
        
        if (val > maxVal) maxVal = val;
        // Обновляем максимум
        
        if (val % 2 != 0) lastOdd = val;
        // Обновляем последний нечётный
    }
    // Теперь в temp1 лежат все элементы, original пуст
    
    while (!isEmpty(temp1)) {
        push(original, pop(temp1));
    }
    // Возвращаем элементы обратно в original
    // Теперь original снова полный, а temp1 пуст
    
    // проверка на четность
    if (lastOdd == -1) {
        cout << "Нет нечётных элементов!" << endl;
        clearQueue(original);
        return 0;
    }
    // Если нет нечётных — выходим
    
    // второй проход: формируем результат 
    Queue result;
    initQueue(result);
    // Создаём очередь для результата
    
    while (!isEmpty(original)) {
        int val = pop(original);
        push(result, val);
        // Кладём элемент в результат
        
        if (val == maxVal) {
            push(result, lastOdd);
            // Если это максимум — добавляем после него последний нечётный
        }
    }
    // Теперь в result готовая очередь
    
    // вывод результата
    cout << "\nРезультат: ";
    while (!isEmpty(result)) {
        cout << pop(result) << " ";
    }
    cout << endl;
    // Выводим и очищаем result
    
    // очистка памяти
    clearQueue(original);
    clearQueue(temp1);
    
    return 0;
}