#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* root = NULL;

struct Node* CreateTree(struct Node* root, struct Node* r, int data) {
    if (r == NULL) {
        r = (struct Node*)malloc(sizeof(struct Node));
        if (r == NULL) {
            printf("Ошибка выделения памяти");
            exit(0);
        }

        r->left = NULL;
        r->right = NULL;
        r->data = data;
        if (root == NULL) return r;

        if (data > root->data) root->left = r;
        else root->right = r;
        return r;
    }

    if (data > r->data)
        CreateTree(r, r->left, data);
    else
        CreateTree(r, r->right, data);

    return root;
}

void print_tree(struct Node* r, int l) {
    if (r == NULL) {
        return;
    }

    print_tree(r->right, l + 1);
    for (int i = 0; i < l; i++) {
        printf("\t");
    }

    printf("%d (уровень: %d)\n", r->data, l); // Выводим уровень узла
    print_tree(r->left, l + 1);
}

void find(struct Node* root, int data, int level, int* levels, int* count) {
    if (root == NULL) return; // Если узел пуст, выходим

    if (root->data == data) {
        levels[*count] = level; // Сохраняем уровень найденного элемента
        (*count)++; // Увеличиваем счетчик найденных элементов
    }

    // Рекурсивно ищем в левом и правом поддеревьях
    find(root->left, data, level + 1, levels, count);
    find(root->right, data, level + 1, levels, count);
}

int countOccurrences(struct Node* root, int data, int cnt) {
    if (root == NULL) return cnt; // Если узел пуст, возвращаем счетчик

    if (root->data == data) cnt++;
    cnt = countOccurrences(root->left, data, cnt);
    cnt = countOccurrences(root->right, data, cnt);
    return cnt;
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
            root = CreateTree(root, root, D);
        }
    }

    print_tree(root, 0);
    int num;
    printf("Введите элемент для поиска: ");
    scanf("%d", &num);

    int levels[100]; // Массив для хранения уровней найденных элементов
    int count = 0; // Счетчик найденных элементов
    find(root, num, 0, levels, &count); // Ищем элементы и их уровни

    if (count > 0) {
        printf("Элемент %d найден на уровнях: ", num);
        for (int i = 0; i < count; i++) {
            printf("%d ", levels[i]);
        }
        printf("\n");
    }
    else {
        printf("Элемент не найден\n");
    }

    int cnt = countOccurrences(root, num, 0);
    printf("Элементов %d найдено: %d\n", num, cnt);

    scanf("%d", &D);
    return 0;
}