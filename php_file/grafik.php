
/***************************************************************************************
*    Title: Insert_data_php
*    Author: Evi Andrianto
*    Date: 27-Jan-17
*    Code version: v1.0
*
***************************************************************************************/






<?php // content="text/plain; charset=utf-8"
$url=$_SERVER['REQUEST_URI'];
header("Refresh: 5; URL=$url");  // Refresh the webpage every 5 seconds

require_once ('jpgraph/src/jpgraph.php');
require_once ('jpgraph/src/jpgraph_line.php');

$hum_axis = array();

$temp_axis = array();

$i = 0;

// Connect to database

// IMPORTANT: If you are using XAMPP you will have to enter your computer IP address here, if you are using webpage enter webpage address (ie. "www.yourwebpage.com")
$con=mysqli_connect('localhost','root','','data monitoring');
       
// Retrieve all records and display them   
$result = mysqli_query($con,'SELECT * FROM dht11 ORDER BY id DESC');
      
// Process every record

while($row = mysqli_fetch_array($result))
{

$hum_axis[$i] =  $row['humidity'];
$temp_axis[$i] = $row['Temp'];
    $i++;

}

$hum=array_reverse($hum_axis);
$temp=array_reverse($temp_axis);

// Close the connection   
mysqli_close($con);


// Setup the graph
$graph = new Graph(1400,600);
$graph->SetScale("textlin");

$theme_class=new UniversalTheme;

$graph->SetTheme($theme_class);
$graph->img->SetAntiAliasing(false);
$graph->title->Set('Filled Y-grid');
$graph->SetBox(false);

$graph->img->SetAntiAliasing();

$graph->yaxis->HideZeroLabel();
$graph->yaxis->HideLine(false);
$graph->yaxis->HideTicks(false,false);

$graph->xgrid->Show();
$graph->xgrid->SetLineStyle("solid");
$graph->xaxis->SetTickLabels(array('1','2','3','4'));
$graph->xgrid->SetColor('#E3E3E3');

// Create the first line
$p1 = new LinePlot($hum);
$graph->Add($p1);
$p1->SetColor("#6495ED");
$p1->SetLegend('Humidity');

// Create the second line
$p2 = new LinePlot($temp);
$graph->Add($p2);
$p2->SetColor("#B22222");
$p2->SetLegend('Temperature');


$graph->legend->SetFrameWeight(1);

// Output line
$graph->Stroke();

?>

