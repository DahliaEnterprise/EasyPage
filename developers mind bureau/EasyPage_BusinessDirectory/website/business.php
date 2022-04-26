<?php

include "./database.php";

$dsn = "mysql:host=$host;dbname=$db;charset=$charset";
$options = [
    PDO::ATTR_ERRMODE            => PDO::ERRMODE_EXCEPTION,
    PDO::ATTR_DEFAULT_FETCH_MODE => PDO::FETCH_ASSOC,
    PDO::ATTR_EMULATE_PREPARES   => false,
];
try {
     $connection = new PDO($dsn, $user, $pass, $options);
} catch (PDOException $e) {
     throw new PDOException($e->getMessage(), (int)$e->getCode());
}

$sql_query_business_information_as_string = "";
$integer_from_string = 0;
if(isset($_GET['id']) == true)
{
  $infiltration_detected = 1;
  //is number? anything else is an attempt to infiltrate.
  if(is_numeric($_GET['id']) == true)
  {
    $infiltration_detected = 0;
  }
  
  if($infiltration_detected == 0)
  {
    //convert/ensure base ten number interpretation.
    $integer_from_string = intval($_GET['id'], 10);
    $sql_query_business_information_as_string = "SELECT `id`,`business_name`,`business_sort_name`, `business_display_description` FROM `business_generic_data` WHERE `id` = ? LIMIT 0,1;";
  }
}

//obtain business information.
$query_in_progress = $connection->prepare($sql_query_business_information_as_string);
$query_in_progress->execute([$integer_from_string]);
$business_information = $query_in_progress->fetch();

//obtain all the columns within the "business_hours_day_name".
$sql_query_business_hours_day_name = "SELECT day_name FROM business_hours_day_name ORDER BY sort_order ASC";
$query_in_progress_business_hours_day_name = $connection->prepare($sql_query_business_hours_day_name);
$query_in_progress_business_hours_day_name->execute();
//todo: create a multi dimensional array by continually calling fetch.
$business_hours_day_name = $query_in_progress_business_hours_day_name->fetch();


//obtain all the columns within the "business_hours_name".
  
//obtain all the "hours".
  

?><html>
 <head>
  <title><?php echo $business_information["business_name"]; ?>, Business Information, Shasta Exchange</title>
  
  <style>
  * {
     padding: 0;
     margin: 0;
  }
	
  #doing_business_as_heading {
    font-size: 5em;
    text-align:center;
  }
	
  #product_title {
    font-size: 3em;
    text-align:center;
  }
  
  #business_name {
    font-size: 4em;
    background: black;
    color: white;
    text-align:center;
    padding: 0.1em 0 0.1em 0;
    margin: 0 0.5em 0.5em 0.5em;
  }
  
  #business_display_description {
    font-size: 3em;
    padding: 0.1em 0 0.1em 0.2em;
    margin: 0 0.5em 2.5em 0.5em;
    text-align: left;
  }
  
  #hours_heading {
    font-size: 4em;
    background: black;
    color: white;
    text-align:center;
    padding: 0.1em 0 0.1em 0;
    margin: 0 0.5em 0.5em 0.5em;
  }
  
  .business_information {
    padding: 0.1em 0 0.1em 1.5em;
    margin: 0 0.5em 0.5em 0.5em;
    text-align: left;
  }
  .business_name {
    font-size: 4em;
    text-decoration: none;
    text-align: left;
    color: #480355;
    font-weight: bold;
  }
  
  .business_description {
    font-size: 2.5em;
  }
  
  .directory_firstletter_heading {
    font-size: 4em;
    background: black;
    color: white;
    text-align:center;
    padding: 0.1em 0 0.1em 0;
    margin: 0 0.5em 0.5em 0.5em;
  }
  
  .horizontal_spacer_oneem {
   margin: 0.5em;
   padding: 0.5em;
  }
  
  .horizontal_spacer_threeem {
   margin: 2.5em;
   padding: 0.5em;
  }
  
 
  </style>
 </head>
 <body>
  <div id="doing_business_as_heading" onMouse>The Shasta Exchange</div>
  <div id="product_title">Business Directory</div>
  
  <div class="horizontal_spacer_oneem">&nbsp;</div>
 
  
  <div class="horizontal_spacer_oneem">&nbsp;</div>
   
  <div id="business_name"><?php echo $business_information["business_name"];?></div>
  <div id="business_display_description"><?php echo $business_information["business_display_description"];?></div>
  
<?php

?>
  <div id="hours_heading">Business Hours</div>
  
<?php


  ?>
  
  <div class="horizontal_spacer_threeem">&nbsp;</div>
 </body>
</html>
