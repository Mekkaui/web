<!DOCTYPE html>
<html lang="fr">
<?php include("head.php") ?>

<body>

	<!-- header starts from here -->
	<header>
		<?php include("header.php") ?>
	</header>
	<!-- end of header -->


	<!-- Le contenu de la page doit être ici -->
	<!-- Bouton execution modal -->
	<button class="btn btn-primary btn-lg" data-toggle="modal" data-target="#myModal">
	  Lancer la modal
	</button>

	<!-- Modal -->
	<div class="modal fade" id="myModal" tabindex="-1" role="dialog" aria-labelledby="myModalLabel" aria-hidden="true">
		<div class="modal-dialog">
			<div class="modal-content">
				<div class="modal-header">
					<button type="button" class="close" data-dismiss="modal" aria-hidden="true">&times;</button>
					<h4 class="modal-title" id="myModalLabel">Modal title</h4>
				</div>
				<div class="modal-body">
					<p>Vous n'avez pas de compte ? <a href="registration.php"> Inscription </a> </p>

					<div>
						<form action="header.php" method="post">
							<input type="text" placeholder="Votre pseudo" name="username" />
							<input type="passwd" placeholder="Mot de passe (Au moins 6 caractères)" name="passwd" />
							<input type="submit" value="Connexion" />
						</form>
					</div>
				</div>
			</div><!-- /.modal-content -->
		</div><!-- /.modal-dialog -->
	</div><!-- /.modal -->





	<!--footer starts from here-->
	<footer>
		<?php include("footer.php") ?>

	</footer>
	<!-- end of footer -->
</body>
</html>
