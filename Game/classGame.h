//
// Created by dartmoor on 02.12.18.
//

#ifndef NIGHTSWORD_CLASSGAME_H
#define NIGHTSWORD_CLASSGAME_H
#include <iostream>
#include "../characters/characters.h"
#include "../items/items.h"
#include <vector>
#include <string>
#include "MyVector.h"






class Location;

/*!

 \brief Главный класс, отвечающий за выполнение программы.
 \author Юрий Головушкин

 В данном классе содержатся игровые персонажи, враги и предметы на карте.
 Класс управляет игровым процессом.

*/


class classGame {
public:
    std::vector<std::string> lvl;
    /// Группа геров
    vector<Hero> mans;
    /// Группа врагов
    std::vector<Enemy> evils;
    /// Предметы
    Inventory someItem;

    /*!
Перемещение персонажей по карте в зависимости от доступности клетки
\param[in] choiseMan  Выбранный персонаж
\param[out] X Координата цели по X
\param[out] Y Координата цели по Y
\param[out] location объект классы Location в котором содержится информация о карте
\return Возможность переместиться на выбраную клетку
*/
    bool moveHero(int,float, float,Location&);

    /*!
 Атака персонажей врагами если это возможно

*/
    void heroIsNear();
    /*!
    Переммещение врагов по их траектории
   \param[in] countOfMove переменная отвечающая за траекторию
   */
    void moveAI(int);
    /*!
       Проверка конца игры

      */
    bool endGameCheck();
    /*!
  Открытие двери
  \param[in] choiseMan  Выбранный персонаж
  \param X Координата цели по X
  \param Y Координата цели по Y
  \param plX Координата игрока по X
  \param plY Координата игрока по Y
  \return Возможность открытие двери
  */
    bool openDoor(float X, float Y, float plX, float plY);
    /*!
    Проверка дистанции для действия
    \param[in] choiseMan  Выбранный персонаж
    \param X Координата цели по X
    \param Y Координата цели по Y
    \param anX Координата игрока по X
    \param anY Координата игрока по Y
    \param plus параметр зависящий от действия
    \return Возможность выполнить действие
    */
    bool rangeOfAct (float X, float Y,float anX, float anY,float plus);
/*!
    Проверка клетки карты
    \param[in] choiseMan  Выбранный персонаж
    \param X Координата цели по X
    \param Y Координата цели по Y
    \param mans группа персонажей
    \param evils группа врагов
    \return Свободна клетка или нет
    */
    bool tileInfo(float X , float Y, vector<Hero>*, std::vector<Enemy>*);

    bool tileCheck(float X , float Y, Location* location);
/*!
    Проверка дистанции
    \param[in] choiseMan  Выбранный персонаж
    \param X Координата цели по X
    \param Y Координата цели по Y
    \param anX Координата объекта который вызвал метод по X
    \param anY Координата объекта который вызвал метод по Y
    \return Дистанцию
    */
    float rangeOfMove(float X,float Y,float anX,float anY){return ((X - anX)*(X - anX) + (Y - anY) * (Y - anY) );}
/*!
    Начальные координаты для врагов и преметов
    \param[in,out] evils группа врагов
    \param[in,out] item предметы

    */
    void startCord(std::vector<Enemy> &evils,Inventory& item);
};

/*!

 \brief Класс карты
 \author Юрий Головушкин

 В данном классе содержится информация о каждой клетки уровня.

*/
class Location{
private:
    /// Массив инфорамции о карте
    bool cellInfo[16][42];
public:
/*!
    Начальные координаты для врагов и преметов
    \param x координата клетки карты по X
    \param y координата клетки карты по Y
    \return Занятость клетки
    */
    bool getCellInfo(float x,float y){int X = (int)x/32;int Y = (int)y/32; return cellInfo[Y][X];}
/*!
    Очищает информацию о всех клетках

    */
    void clearMap();
/*!
    Обновление информации для клетки
    \param X новая координата X
    \param Y новая координата Y
    \param prevY старая координата X
    \param prevX старая координата Y

    */
    void miniUpdate(float ,float ,float , float );
/*!
    обновление информации карты по координатам
    \param X координата X
    \param Y координата Y

    */
    void updateMap(float x,float y){int X = (int)x/32;int Y = (int)y/32;  cellInfo[Y][X] = true;}
};








#endif //NIGHTSWORD_CLASSGAME_H
