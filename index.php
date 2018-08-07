<?php
/********************************************************************
* @name Index
* @abstract Main file, redirects to other pages
* @since Feb 12, 2006
* -------------------------------------------------------------------/
*
* 				Jameson Lopp jameson@unc.edu
* @author		Adi Unnithan adi@unc.edu
*				Daniel Watson dcwatson@email.unc.edu
*********************************************************************/

require('config.inc.php');

#-------use the hash password-----------#
$_POST['pass'] = md5($_POST['pass']);
#---------------------------------------#

if (isset($_POST['user']) && isset($_POST['pass'])) {
	$smarty->clear_all_assign();
	$user = new UserDAO();
	$user->set("username", $_POST['user']);
	$user->set("password", $_POST['pass']);
	if ($user->login()) {
		$_SESSION["user"] = serialize($user);
		$smarty->clear_all_assign();
	} else {
		$smarty->assign('loginError', "user/password is not valid.");
		$smarty->assign('user', $user);
	}
}

if (isset($_GET['registerSuccess'])) {
	$smarty->assign_by_ref('registerSuccess', unserialize(base64_decode($_GET['registerSuccess'])));
}

if (isset($_GET['registerError'])) {
	$smarty->assign('registerError', "Register failed: username exists");
	$smarty->assign('user', unserialize(base64_decode($_GET['registerError'])));
}

if (isset($_SESSION['user'])) {	
	$user = unserialize($_SESSION['user']);
	$userTasksDAO = new TaskDAO();
	$userTasksDAO->set('created_by', $user->get('id'));
	$tasks = $userTasksDAO->getUserTasks();
	
	$numCompleted = 0;
	$numProcessing = 0;
	$numQueued = 0;
	
	foreach ($tasks as $task) {
		if ($task->get('status') == '5') $numCompleted++;
		if ($task->get('status') == '3' || $task->get('status') == '4') $numProcessing++;
		if ($task->get('status') == '1') $numQueued++;	
	}
	
	$smarty->assign_by_ref('user', $user);
	$smarty->assign('numCompleted', $numCompleted);
	$smarty->assign('numProcessing', $numProcessing);
	$smarty->assign('numQueued', $numQueued);
	
	$smarty->display_page();
} else {
	$smarty->display_welcome();
}
?>
