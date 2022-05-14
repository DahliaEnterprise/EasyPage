CREATE TABLE `credentials` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `user_name` varchar(255) DEFAULT NULL,
  `password` varchar(255) DEFAULT NULL,
  `password_user_specific_salt` varchar(255) DEFAULT NULL,
  `password_input_repeat` int(11) DEFAULT NULL,
  `password_hash_repeat` int(11) DEFAULT NULL,
  `timestamp_credential_created` int(11) DEFAULT NULL,
  `kyc_firstname` varchar(31) DEFAULT NULL,
  `kyc_lastname` varchar(31) DEFAULT NULL,
  `kyc_birthyear` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`)
)
