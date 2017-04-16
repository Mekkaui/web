<!DOCTYPE HTML>

<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.12.4/jquery.min.js"></script>
<script src="js/bootstrap.min.js"></script>
<nav class="navbar navbar-default">
  <div class="container-fluid">
    <!-- Brand and toggle get grouped for better mobile display -->
    <div class="navbar-header">
      <button type="button" class="navbar-toggle collapsed" data-toggle="collapse" data-target="#bs-example-navbar-collapse-1" aria-expanded="false">
        <span class="sr-only">Toggle navigation</span>
        <span class="icon-bar"></span>
        <span class="icon-bar"></span>
        <span class="icon-bar"></span>
      </button>
      <a class="navbar-brand" href="index.php">MM'IMK Pétitions</a>
    </div>

    <!-- Collect the nav links, forms, and other content for toggling -->
    <div class="collapse navbar-collapse" id="bs-example-navbar-collapse-1">

      <form class="navbar-form navbar-right">
        <div class="form-group">
          <input type="text" class="form-control" placeholder="Search">
        </div>
        <button type="button" class="btn btn-default">
          <span class="glyphicon glyphicon-search" aria-hidden="true"></span> Rechercher
        </button>
      </form>
      <ul class="nav navbar-nav navbar-right">

        <li class="dropdown">
          <a href="#" class="dropdown-toggle" data-toggle="dropdown" role="button" aria-haspopup="true" aria-expanded="false">Catégories <span class="caret"></span></a>
          <ul class="dropdown-menu">
            <li><a href="#">Société</a></li>
            <li><a href="#">Politique</a></li>
            <li><a href="#">Sports</a></li>
            <li><a href="#">Sciences</a></li>
            <li><a href="#">Education</a></li>
            <li><a href="#">Economie</a></li>
            <li><a href="#">Environnement</a></li>
            <li role="separator" class="divider"></li>
            <li><a href="#">Autres</a></li>
          </ul>
        </li>
        <li role="button" data-toggle="modal" data-target="#myModal" class="btn btn-default" aria-haspopup="true" aria-expanded="false"/> Connexion </li>
      </ul> 
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




    	</div>
    </div>

<!--



          <div id="demoLightbox" class="lightbox hide fade"  tabindex="-1" role="dialog" aria-hidden="true">
            <div class='lightbox-content'>
              <img src="image.png">
              <div class="lightbox-caption"><p>Your caption here</p></div>
            </div>
          </div>




          <div>
            <label class="button" for="modalCheck">Connexion</label>
            <input type="checkbox" id="modalCheck" />
            <div class="modalLayer">
              <div class="popup_block">
                <label for="modalCheck"><img alt="Fermer" title="Fermer la fenêtre" class="btn_close" src="close_pop.png"/></label>


                <p>
                   Connexion
                  <p>Vous n'avez pas de compte ? <a href="registration.php"> Inscription </a> </p>

                  <div>
                    <form action="header.php" method="post">
                      <input type="text" placeholder="Votre pseudo" name="username" />
                      <input type="passwd" placeholder="Mot de passe (Au moins 6 caractères)" name="passwd" />
                      <input type="submit" value="Connexion" />
                    </form>
                  </div>


                </p>

              </div>
            </div>
          </div>   -->


        </a></li>




      </ul>
    </div><!-- /.navbar-collapse -->
  </div><!-- /.container-fluid -->
</nav>
