<?php
include("functions.php");

$qDb = "CREATE DATABASE IF NOT EXISTS `PETITIONS`;";

$qSelDb = "USE `PETITIONS`;";

$qTbPetitions = "CREATE TABLE IF NOT EXISTS `petitions` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `category` varchar2(128) NOT NULL,
  `date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `title` varchar2(128) NOT NULL,
  `required_signature` int(50) NOT NULL,
  `current_signature` int(50),
  `goal` varchar2(255) NOT NULL,
  `problem` longtext NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB;";

$qTbUser = "CREATE TABLE IF NOT EXISTS `user` (
  `username` varchar2(50) NOT NULL,
  `passwd` varchar2(255) NOT NULL,
  `email` varchar2(100) NOT NULL,
  `f_name` varchar2(255) NOT NULL,
  `l_name` varchar2(255) NOT NULL,
  `address` longtext,
  PRIMARY KEY(`username`)
) ENGINE=InnoDB;";

$qTbBookmarks = "CREATE TABLE IF NOT EXISTS `bookmark` (
  `username` varchar2(50) NOT NULL,
  `id` int(11) NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (`id`, `username`),
  FOREIGN KEY (`username`) REFERENCES `user`(`username`),
  FOREIGN KEY (`id`) REFERENCES `petitions`(`id`)
) ENGINE=InnoDB;";


echo "Connexion au serveur MySQL.";

$con = db_connect();

echo "Création de la table pétitions.";
mysqli_query($con, $qTbPetitions);
echo mysqli_info($con);
echo mysqli_error($con);


echo "Création de la table User.";
mysqli_query($con, $qTbUser);
echo mysqli_info($con);
echo mysqli_error($con);

echo "Création de la table Bookmarks.";
mysqli_query($con, $qTbBookmarks);
echo mysqli_info($con);
echo mysqli_error($con);


mysqli_close($con);
?>
