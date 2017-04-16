<?php
include("config.php");

//
function siteTitle() {
	return $GLOBALS['siteTitle'];
}


// Permet de vérifier qu'un utilisateur peut voir la partie admin.
function testAcces() {
  if (!isset($_SESSION['connecte'])) die("Access interdit.");
}

// Pernet de vérifier le mot de passe
function auth($pass) {
  return $pass == $GLOBALS['blogPass'];
}

// Établi une connexion à la base
function db_connect() {
  $result = mysqli_connect($GLOBALS['dbServ'], $GLOBALS['dbUser'], $GLOBALS['dbPass'], $GLOBALS['dbName']);
	if (!$result) {
		throw new Exception("Impossible de se connecter à la base de données.";
	}
	else {
		return $result;
	}
}

// Vérifie si tous les champs du formulaire sont remplis
function valid_form($tab) {
	foreach ($tab as $key => $value) {
		if ((!isset($key)) || ($value == '')) {
			return false;
		}
	}
	return true;
}

// Vérifie si l'adresse email est valide
function valid_email($address) {
	if (ereg('^[a-zA-Z0-9_\.\-]+@[a-zA-Z0-9\-]+\.[a-zA-Z0-9\-\.]+$',$address)) {
		return true;
	}
	else {
		return false;
	}
}

// Ajoute les infos du nouvel user dans la database
function register($username, $email, $passwd) {
	$con=db_connect();
	$stmt = mysqli_prepare($con, "SELECT * FROM user WHERE username = ?");
	mysqli_stmt_bind_param($stmt,'s',$username);
	mysqli_stmt_execute($stmt);
	$res=mysqli_stmt_get_result($stmt);
	if(!$res) {
		throw new Exception("Impossible d'exécuter la requête.");
	}
	if (mysql_num_rows($res) > 0) {
		throw new Exception("Nom d'utilisateur déjà pris ! Veuillez recommencer avec un nom d'utilisateur différent.");
	}
	$stmt2 = mysqli_prepare($con, "INSERT INTO user (username, passwd, email) VALUES (?,?,?)");
	mysqli_bind_param($stmt2,'sss',$username, sha1($passwd), $email);
	mysqli_stmt_execute($stmt2);
	$res=mysqli_stmt_get_result($stmt2);
	if(!$res) {
		throw new Exception("Impossible de vous enregistrer dans la base de données. Veuillez recommencer plus tard");
	}
	mysqli_free_result($res);
	mysqli_close($con);
	return true;
	}
