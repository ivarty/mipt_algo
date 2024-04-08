### Задание: Собственный аналог библиотеки функций для работы с C-style строками

C-style строкой называется последовательность байт (char), ограниченная нулевым символом ('\0'). Работа с C-style строками аналогична работе с массивами, однако специфичные операции (вычисление длины, конкатенация, сравнение и т.п.) вынесены в отдельную библиотеку функций `<cstring>`.

В этом задании ваша задача - реализовать собственный аналог библиотеки функций для работы с C-style строками.

Ваша библиотека должна включать следующие функции:
- `strlen`: вычисляет длину строки.
- `strcpy`: копирует строку из одной переменной в другую.
- `strcat`: конкатенирует две строки.
- `strcmp`: сравнивает две строки лексикографически.
- `strchr`: находит первое вхождение символа в строке.
- `strstr`: находит первое вхождение подстроки в строке.