<?php	
$dsn = "mysql:host=127.0.0.1;dbname=".$_POST["database_name"].";charset=utf8mb4";
		$options = [
PDO::ATTR_ERRMODE            => PDO::ERRMODE_EXCEPTION,
PDO::ATTR_DEFAULT_FETCH_MODE => PDO::FETCH_ASSOC,
PDO::ATTR_EMULATE_PREPARES   => false,
PDO::ATTR_PERSISTENT => false
];
try {
	$connection = new PDO($dsn, $_POST["database_username"], $_POST["database_password"], $options);
} catch (PDOException $e)
{
	var_dump($e);
//  throw new PDOException($e->getMessage(), (int)$e->getCode());
}
try{
	$query_in_progress = $connection->prepare("SELECT * FROM Persons" /*$_POST["select_query"]*/);
}catch(PDOException $e)
{
	var_dump($e);
}

$query_in_progress->execute();

$table_created = 0;
$keep_fetching = 1;
while($keep_fetching == 1)
{
	$fetched = $query_in_progress->fetch(PDO::FETCH_ASSOC);
	if(is_array($fetched)== false)
	{
		$keep_fetching = 0;
	}else if(is_array($fetched) == true)
	{
		$keys = array_keys($fetched);
		$total_keys = count($keys);
		$index = 0;
		if($table_created == 0)
		{
			echo '<table style="border:1px solid #000; width:99%;">';
			echo '<tr>';
		
			while($index < $total_keys)
			{
				if($index < ($total_keys-1))
				{
				echo '<td style="text-align:center;font-size:0.5em;border-right:1px solid black;">';
				}else if($index == ($total_keys-1))
				{
					echo '<td style="font-size:0.5em;">';
				}
			  echo $keys[$index]; 
				echo '</td>';
				
				$index = $index + 1;
			}
			
			echo '</tr>';
			
			$table_created = 1;
		}
		
		echo '<tr>';
		
		$keys = array_keys($fetched);
		$total_keys = count($keys);
		$index = 0;
		while($index < $total_keys)
		{
			if($index < ($total_keys-1))
			{
				echo '<td style="font-size:0.5em;border-top:1px solid #000;border-right:1px solid #000;">';
			}else if($index == ($total_keys-1))
			{
					echo '<td style="font-size:0.5em;border-top:1px solid #000;">';
			}
			echo $fetched[$keys[$index]];
			echo '</td>';
			$index = $index + 1;	
		}	
		echo '</tr>';
	
	}
}
echo "</table>";
?>
