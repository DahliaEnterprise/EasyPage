<?php

include "./database.php";

$dsn = "mysql:host=$host;dbname=$db;charset=$charset";
$options = [
    PDO::ATTR_ERRMODE            => PDO::ERRMODE_EXCEPTION,
    PDO::ATTR_DEFAULT_FETCH_MODE => PDO::FETCH_ASSOC,
    PDO::ATTR_EMULATE_PREPARES   => false,
    PDO::ATTR_PERSISTENT => false
];
try {
     $connection = new PDO($dsn, $user, $pass, $options);
} catch (PDOException $e) {
     throw new PDOException($e->getMessage(), (int)$e->getCode());
}

$sql_query_business_information_as_string = "";
$business_generic_data_id = 0;
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
    $business_generic_data_id = intval($_GET['id'], 10);
    $sql_query_business_information_as_string = "SELECT `id`,`business_name`,`business_sort_name`, `business_display_description` FROM `business_generic_data` WHERE `id` = ? LIMIT 0,1;";
  }
}

//obtain business information.
$query_in_progress = $connection->prepare($sql_query_business_information_as_string);
$query_in_progress->execute([$business_generic_data_id]);
$business_information = $query_in_progress->fetch();

//obtain all the columns within the "business_hours_day_name".
$business_hours_day_name = [];
$business_hours_day_name_index = 0;

$sql_query_business_hours_day_name = "SELECT id, day_name FROM business_hours_day_name ORDER BY sort_order ASC;";
$query_in_progress_business_hours_day_name = $connection->prepare($sql_query_business_hours_day_name);
$query_in_progress_business_hours_day_name->execute();
$continue_fetching_day_name = 1;
while($continue_fetching_day_name == 1)
{
	$business_hours_day_name_fetch = $query_in_progress_business_hours_day_name->fetch();
	
	//stop while-loop?
	if($business_hours_day_name_fetch == false)
	{
		$continue_fetching_day_name = 0;
	}else{
		$business_hours_day_name[$business_hours_day_name_index]["id"] = $business_hours_day_name_fetch["id"];
		$business_hours_day_name[$business_hours_day_name_index]["day_name"] = $business_hours_day_name_fetch["day_name"];
		
		$business_hours_day_name_index = $business_hours_day_name_index + 1;
	}
}

//close query/connection.
$query_in_progress_business_hours_day_name = null;


//obtain all the columns within the "business_hours_name".
$business_hours_name = [];
$business_hours_name_index = 0;

$sql_query_business_hours_name = "SELECT id, hours_name FROM business_hours_name ORDER BY sort_order ASC;";
$query_in_progress_business_hours_name = $connection->prepare($sql_query_business_hours_name);
$query_in_progress_business_hours_name->execute();
$continue_fetching_hours_name = 1;
while($continue_fetching_hours_name == 1)
{
	$business_hours_name_fetch = $query_in_progress_business_hours_name->fetch();
	
	//stop while-loop?
	if($business_hours_name_fetch == false)
	{
		$continue_fetching_hours_name = 0;
	}else{
		$business_hours_name[$business_hours_name_index]["id"] = $business_hours_name_fetch["id"];
		$business_hours_name[$business_hours_name_index]["hours_name"] = $business_hours_name_fetch["hours_name"];
		
		$business_hours_name_index = $business_hours_name_index + 1;
	}
}

//close query/connection.
$query_in_progress_business_hours_name = null;



//obtain all the "hours".
$business_hours = [];
$business_hours_index = 0;

$sql_query_business_hours = "SELECT hours_name_id, day_name_id, hours FROM business_hours WHERE business_generic_data_id = ?;";
$query_in_progress_business_hour = $connection->prepare($sql_query_business_hours);
$query_in_progress_business_hour->execute([$business_generic_data_id]);
$continue_fetching_business_hours = 1;
while($continue_fetching_business_hours == 1)
{
  $business_hours_fetch = $query_in_progress_business_hour->fetch();
  
  //stop while-loop?
  if($business_hours_fetch == false)
  {
    $continue_fetching_business_hours = 0;
  }else{
    $business_hours[$business_hours_index]["hours_name_id"] = $business_hours_fetch["hours_name_id"];
    $business_hours[$business_hours_index]["day_name_id"] = $business_hours_fetch["day_name_id"];
    $business_hours[$business_hours_index]["hours"] = $business_hours_fetch["hours"];
    
    $business_hours_index = $business_hours_index + 1;
  }
}

//close query/connection.
$query_in_progress_business_hour = null;

//close pdo(database) connection
$connection = null;


//hours types to display.
$enabled_hours_type_by_id = [];
$business_hours_name_index = 0;
$business_hours_name_total = count($business_hours);
while($business_hours_name_index < $business_hours_name_total)
{
  $integer_from_possible_string = intval($business_hours[$business_hours_name_index]["hours_name_id"]);
  if(in_array($integer_from_possible_string, $enabled_hours_type_by_id) == false)
  {
    array_push($enabled_hours_type_by_id, $integer_from_possible_string);
  }
  
  $business_hours_name_index = $business_hours_name_index + 1;
}

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
  
  #product_title_subheading_as_business_directory {
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
    padding: 0.1em 1em 0.1em 1em;
    margin: 0 0em 2.5em 0;
    text-align: left;
  }
  
  .hours_heading {
    font-size: 4em;
    background: black;
    color: white;
    text-align:center;
    padding: 0.1em 0 0.1em 0;
    margin: 0 0.5em 0.5em 0.5em;
  }
  
  .day_and_hours {
    font-size: 3em;
    text-align:left;
    padding: 0.5em 0.5em 0.5em 0.5em;
    margin: 0 0.67em 0 0.67em;
    background-color: #f7f7f7;
    
  }

  
  .business_information {
    padding: 0.1em 0 0.1em 1.5em;
    margin: 0 0.5em 0.5em 0.5em;
    text-align: left;
  }
  
  
  .horizontal_spacer_halfem {
   margin: 0.25em;
   padding: 0.25em;
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
  <div id="product_title_subheading_as_business_directory">Business Directory</div>
  
  <div class="horizontal_spacer_oneem">&nbsp;</div>
 
  
  <div class="horizontal_spacer_oneem">&nbsp;</div>
   
  <div id="business_name"><?php echo $business_information["business_name"];?></div>
  <div id="business_display_description"><?php echo $business_information["business_display_description"];?></div>
  
<?php
  //for each "business hours type":
  $business_hours_name_index = 0;
  $business_hours_name_total = count($business_hours_name);
  while($business_hours_name_index < $business_hours_name_total)
  {
    //show only if enabled.
    if(in_array(intval($business_hours_name[$business_hours_name_index]["id"]), $enabled_hours_type_by_id) == true)
    {
?>
  <div class="hours_heading"><?php echo $business_hours_name[$business_hours_name_index]["hours_name"]; ?></div>
  
<?php
    //for each "business day":
    $business_hours_day_name_index = 0;
    $business_hours_day_name_total = count($business_hours_day_name);
    while($business_hours_day_name_index < $business_hours_day_name_total)
    {
      //for each hours matches with a day, we are already in the days cycle, find the matching hour(s) to display.
      $business_hours_index = 0;
      $business_hours_total = count($business_hours);
      $continue_finding_match = 1;
      while($continue_finding_match == 1)
      {
        $next_index = 0;
        //ignore non relavent business hours type("office", "delivery", "etc").
        if($business_hours[$business_hours_index]["hours_name_id"] == $business_hours_name[$business_hours_name_index]["id"])
        {
          if($business_hours[$business_hours_index]["day_name_id"] ==  $business_hours_day_name[$business_hours_day_name_index]["id"])
          {
            $continue_finding_match = 0;
          }else{
            $next_index = 1;
          }
        }else{
          $next_index = 1;
        }
        
        if($next_index == 1)
        {
          $business_hours_index = $business_hours_index + 1;
          //stop potentially infinite loop in during the condition of the database records not set appropriately.
          if($business_hours_index >= $business_hours_total)
          {
            $continue_finding_match = -1;
          }
        }
      }
      
      //display day and hours if all data is present to be able to display day and hours.
      if($continue_finding_match == 0)
      {
?>
  <div class="day_and_hours">
    <div class="day_and_hours_record"><?php echo $business_hours_day_name[$business_hours_day_name_index]["day_name"]; ?>: <?php echo $business_hours[$business_hours_index]["hours"];?></div>
  </div>

<?php
     
      }
      
      $business_hours_day_name_index = $business_hours_day_name_index + 1;
    }
?>
<div class="horizontal_spacer_halfem">&nbsp;</div>
<?php
    }
    $business_hours_name_index = $business_hours_name_index + 1;
  }
?>
  
  <div class="horizontal_spacer_threeem">&nbsp;</div>
 </body>
</html>
