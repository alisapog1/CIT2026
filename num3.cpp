#include <iostream>
using namespace std;

// структуры
struct Node {
    int data;
    Node* next;
};

struct Stack {
    Node* head;
};

// базовые функции
void initStack(Stack& s) {
    s.head = NULL;
}
// Инициализация: вершина = NULL (стек пуст)

bool isEmpty(Stack& s) {
    return s.head == NULL;
}
// Проверка на пустоту

void push(Stack& s, int x) {
    Node* newNode = new Node;
    newNode->data = x;
    newNode->next = s.head;
    s.head = newNode;
}
// Добавление на вершину стека

int pop(Stack& s) {
    Node* temp = s.head;
    int value = temp->data;
    s.head = s.head->next;
    delete temp;
    return value;
}
// Удаление с вершины стека

void clearStack(Stack& s) {
    while (!isEmpty(s)) pop(s);
}
// Очистка стека

// основная функция
int main() {
    Stack original;
    initStack(original);
    // Создали и инициализировали стек
    
    Stack tempInput;
    initStack(tempInput);
    // Временный стек для ввода
    
    // ввод данных
    cout << "Введите количество элементов: ";
    int n;
    cin >> n;
    cout << "Введите " << n << " целых чисел через пробел: ";
    
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        push(tempInput, x);
    }
    // Сначала кладём во временный стек (они лягут в обратном порядке)
    
    while (!isEmpty(tempInput)) {
        push(original, pop(tempInput));
    }
    // Переворачиваем: теперь первый введённый элемент внизу, последний - наверху
    clearStack(tempInput);
    
    // первый проход: находим последний чётный
    Stack temp;
    initStack(temp);
    // Временный стек
    
    int lastEven = -1;
    // Будем хранить последний чётный элемент
    
    while (!isEmpty(original)) {
        int val = pop(original);
        push(temp, val);
        // Перекладываем из original в temp
        
        if (val % 2 == 0) lastEven = val;
        // Запоминаем последний встреченный чётный
    }
    // Теперь original пуст, все элементы в temp
    
    while (!isEmpty(temp)) {
        push(original, pop(temp));
    }
    // Возвращаем элементы обратно в original
    // Теперь original снова полный
    
    // проверка на четность
    if (lastEven == -1) {
        cout << "Нет чётных элементов!" << endl;
        clearStack(original);
        return 0;
    }
    
    // ввод нового элемента
    int newElement;
    cout << "Введите элемент для вставки: ";
    cin >> newElement;
    
    // второй результат: формируем результат 
    Stack buffer;
    initStack(buffer);
    // Буферный стек
    
    while (!isEmpty(original)) {
        push(buffer, pop(original));
    }
    // Перекладываем original в buffer (чтобы первый элемент оказался наверху)
    
    Stack result;
    initStack(result);
    // Стек для результата
    
    while (!isEmpty(buffer)) {
        int val = pop(buffer);
        push(result, val);
        // Кладём элемент в результат
        
        if (val == lastEven) {
            push(result, newElement);
            // Если это последний чётный - после него вставляем новый элемент
        }
    }
    // Теперь в result стек, но порядок обратный
    
    // переворачиваем результат
    Stack final;
    initStack(final);
    
    while (!isEmpty(result)) {
        push(final, pop(result));
    }
    // Переворачиваем, чтобы порядок стал правильным
    
    // вывод результата
    cout << "Результат: ";
    while (!isEmpty(final)) {
        cout << pop(final) << " ";
    }
    cout << endl;
    
    // очистка памяти
    clearStack(original);
    clearStack(temp);
    clearStack(result);
    clearStack(final);
    clearStack(buffer);
    
    return 0;
}