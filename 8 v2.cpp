#include <iostream>

struct Node {
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}
};

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

bool isOrdered(Node* head, bool increasing) {
    while (head != nullptr && head->next != nullptr) {
        if ((increasing && head->data > head->next->data) || (!increasing && head->data < head->next->data)) {
            return false;
        }
        head = head->next;
    }
    return true;
}

void removeNumbersAndDuplicate(Node*& head) {
    Node* current = head;
    Node* prev = nullptr;

    while (current != nullptr) {
        int number = current->data;

        if ((number % 10 == 2 || number % 10 == 8) && (number / 10 % 10 == 2 || number / 10 % 10 == 8)) {
            Node* temp = current;
            if (prev == nullptr) {
                head = current->next;
                current = current->next;
            }
            else {
                prev->next = current->next;
                current = current->next;
            }
            delete temp;
        }
        else if (number % 10 == 5) {
            Node* duplicate = new Node(number);
            duplicate->next = current->next;
            current->next = duplicate;
            current = duplicate->next;
        }
        else {
            prev = current;
            current = current->next;
        }
    }
}

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

void printList(Node* head) {
    while (head != nullptr) {
        std::cout << head->data << " ";
        head = head->next;
    }
    std::cout << std::endl;
}

int main() {
    setlocale(LC_ALL, "ru");
    Node* sequence = inputSequence();

    if (isOrdered(sequence, true) || isOrdered(sequence, false)) {
        removeNumbersAndDuplicate(sequence);
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
