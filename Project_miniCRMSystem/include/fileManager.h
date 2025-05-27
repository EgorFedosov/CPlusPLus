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
 * @brief Очищает бинарный файл клиентов.
 *
 * Безвозвратно очищает содержимое файла clients.bin после проверки:
 * - Файл открыт успешно
 * - Файл не пуст
 */
void removeClients();

#endif