<?php session_start(); ?>
<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <link href="style.php" rel="stylesheet">
    <title>Квадраты</title>

</head>

<body>
<div class="parent">
    <div class="block">
        <table>


            <?php
            echo "<div class = \"container \">";
            $cellsArray = $_SESSION['cellsArray'];
            $arrayLines = array(false, false, false); // true - if all row is one line else - false;
            $cyclesAmount = 1;
            $arrayJumps =array(0);
            $colArray = array(1,2,3);
            $currentDimension = 3;
            $step=1;

            function getAmountOfCycles(&$cellsArray, &$cyclesAmount, &$arrayJumps, &$arrayLines, &$currentDimension, &$step)
            {
                for($i=0;$i<$currentDimension;$i++) {
                    $temp = 0;
                    for ($j = 0; $j < $currentDimension; $j++)
                    {
                        if(isset($cellsArray[$currentDimension*$i+$j+$step]) &&
                            $currentDimension*$i+$j+$step<$i*$currentDimension+$currentDimension &&
                            $cellsArray[$currentDimension*$i+$j]!=0 &&
                            $cellsArray[$currentDimension*$i+$j]==$cellsArray[$currentDimension*$i+$j+$step])
                        {
                            $temp++;
                        }
                    }
                    if($temp == $currentDimension-$step)
                    {
                        $arrayLines[$i]=true;
                        $arrayJumps[$cyclesAmount] = 0;
                        $cyclesAmount++;
                        if($i!=2 && $i!=0)
                        {
                            $cyclesAmount++;
                        }
                    }
                }
            }

            function getColArray(&$arrayJumps, &$cycle, &$cellsArray, &$colArray, &$arrayLines, &$currentDimension, &$step)
            {
                $i = $arrayJumps[$cycle];
                for($j = 0; $j < $currentDimension; $j++) {
                    if (isset($cellsArray[$currentDimension * $i + $j + $step]) &&
                        $cellsArray[$currentDimension * $i + $j] != 0 &&
                        $currentDimension * $i + $j + $step < $i * $currentDimension + $currentDimension &&
                        $cellsArray[$currentDimension * $i + $j] == $cellsArray[$currentDimension * $i + $j + $step]
                    ) {

                        $colArray[$j] = $step+$currentDimension;
                        $colArray[$j + $step] = $step+$currentDimension;


                    }
                    if ($j == $currentDimension-$step) {
                        if (isset($arrayLines[$i + $step]) &&
                            $arrayLines[$i] == $arrayLines[$i + $step]
                        ) {
                            $i++;
                            $j = -1;
                        } else {
                            $arrayJumps[$cycle + $step] = $i + $step;
                        }
                    }
                }
            }

            function checkRestriction(&$cycle, &$arrayJumps, &$restrictionI, &$step)
            {
                if(isset($arrayJumps[$cycle+$step]))
                {
                    $restrictionI= $arrayJumps[$cycle+$step]-$step;
                }
            }

            getAmountOfCycles($cellsArray, $cyclesAmount, $arrayJumps, $arrayLines, $currentDimension, $step);

            for($cycle=0;$cycle<$cyclesAmount;$cycle++)
            {
                $colArray = array(1,2,3);
                getColArray($arrayJumps, $cycle, $cellsArray, $colArray, $arrayLines, $currentDimension, $step);
                $i = $arrayJumps[$cycle];
                $restrictionI=2;
                $tempJ =0;
                checkRestriction($cycle, $arrayJumps, $restrictionI, $step);
                echo "<div class = \" clear \">";// block 1 start
                echo "<div class = \"inline left\">";//block 2 start
                for($j = 0; $j < $currentDimension; $j++)
                {

                    $cellWidth = 50;
                    $cellHeight = 50;
                    $width = $cellWidth;
                    $height = $cellHeight;
                    // Here graphic rules*********************************
                    $cellValue = $cellsArray[$i*$currentDimension+$j];
                    if($cellValue === 0)
                    {
                        echo "<div class = \"border inline left style$cellValue\" style='width: {$cellWidth}px; height: {$cellHeight}px;'></div>";
                    }
                    if($cellValue != 0 && $cellValue != -1)
                    {$right = 0;

                        for($k = $j+$step; $k < $currentDimension; $k++)
                        {
                            if(  $cellValue === $cellsArray[$i*$currentDimension+$k])
                            {
                                $width+=$cellWidth;
                                $cellsArray[$i*$currentDimension+$k] = -1;
                                $right++;
                            }
                        }
                        for($l = $i*$currentDimension+$j+$currentDimension;$l < $currentDimension*$currentDimension;$l+=$currentDimension)
                        {
                            if($cellValue === $cellsArray[$l])
                            {
                                $height+=$cellHeight;
                                $cellsArray[$l] = -1;
                                if($right==($currentDimension-$step-$step))
                                {
                                    $cellsArray[$l+$step] = -1;
                                }
                                if($right==($currentDimension-$step))
                                {
                                    $cellsArray[$l+$step] = -1;
                                    $cellsArray[$l+$step] = -1;
                                }
                            }
                        }

                        $text = $_SESSION['style'][$cellValue-1]['text'];
                        echo "<div class = \"border  inline left ";
                        if((isset($colArray[$j+1])&&$colArray[$j]!=$colArray[$j+1])||(!isset($colArray[$j+1])))
                        {
                            echo " right ";
                        }
                        echo " \">" ;
                        echo "<div class = \"table  style$cellValue \" style='width: {$width}px; height: {$height}px;'>
$text
</div>
</div>";
                    }
                    //***********************************
                    if(isset($colArray[$j+$step]))
                    {
                        if($colArray[$j]!=$colArray[$j+$step])
                        {
                            if($i<$restrictionI)
                            {
                                $i++;
                                echo "<div>  </div>";//new string
                                $j = $tempJ-$step;
                            }else
                            {
                                echo "</div>"; //block 2 end int
                                $i=$arrayJumps[$cycle];
                                $tempJ = $j+$step;
                                echo "<div class = \"inline left \" >";//block 2 start

                            }

                        }
                    } else
                    {
                        if($i<$restrictionI)
                        {
                            $i++;
                            echo "<div></div>";// new string
                            $j=$tempJ-$step;
                        }else{
                            echo "</div>";//block2 end ext
                        }
                    }
                }
                echo "</div>";//block 1 end

            }

            echo "</div>";
            ?>


        </table>
    </div>
</div>

</body>
</html>