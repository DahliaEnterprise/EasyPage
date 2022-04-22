<?php
  $page_to_show = 0; 
  //zero means show directory listing; one shows search results; two means show error occurred instead of the requested page.
  $database_error_return_code = 0;
  
  $servername = "localhost";
  $username = "root";
  $password = "password";

  //Create connection
  $conn = new mysqli($servername, $username, $password);

  //Check connection
  if($conn->connect_error) {
    $database_error_return_code = 1;
  }
  
  if($database_error_return_code == 1)
  {
    $page_to_show = 2;
  }
  
  //attempt to produce directory listing.
  $page_error = 0;
  if($page_to_show == 0)
  {
    $sql_query = "SELECT `display_title`, `sort_placement`, `display_description`, `associated_business_attribute_id` FROM `compiled_directory_page` ORDER BY `sort_placement` ASC";
    $sql_result = $conn->query($sql_query);
    if($sql_result->num_rows <= 0)
    {
      $page_error = 1;
    }
  }
  
?><html>
 <head>
  <title>Business Directory, Shasta Exchange</title>
  
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
  
  #directory_heading {
    font-size: 3em;
    text-align: center;
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
     window.location.href = '/index.php?search='+document.getElementById("search_phrase_input").value;
   }
  </script>
  

 </head>
 <body>
  <div id="doing_business_as_heading">The Shasta Exchange</div>
  <div id="product_title">Business Directory</div>
  
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
  while($row = $result->fetch_assoc())
  {
    //append first letter of sort placement to "letters_posted" if non existant.
    
      //if first time letter posted, create a heading for the letter.
      
    
    //echo a link to the business.
    echo '<a href="#">'.$row["display_title"].'</a>';
    echo '<div style="height:10px;width:99%;">&nbsp;</div>';
  }
  ?>
  
  <div class="horizontal_spacer_threeem">&nbsp;</div>
 </body>
</html>
