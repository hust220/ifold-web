<?php
/********************************************************************
* @name AdminUserList
* @abstract - Lists users for admins
* @since Feb 20, 2006
* -------------------------------------------------------------------/
*
* @author		Jameson Lopp jameson@unc.edu
* @author		Adi Unnithan adi@unc.edu
*				Daniel Watson dcwatson@email.unc.edu
*********************************************************************/

require 'config.inc.php';

// if not logged in, redirect to main page
if (! isset($_SESSION["user"])) {
	header('Location: index.php');
	return;
}

$user = unserialize($_SESSION['user']);
$smarty = new SmartyIfold();

// user is not admin, thus redirect to main page
if ($user->get('level') < 5) 
	header('Location: index.php');

// user is admin, thus show all users
else if ($user->get('level') >= 5) 
	$users = $user->getUsers();

$smarty->assign_by_ref('user',$user);
$smarty->assign_by_ref('userList', $users);
$smarty->display_page('adminUserList.tpl');

?>