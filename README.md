# arduino-robotbtcontrol
Управление роботом на основе arduini-uno посредством bluetooth.
v 0.0001a
4-х колесное шасси на основе Arduino-UNO с 4-мя редукторными двигателями управлямыми ШИМ.
Система команд, передаваемых по bluetooth соответствует использумой в программе "Bluetooth RC Controller" под Android.
Параметр программы "Data stream frequency" установлен в положение "On change/touch"
    'F' - стрелка вверх - движение вперед
    'L' - стрелка влево - движение разворот влево
    'R' - стрелка вправо - движение разворот вправо
    'S' - Отпускание клавишей управления - останов движения
    'B' - стрелка вниз - движение назад
    'G' - стрелки вверх и влево - движение вперед и влево
    'I' - стрелки вверх и вправо - движение вперед и вправо
    'H' - стрелки вниз и влево - движение назад и влево
    'J' - стрелки вниз и вправо - движение назад и вправо
    'D' - завершение работы управляющей программы на удаленном устройстве
	'0' - скороcть 0%
	'1' - скороcть 10%
	'2' - скороcть 20%
	'3' - скороcть 30%
	'4' - скороcть 40%
	'5' - скороcть 50%
	'6' - скороcть 60%
	'7' - скороcть 70%
	'8' - скороcть 80%
	'9' - скороcть 90%
	'q' - скороcть 100%
	
	Нереализованные команды в этой версии:
	'V' - включить звук или что-то другое
	'v' - выключить звук или что-то другое
	'W' - включить фары или что-то другое
	'w' - выключить фары или что-то другое
	'U' - включить задний свет или что-то другое
	'u' - выключить задний свет или что-то другое
	'X' - включить дополнительную опцию или что-то другое
	'x' - выключить дополнительную опцию или что-то другое
