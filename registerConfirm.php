<?php
/********************************************************************
* @name Register Confirm
* @abstract - Allows users to confirm their email address 
* @since Feb 27, 2006
* -------------------------------------------------------------------/
*
* @author		Jameson Lopp jameson@unc.edu
* @author		Adi Unnithan adi@unc.edu
*				Daniel Watson dcwatson@email.unc.edu
*********************************************************************/

require('config.inc.php');

$errString = 'Sorry, we could not confirm your registration. Please try the URL again or contact an iFold Administrator.';
if (isset($_GET['key'])) {
	$key = $_GET['key'];
	if(!preg_match('/[0-9]*|/', $key, $id)) {
		$smarty->assign('confirmRegisterError', $errString);
	} else {
		$conn =& IFoldDB::getConn();
		$props = new IFoldProps();
	   	$userDAO = new UserDAO();
	   	$userDAO->fetch($id[0]);
		$dbHash = sha1(md5($userDAO->get('email')) . md5($userDAO->get('password')) . md5($userDAO->get('username')));
		$urlHash = substr($key, strlen($id[0])+1);
		// if hashes are the same, proceed with updating the db flag for email confirmation
		if (strcmp($dbHash, $urlHash) == 0) {
		   	$userDAO->set('emailConfirmed', 1);
		   	$userDAO->save();
		   	// if user is not approved, send email to an admin (user may merely be updating registered email address)
			if ($userDAO->get('approved') == 0)
			{
			   	$smarty->assign_by_ref('userRegConfirm', $userDAO);
			   	$mail_subject = "iFold Registration: " . ucwords ($userDAO->get('namefirst')) . " " . ucwords ($userDAO->get('namelast')) . " has requested an account.";
		    		$mail_message = "{$userDAO->get('namefirst')} {$userDAO->get('namelast')} has just requested an account under the username: {$userDAO->get('username')}" .
							"\n\nPlease visit the Manage Users page to approve them:\n" .
							"http://" . $_SERVER['HTTP_HOST'] . str_replace('registerConfirm.php', 'adminUserList.php', $_SERVER['SCRIPT_NAME']) . "\n\n" .
							"Thanks, [The iFold Application]";
		    		$mail_headers = "From: iFold: Interactive Folding\r\nReply-To:\r\nX-Mailer: iFold Registration PHP Script" . phpversion ();
		    		mail ($props->getAdminEmail(), $mail_subject, $mail_message, $mail_headers);
			}
		   	else{
			   	$smarty->assign_by_ref('emailReconfirm', $userDAO);
			}
		} else {
	    	$smarty->assign('confirmRegisterError', $errString);
		}
	}
} else {
	$smarty->assign('confirmRegisterError', $errString);	
}

$smarty->display_welcome('registerConfirm.tpl');
?>
