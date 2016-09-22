<?php
session_start();
function getHtml($input) {
    $mainArray =  array(0,0,0,
                        0,0,0,
                        0,0,0);
    $count = 1;
    $currentDimension=3;
    $step=1;
        foreach ($input as $value) {
            $cellsArray = explode(",",$value['cells']);
            //************************************
            if(count($cellsArray) == 3)
            {
                if (!($cellsArray[1]== $cellsArray[0]+$currentDimension && $cellsArray[2]== $cellsArray[0]+$currentDimension+$currentDimension) ||
                    !($cellsArray[1]== $cellsArray[0]+$step && $cellsArray[2]== $cellsArray[0]+$step+$step))
                {
                    continue;
                }
            }
            if(count($cellsArray) == 4)
            {
                if (!($cellsArray[1]== $cellsArray[0]+$step &&
                        $cellsArray[2]== $cellsArray[0]+$currentDimension &&
                        $cellsArray[3]== $cellsArray[0]+$currentDimension+$step)
                    )
                {
                    continue;
                }
            }
            if(count($cellsArray) == 6)
            {
                if(!($cellsArray[1]== $cellsArray[0]+$step &&
                    $cellsArray[2]== $cellsArray[0]+$currentDimension &&
                    $cellsArray[3]== $cellsArray[0]+$currentDimension+$step &&
                     $cellsArray[4]== $cellsArray[0]+$currentDimension +$currentDimension &&
                     $cellsArray[5]== $cellsArray[0]+$currentDimension+$currentDimension+$step) ||
                    !($cellsArray[1]== $cellsArray[0]+$step &&
                        $cellsArray[2]== $cellsArray[0]+$step+$step &&
                        $cellsArray[3]== $cellsArray[0]+$currentDimension &&
                        $cellsArray[5]== $cellsArray[0]+$currentDimension+$step &&
                        $cellsArray[6]== $cellsArray[0]+$currentDimension+$step+$step)
                )
                {
                    continue;
                }
            }
            if(count($cellsArray) == 5 || count($cellsArray) == 7 || count($cellsArray) == 8)
            {
                continue;
            }
            //************************************
            foreach ($cellsArray as $valueCell) {
                if(isset($mainArray[$valueCell-1]))
                {
                    $mainArray[$valueCell-1] = $count;
                }
            }
            $count++;
        }
        $_SESSION['cellsArray'] = $mainArray;
        $_SESSION['style'] = $input;

}

getHtml(array(
            array(  'text'      => 'text_1'
                ,  'cells'     => '1,2,4,5'
                ,  'align'     => 'center'
                ,  'valign'    => 'center'
                ,  'color'     => 'FF0000'
                ,  'bgcolor'   => '0000FF')
        ,   array(  'text'      => 'text_2'
                ,  'cells'     => '8,9'
                ,  'align'     => 'right'
                ,  'valign'    => 'bottom'
                ,  'color'     => '00ff00'
                ,  'bgcolor'   => 'FFFFFF')
        ));
header ('Location: main_view.php');