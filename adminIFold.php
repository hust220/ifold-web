<?php
/********************************************************************
* @name AdminIFold
* @abstract - Manage Daemons, Manager eventually, etc.
* @since Feb 20, 2006
* -------------------------------------------------------------------/
*
* 				Jameson Lopp jameson@unc.edu
* @author		Adi Unnithan adi@unc.edu
*				Daniel Watson dcwatson@email.unc.edu
*********************************************************************/

require 'config.inc.php';
require_once IFOLD_DIR . 'lib/DaemonDAO.class.php';

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
else if ($user->get('level') >= 5) {
	$daemonDAO = new DaemonDAO();
	$daemons = $daemonDAO->getDaemons();
}

$props = new IFoldProps();
$smarty->assign_by_ref('daemonstatuses', $props->getDaemonStatuses());
$smarty->assign_by_ref('daemonactions', $props->getDaemonActions());
	
$smarty->assign_by_ref('user', $user);
$smarty->assign('daemonList', $daemons);
$smarty->display_page('adminIFold.tpl');

?>
