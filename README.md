# LogParser

test work for cpp-school
https://cpp-school.unigine.com/send-test-task

Парсим логи!
=============

На входе лог, имя файла задано с командной строки.
Лог это текстовый файл, в некоторых (именно некоторых) строчках которого встречаются URL.
URL-ом считается подстрока, обязательно состоящая из префикса и домена, и, возможно, необязательного дополнительного пути.
Префикс это либо "http://" либо "https://".
Домен это любой набор символов "a-z A-Z 0-9 . -" (латиница плюс цифры точка плюс дефис).
Путь всегда начинается строго со "/" и далее может состоять из символов: "a-z A-Z 0-9 . , / + _" (латиница плюс цифры плюс еще 5 спецсимволов).
В случае отсутствия пустой путь заменяется на путь "/".
Таким образом, "http://google.com/" это домен "google.com" плюс путь "/".
Таким образом, "http://...oh" это домен "...oh" и пустой путь, который заменяется на "/".
(Ага, для целей задания несколько упрощённые правила, в которые можно просунуть некорректное.)

На выходе отчет, имя файла задано с командной строки.
Отчет это текстовый файл, в котором сначала выведена общая статистика, а далее перечислены top-N доменов и top-N путей по частоте их упоминания в логе.
В случае одинаковой частоты домены и пути сортируются в лексикографическом порядке (без учета кодировки, то есть побайтово).
Обратите внимание, путь "/" в составе 4 разных URL из 4 разных доменов это 4 упоминания.
В смысле, что путю "/" должно быть засчитано 4 упоминания. Несмотря на разные домены и как бы разные упоминания, путь-то одинаковый.
N может быть задано опциональным ключом командной строки "-n".
При этом формат файла должен быть строго такой, как в приведенном примере.

Формат командной строки:
	mytest [-n NNN] in.txt out.txt

Пример входного файла:
	ssl1001 129960997 2014-01-21T08:36:33.097 0.426 1.2.3.4 -/200 12324 GET https://en.wikipedia.org/w/index.php?title=Kirschkuchen&action=edit&section=8	NONE/wikimedia - https://en.wikipedia.org/wiki/Kirschkuchen	- Mozilla/5.0 (Windows NT 5.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/32.0.1700.76 Safari/537.36 en-US,en;q=0.8 -
	sq18.wikimedia.org 1715898 2010-12-01T21:57:22.331 0 1.2.3.4 TCP_MEM_HIT/200 13208 GET http://en.wikipedia.org/wiki/Main_Page	NONE/- text/html - - Mozilla/4.0%20(compatible;%20MSIE%206.0;%20Windows%20NT%205.1;%20.NET%20CLR%201.1.4322) en-US -
	cp1048.eqiad.wmnet 8883921154 2013-09-26T06:28:16 0.001308203 1.2.3.4 hit/200 52362 GET http://en.wikipedia.org/wiki/Free_software	- text/html https://www.google.com/search?q=free+software	4.3.2.1 Mozilla/5.0 (Windows NT 6.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/29.0.1547.76 Safari/537.36 en-US,en;q=0.8 - 

Пример выходного файла:
	total urls 5, domains 2, paths 5

	top domains
	4 en.wikipedia.org
	1 www.google.com

	top paths
	1 /search
	1 /w/index.php
	1 /wiki/Free_software
	1 /wiki/Kirschkuchen
	1 /wiki/Main_Page

Программа должна компилироваться под Windows MSVC 2013 или Linux gcc 5.4.0. Когда мы получим файл с заданием, запустится автопроверка на компилируемость на указанных окружениях. По результатам вы получите 2 отчета о сборке. Это не является критерием выполнения, а лишь служит подтверждением и уверенностью для Вас, что Ваш код собрался на нашей стороне. ВСЕ задания будут отсматриваться и прогоняться затем вручную человеком-Шоданом. То есть, если вам доступен только Borland C++ 3.1, то можно скомпилироваться удаленно с помощью нашей системы. Возможно сколько угодно попыток и правок.

Можно использовать язык в рамках стандарта, т.е. C++ и ещё STL.
Loki, Boost, Qt и прочие сторонние библиотеки использовать нельзя (да и не выйдет).
Самопальные контейнеры в виде сторонних библиотек тоже использовать нельзя (да и не выйдет).
Иначе можно. В целом, можно всё, что влезает в 1 файл и компилируется голым VS 2013 или gcc 5.4.0. 
