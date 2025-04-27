#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "client.h"

/**
 * @brief Сохраняет клиента в бинарный файл.
 *
 * Записывает структуру Client в конец файла clients.bin.
 * Если файл не существует - создает новый.
 *
 * @param client Константная ссылка на структуру клиента.
 */
void saveToBinaryFile(const Client &client);

/**
 * @brief Выводит содержимое бинарного файла.
 *
 * Считывает всех клиентов из файла clients.bin и выводит их
 * с помощью функции printClient(). Автоматически проверяет:
 * - Существование файла
 * - Наличие записей в файле
 */
void displayBinaryFile();

/**
 * @brief Удаляет бинарный файл клиентов.
 *
 * Безвозвратно удаляет файл clients.bin после проверки:
 * - Существования файла
 * - Наличия данных в файле
 */
void removeBinaryFile();

#endif 