<?php
session_start();
header('Content-type: text/css');
if(isset($_SESSION['style'])) {
    $styles = $_SESSION['style'];
    $count = 1;
    foreach ($styles as $style) {
        echo ".container div.style$count {";
        foreach ($style as $key => $value) {

                if($key == 'bgcolor')
                {
                    $key = "background-color";
                    $value ="#$value";
                }
                if($key == 'align')
                {
                    $key = "text-align";
                }
                if($key == 'valign')
                {$key = "vertical-align";
                    if($value=="center")
                    {

                        $value ="middle";
                    }

                }
                if($key == 'color')
                {
                    $key = "color";
                    $value ="#$value";
                }
                echo "$key: $value;
";

        }
        echo "}
";
        $count++;
    }
}
else {

}
?>
.parent {
width: 100%;
height: 100%;
position: absolute;
top: 0;
left: 0;
overflow: auto;
}

.block {
position: absolute;
top: 45%;
left: 45%;
}
.container{overflow: visible; width:700;height: 700; }
.container div.border {border:1px solid black;white-space:nowrap;border-collapse: collapse}
.container div.inline{display: inline-block; }
.container div.table{display: table-cell; }
.left{float:left}
.right{float:right}
.clear{clear:left}
