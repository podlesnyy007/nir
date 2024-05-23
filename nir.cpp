#include <iostream>
#include <queue>
#include <chrono>
#include <string>
using namespace std;

// Реализация очереди на основе массива
template <typename T>
class ArrayQueue {
private:
    T* data;         // массив для хранения данных
    int front;       // индекс переднего элемента
    int rear;        // индекс заднего элемента
    int capacity;    // емкость очереди
    int count;       // количество элементов в очереди

    // Увеличение размера массива при необходимости
    void resize() {
        capacity *= 2;
        T* newData = new T[capacity];
        for (int i = 0; i < count; ++i) {
            newData[i] = data[(front + i) % capacity];
        }
        delete[] data;
        data = newData;
        front = 0;
        rear = count;
    }

public:
    // Конструктор с начальным размером массива
    ArrayQueue(int size = 100) : front(0), rear(0), capacity(size), count(0) {
        data = new T[capacity];
    }

    // Деструктор для освобождения памяти
    ~ArrayQueue() {
        delete[] data;
    }

    // Добавление элемента в очередь
    void enqueue(const T& value) {
        if (count == capacity) {
            resize();
        }
        data[rear] = value;
        rear = (rear + 1) % capacity;
        ++count;
    }

    // Удаление элемента из очереди
    void dequeue() {
        if (count > 0) {
            front = (front + 1) % capacity;
            --count;
        }
    }

    // Возвращение переднего элемента
    T& peek() {
        if (count > 0) {
            return data[front];
        }
        throw out_of_range("Queue is empty");
    }

    // Проверка, пуста ли очередь
    bool isEmpty() const {
        return count == 0;
    }
};

// Реализация очереди на основе связанного списка
template <typename T>
class ListQueue {
private:
    // Узел связанного списка
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };
    Node* front; // указатель на передний элемент
    Node* rear;  // указатель на задний элемент

public:
    // Конструктор
    ListQueue() : front(nullptr), rear(nullptr) {}

    // Деструктор для освобождения памяти
    ~ListQueue() {
        while (front != nullptr) {
            dequeue();
        }
    }

    // Добавление элемента в очередь
    void enqueue(const T& value) {
        Node* newNode = new Node(value);
        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    // Удаление элемента из очереди
    void dequeue() {
        if (front != nullptr) {
            Node* temp = front;
            front = front->next;
            if (front == nullptr) {
                rear = nullptr;
            }
            delete temp;
        }
    }

    // Возвращение переднего элемента
    T& peek() {
        if (front != nullptr) {
            return front->data;
        }
        throw out_of_range("Queue is empty");
    }

    // Проверка, пуста ли очередь
    bool isEmpty() const {
        return front == nullptr;
    }
};

// Функция для тестирования очереди
template <typename QueueType, typename T>
void testQueue(QueueType& queue, const T& sampleValue) {
    auto start = chrono::high_resolution_clock::now();

    // Операции добавления
    for (int i = 0; i < 100000; ++i) {
        queue.push(sampleValue);
    }

    // Операции удаления
    for (int i = 0; i < 100000; ++i) {
        queue.pop();
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "Duration: " << duration.count() << " seconds" << endl;
}

// Тестирование производительности. Функция измеряет время
template <typename T>
void testQueue(ArrayQueue<T>& queue, const T& sampleValue) {
    auto start = chrono::high_resolution_clock::now();

    // Операции добавления
    for (int i = 0; i < 100000; ++i) {
        queue.enqueue(sampleValue);
    }

    // Операции удаления
    for (int i = 0; i < 100000; ++i) {
        queue.dequeue();
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "Duration: " << duration.count() << " seconds" << endl;
}

//
template <typename T>
void testQueue(ListQueue<T>& queue, const T& sampleValue) {
    auto start = chrono::high_resolution_clock::now();

    // Операции добавления
    for (int i = 0; i < 100000; ++i) {
        queue.enqueue(sampleValue);
    }

    // Операции удаления
    for (int i = 0; i < 100000; ++i) {
        queue.dequeue();
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "Duration: " << duration.count() << " seconds" << endl;
}

int main() {
    // Тестирование очереди с целыми числами
    ArrayQueue<int> arrayQueueInt;
    ListQueue<int> listQueueInt;
    queue<int> stlQueueInt;

    cout << "ArrayQueue<int>: ";
    testQueue(arrayQueueInt, 42);

    cout << "ListQueue<int>: ";
    testQueue(listQueueInt, 42);

    cout << "STL Queue<int>: ";
    testQueue(stlQueueInt, 42);

    // Тестирование очереди со строками
    ArrayQueue<string> arrayQueueString;
    ListQueue<string> listQueueString;
    queue<string> stlQueueString;

    cout << "ArrayQueue<string>: ";
    testQueue(arrayQueueString, string("test"));

    cout << "ListQueue<string>: ";
    testQueue(listQueueString, string("test"));

    cout << "STL Queue<string>: ";
    testQueue(stlQueueString, string("test"));

    // Тестирование очереди с пользовательским типом данных
    struct CustomType {
        int id;
        string name;
    };

    ArrayQueue<CustomType> arrayQueueCustom;
    ListQueue<CustomType> listQueueCustom;
    queue<CustomType> stlQueueCustom;

    CustomType sampleCustom = {1, "Sample"};

    cout << "ArrayQueue<CustomType>: ";
    testQueue(arrayQueueCustom, sampleCustom);

    cout << "ListQueue<CustomType>: ";
    testQueue(listQueueCustom, sampleCustom);

    cout << "STL Queue<CustomType>: ";
    testQueue(stlQueueCustom, sampleCustom);

    return 0;
}
