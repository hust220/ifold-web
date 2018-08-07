<?php
/********************************************************************
* @name ActivityEdit
* @abstract - Functions to edit activity outputs and such
* @since Feb 27, 2006
* -------------------------------------------------------------------/
*
* 				Jameson Lopp jameson@unc.edu
* @author		Adi Unnithan adi@unc.edu
*				Daniel Watson dcwatson@email.unc.edu
*********************************************************************/

require('config.inc.php');
require_once IFOLD_DIR . 'lib/TaskDAO.class.php';
require_once IFOLD_DIR . 'lib/OutputDAO.class.php';

// if not logged in, redirect to main page
if(!isset($_SESSION['user'])) 
{
	header('Location: index.php');
	return;
}
$user = unserialize($_SESSION['user']);

$fetchOutput = new OutputDAO();
$fetchOutput->fetch($_POST['id']);
$task = new TaskDAO();
$task->fetch($fetchOutput->get('task_id'));

// user is not admin, thus redirect to main page
if (($user->get('id') == $task->get('created_by')) || ($user->get('level') >= 5)) {
	if (isset($_POST['action'])) {
		if (($_POST['action'] == 'deleteOutput')) {
			if (! $fetchOutput->delete()) {
				print "Error: Could not delete output. Try again later.";
			} else {
				print "Success: Deleted output '" . $fetchOutput->get('fileName') . "'";
			}
		}
	} else {
		print "Error: Unknown Action...";
	}
} else {
	print "Error: You do not have privileges.";
}

?>
