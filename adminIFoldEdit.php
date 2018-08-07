<?php
/********************************************************************
* @name AdminIFoldEdit
* @abstract - Provides ifold management functionality
* @since Feb 22, 2006
* -------------------------------------------------------------------/
*
* 				Jameson Lopp jameson@unc.edu
* @author		Adi Unnithan adi@unc.edu
*				Daniel Watson dcwatson@email.unc.edu
*********************************************************************/

require('config.inc.php');
require_once IFOLD_DIR . 'lib/DaemonDAO.class.php';

// if not logged in, redirect to main page
if(!isset($_SESSION['user'])) 
{
	header('Location: index.php');
	return;
}
$user = unserialize($_SESSION['user']);

// user is not admin, thus redirect to main page
if ($user->get('level') < 5) 
	header('Location: index.php');

// user is admin, thus allow editing
else if ($user->get('level') >= 5) 
{
	if (isset($_POST['action'])) {
		if (($_POST['action'] == 'pauseDaemon')) {
			$daemonToEdit = new DaemonDAO();
			$daemonToEdit->set('id', $_POST['id']);
			$daemonToEdit->set('action', '2');
			if (! $daemonToEdit->save()) {
				print "failure";
				exit;
			}
		} else if (($_POST['action'] == 'wakeDaemon')) {
			$daemonToEdit = new DaemonDAO();
			$daemonToEdit->set('id', $_POST['id']);
			$daemonToEdit->set('action', '1');
			if (! $daemonToEdit->save()) {
				print "failure";
				exit;
			}
		} else {
			print "failure";
		}
		print "success";
	}
}