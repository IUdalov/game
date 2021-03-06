#**Игра**
---------

###Основная идея
Реализовать расширение классической игры "Чапаев". Мультиплеер, синглплеер.

#### В первом релизе планируется
 - правила чередования хода как в классической игре "Чапаев"
 - шашки расставляются игроками в начале (в произвольном порядке)
 - шашки могут быть разной массы
 - разного диаметра
 - разной упругости (возможно)
 - трение шашки линейно зависит от массы
 - не только мультиплеер, но и синглплеер

#### второй релиз 
 - сначала бы первый выпустить
 - мечтать рано

###Инструменты
 - Qt (в качестве IDE настоятельно рекомендуется Qt Creator 5), в качестве компилятора под win - MinGW
 - Графика - Open GL
 - Игра пока собиралась только на Linux и Windows.
 - Движок у игры собственный, написан единолично [Михаилом](https://github.com/mihacooper])

###*Глобальные задачи на будущее*
 - сеттинг игры (найти человека который нарисует, программистам нельзя заниматься дизайном)
 - Попробовать собрать под android/ios, посмотреть чем tap отличаается от клика мышью
 - придумать название
 
###*Что планируется сделать в ближайшее время*
 - расстановщик шашек перед началом игры (делает [Михаил](https://github.com/mihacooper])) 
 - стартовое меню (делает [Илья](https://github.com/IUdalov/))
 - присоединился [Сергей](https://github.com/SergeyFrolov) и пытается сделать ИИ

--------------------------------------------------------------------

#Пояснения к текущей работе:
 - при расстановке каждому игроку выдается по 4 шашки каждого типа(тяжелая, средняя легкая)
 - вместо клавиши 'play' для окончания расстановки надо нажимать клавишу 'enter'
 - ходы переключаются после каждого сдвига шашек
 - окончание игры пока не наблюдается
 - выход из игры по клавише 'escape'

 ++
 - по клавише 'F1' происходит реплей. В том числе, когда игра завершается
   (хотя бы у одного из игроков не осталось шашек).

 ++
 - по клавише 'F2' завершает игру в смысле игрового процесса(начинает заново если была завершена).
 - расстановка теперь только на свою половину поля

 *!!! папку билда кладем в корень, т.е. туда, где лежит файл game.pro!!!*
