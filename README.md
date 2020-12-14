# ppvis-2_additional_assignment
Created by: Vernikovskaya Nastya, Group 921702


Task:Разработать абстрактные типы данных, описывающие однонаправленный список, двунаправленный список и очередь. 
Необходимо учесть следующие требования:

- не использовать контейнеры STL,

- использовать умные указатели STL,

//используем unique_ptr 

- использовать google code style,

//проверялось так:
//cpplint.py ./tests/*.cpp ./include/*

- абстрактные типы данных не должны зависить от типа элементов, которые содержат

//использовались шаблоны

- однонаправленный и двунаправленный список должны быть связаны наследованием

- очередь надо реализовать как декоратор по отношению к спискам, т.е. очередь можно создавать как на основе однонаправленного или двунаправленного списка,

//сделано в конструкторе очереди, передаем список на основе которого создавать 

- в примере продемонстрировать добавление, происк и удаление элементов из абстрактных типов данных.

//файл tests/test.cpp
