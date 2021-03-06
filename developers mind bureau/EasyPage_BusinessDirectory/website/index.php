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

?><html>
 <head>
  <title>Business Directory, Shasta Exchange</title>
  
  <style>
  * {
     padding: 0;
     margin: 0;
  }
  
  body {
   background-color: #FAFAFF;
  }
	
  #doing_business_as_heading {
    font-size: 5em;
    text-align:center;
    color:#000000;
  }
  
  .doing_business_as_heading_a {
    text-decoration: none;
    color:#000000;
  }
	
  .doing_business_as_heading_a:hover {
    text-decoration: none;
    color:#000000;
  }
	
  #product_title {
    font-size: 3em;
    text-align:center;
  }
  
  .product_title_a {
    color:#000000;
    text-decoration: none;
  }
  
  #view_directory_button_div {
   text-align: center;
   font-weight: bold;
 
  }
  
  #view_directory_button_link:link {
   text-decoration: none;
   font-size: 3em;
   text-align:center;
  }
  
  #view_directory_button_link:visited {
   text-decoration: none;
   font-size: 3em;
   text-align:center;
  }
  
  #search_phrase_div {
   width: 99.999999%;
   text-align:center;
  }
  
  #search_phrase_input {
   width:94.1%;
   border-radius: 20px;
   font-size: 5em;
   border:5px solid black;
   margin: 0 0 0.5em 0em;
   background-color: white;
   padding: 0.3em;
  }
  
  #search_heading {
    font-size: 4em;
    background: black;
    color: white;
    text-align:center;
    padding: 0.1em 0 0.1em 0;
    margin: 0 0.5em 0.5em 0.5em;
  }
  
  #directory_heading {
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
  <script>
   function initiate_manual_submit()
   {
     window.location.href = '/search.php?phrases='+document.getElementById("search_phrase_input").value;
   }
  </script>
  

 </head>
 <body>
  <div id="doing_business_as_heading"><a href="http://shastaexchange.com" class="doing_business_as_heading_a">The Shasta Exchange</a></div>
  <div id="product_title"><a href="http://shastadirectory.com" class="product_title_a">Business Directory</a></div>
  
  <div class="horizontal_spacer_oneem">&nbsp;</div>
  
  <div id="search_heading">Search Directory</div>

  <form onSubmit="event.preventDefault(); initiate_manual_submit();">
   <div id="search_phrase_div">
    <input type="text" placeholder="" id="search_phrase_input" size="33"/>
   </div>
  </form>
  
  <div class="horizontal_spacer_oneem">&nbsp;</div>
   
  <div id="directory_heading">Directory</div>
  
<?php
  $letters_posted = "";
  
  $sql_query_list_all_businesses = "SELECT `id`,`business_name`,`business_sort_name`, `business_display_description` FROM `business_generic_data` ORDER BY `business_sort_name` ASC;";
  $query_in_progress_list_all_businesses = $connection->prepare($sql_query_list_all_businesses);
  $query_in_progress_list_all_businesses->execute();
  $continue_fetching_list_all_businesses = 1;
  while($continue_fetching_list_all_businesses == 1)
  {
    $business_generic_data = $query_in_progress_list_all_businesses->fetch();
    
    //stop while-loop
    if($business_generic_data == false)
    {
      $continue_fetching_list_all_businesses = 0;
    }else{
       //append first letter of sort placement to "letters_posted" if non existant.
       //dont show the first appearance letter heading.(show some of the directory before showing a letter headinng for orientation).
       if(strlen($letters_posted) >= 1){
         if(str_contains($letters_posted, $business_generic_data["business_sort_name"][0]) == false)
         {
           echo '<div class="directory_firstletter_heading">'.strtoupper($business_generic_data["business_sort_name"][0]).'</div>';
         }
       }
      
      //declare first letter heading has been used in some way.
      if(str_contains($letters_posted, $business_generic_data["business_sort_name"][0]) == false)
      { 
        $letters_posted = $letters_posted.$business_generic_data["business_sort_name"][0];
      }
    
    
      //echo a link to the business.
      echo '<div class="business_information">';
      echo '<a href="/business.php?id='.$business_generic_data["id"].'" class="business_name">'.$business_generic_data["business_name"].'</a>';
      echo '<div class="business_description">'.$business_generic_data["business_display_description"].'</div>';
      echo '<div style="height:10px;width:99%;">&nbsp;</div>';
      echo '</div>';
    }
  }
  
  //close connection.
  $query_in_progress_list_all_businesses = null;
  $connection = null;
  ?>
  
  <div class="horizontal_spacer_threeem">&nbsp;</div>
 </body>
</html>
