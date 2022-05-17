<?php
//conceal hashing techniques, make bruteforce attempts wait before knowing the result of their failure, sleep time decreaes chances of guessing password at random by thousands of year of ten seconds per wait.
if(isset($_POST["attempt"]) == true)
{
	if($_POST["attempt"]	== "1")
{
sleep(10);
echo "yeah";
}
}
?>
<html>
 <head>
	 
 </head>
 <body>
	 <?php
	   var_dump($_POST);
	 ?>
	 <form action="/accounting/login.php" method="post">
		 <input type="hidden" name="attempt" value="1" >
		 <input type="text" name="username" >
		 <input type="password" name="password" >
		 <input type="submit" >
	 </form>
	 
 </body>
</html>
