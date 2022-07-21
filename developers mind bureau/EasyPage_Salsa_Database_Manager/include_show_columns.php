<table style="border:solid #000 1px; width:99%;">
						 <tr>
							 <td style="text-align:center;">
								 Name
								</td>
								<td style="text-align:center;">
									Type
								</td>
							</tr>
						<?php
					 	$dsn = "mysql:host=127.0.0.1;dbname=".$_POST["database_name"].";charset=utf8mb4";
					$options = [
					    PDO::ATTR_ERRMODE            => PDO::ERRMODE_EXCEPTION,
					    PDO::ATTR_DEFAULT_FETCH_MODE => PDO::FETCH_ASSOC,
					    PDO::ATTR_EMULATE_PREPARES   => false,
					    PDO::ATTR_PERSISTENT => false
					];
					try {
					     $connection = new PDO($dsn, $_POST
							 ["database_username"], $_POST["database_password"], $options);
					} catch (PDOException $e) {
						var_dump($e);
					   //  throw new PDOException($e->getMessage(), (int)$e->getCode());
					}
					try{
 						$query_in_progress = $connection->query("DESCRIBE ".$_POST["table_name"]);
					}catch(PDOException $e)
						{
							var_dump($e);
						}
						$query_in_progress->execute();
						
						$keep_fetching = 1;
						while($keep_fetching == 1)
						{
								$fetched = $query_in_progress->fetch();
								
								if($fetched == false)
								{
										$keep_fetching = 0;
								}else{
									?>
									<tr>
									<td style="text-align:center;border:1px solid #000;">
											<?php echo $fetched["Field"]; ?>
										</td>
											<td style="text-align:center;border:1px solid #000;">
											<?php echo $fetched["Type"]; ?>
										</td>
									</tr>
									<?php
								}
								
								
							}
						}
					?>
				</table>
