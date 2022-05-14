CREATE TABLE `account` (
  `id` bigint(20) NOT NULL AUTO_INCREMENT,
  `account_name_id` bigint(20) DEFAULT NULL,
  `source_account_id` bigint(20) DEFAULT NULL,
  `destination_account_id` bigint(20) DEFAULT NULL,
  `total_united_states_pennies` bigint(20) DEFAULT NULL,
  `total_united_states_pennies_written_form` varchar(255) DEFAULT NULL,
  `timestamp_microseconds` bigint(20) DEFAULT NULL,
  PRIMARY KEY (`id`)
)
