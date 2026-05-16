#include <iostream>
using namespace std;

// свой стек для пути, потому что библиотеки использовать нельзя
struct stack {
    int x;
    int y;
    stack* next;
};

// положить клетку в стек
void push(stack*& top, int x, int y) {
    stack* p = new stack;
    p->x = x;
    p->y = y;
    p->next = top;
    top = p;
}

// достать клетку из стека
int pop(stack*& top, int& x, int& y) {
    if (top == NULL) {
        return 0; // стек пустой
    }
    stack* p = top;
    x = top->x;
    y = top->y;
    top = top->next;
    delete p;
    return 1; // успешно достали
}

// букву в число (A=0, B=1, ..., H=7)
int bukva_v_chislo(char c) {
    return c - 'A';
}

// число в букву (0=A, 1=B, ...)
char chislo_v_bukvu(int n) {
    return 'A' + n;
}

// проверка, что клетка на доске (не вылезла за границы)
int norm_kletka(int x, int y) {
    if (x >= 0 && x < 8 && y >= 0 && y < 8) {
        return 1;
    }
    return 0;
}

// возможные ходы коня: (dx, dy) на 8 клеток
int sdvig_x[8] = {2, 2, -2, -2, 1, 1, -1, -1};
int sdvig_y[8] = {1, -1, 1, -1, 2, -2, 2, -2};

// рекурсивный поиск пути
// возвращает 1 если нашел путь, 0 если нет
int poisk(int x1, int y1, int x2, int y2, int vidjeno[8][8], stack*& put) {
    // если дошли до цели
    if (x1 == x2 && y1 == y2) {
        push(put, x1, y1); // запоминаем клетку
        return 1;
    }
    
    // помечаем текущую клетку как посещенную, чтобы не ходить по кругу
    vidjeno[x1][y1] = 1;
    
    // пробуем все 8 ходов коня
    for (int i = 0; i < 8; i++) {
        int nov_x = x1 + sdvig_x[i];
        int nov_y = y1 + sdvig_y[i];
        
        // если новая клетка на доске и еще не были там
        if (norm_kletka(nov_x, nov_y) && vidjeno[nov_x][nov_y] == 0) {
            if (poisk(nov_x, nov_y, x2, y2, vidjeno, put)) {
                push(put, x1, y1); // нашли путь, запоминаем клетку
                return 1;
            }
        }
    }
    
    return 0; // ни один ход не привел к цели
}

int main() {
    char bukva1, bukva2;
    int cifra1, cifra2;
    int x1, y1, x2, y2;
    
    // вводим начальную клетку
    cout << "Vvedite nachalnuyu kletku (naprimer A2): ";
    cin >> bukva1 >> cifra1;
    
    // вводим конечную клетку
    cout << "Vvedite konechnuyu kletku (naprimer E6): ";
    cin >> bukva2 >> cifra2;
    
    // переводим в координаты
    x1 = bukva_v_chislo(bukva1);
    x2 = bukva_v_chislo(bukva2);
    y1 = cifra1 - 1; // в шахматах цифры от 1 до 8, а нам нужны 0..7
    y2 = cifra2 - 1;
    
    // проверяем, что клетки вообще существуют
    if (norm_kletka(x1, y1) == 0 || norm_kletka(x2, y2) == 0) {
        cout << "Nevernie koordinati" << endl;
        return 1;
    }
    
    // массив для посещенных клеток (0 - не были, 1 - были)
    int posetili[8][8];
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            posetili[i][j] = 0;
        }
    }
    
    // стек для пути
    stack* put = NULL;
    
    // ищем путь
    if (poisk(x1, y1, x2, y2, posetili, put)) {
        cout << "Put: ";
        int x, y;
        // достаем из стека и выводим
        // стек хранит путь в обратном порядке (от конца к началу)
        // поэтому просто вытаскиваем все и печатаем
        while (pop(put, x, y)) {
            cout << chislo_v_bukvu(x) << y + 1 << " ";
        }
        cout << endl;
    } else {
        cout << "Put ne naiden" << endl;
    }
    
    return 0;
}