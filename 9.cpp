#include <iostream>

// Структура для элемента списка
struct Node {
    int data;
    Node* prev;
    Node* next;

    Node(int val) : data(val), prev(nullptr), next(nullptr) {}
};

// Функция для проверки палиндрома
bool isPalindrome(int num) {
    int originalNum = num;
    int reversedNum = 0;

    while (num > 0) {
        reversedNum = reversedNum * 10 + num % 10;
        num /= 10;
    }

    return originalNum == reversedNum;
}

// Функция для проверки простого числа
bool isPrime(int num) {
    if (num <= 1) {
        return false;
    }

    for (int i = 2; i * i <= num; ++i) {
        if (num % i == 0) {
            return false;
        }
    }

    return true;
}

// Функция для удаления простых чисел и дублирования чисел, заканчивающихся нулем
void processSequence(Node* head) {
    Node* current = head->next;

    // Проверка наличия палиндромов
    bool hasPalindrome = false;

    while (current != head) {
        Node* nextNode = current->next;

        if (isPalindrome(current->data)) {
            hasPalindrome = true;
            break;
        }

        current = nextNode;
    }

    if (!hasPalindrome) {
        current = head->next;

        // Упорядочивание по невозрастанию
        while (current != head) {
            Node* nextNode = current->next;

            while (nextNode != head) {
                if (current->data < nextNode->data) {
                    // Обмен значениями
                    int temp = current->data;
                    current->data = nextNode->data;
                    nextNode->data = temp;
                }

                nextNode = nextNode->next;
            }

            current = current->next;
        }
    }
    else {
        current = head->next;

        while (current != head) {
            Node* nextNode = current->next;

            if (current->data % 10 == 0) {
                // Дублирование чисел, заканчивающихся нулем
                Node* newNode = new Node(current->data);
                newNode->next = current->next;
                newNode->prev = current;
                current->next = newNode;
                nextNode->prev = newNode;
                current = newNode->next;  // Переход к следующему узлу, чтобы пропустить только что вставленный узел
            }
            else {
                bool isPrimeNumber = isPrime(current->data);

                if (isPrimeNumber) {
                    // Удаление простых чисел
                    Node* temp = current;
                    current = nextNode;
                    temp->prev->next = temp->next;
                    temp->next->prev = temp->prev;
                    delete temp;
                }
                else {
                    current = nextNode;
                }
            }
        }
    }
}

int main() {
    setlocale(LC_ALL, "ru");
    // Создание фиктивного элемента
    Node* head = new Node(0);
    head->prev = head;
    head->next = head;

    int n;
    std::cout << "Введите количество элементов: ";
    std::cin >> n;

    std::cout << "Введите последовательность чисел: ";
    for (int i = 0; i < n; ++i) {
        int num;
        std::cin >> num;

        // Добавление элемента в конец списка
        Node* newNode = new Node(num);
        newNode->prev = head->prev;
        newNode->next = head;
        head->prev->next = newNode;
        head->prev = newNode;
    }

    // Обработка последовательности
    processSequence(head);

    // Вывод обработанной последовательности
    std::cout << "Результат: ";
    Node* current = head->next;

    while (current != head) {
        std::cout << current->data << " ";
        current = current->next;
    }

    // Освобождение памяти
    current = head->next;
    while (current != head) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }

    delete head;

    return 0;
}
