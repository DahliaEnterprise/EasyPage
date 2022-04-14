<?php
//to be replaced by a alternative database method.
 $simulated_index_folder[0]["title"] = "Sports Shop";
 $simulated_index_folder[0]["description"] = "This is a pharagraph that goes under the title during search results.";
 $simulated_index_folder[0]["search_phrases"][0] = "baseball";
  $simulated_index_folder[0]["search_phrases"][1] = "golf";
 
 
 $simulated_index_folder[1]["title"] = "Generic Restaurant";
 $simulated_index_folder[1]["description"] = "This is a pharagraph that goes under the title during search results.";
  $simulated_index_folder[1]["search_phrases"][0] = "bread";
  $simulated_index_folder[1]["search_phrases"][1] = "meat";
   
 
 /* to do: create a connection here and "read" from the network
           that has all the data pertaining to the respective search.
           
           placement is so the page isnt present until it is determined what
           the page will display, the directory listing, search results, 
           and or search results with error response.
 */
 
?><html>
 <head>
  <title>Shasta Exchange, Business Directory</title>
  <style>
  * {
        
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
   width:94%;
   border-radius: 20px;
   font-size: 5em;
   border:5px solid black;
   margin: 0 0 0 0.38em;
   background-color: white;
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
     window.location.href = '/index.php?search_activated='+document.getElementById("search_phrase_input").value
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
 
if(!($sock = socket_create(AF_INET, SOCK_STREAM, 0)))
{
	$errorcode = socket_last_error();
    $errormsg = socket_strerror($errorcode);
    
    die("Couldn't create socket: [$errorcode] $errormsg \n");
}

socket_set_block($sock);

echo "Socket created \n";

if(!socket_connect($sock , 'localhost' , 3456))
{
	$errorcode = socket_last_error();
    $errormsg = socket_strerror($errorcode);
    
    die("Could not connect: [$errorcode] $errormsg \n");
}

echo "Connection established \n";
 
$continue_reading = 1;
$timestamp_since_last_recieved = microtime();
$complete_string_read = "";
while($continue_reading == 1)
{
  $read_as_string = socket_read($sock, 1048576, PHP_BINARY_READ);
  echo $read_as_string;
  if($read_as_string != "")
  {
    $complete_string_read = $complete_string_read + $read_as_string;
    $timestamp_since_last_recieved = microtime();
  }else if($read_as_string == "")
  {
    //break out of while loop if time out reached.
    if(time() >= ($timestamp_since_last_recieved+1000))
    {
      $continue_reading = 0;
    }
  }
}

//shut down (stop read writing) and close socket.
socket_shutdown($sock, 2);
socket_close($sock);


//print_f(explode($complete_string_read, "1B480158E1F30E0B6CEE7813E9ECF094BD6B3745");

//interpret data

// print data for now.
echo $complete_string_read;
 
 //has a search been invoked by the user/customer?
 if(isset($_GET["search_activated"]) == true)
 {
 $search_activated = $_GET["search_activated"];
 if(strlen($search_activated) > 0)
 {
   //search invoked by user/customer, either by search bar or unconventional method of url parameters.
   
   //loop through each file within the index folder to determine the result, a preindex created by a C program is nessecary to produce consistant results and a more pragmatic engine.
   $total_possible_results = count($simulated_index_folder, COUNT_NORMAL);
   $index = 0;
   while($index < $total_possible_results)
   {
     //this while search is producing the results but the c program should produce the results and this while search iterates theough the list.
     
     $total_possible_matching_phrases = count($simulated_index_folder[$index]["search_phrases"], COUNT_NORMAL);
     $index_of_possible_matching_phrases = 0;
     while($index_of_possible_matching_phrases < $total_possible_matching_phrases)
     {
       if($simulated_index_folder[$index]["search_phrases"][$index_of_possible_matching_phrases] == $search_activated)
       {
     
       echo $simulated_index_folder[$index]["title"];
       echo "<br/>";
       }
       $index_of_possible_matching_phrases = $index_of_possible_matching_phrases + 1;
     }
     
     $index = $index + 1;
   }
   }
   }
   
   
  ?>
  
    <div class="horizontal_spacer_threeem">&nbsp;</div>
  
 </body>
</html>
