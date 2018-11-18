<?php

$name = $_GET['name'];
$password = $_GET['pass'];

$link = mysql_connect('localhost', 'h134199_usue_cw', 'bk123456')
        or exit('1');

mysql_select_db('h134199_cwdbms')
        or exit('1');

/* Создаем запрос на проверку наличия пользователя
   с полученным логином и паролем */
$query = "SELECT * FROM users WHERE name = '$name' "
        . "and pass = '$password'";

//Если пользователя не существует, возвращаем ошибку
if(mysql_num_rows(mysql_query($query)) == 0)
    exit('2');

//Пользователь успешно вошел, установим дату последнего входа
/* т.к. имя пользователя уникально для каждого,
 не будем проверять пароль еще раз */
$query = "UPDATE users SET lastlogin = NOW()"
        . " WHERE name = '$name'"; 

mysql_query($query);

echo('0'); // Уведомляем об успешном входе
