<?php
usleep(rand(1000, 3000));
$allow_software_usage = 0;
$token = "";
if(isset($_POST["token"]) == true)
{
	$token = $_POST["token"];
}
$token_to_match = "b81bf90b90152555d2f1caeacef0d8aa60f849941df07c211898a6e64e94456f";

if(isset($_POST["password"]) == true)
{
	if(hash_equals($_POST["password"], "3cecc61248fda100eaf2f2b65dbfee73dd41d386de829ba7b1f5c7b16122afc5") == true)
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