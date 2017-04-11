
<?php
include("functions.php");
  session_start();
  testAcces();
  include("boilerplate.php");
  if (isset($_GET['suppr'])) supprCategorie($_GET['suppr']);
?>
<body>
<div class="container">
<div class="header">
<nav><ul class="nav nav-pills pull-right">
<li role="presentation"><a href="index.php">Accueil</a></li>
<li role="presentation"><a href="search.php">Rechercher</a></li>
<li role="presentation"><a href="categories.php">Catégories</a></li>
<li role="presentation"><a href="connect.php">Connexion</a></li>
</ul></nav><h3 class="text-muted">Nom du site</h3>
</div>
    <div class="container">
  	<div class="jumbotron">
  		<h1 class="text-center">Catégories</h1>
  	</div>
    /*just to know that wa are in "catégories"
  	<div class="row">
	<div class="col-md-4">
		<nav id='menu'>
    	<h3>Menu</h3>
    	<ul class="nav nav-pills nav-stacked">
        <?php
          $cats = categories();
          foreach ($cats as $cat) {
            $nom = $cat['nom'];
            $id = $cat['id'];
            echo "<li>$nom <a href='petitions_in_cat.php?edite=$id'>editer</a> <a href='?suppr=$id'>supprimer</a></li>";
          }
        ?>
    	</ul>
  	</nav>
</div>
<div class="col-md-8">
  <section id='contenu'>
    <h1>Populaires</h1>
    <ul>
      <?php
      $petitions = petitions();/*we must create a function which return petitions having a cat*/
      foreach ($petitions as $petition) {
      $nom = $petition['nom'];
      $id = $petition['id'];
      /*here we must extract the article from database*/
        }
      ?>
    </ul>
  </section>
</div>
</div>
</body>
</html>
