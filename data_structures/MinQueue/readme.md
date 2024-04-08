### Задание: Реализация типа данных "очередь с поддержкой минимума"

Реализуйте тип данных "очередь с поддержкой минимума", который поддерживает следующие операции:

- `enqueue n`: Добавить в хвост очереди число `n` (1 ≤ n ≤ 10^9) (значение `n` задается после команды). Программа должна вывести `ok`.
- `dequeue`: Удалить из очереди головной элемент. Программа должна вывести его значение.
- `front`: Программа должна вывести значение головного элемента, не удаляя его из очереди.
- `size`: Программа должна вывести количество элементов в очереди.
- `clear`: Программа должна очистить очередь и вывести `ok`.
- `min`: Программа должна вывести минимум в очереди, не удаляя его из очереди.

Если во входных данных встречается операция `front`, `dequeue` или `min`, и при этом очередь пуста, то программа должна вместо числового значения вывести строку `error`.