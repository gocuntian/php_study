<?php
function recurse($num) {
      recurse(++$num);
}
 
recurse(0);
