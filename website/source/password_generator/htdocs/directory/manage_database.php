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
	
		<script type="text/javascript">
			function form_type_changed()
			{
				//update forms to carry the form type information.
				let nodeList = document.querySelectorAll(".relayformtype");
				for (let i = 0; i < nodeList.length; i++) {
  				nodeList[i].value = document.getElementById("form_type").value;
				}
				
				//hide all
				let form_ids = ["div_list_tables", "div_list_databases", "div_list_tables", "div_list_columns", "div_select_results","div_update_results"];
				let index = 0;
				
				while(index < form_ids.length)
				{
					
					document.getElementById(form_ids[index]).style.display = "none";
				  index = index + 1;
				}
				
				//show selected
				document.getElementById(document.getElementById("form_type").value).style.display = "block";
			}
		</script>
  </head>
  <body onLoad="form_type_changed()">
   <?php 
	 
	 include('./include_authorization.php');
	 
	 if(isset($_POST["token"]) == true)
	 {
			if(hash_equals($_POST["token"], $token_to_match) == true)
			{
				$allow_software_usage = 1;
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
		

   <?php
			}else
			{
		 
   ?>
   <div style="margin: 3em;">&nbsp;</div>
    <div class="menu_header">
     Salsa Database Manager 
    </div>
    <div class="about_the_company">
			<select name="form_type" id="form_type" onchange="form_type_changed();" style="font-size:1em">
					<option value="div_list_databases" <?php if(isset($_POST["relay_formtype"])){ if($_POST["relay_formtype"] == "div_list_databases"){ echo "selected"; } }?>>List Databases</option>
					<option value="div_list_tables" <?php if(isset($_POST["relay_formtype"])){ if($_POST["relay_formtype"] == "div_list_tables"){ echo "selected"; } }?> >List Tables</option>
					<option value="div_list_columns"<?php if(isset($_POST["relay_formtype"])){ if($_POST["relay_formtype"] == "div_list_columns"){ echo "selected"; } }?> >List columns</option>
					<option value="div_select_results" <?php if(isset($_POST["relay_formtype"])){ if($_POST["relay_formtype"] == "div_select_results"){ echo "selected"; } }?>>Select Statement</option>
					<option value="div_update_results" <?php if(isset($_POST["relay_formtype"])){ if($_POST["relay_formtype"] == "div_update_results"){ echo "selected"; } }?>>update Statement</option>
					
				</select>
				<div style="margin:1em 0 1em 0;"><hr/></div>
				
					<div id="div_list_databases" style="display:none;">
						
				<form action="manage_database.php" method="post">
					
				<input type="text" placeholder="Database Username" name="database_username" <?php if(isset($_POST["database_username"])){ echo 'value="'.$_POST["database_username"].'"';} ?> style="font-size:1em;"/>
				<input type="password" placeholder="Database password" name="database_password" <?php if(isset($_POST["database_password"])){ echo 'value="'.$_POST["database_password"].'"';} ?> style="font-size:1em;"/>
				<input type="database" placeholder="Database" name="database_name" <?php if(isset($_POST["database_name"])){ echo 'value="'.$_POST["database_name"].'"';} ?> style="font-size:1em;"/>
				<input type="hidden" name="token" value="<?php echo $token; ?>"/>
				<input type="hidden" name="actiontype" value="listDatabases"/>
				<input type="hidden" name="relay_formtype" value="" class="relayformtype"/>
			  <input type="submit" value="Request List Databases" style="font-size:1em;" />
				
			</form>
		</div>
		
			
			<div id="div_list_tables" style="display:none;">
			<form action="manage_database.php" method="post">
			<input type="text" placeholder="Database Username" name="database_username" <?php if(isset($_POST["database_username"])){ echo 'value="'.$_POST["database_username"].'"';} ?> style="font-size:1em;"/>
			<input type="password" placeholder="Database password" name="database_password" <?php if(isset($_POST["database_password"])){ echo 'value="'.$_POST["database_password"].'"';} ?> style="font-size:1em;"/>
			<input type="database" placeholder="Database" name="database_name" <?php if(isset($_POST["database_name"])){ echo 'value="'.$_POST["database_name"].'"';} ?> style="font-size:1em;"/>
			<input type="hidden" name="token" value="<?php echo $token; ?>"/>
			<input type="hidden" name="actiontype" value="showTables"/>
			<input type="hidden" name="relay_formtype" value="" class="relayformtype"/>
		  <input type="submit" value="Request List of Tables" style="font-size:1em;" />
			
			</form>
			</div>
				
					
						<div id="div_list_columns" style="display:none;">
							
			<form action="manage_database.php" method="post">
			<input type="text" placeholder="Database Username" name="database_username" <?php if(isset($_POST["database_username"])){ echo 'value="'.$_POST["database_username"].'"';} ?> style="font-size:1em;"/>
			<input type="password" placeholder="Database password" name="database_password" <?php if(isset($_POST["database_password"])){ echo 'value="'.$_POST["database_password"].'"';} ?> style="font-size:1em;"/>
			<input type="text" placeholder="Database" name="database_name" <?php if(isset($_POST["database_name"])){ echo 'value="'.$_POST["database_name"].'"';} ?> style="font-size:1em;"/>
			<input type="text" placeholder="Table Name" name="table_name" <?php if(isset($_POST["table_name"])){ echo 'value="'.$_POST["table_name"].'"';} ?> style="font-size:1em;"/>
			<input type="hidden" name="token" value="<?php echo $token; ?>"/>
			<input type="hidden" name="actiontype" value="showColumns"/>
			<input type="hidden" name="relay_formtype" value="" class="relayformtype"/>
		  <input type="submit" value="Request List of Columns" style="font-size:1em;" />
				
		</form>
	</div>
			
					<div id="div_select_results" style="display:none;">
						
				<form action="manage_database.php" method="post">
			<input type="text" placeholder="Database Username" name="database_username" <?php if(isset($_POST["database_username"])){ echo 'value="'.$_POST["database_username"].'"';} ?> style="font-size:1em;"/>
			<input type="password" placeholder="Database password" name="database_password" <?php if(isset($_POST["database_password"])){ echo 'value="'.$_POST["database_password"].'"';} ?> style="font-size:1em;"/>
			<input type="text" placeholder="Database" name="database_name" <?php if(isset($_POST["database_name"])){ echo 'value="'.$_POST["database_name"].'"';} ?> style="font-size:1em;"/>
			<input type="text" placeholder="SELECT * FROM table_name" name="select_query" <?php if(isset($_POST["select_query"])){ echo 'value="'.$_POST["select_query"].'"';} ?> style="font-size:1em;"/>
			<input type="hidden" name="token" value="<?php echo $token; ?>"/>
			<input type="hidden" name="actiontype" value="showSelectResults"/>
			<input type="hidden" name="relay_formtype" value="" class="relayformtype"/>
		  <input type="submit" value="Request Result" style="font-size:1em;" />
				
		</form>
		
    </div>
		
		<div id="div_update_results" style="display:none;">
						
				<form action="manage_database.php" method="post">
			<input type="text" placeholder="Database Username" name="database_username" <?php if(isset($_POST["database_username"])){ echo 'value="'.$_POST["database_username"].'"';} ?> style="font-size:1em;"/>
			<input type="password" placeholder="Database password" name="database_password" <?php if(isset($_POST["database_password"])){ echo 'value="'.$_POST["database_password"].'"';} ?> style="font-size:1em;"/>
			<input type="text" placeholder="Database" name="database_name" <?php if(isset($_POST["database_name"])){ echo 'value="'.$_POST["database_name"].'"';} ?> style="font-size:1em;"/>
			<input type="text" placeholder="UPDATE table_name SET column_name = newvalue" name="update_query" <?php if(isset($_POST["update_query"])){ echo 'value="'.$_POST["update_query"].'"';} ?> style="font-size:1em;"/>
			<input type="hidden" name="token" value="<?php echo $token; ?>"/>
			<input type="hidden" name="actiontype" value="showUpdateResults"/>
			<input type="hidden" name="relay_formtype" value="" class="relayformtype"/>
		  <input type="submit" value="Request Result" style="font-size:1em;" />
				
		</form>
		
	</div>
		
		</div>
		
		 <div style="margin: 3em;">&nbsp;</div>
    <div class="menu_header">
     Result 
	 </div>
		 <div class="about_the_company">
		<?php
			
			if(isset($_POST["database_password"]) == true)
			{
				if(isset($_POST["actiontype"]) == true)
				{
				if($_POST["actiontype"] == "listDatabases")
					{
						include("./include_results_listdatabases.php");
					}else if($_POST["actiontype"] == "showTables")
					{
					 
						include("./include_show_tables.php");
					}else if($_POST["actiontype"] == "showColumns")
					{
						include("./include_show_columns.php");
					}else if($_POST["actiontype"] == "showSelectResults")
					{
						include("./include_show_select_results.php");
			
					}else if($_POST["actiontype"] == "showUpdateResults")
					{
						include("./include_show_update_results.php");
			
					}
				}
		 }
		 
		 ?>
    </div>
		<?php } //closing allow_software_usage ?>
    <div style="margin:3em;"></div> 
	
    
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