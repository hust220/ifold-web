<?php
/********************************************************************
* @name Submit
* @abstract - Submission handler for tasks
* @since Feb 20, 2006
* -------------------------------------------------------------------/
*
* 				Jameson Lopp jameson@unc.edu
* @author		Adi Unnithan adi@unc.edu
*				Daniel Watson dcwatson@email.unc.edu
*********************************************************************/

require 'config.inc.php';
require_once IFOLD_DIR . 'lib/TaskDAO.class.php';
require_once IFOLD_DIR . 'lib/TaskOutputsDAO.php';
require_once IFOLD_DIR . 'lib/TaskParamsDAO.php';

// if not logged in, redirect to main page
if (! isset($_SESSION["user"])) {
	header('Location: index.php');
	return;
}

$user = unserialize($_SESSION['user']);
$smarty->assign_by_ref('user', $user);

$props = new IFoldProps();
$foldtypesArray = $props->getFoldTypes();
$paramsArray = $props->getTaskParams();
$outputsArray = $props->getTaskOutputs();

$smarty->assign_by_ref('foldtypes', $foldtypesArray);
$smarty->assign_by_ref('taskparams', $paramsArray);
$smarty->assign_by_ref('taskoutputs', $outputsArray);

$filestatus = array(
       0=>"There is no error, the file uploaded with success",
       1=>"The uploaded file exceeds the upload_max_filesize directive in php.ini",
       2=>"The uploaded file exceeds the MAX_FILE_SIZE directive that was specified in the HTML form",
       3=>"The uploaded file was only partially uploaded",
       4=>"No file was uploaded",
       6=>"Missing a temporary folder",
       7=>"Failed to write file to disk"
);

if (isset($_POST['action']) && (strtolower($_POST['action']) == 'submit task')) {
	
	if ($user->get('emailConfirmed') == 0) {
		$smarty->assign('submitError', "<strong>Cannot Submit Task:</strong> Your email address is not confirmed. Please click on the link in your verification email.");
		$smarty->display_page('submit.tpl');
		exit;
	}
	
	$searchTask = new TaskDAO();
	if ($searchTask->search(array('name'), array($_POST['name']))) {
		$smarty->assign('submitError', "<strong>Cannot Submit Task:</strong> Task name is already taken. Please select " .
										"a different one.");
		$smarty->display_page('submit.tpl');
		exit;
	}
	
	$task = new TaskDAO();
	$taskParamsObj = new TaskParamsDAO();
	$taskOutputsObj = new TaskOutputsDAO();
	$completeError = "";
	
	// START TRANSACTION
	$conn->StartTrans();
	
	// set parameter variables and add taskparams
	$taskParamsObj->set('foldtype', $_POST['foldtype']);
	
	for ($p=1;$p<=count($paramsArray);$p++) {
		if (isset($_POST[(string)$paramsArray[$p]->name])) {
			$taskParamsObj->set((string)$paramsArray[$p]->name, $_POST[(string)$paramsArray[$p]->name]);
		}
	}
	if (!$taskParamsObj->add()) {
		$completeError = "<strong>Cannot Submit Task:</strong> Error submitting task parameters. Please check to " .
							"make sure that they are correct. If so, contact an iFold Administrator.";
		$conn->FailTrans();
	}
	
	// set task variables and add task
	$task->set('param_id', $taskParamsObj->get('id'));
	$task->set('name', $_POST['name']);
	$task->set('description', $_POST['description']);
	$task->set('created_by', $user->get('id'));
	
	if (!$task->add()) {
		$completeError = "<strong>Cannot Submit Task:</strong> You have submitted your maximum number of tasks." .
							" If you need to submit more, please submit a request to be an 'advanced' iFold user.";
		$conn->FailTrans();
	}
	
	// set output variables and add output
	for ($o=1;$o<=count($outputsArray);$o++) {
		if (isset($_POST[(string)$outputsArray[$o]->name])) {
			$taskOutputsObj->set((string)$outputsArray[$o]->name, $_POST[(string)$outputsArray[$o]->name]);
		}
	}
	$taskOutputsObj->set('task_id', $task->get('id'));
	if (!$taskOutputsObj->add()) {
		$completeError = "<strong>Cannot Submit Task:</strong> You have submitted your maximum number of tasks." .
							" If you need to submit more, please submit a request to be an 'advanced' iFold user.";
		$conn->FailTrans();
	}
	
	// move uploaded files to the appropriate place
	foreach ($_FILES as $fname => $fvalue) { 
		if ($fvalue['error'] != 4) {
			if ($fvalue['error'] != 0) {
				$completeError = "<strong>Cannot Submit Task:</strong> {$filestatus[$fvalue['error']]}. Please try again later.";
				$conn->FailTrans();
			} else {
				$uploadfile = UPLOAD_DIR . $task->get('id') . "-" . $fname;
				if (! move_uploaded_file($fvalue['tmp_name'], $uploadfile )) {
				   	$completeError = "<strong>Cannot Submit Task:</strong> Could not move uploaded file to appropriate place on the server. Please try again later.";
					$conn->FailTrans();
				}
				chmod(UPLOAD_DIR . $task->get('id') . "-" . $fname, 0777);
				$taskParamsObj->set($fname, $task->get('id') . "-" . $fname);
				$taskParamsObj->save();
			}
		}
	}
	
	// CHECK IF ERROR WITH TRANSACTION
	if ($conn->HasFailedTrans()) {
		$smarty->assign('submitError', $completeError);
	} else {
		$smarty->assign('submitSuccess', true);
	}
	
	// COMPLETE TRANSACTION
	$conn->CompleteTrans();
	
	// SOCKET TRIGGER TO JAVA MANAGER
	$address = $props->getManagerHost(); 
	$port = $props->getManagerPhpPort(); 
	$socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP); 
	if (socket_connect($socket,$address,$port)) {
		socket_close($socket);
	} else {
		DaemonDAO::setAllDaemons("3");
	}
}

$smarty->display_page('submit.tpl');

?>
