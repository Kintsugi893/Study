#include <iostream>

// Структура для представления узла списка
struct Node {
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}
};

// Функция для ввода последовательности и создания списка
Node* inputSequence() {
    Node* head = nullptr;
    Node* tail = nullptr;

    std::cout << "Введите последовательность натуральных чисел (введите 0 для завершения ввода): ";
    int value;
    while (true) {
        std::cin >> value;
        if (value == 0) {
            break;
        }

        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    return head;
}

// Функция для проверки упорядоченности списка по неубыванию или по невозрастанию
bool isOrdered(Node* head, bool increasing) {
    while (head != nullptr && head->next != nullptr) {
        if ((increasing && head->data > head->next->data) || (!increasing && head->data < head->next->data)) {
            return false;
        }
        head = head->next;
    }
    return true;
}

// Функция для удаления чисел, в которые входят цифры 2 и 8
void removeNumbers(Node*& head) {
    Node* current = head;
    Node* prev = nullptr;

    while (current != nullptr) {
        int number = current->data;

        if (number % 10 == 5) {
            // Дублирование чисел, заканчивающихся цифрой 5
            Node* duplicate = new Node(number);
            duplicate->next = current->next;
            current->next = duplicate;
            current = duplicate->next;
        }
        else if ((number % 10 == 2 || number % 10 == 8) && number >= 10) {
            // Удаление чисел, в которые входят цифры 2 и 8
            if (prev == nullptr) {
                head = current->next;
            }
            else {
                prev->next = current->next;
            }
            Node* temp = current;
            current = current->next;
            delete temp;
        }
        else {
            prev = current;
            current = current->next;
        }
    }
}

// Функция для упорядочивания списка по неубыванию
void sortList(Node*& head) {
    if (head == nullptr || head->next == nullptr) {
        return;
    }

    Node* sorted = nullptr;
    Node* current = head;

    while (current != nullptr) {
        Node* nextNode = current->next;

        if (sorted == nullptr || sorted->data >= current->data) {
            current->next = sorted;
            sorted = current;
        }
        else {
            Node* temp = sorted;

            while (temp->next != nullptr && temp->next->data < current->data) {
                temp = temp->next;
            }

            current->next = temp->next;
            temp->next = current;
        }

        current = nextNode;
    }

    head = sorted;
}

// Функция для вывода списка
void printList(Node* head) {
    while (head != nullptr) {
        std::cout << head->data << " ";
        head = head->next;
    }
    std::cout << std::endl;
}

// Основная функция
int main() {
    setlocale(LC_ALL, "ru");
    Node* sequence = inputSequence();

    if (isOrdered(sequence, true) || isOrdered(sequence, false)) {
        removeNumbers(sequence);
    }
    else {
        sortList(sequence);
    }

    std::cout << "Результат: ";
    printList(sequence);

    // Освобождаем память
    Node* current = sequence;
    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }

    return 0;
}

