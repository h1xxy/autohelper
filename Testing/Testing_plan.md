# План тестирования

## Содержание
1. [Введение](#introduction)
2. [Объект тестирования](#items)
3. [Атрибуты качества](#quality)
4. [Риски](#risks)
5. [Аспекты тестирования](#features)
6. [Подходы к тестированию](#approach)
7. [Представление результатов](#pass)
8. [Выводы](#conclusion)

## 1 Введение <a name = "#introduction"></a>

Данный документ описывает план тестирования приложения autohelper. Он предназначен для людей, выполняющих тестирование приложения, в частности тестировщиков. Цель тестирования - проверка соответствия между реальным поведением программы и её ожидаемым поведением на основе [требований](../SRS_ru.md).

## 2 Объект тестирования <a name = "#items"></a>

В качестве объектов тестирования можно выделить основные [функциональные требования](../SRS_ru.md). К основным модулям следует отнести:
* модуль авторизации пользователя
* модуль регистрации пользователя
* модуль добавления автомобиля
* модуль удаления автомобиля
* модуль редактирования файла
* модуль просмотра автомобиля

## 3 Атрибуты качетсва <a name = "#quality"></a>

1. Функциональность:
   1. Функциональная полнота: приложение должно выполнять все заявленные [функции](../SRS_ru.md);
   2. Функциональная корректность: приложение должно выполнять все заявленные функции корректно;
   3. Функциональная целесообразность: отсутствуют не заявленные функции, которые бы мешали приложению выполнить первоначально поставленные задачи;
2. Удобство использования:
   1. эстетика пользовательского интерфейса: плавный интерфейс;

## 4 Риски <a name = "#risks"></a>

К рискам можно отнести:
* удаление файла автомобила пользователем во время просмотра;
* удаление файлов приложения пользователем.

## 5 Аспекты тестирования <a name = "#approach"></a>

В ходе тестирования планируется проверить реализацию основных функций приложения. Данное тестирования будет проводится человеком, не имевшим возможность наблюдать за этапами разработки и не знакомым с исходным кодом.

Аспекты, подвергаемые тестированию:
* управление списком автомобилей;
* авторизация;
* регистрация;

### Управление списком автомобилей
Этот вариант использования необходимо протестировать на:
* Попытка добавить автомобиль;
* Попытка удалить автомобиль;
* Попытка редактировать определённое описание автомобиля;
* Попытка просмотреть автомобиль.

### Авторизация
Этот вариант использования необходимо протестировать на:
* Авторизация пользователя который есть в список зарегестрированных;
* Авторизация пользователя которого нет в списке зарегестрированных.

### Регистрация
Этот вариант использования необходимо протестировать на:
* Регистрация нового пользователя;
* Регистрация уже существующегго пользователя.

### Нефункциональные требования

* Доступ ко всем функциям приложения не более, чем за две операции;
* Все функциональные элементы пользовательского интерфейса должны иметь названия или символические обозначения, описывающие действие, которое произойдет при выборе элемента;
* Функциональные элементы должны находится в одной части главного окна приложения.

## 6 Подходы к тестированию <a name = "approach"></a>

Для тестирования приложения будет использован ручной подход.

## 7 Предоставление результатов <a name = "pass"></a>

Результаты тестирования представлены в документе ["Результаты тестирования"](./Testing_results.md).

## 8 Выводы <a name = "conclusion"></a>

Исходя из результатов тестирования можно сделать вывод о том, что приложение полностью соответствует фунциональным требованиям. Также можно сделать вывод о том, что приложение полностью удовлетворяет нефункциональным требованиям. Функционал приложения является небольшим, но позволяющий просматривать автомобили в каталоге без особых проблем.