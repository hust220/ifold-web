<?php
/********************************************************************
* @name Activity
* @abstract - Displays recent tasks submitted by user 
* @since Feb 27, 2006
* -------------------------------------------------------------------/
*
* @author		Jameson Lopp jameson@unc.edu
* @author		Adi Unnithan adi@unc.edu
*				Daniel Watson dcwatson@email.unc.edu
*********************************************************************/

require('config.inc.php');

if(!isset($_SESSION['user'])) // if not logged in, redirect to main page
{
	header('Location: index.php');
	return;
}

$user = unserialize($_SESSION['user']);
$smarty = new SmartyIfold();
$props = new IFoldProps();

$taskObject = new TaskDAO();
$taskObject->set('created_by', $user->get('id'));
$outputs = $taskObject->getUserOutputTasks();
$tasks = $taskObject->getUserTasks();


$smarty->assign_by_ref('outputtypes', $props->getOutputTypes());
$smarty->assign_by_ref('foldstatus', $props->getStatusList());
$smarty->assign_by_ref('user',$user);
$smarty->assign_by_ref('taskList', $tasks);
$smarty->assign_by_ref('outputList', $outputs);

$smarty->display_page('activity.tpl');

?>
