<?php
/********************************************************************
* @name Logout
* @abstract Logout handling, destroy the session
* @since Feb 12, 2006
* -------------------------------------------------------------------/
*
* 				Jameson Lopp jameson@unc.edu
* @author		Adi Unnithan adi@unc.edu
*				Daniel Watson dcwatson@email.unc.edu
*********************************************************************/

require_once('config.inc.php');

session_destroy();

header('Location: index.php');
?>
