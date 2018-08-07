<?php
/********************************************************************
* @name UserEdit
* @abstract - Provides user account editing functionality 
* @since Mar 1, 2006
* -------------------------------------------------------------------/
*
* @author		Jameson Lopp jameson@unc.edu
*				Adi Unnithan adi@unc.edu
*				Daniel Watson dcwatson@email.unc.edu
*********************************************************************/

require('config.inc.php');

// if not logged in, redirect to main page
if(!isset($_SESSION['user'])) 
{
	header('Location: index.php');
	return;
}
$user = unserialize($_SESSION['user']);

if (isset($_POST['action'])) {
	if (($_POST['action'] == 'update')) {
		$userToEdit = new UserDAO();
		$userToEdit->set("id", $user->get('id'));
		$userToEdit->set($_POST['name'], $_POST['value']);
		
		// user edited successfully, return to user edit
		if (! $userToEdit->save()) {
			print "Error in updating the '" . $_POST['name'] . "' field. Please try again later.";
			exit;
		}
	}
	else if (($_POST['action'] == 'delete')) {
		$userToDel = new UserDAO();
		$userToDel->set("id", $user->get('id'));

		// user account deleted, log out
		if (! $userToDel->delete()) {
			print "Error in deletion. Please try again later.";
		} else {
			header('Location: logout.php');
		}
		exit;
	}
	else {
		print "Unknown Action...";
	}
}
	
print "Saved the ''" . $_POST['name'] . "' field'!";

?>