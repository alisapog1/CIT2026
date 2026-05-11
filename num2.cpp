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
// Инициализация: голова и хвост = NULL

bool isEmpty(Queue& q) {
    return q.head == NULL;
}
// Проверка на пустоту

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
// Добавление в конец очереди

int pop(Queue& q) {
    Node* temp = q.head;
    int value = temp->data;
    q.head = q.head->next;
    if (q.head == NULL) q.tail = NULL;
    delete temp;
    return value;
}
// Удаление из начала очереди

void clearQueue(Queue& q) {
    while (!isEmpty(q)) pop(q);
}
// Очистка очереди

// основная функция
int main() {
    Queue original;
    initQueue(original);
    // Создали и инициализировали очередь

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
    // Все числа добавлены

    // первый проход: ищем первый чётный 
    Queue temp;
    initQueue(temp);
    // Временная очередь
    
    int steps = 0;
    bool found = false;
    // steps - сколько элементов было до первого чётного
    // found - нашли ли уже первый чётный
    
    while (!isEmpty(original)) {
        int val = pop(original);
        // Забираем первый элемент из original
        
        if (!found && val % 2 == 0) {
            // Это первый чётный элемент
            push(temp, val);
            found = true;
            // Кладём его в temp, он станет первым
        } else {
            push(temp, val);
            if (!found) steps++;
            // Если ещё не нашли чётный — увеличиваем счётчик steps
        }
    }
    // Теперь в temp: [первый чётный, остальные элементы...]
    // original пуст
    
    // проверка на четность
    if (!found) {
        cout << "Нет чётных элементов!" << endl;
        clearQueue(original);
        clearQueue(temp);
        return 0;
    }
    
    // циклический сдвиг
    for (int i = 0; i < steps; i++) {
        int val = pop(temp);
        push(temp, val);
        // Берём первые steps элементов и перекладываем их в конец
    }
    // Теперь очередь начинается с первого чётного
    
    // вывод результата
    cout << "\nРезультат: ";
    while (!isEmpty(temp)) {
        cout << pop(temp) << " ";
    }
    cout << endl;
    // Выводим результат
    
    // очистка памяти
    clearQueue(original);
    
    return 0;
}