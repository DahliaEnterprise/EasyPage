<?php
usleep(rand(1000, 3000));
$allow_software_usage = 0;
$token = "";
if(isset($_POST["token"]) == true)
{
	$token = $_POST["token"];
}
$token_to_match = "";

if(isset($_POST["password"]) == true)
{
	if(hash_equals($_POST["password"], "") == true)
	{
		usleep(rand(500, 3000));
		if(isset($_POST["username"]) == true)
		{
			if($_POST["username"]	== "xenland")
			{
			
				$token = $token_to_match;
				$allow_software_usage = 1;
			
			}
		}
	}
}
	?>
