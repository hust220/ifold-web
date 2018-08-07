<?php
/********************************************************************
* @name TaskListEdit
* @abstract - Provides task editing functionality
* @since Feb 22, 2006
* -------------------------------------------------------------------/
*
* 				Jameson Lopp jameson@unc.edu
* @author		Adi Unnithan adi@unc.edu
*				Daniel Watson dcwatson@email.unc.edu
*********************************************************************/

require('config.inc.php');
require_once IFOLD_DIR . 'lib/TaskDAO.class.php';
require_once IFOLD_DIR . 'lib/TaskParamsDAO.php';

// if not logged in, redirect to main page
if(!isset($_SESSION['user'])) 
{
	header('Location: index.php');
	return;
}
$user = unserialize($_SESSION['user']);

$task = new TaskDAO();
$task->fetch($_REQUEST['id']);

// user is not admin, thus redirect to main page
if (($user->get('id') == $task->get('created_by')) || ($user->get('level') >= 5)) {
	if (isset($_REQUEST['action'])) {
		if (($_REQUEST['action'] == 'delete')) {
			
			$fetchTask = new TaskDAO();
			$fetchTask->fetch($_REQUEST['id']);
			if (($fetchTask->get('status') == 1) || ($fetchTask->get('status') == 5)) {
				$conn->StartTrans();
				
				if (! $conn->execute("DELETE FROM taskoutputs WHERE task_id = " . $conn->qstr($_REQUEST['id'],get_magic_quotes_gpc()))) {
					$completeError = "Error in deleting task outputs.";
					$conn->FailTrans();
				}
				
				$taskToDel = new TaskDAO();
				if (! $taskToDel->fetch($_REQUEST['id'])) {
					$completeError = "Error in finding the task.";
					$conn->FailTrans();
				}
				
				$paramId = $taskToDel->get('param_id');
				
				if (! $taskToDel->delete()) {
					$completeError = "Error in deleting task.";
					$conn->FailTrans();
				}
				
				$taskParamsToDel = new TaskParamsDAO();
				
				if (! $taskParamsToDel->fetch($paramId)) {
					$completeError = "Error in finding the task parameters.";
					$conn->FailTrans();
				}
				
				if (! $taskParamsToDel->delete()) {
					$completeError = "Error in deleting task params.";
					$conn->FailTrans();
				}
				
				if ($conn->HasFailedTrans()) {
					print "$completeError Please try again later.";
				} else {
					print "Success: Deleted task with name: {$taskToDel->get('name')}";
				}
				$conn->CompleteTrans();
			} else {
				print "Error: Task is already being processed, cannot delete.";
			}
			
			exit;
		}
		else if (($_REQUEST['action'] == 'loadParams')) {
			header('Content-Type: text/xml');
			$task = new TaskDAO();
			$task->fetch($_REQUEST['id']);
			$taskParam = new TaskParamsDAO();
			$taskParam->fetchByTask($_REQUEST['id']);
			$fullxml = "<objects>" . $task->toXML() . $taskParam->toXML() . "</objects>";
			$dom = new DOMDocument();
			$dom->loadXML($fullxml);
			$xpath = new DOMXPath($dom);
			$properties = $xpath->query('//objects/object[table="tasks"]/property[name="messages"]');
			foreach ($properties as $property) {
				$property->parentNode->removeChild($property);
			}
			$fullxml = $dom->saveXML();
			
			print $fullxml;
		}
		else if (($_REQUEST['action'] == 'loadMessages')) {
			header('Content-Type: text/xml');
			$task = new TaskDAO();
			$task->fetch($_REQUEST['id']);
			$taskParam = new TaskParamsDAO();
			$taskParam->fetchByTask($_REQUEST['id']);
			$fullxml = "<objects>" . $task->toXML() . $taskParam->toXML() . "</objects>";
			$dom = new DOMDocument();
			$dom->loadXML($fullxml);
			$xpath = new DOMXPath($dom);
			$properties = $xpath->query('//objects/object[table="tasks"]/property[name="messages"]');
			$appendedXML = "";
			foreach ($properties as $property) {
				$node = $property->parentNode->removeChild($property);
				//$appendedXML += $dom->saveXML($node);
			}
			$fullxml = "<objects><object><table>messages</table>" . $dom->saveXML($node) . "</object></objects>";
			
			print $fullxml;
		}
		else if (($_REQUEST['action'] == 'resetTask')) {
			$task = new TaskDAO();
			$task->fetch($_REQUEST['id']);
			if ( $task->resetTask() )
				print "Successfully resetted task with name: {$task->get('name')}";
			else 
				print "Error: Could not reset task.";
		}
		else {
			print "Error: Unknown Action...";
		}
	} else if (isset($_REQUEST['reset'])) {
		TaskDAO::resetTasks();
	}
	
}

?>