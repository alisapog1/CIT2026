#include <iostream>
using namespace std;

struct Node {
    int val;
    int color; // 0 - черный, 1 - красный
    Node *left, *right, *parent;
};

Node *root = NULL;

// Создание нового узла
Node* newNode(int x, Node *p) {
    Node *t = new Node;
    t->val = x;
    t->color = 1; // красный
    t->left = NULL;
    t->right = NULL;
    t->parent = p;
    return t;
}

// Левый поворот
void leftRotate(Node *x) {
    Node *y = x->right;
    x->right = y->left;
    if (y->left) y->left->parent = x;
    y->parent = x->parent;
    if (!x->parent) root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
}

// Правый поворот
void rightRotate(Node *x) {
    Node *y = x->left;
    x->left = y->right;
    if (y->right) y->right->parent = x;
    y->parent = x->parent;
    if (!x->parent) root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->right = x;
    x->parent = y;
}

// Балансировка после вставки
void fixInsert(Node *n) {
    // Случай 1: корень
    if (!n->parent) {
        n->color = 0;
        return;
    }
    // Случай 2: родитель черный
    if (n->parent->color == 0) return;
    
    // Ищем деда и дядю
    Node *p = n->parent;
    Node *g = p->parent;
    Node *u = (p == g->left) ? g->right : g->left;
    
    // Случай 3: дядя красный
    if (u && u->color == 1) {
        p->color = 0;
        u->color = 0;
        g->color = 1;
        fixInsert(g);
        return;
    }
    
    // Случай 4: зигзаг
    if (n == p->right && p == g->left) {
        leftRotate(p);
        n = n->left;
    }
    else if (n == p->left && p == g->right) {
        rightRotate(p);
        n = n->right;
    }
    
    // Случай 5: прямая линия
    p = n->parent;
    g = p->parent;
    p->color = 0;
    g->color = 1;
    if (n == p->left && p == g->left) rightRotate(g);
    else leftRotate(g);
}

// Вставка
void insert(int x) {
    if (!root) {
        root = newNode(x, NULL);
        root->color = 0;
        return;
    }
    
    Node *cur = root;
    Node *parent = NULL;
    
    while (cur) {
        parent = cur;
        if (x < cur->val) cur = cur->left;
        else if (x > cur->val) cur = cur->right;
        else return;
    }
    
    Node *t = newNode(x, parent);
    if (x < parent->val) parent->left = t;
    else parent->right = t;
    
    fixInsert(t);
}

// Поиск узла
Node* find(int x) {
    Node *cur = root;
    while (cur) {
        if (x == cur->val) return cur;
        if (x < cur->val) cur = cur->left;
        else cur = cur->right;
    }
    return NULL;
}

// Поиск минимального в поддереве
Node* minNode(Node *n) {
    while (n && n->left) n = n->left;
    return n;
}

// Замена узлов
void replace(Node *u, Node *v) {
    if (!u->parent) root = v;
    else if (u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;
    if (v) v->parent = u->parent;
}

// Балансировка после удаления
void fixDelete(Node *n) {
    if (!n->parent) return;
    
    Node *s = (n == n->parent->left) ? n->parent->right : n->parent->left;
    
    // Случай 2: брат красный
    if (s && s->color == 1) {
        n->parent->color = 1;
        s->color = 0;
        if (n == n->parent->left) leftRotate(n->parent);
        else rightRotate(n->parent);
        s = (n == n->parent->left) ? n->parent->right : n->parent->left;
    }
    
    // Случай 3 и 4
    Node *sl = s ? s->left : NULL;
    Node *sr = s ? s->right : NULL;
    
    if ((!sl || sl->color == 0) && (!sr || sr->color == 0)) {
        s->color = 1;
        if (n->parent->color == 1) {
            n->parent->color = 0;
            return;
        }
        fixDelete(n->parent);
        return;
    }
    
    // Случай 5
    if (n == n->parent->left && sl && sl->color == 1 && (!sr || sr->color == 0)) {
        s->color = 1;
        sl->color = 0;
        rightRotate(s);
    }
    else if (n == n->parent->right && sr && sr->color == 1 && (!sl || sl->color == 0)) {
        s->color = 1;
        sr->color = 0;
        leftRotate(s);
    }
    
    // Случай 6
    s = (n == n->parent->left) ? n->parent->right : n->parent->left;
    sl = s ? s->left : NULL;
    sr = s ? s->right : NULL;
    
    s->color = n->parent->color;
    n->parent->color = 0;
    if (n == n->parent->left) {
        if (sr) sr->color = 0;
        leftRotate(n->parent);
    } else {
        if (sl) sl->color = 0;
        rightRotate(n->parent);
    }
}

// Удаление
void deleteNode(int x) {
    Node *n = find(x);
    if (!n) return;
    
    // Два ребенка
    if (n->left && n->right) {
        Node *m = minNode(n->right);
        n->val = m->val;
        deleteNode(m->val);
        return;
    }
    
    // Один ребенок
    Node *ch = n->left ? n->left : n->right;
    
    if (ch) {
        replace(n, ch);
        if (n->color == 0) {
            if (ch->color == 1) ch->color = 0;
            else fixDelete(ch);
        }
        delete n;
    }
    // Нет детей
    else {
        if (n->color == 0) fixDelete(n);
        replace(n, NULL);
        delete n;
    }
}

// Симметричный обход
void inorder(Node *n) {
    if (!n) return;
    inorder(n->left);
    cout << n->val << (n->color ? "(К)" : "(Ч)") << " ";
    inorder(n->right);
}

// Печать по уровням (с очередью)
void printByLevels() {
    if (!root) {
        cout << "Дерево пусто" << endl;
        return;
    }
    
    Node *q[100];
    int head = 0, tail = 0;
    q[tail++] = root;
    int level = 0;
    
    while (head < tail) {
        int size = tail - head;
        cout << "Уровень " << level << ": ";
        
        for (int i = 0; i < size; i++) {
            Node *cur = q[head++];
            cout << cur->val << (cur->color ? "(К)" : "(Ч)") << " ";
            if (cur->left) q[tail++] = cur->left;
            if (cur->right) q[tail++] = cur->right;
        }
        cout << endl;
        level++;
    }
}

// Создание дерева из массива
void createTree(int arr[], int n) {
    root = NULL;
    for (int i = 0; i < n; i++) {
        insert(arr[i]);
    }
}

int main() {
    int choice, x, n;
    int arr[100];
    
    do {
        cout << "\n1-создать 2-вставить 3-удалить 4-обход 5-по уровням 0-выход: ";
        cin >> choice;
        
        if (choice == 1) {
            cout << "Сколько чисел? ";
            cin >> n;
            cout << "Введите числа: ";
            for (int i = 0; i < n; i++) cin >> arr[i];
            createTree(arr, n);
            printByLevels();
        }
        else if (choice == 2) {
            cout << "Что вставить? ";
            cin >> x;
            insert(x);
            printByLevels();
        }
        else if (choice == 3) {
            cout << "Что удалить? ";
            cin >> x;
            deleteNode(x);
            printByLevels();
        }
        else if (choice == 4) {
            inorder(root);
            cout << endl;
        }
        else if (choice == 5) {
            printByLevels();
        }
    } while (choice != 0);
    
    return 0;
}