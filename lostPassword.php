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

if (isset($_POST['email'])) {
	// check that email address matches an account and find corresponding password
	$user = new userDAO();
	$user->set('email', $_POST['email']);
	if ($rs = $user->search(array('email'), array($_POST['email'])))
	{
		$user->digest($rs[0]);
    	$charset = "abcdefghijklmnopqrstuvwxyz0123456789";
    	for ($i=0; $i<7; $i++) // build a 7 character random string as the new password
    		$newPassword .= $charset[(mt_rand(0,(strlen($charset)-1)))];
#-------use the hash password-----------#
				$newPasswordHash = md5($newPassword);
#------------------#
    	$user->set('password', $newPasswordHash);
		// save new password to database
		if (! $user->save()) {
			$smarty->assign('lostPasswordError', "Unable to save reset password to database. Please try again later.");
			exit;
		}
	   	$mail_subject = "iFold lost password: " . ucwords ($rs[0]['namefirst']) . " " . ucwords ($rs[0]['namelast']);
	    $mail_message = ucwords($rs[0]['namefirst']) . ' ' . ucwords($rs[0]['namelast']) . " requested the password reset for username: {$rs[0]['username']}" .
						"\n\nThe new password is: " . $newPassword . "\n\n\nThe iFold Team";
	    $mail_headers = "From: iFold: Interactive Folding\r\nReply-To:\r\nX-Mailer: iFold Lost Password PHP Script " . phpversion ();
	    mail ($_POST['email'], $mail_subject, $mail_message, $mail_headers);
       	$smarty->assign('lostPasswordError',  "An email with your reset password has been sent to the given address.");
	}
	else {
   		$smarty->assign('lostPasswordError',  "Email address not found in database");
	}
}

$smarty->display_welcome('lostPassword.tpl');
?>
