<!DOCTYPE HTML>
<?php include("functions.php") ?>
<html lang="fr">
<?php include("head.php") ?>
<body>
  <?php
  $email=$_POST['email'];
  $username=$_POST['username'];
  $passwd=$_POST['passwd'];
  $passwd2=$_POST['passwd2'];
  session_start();
  try {
    if (!valid_form($_POST)) {
      throw new Exception("Vous n'avez pas bien rempli le formulaire ! Veuillez recommencer l'incription.");
    }
    if (!valid_email($email)) {
      throw new Exception("Adresse email incorrecte !  Veuillez recommencer l'inscription.");
    }
    if ($passwd  != $passwd2) {
      throw new Exception("Mots de passe non-identiques ! Veuillez recommencer l'inscription.");
    }
    if (strlen($passwd < 6)) {
      throw new Exception("Mot de passe trop court ! Veuillez recommencer l'inscription.");
    }
    register($username, $email, $passwd);
    $_SESSION['valid_user'] = $username;
    include("header.php");
    echo "Inscription réussie ! Vous pouvez dés à présent éditer votre ".?><a href="profile.php">profile</a> <?php
    include("footer.php");
  } catch (Exception $e) {
    include("header.php");
    echo "Il y a un problème";
    include("footer.php");
    exit;
  }
  ?>
