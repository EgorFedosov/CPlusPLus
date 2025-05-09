#ifndef SORTALGORITHM_H
#define SORTALGORITHM_H

#include "client.h"

/**
 * @brief Быстрая сортировка клиентов по названию товара.
 *
 * Реализация алгоритма quick sort с выбором среднего опорного элемента.
 * Сортирует клиентов в лексикографическом порядке по полю product.
 *
 * @param arr Массив структур Client
 * @param left Индекс левой границы сортировки
 * @param right Индекс правой границы сортировки
 */
void sortQuickProduct(Client arr[], int left, int right);

/**
 * @brief Сравнение клиентов по дате покупки.
 *
 * Сравнивает даты в формате ГГГГ > ММ > ДД.
 *
 * @param a Первый клиент для сравнения
 * @param b Второй клиент для сравнения
 * @return
 *   - Отрицательное число: дата a < даты b\n
 *   - Ноль: даты равны\n
 *   - Положительное число: дата a > даты b
 */
int compareDates(Client a, Client b);

/**
 * @brief Сортировка выбором по дате покупки.
 *
 * Сортирует клиентов по возрастанию дат (от старых к новым).
 * Использует compareDates для сравнения элементов.
 *
 * @param arr Массив структур Client
 * @param size Размер массива
 */
void sortSelection(Client arr[], int size);

/**
 * @brief Сортировка вставками по ФИО клиента.
 *
 * Сортирует клиентов в лексикографическом порядке по полю name.
 * Использует my_strcmp для сравнения строк.
 *
 * @param arr Массив структур Client
 * @param size Размер массива
 */
void sortInsertion(Client arr[], int size);

/**
 * @brief Обмен значениями двух переменных.
 *
 * Универсальная функция для обмена любыми типами данных.
 * Используется в алгоритмах сортировки.
 *
 * @tparam T Тип данных элементов
 * @param a Ссылка на первый элемент
 * @param b Ссылка на второй элемент
 */
template <typename T>
void my_swap(T &a, T &b);

#endif