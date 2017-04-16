<?php
session_start();
include("functions.php")

?>

<!DOCTYPE HTML >
<html lang="fr">
<?php include("head.php") ?>
<body>
  <?php
  include("header.php");
  $username=$_POST['username'];
  $passwd=$_POST['passwd'];
  if ($username & $passwd) {
    // The user is trying to connect
    try {
      login($username, $passwd);
      // On enregistre son ID s'il est dans la base
      $_SESSION['valid_user']=$username;
    } catch (Exception $e) {
      // Connexion failed
      echo "Vous ne pouvez pas vous connecter ! Vous devez vous connecter pour voir cette page";
      include("footer.php");
    }
  }
  check_valid_user();
  // On affiche son profil puis on gère l'accès à la base de données et tout tout :))
  include("footer.php");
  ?>
</body>
</html>
