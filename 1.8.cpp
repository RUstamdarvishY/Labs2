
#include <iostream>
#include <chrono>

using namespace std;

int Recursion(int[], int);
int Iteration(int[], int);

int main()
{
    int size, *array, input, result = 0;
    srand(static_cast<unsigned int>(time(0)));
    cout << "Введите размер массива\n";
    cin >> size;
    array = new int[size];
    cout << "Выберите способ заполнения массива:\n1 - ввод с клавиатуры\n2 - случайное число от -10 до 10" << endl;
    cin >> input;
    for (int i = 0; i < size; i++)
    {
        cout << "[" << i << "]: ";
        if (input == 2)
        {
            array[i] = rand() % 21 - 10;
            cout << array[i] << "\n";
        }
        else
            cin >> array[i];
    }
    cout << "\n"
         << "Использовать рекурсивную функцию? (да - 1, нет - 2)\n";
    cin >> input;
    cout << "\n";
    if (input == 1)
    {
        auto t1 = chrono::high_resolution_clock::now();
        result = Recursion(array, size);
        auto t2 = chrono::high_resolution_clock::now();
        chrono::duration<double, std::milli> ms_double = t2 - t1;
        cout << "Затраченое время: " << ms_double.count() << endl;
    }
    else
    {
        auto t1 = chrono::high_resolution_clock::now();
        result = Iteration(array, size);
        auto t2 = chrono::high_resolution_clock::now();
        chrono::duration<double, std::milli> ms_double = t2 - t1;
        cout << "Затраченое время: " << ms_double.count() << endl;
    }
    cout << "Максимальный элемент: " << result << "\n\n";
}

int Recursion(int array[], int count)
{
    return count < 2 ? array[0] : Recursion(array + (array[0] < array[--count]), count);
}

int Iteration(int array[], int count)
{
    int max = 0;
    for (int i = 0; i < count; i++)
        if (array[i] > array[max])
            max = i;
    return array[max];
}