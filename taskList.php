<?php
/********************************************************************
* @name TaskList
* @abstract - Provides task viewing functionality 
* @since Feb 20, 2006
* -------------------------------------------------------------------/
*
* @author		Jameson Lopp jameson@unc.edu
* @author		Adi Unnithan adi@unc.edu
*				Daniel Watson dcwatson@email.unc.edu
*********************************************************************/

require_once 'config.inc.php';
require_once IFOLD_DIR . 'lib/TaskDAO.class.php';

// if not logged in, redirect to main page
if(!isset($_SESSION['user'])) 
{
	header('Location: index.php');
	return;
}

$user = unserialize($_SESSION['user']);
$task = new TaskDAO();

// user is not admin, thus only show only the date it
// was created, the status, and the queue number.
if ($user->get('level') < 5) 
	$admin = false;
	
// user is admin, so show everything.
else if ($user->get('level') >= 5) 
	$admin = true;
	
$queue = $task->getQueue($admin, null, "ORDER BY queuenum");

$props = new IFoldProps();
$smarty->assign_by_ref('foldstatus', $props->getStatusList());
$smarty->assign_by_ref('user', $user);
$smarty->assign_by_ref('queue', $queue);
$smarty->display_page('taskList.tpl');

?>
