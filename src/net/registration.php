<?php

//Получаем данные с запроса
$name = $_GET['name'];
$password = $_GET['pass'];

//Подключаемся к серверу БД
$link = mysql_connect('localhost', 'h134199_usue_cw', 'bk123456')
        or exit('1_1');

mysql_select_db('h134199_cwdbms')
        or exit('1_2');

//Проверяем, не занято ли имя пользователя
$query = "SELECT * FROM users WHERE name = '$name'";

if(mysql_num_rows(mysql_query($query)) > 0)
    exit('2');

$query = "INSERT INTO users VALUES"
        . " ('$name', '$password', NOW(), NOW())";

mysql_query($query)
    or exit('1_3 '. mysql_error());

echo '0';




