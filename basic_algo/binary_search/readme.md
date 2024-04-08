### Задание: Определение трех шаблонных функций для работы с отсортированными последовательностями

Напишите заголовочный файл с определениями трех шаблонных функций для работы с отсортированными последовательностями. Каждая функция принимает три аргумента: 
- `begin`: указатель на начало последовательности,
- `end`: указатель на конец последовательности (элемент следующий за последним),
- `value`: значение запроса.

#### BinarySearch
Функция `BinarySearch` осуществляет проверку наличия элемента `value` в отсортированной последовательности [`begin`, `end`). Возвращает `true`, если и только если на полуинтервале [`begin`, `end`) имеется значение `value`.

#### LowerBound
Функция `LowerBound` осуществляет поиск первого элемента не меньшего (`>=`) `value` на полуинтервале [`begin`, `end`). Возвращает указатель на найденный элемент, либо `end`, если такого нет.

#### UpperBound
Функция `UpperBound` осуществляет поиск первого элемента строго большего (`>`) `value` на полуинтервале [`begin`, `end`). Возвращает указатель на найденный элемент, либо `end`, если такого нет.