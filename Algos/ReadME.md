Сложность https://github.com/MonkeBrainIsReal/AaDs/blob/master/Algos/Source.cpp#L57 в худшем случае O(n), потому что в цикле осуществляется 
сдвиг элементов вправо относительно позиции вставки, что занимает O(n) времени. Эффективность операции зависит от количества элементов в массиве.
Upd: Так же там вызывается метод expand который занимает O(n) времени и в сумме вся сложность алгоритма в худшем случае будет O(n).



Upd: Сложность https://github.com/MonkeBrainIsReal/AaDs/blob/master/Algos/Source.cpp#L190 в худшем случае O(n), потому что в худшем случае нам придется
пройти через половину элементов списка, чтобы найти требуемый элемент.


Сложность https://github.com/MonkeBrainIsReal/AaDs/blob/master/Algos/Source.cpp#L435 в худшем случае O(n), потому что каждый токен обрабатывается один раз в цикле,
и в каждой итерации выполняется постоянное количество операций (например, операции с добавлением и удалением элементов из стека). 
Таким образом, сложность функции линейна относительно количества токенов в выражении.
