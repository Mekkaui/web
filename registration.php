<!DOCTYPE HTML>
<html lang="fr">
<?php include("head.php") ?>
<body>
  <?php include("header.php") ?>
  <form action="registration.php" method="post">
    <p>Prénom <input type="text" placeholder="Prénom" name="f_name"/> </p>
    <p>Nom<input type="text" placeholder="Nom" name="l_name"/> </p>
    <p>Pseudo<input type="text" placeholder="Pseudo" name="username"/></p>
    <p>Email<input type="email" placehoolder="Adresse email valide" name="email"/></p>
    <p>Sexe
    <select name="gender">
      <option value="M"> Masculin </option>
      <option value="F"> Féminin </option>
    </select> </p>
    <p> Mot de passe <input type="password" placeholder="Au moins 6 caractères " name="passwd"/></p>
    <p> Confirmer le mot de passe <input type="password" placeholder="Au moins 6 caractères " name="passwd2"/></p>
    <div>
      <input type="submit" value="Inscription"/>
    </div>
  </form>
  <?php include("footer.php") ?>
</body>
</html>
