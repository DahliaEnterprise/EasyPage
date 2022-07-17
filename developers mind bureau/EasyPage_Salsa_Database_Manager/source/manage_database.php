<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
  <head>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
    <title>Shasta Exchange</title>
 
    <style type="text/css">
       .about_the_company {
     border-radius: 10px;
     background: #008CBA;
     border: 3px solid #000000;
     margin: 0 0.5em 0.5em 0.5em;
     font-size: 3.5em;
     color: #ffffff;
     padding: 1em;
    }
    </style>
  
    
    <link rel="stylesheet" href="/include_stylesheet.css"/>
  </head>
  <body>
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
 
   if($allow_software_usage == 0)
   {
   ?>
    <div style="margin: 3em;">&nbsp;</div>
    <div class="menu_header">
     Salsa Database Manager <a href="http://www.shastaexchange.com">Shasta Exchange</a>
    </div>
    <div class="about_the_company">
     <div style="text-align: center;">Request Authorization</div>
     <form action="manage_database.php" method="post">
     <input type="text" name="username" style="font-size: 1em;"/><br/>
     <input type="password" name="password" style="font-size: 1em;"/><br/>
     <div style="text-align:center;">
     <input type="submit" style="font-size:1em;" value="Submit Request"/>
     </div>
     </form>
    </div>
    <div style="margin:3em;"></div> 
		<form action="https://www.paypal.com/donate" method="post" target="_top">
<input type="hidden" name="hosted_button_id" value="ML2XZ27UANAL8" />
<input type="image" src="https://www.paypalobjects.com/en_US/i/btn/btn_donateCC_LG.gif" border="0" name="submit" title="PayPal - The safer, easier way to pay online!" alt="Donate with PayPal button" />
<img alt="" border="0" src="https://www.paypal.com/en_US/i/scr/pixel.gif" width="1" height="1" />
</form>

		
   <?php
   }else{
   ?>
   <div style="margin: 3em;">&nbsp;</div>
    <div class="menu_header">
     Salsa Database Manager 
    </div>
    <div class="about_the_company">
     <a href="#">List databases</a>
    </div>
    
    <div style="margin:3em;"></div> 
    <?php } ?>
    <div style="text-align:center;">
		<form action="https://www.paypal.com/donate" method="post" target="_top">
<input type="hidden" name="hosted_button_id" value="ML2XZ27UANAL8" />
<input type="image" src="https://www.paypalobjects.com/en_US/i/btn/btn_donateCC_LG.gif" border="0" name="submit" title="PayPal - The safer, easier way to pay online!" alt="Donate with PayPal button" />
<img alt="" border="0" src="https://www.paypal.com/en_US/i/scr/pixel.gif" width="1" height="1" />
</form>

		<div style="margin:3em;"></div> 
    <div style="margin:0.5em;text-align:center; color:#ffffff; font-size:2.5em;">Software created by Shane Bryan Betz</div>
    <div style="margin:6em;"></div>
   </body>
</html>
