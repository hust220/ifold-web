<?php
/********************************************************************
* @name Help
* @abstract - Displays appropriate help page
* @since Mar 20, 2006
* -------------------------------------------------------------------/
*
* 				Jameson Lopp jameson@unc.edu
* @author		Adi Unnithan adi@unc.edu
*				Daniel Watson dcwatson@email.unc.edu
*********************************************************************/

require 'config.inc.php';
require_once IFOLD_DIR . "lib/HelpDAO.class.php";

if (isset($_SESSION['user'])) {	
	$user = unserialize($_SESSION['user']);
	$smarty->assign_by_ref('user', $user);
	$help = new HelpDAO();

	if (isset($_GET['action']) && (strtolower($_GET['action']) == 'view')) {
		$help->fetch($_GET['id']);
		$smarty->assign_by_ref('helpdata', $help);
		$smarty->display_page('helpView.tpl');
	}
	elseif (isset($_POST['action']) && (strtolower($_POST['action']) == 'edit')) {
		$help->fetch($_POST['id']);
		// format string with escape chars suitable for javascript text editor
		$help->set('content', addslashes($help->get('content')));
		$search = array("\x00", "\x0a", "\x0d", "\x1a", "\x09");
		$replace = array('\0', '\n', '\r', '\Z' , '\t');
		$help->set('content', str_replace($search, $replace, $help->get('content')));
		$smarty->assign_by_ref('helpdata', $help);
		$smarty->display_page('helpEdit.tpl');
	}
	elseif (isset($_POST['action']) && (strtolower($_POST['action']) == 'update')) {
		$help->set("name", $_POST['name']);
		$help->set("level", $_POST['level']);
		$help->set("description", $_POST['description']);
		$help->set("content", $_POST['rte1']);			
		if($_POST['id'] == "")
		{
			if (! $help->add()) {
				$smarty->assign('saveError', "Error in saving the '" . $_POST['name'] . "' help page. Please try again later.");
				exit;
			}
		}
		else
		{
			$help->set("id", $_POST['id']);
			// help edited successfully, return to help index
			if (! $help->save()) {
				$smarty->assign('saveError', "Error in saving the '" . $_POST['name'] . "' help page. Please try again later.");
				exit;
			}
		}
		$smarty->assign('saveSuccess', "Saved the '" . $_POST['name'] . "' help page.");
		$helpdata = $help->getHelp();
		$smarty->assign_by_ref('helpdata', $helpdata);
		$smarty->display_page('help.tpl');
	}
	elseif (isset($_POST['action']) && (strtolower($_POST['action']) == 'add')) {
		$smarty->assign_by_ref('helpdata', $help);
		$smarty->display_page('helpEdit.tpl');
	}
	elseif (isset($_POST['action']) && (strtolower($_POST['action']) == 'delete')) {
		$help->set("id", $_POST['id']);
		// help deleted successfully, return to help index
		if (! $help->delete()) {
			$smarty->assign('deleteError', "Error in deleting the '" . $_POST['name'] . "' help page. Please try again later.");
			exit;
		}
		$smarty->assign('deleteSuccess', "Deleted the '" . $_POST['name'] . "' help page.");
		$helpdata = $help->getHelp();
		$smarty->assign_by_ref('helpdata', $helpdata);
		$smarty->display_page('help.tpl');
	}
	else
	{
		$helpdata = $help->getHelp();
		$smarty->assign_by_ref('helpdata', $helpdata);
		$smarty->display_page('help.tpl');
	}
} // if not logged in, redirect to main page 
else {
	$smarty->display_welcome();
}

?>