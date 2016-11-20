<?php
$n = new person(array('key'=>'value'));

$n->setkey('testparam1','testparam2');
var_dump($n->param1);
var_dump($n->param2);


