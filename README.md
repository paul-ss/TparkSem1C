[![Build Status](https://travis-ci.com/paul-ss/TparkSem1C.svg?branch=hw-2)](https://travis-ci.com/paul-ss/TparkSem1C)[![codecov](https://codecov.io/gh/paul-ss/TparkSem1C/branch/hw-2/graph/badge.svg)](https://codecov.io/gh/paul-ss/TparkSem1C)

#Условие ИЗ №2:
В вашем распоряжении — прямоугольная матрица из 10 000 x 5000 вещественных чисел двойной точности. Составьте наивный алгоритм подсчета суммы в каждом столбце, который сначала ищет сумму чисел в первом столбце, затем — во втором и т.д., а затем реализуйте параллельный алгоритм с использованием нескольких потоков решения задачи с учетом оптимизации работы с кэш-памятью.

#Результаты
|Размер матрицы|	100x100|	1000x1000|	5000x5000|	10000x10000|
|--------------|-----------|-------------|-----------|-------------|
Наивный алгоритм, c|	0,000146|	0,019383|	2,15013|	14,586898|
Параллельный алгоритм, c|	0,000703|	0,013346|	0,17485|	0,680658|

