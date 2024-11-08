#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* root = NULL;

struct Node* CreateTree(struct Node* root, int data) {
    if (root == NULL) {
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        if (newNode == NULL) {
            printf("Ошибка выделения памяти");
            exit(0);
        }

        newNode->left = NULL;
        newNode->right = NULL;
        newNode->data = data;
        return newNode;
    }

    if (data < root->data) {
        root->left = CreateTree(root->left, data); // Вставляем в левое поддерево
    }
    else if (data > root->data) {
        root->right = CreateTree(root->right, data); // Вставляем в правое поддерево
    }
    else {
        printf("Элемент %d уже существует. Он не будет добавлен.\n", data);
    }

    return root;
}

void print_tree(struct Node* r, int l) {
    if (r == NULL) {
        return;
    }

    print_tree(r->right, l + 1);
    for (int i = 0; i < l; i++) {
        printf(" ");
    }

    printf("%d\n", r->data); // Выводим узел
    print_tree(r->left, l + 1);
}

struct Node* find(struct Node* root, int data) {
    if (root == NULL) return NULL; // Проверка на NULL

    if (root->data == data) return root; // Если нашли элемент, возвращаем его
    if (data < root->data) return find(root->left, data); // Ищем в левом поддереве
    return find(root->right, data); // Ищем в правом поддереве
}

int count(struct Node* root, int data) {
    if (root == NULL) return 0;

    if (root->data == data) {
        return 1 + count(root->left, data) + count(root->right, data);
    }
    return count(root->left, data) + count(root->right, data);
}

int main() {
    setlocale(LC_ALL, "Rus");
    int D, start = 1;

    printf("-1 - окончание построения дерева\n");
    while (start) {
        printf("Введите число: ");
        scanf("%d", &D);
        if (D == -1) {
            printf("Построение дерева окончено\n\n");
            start = 0;
        }
        else {
            root = CreateTree(root, D);
        }
    }

    print_tree(root, 0);
    int num;
    printf("Введите элемент для поиска: ");
    scanf("%d", &num);
    struct Node* r = find(root, num);
    if (r) {
        printf("Элемент найден: %d\n", r->data);
    }
    else {
        printf("Элемент не найден\n");
    }

    int cnt = count(root, num);
    printf("Элементов %d найдено: %d\n", num, cnt);

    scanf("%d", &D);
    return 0;
}