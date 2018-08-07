<?php
/********************************************************************
* @name Ajax Utilities
* @abstract - utility class to handle various ajax requests
* @since Feb 20, 2006
* -------------------------------------------------------------------/
*
* 				Jameson Lopp jameson@unc.edu
* @author		Adi Unnithan adi@unc.edu
*				Daniel Watson dcwatson@email.unc.edu
*********************************************************************/

require('config.inc.php');
require_once IFOLD_DIR . 'lib/TaskDAO.class.php';

// if not logged in, redirect to main page
if(!isset($_SESSION['user'])) 
{
	header('Location: index.php');
	return;
}
$user = unserialize($_SESSION['user']);
if ($user->get('level') < 5) 
	$admin = false;
	
// user is admin, so show everything.
else if ($user->get('level') >= 5) 
	$admin = true;

$props = new IFoldProps();
$foldstatus = $props->getStatusList();

$ajaxResponse = "";
header("Content-Type: text/xml");
$ajaxResponse .= '<?xml version="1.0" encoding="ISO-8859-1"?>';

if (isset($_GET['action'])) {
	
	if (($_GET['action'] == 'getCompletedTasks')) {
		
		$ajaxResponse .= '<ajax-response>';
		$ajaxResponse .= '<response type="object" id="completedQueueTable_updater">';
		$ajaxResponse .= '<rows update_ui="true">';
		$task = new TaskDAO();
		$options = "";
		
		if (isset($_GET['sort_col'])) {
			$options .= "ORDER BY ";
			switch ($_GET['sort_col']) {
				case 'name':
					$options .= "name ";
					break;
				case 'description':
					$options .= "description ";
					break;
				case 'completed':
					$options .= "completed_on ";
					break;
				case 'owner':
					$options .= "created_by ";
					break;
			}
			$options .= $_GET['sort_dir'] . " ";
		}
		
		if (isset($_GET['offset']) && isset($_GET['page_size'])) {
			$options .= "LIMIT " . $_GET['offset'] . "," .$_GET['page_size'] . " ";
		}
		$queue = $task->getQueue($admin, "status=5", $options);

		foreach ($queue as $task) {
			$ajaxResponse .= '<tr>';
			$ajaxResponse .= '<td>' . $task['task']->get('name') . '</td>';
			$ajaxResponse .= '<td>' . $task['task']->get('description') . '</td>';
			$ajaxResponse .= '<td>' . $task['task']->get('completed_on') . '</td>';
			$ajaxResponse .= '<td>' . $task['user']->get('username') . '</td>';
			$ajaxResponse .= '<td>';
			
			if (($task['task']->get('status') != 2) &&
				($task['task']->get('status') != 3) &&
				($task['task']->get('status') != 4) &&
				($task['task']->get('status') != 8)) {
				if ((($user->get('level') < 5) && ($task['user']->get('id') == $user->get('id'))) || 
					($user->get('level') > 5)) {
					$ajaxResponse .= "<img src=\"style/img/a_user-idelete.png\" " .
										"alt=\"Delete {$task['task']->get('name')}\" " .
										"title=\"Delete {$task['task']->get('name')}\" " .
										"style=\"cursor:pointer\" " .
										"onclick=\"if (confirm('Are you sure you want to delete the task: {$task['task']->get('name')}')) deleteRow(this, 'completedQueueMessages', true)\"/>";
				} else {
					$ajaxResponse .= " ";
				}
			}
			$ajaxResponse .= " ";
			if ((($user->get('level') < 5) && ($task['user']->get('id') == $user->get('id'))) || 
				($user->get('level') > 5)) {
				$ajaxResponse .= "<img src=\"style/img/edit-find-small.png\" " .
									"alt=\"Look at the task parameters for {$task['task']->get('name')}\" " .
									"title=\"Look at the task parameters for {$task['task']->get('name')}\" " .
									"style=\"cursor:pointer\" " .
									"onclick=\"return GB_show('Task Parameters', 'popTaskInformation.php?type=parameters&amp;id={$task['task']->get('id')}', 500, 500)\" /> ";
				$ajaxResponse .= "<img src=\"style/img/messages.png\" " .
										"alt=\"Look at the task messages for {$task['task']->get('name')}\" " .
										"title=\"Look at the task messages for {$task['task']->get('name')}\" " .
										"style=\"cursor:pointer\" " .
										"onclick=\"return GB_show('Task Messages', 'popTaskInformation.php?type=messages&amp;id={$task['task']->get('id')}', 170, 500)\" />";
			} else {
				$ajaxResponse .= " ";
			}
			
			$ajaxResponse .= '</td>';
			$ajaxResponse .= '</tr>';
		}
		$ajaxResponse .= '</rows>';
  		$ajaxResponse .= '</response>';
		$ajaxResponse .= '</ajax-response>';
		
	} else {
		$ajaxResponse .= '<ajax-response><response type="object">action {$_POST["action"]} not available</response></ajax-response>';
	}
	
} else {
	$ajaxResponse .= '<ajax-response><response type="object">no action defined</response></ajax-response>';
}

print $ajaxResponse;
?>
