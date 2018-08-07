<?php
/********************************************************************
* @name Register
* @abstract - Allows users to create an account 
* @since Feb 21, 2006
* -------------------------------------------------------------------/
*
* @author		Jameson Lopp jameson@unc.edu
* @author		Adi Unnithan adi@unc.edu
*				Daniel Watson dcwatson@email.unc.edu
*********************************************************************/

require('config.inc.php');

#-------use the hass password-----------#
$_POST['password'] = md5($_POST['password']);
#---------------------------------------#


if (isset($_POST['username']) && isset($_POST['password']) && isset($_POST['email'])) {
	$user = new UserDAO();
	$user->set("username", $_POST['username']);
	$user->set("password", $_POST['password']);
	$user->set("namefirst", $_POST['namefirst']);
	$user->set("namelast", $_POST['namelast']);
	$user->set("email", $_POST['email']);
	$user->set("emailConfirmed", 0);
	$user->set("organization", $_POST['organization']);
	$user->set("approved", 0);	
	$user->set("numtasks", 10);
	$user->set("level", 1);
	$user->set("cpuHours", 100);
	if ($user->add()) {
		//$smarty->clear_assign('registerError');
		//$smarty->assign_by_ref('registerSuccess', $user);
		
		// Send an email with an autogenerated link
		if (strtoupper(substr(PHP_OS,0,3)=='WIN')): $eol="\r\n"; elseif (strtoupper(substr(PHP_OS,0,3)=='MAC')): $eol="\r"; else: $eol="\n"; endif;
	    $mailsubject = "iFold Registration (Step 2): " . ucwords ($user->get('namefirst')) . " " . ucwords ($user->get('namelast')) . "!";
	    
	    # Common Headers
		$headers .= 'From: iFold: Interactive Folding '.$eol;
		$headers .= 'Reply-To: iFold: Interactive Folding'.$eol;
		$headers .= 'Return-Path: iFold: Interactive Folding'.$eol;    // these two to set reply address
		$headers .= "Message-ID: <".$now." TheSystem@".$_SERVER['SERVER_NAME'].">".$eol;
		$headers .= "X-Mailer: PHP v".phpversion().$eol;          // These two to help avoid spam-filters
		# Boundry for marking the split & Multitype Headers
		$mime_boundary=md5(time());
		$headers .= 'MIME-Version: 1.0'.$eol;
		$headers .= "Content-Type: multipart/related; boundary=\"".$mime_boundary."\"".$eol;
		$msg = "";
		
		$link = "http://" . $_SERVER['HTTP_HOST'] . 
				str_replace('register.php', 'registerConfirm.php', $_SERVER['SCRIPT_NAME']) . "?key=" . 
				$user->get('id') . "|" . sha1(md5($user->get('email')) . md5($user->get('password')) . 
				md5($user->get('username')));
		
		# HTML Version
		$msg .= "--".$mime_boundary.$eol;
		$msg .= "Content-Type: text/html; charset=iso-8859-1".$eol;
		$msg .= "Content-Transfer-Encoding: 8bit".$eol;
		$msg .= "Thanks for completing the first part of the iFold Registration!<br/><br/>\n" .
				"\nPlease click on the following link to complete your registration:<br/>" .
				"\n\n<a href=\"$link\">$link</a><br/><br/>\n\nThanks!\n\n<br/><br/>iFold Administrators".$eol.$eol;
		
		# Text Version
		$msg .= "--".$mime_boundary.$eol;
		$msg .= "Content-Type: text/plain; charset=iso-8859-1".$eol;
		$msg .= "Content-Transfer-Encoding: 8bit".$eol;
		$msg .= "Thanks for completing the first part of the iFold Registration!\n" .
				"\nPlease paste the following link into the location bar of your " .
				"browser and visit it to complete your registration:" .
				"\n\n$link\n\nThanks!\n\niFold Administrators. \n\nBefore using iFold, please see the terms of use for iFold server at: http://ifold.dokhlab.org/terms.txt".$eol;
		$msg .= "+ + Text Only Email from iFold + +".$eol.$eol;
		
		# Finished
		$msg .= "--".$mime_boundary."--".$eol.$eol;
		
	    mail ($user->get('email'), $mailsubject, $msg, $headers);
      
      	header ('Location: index.php?registerSuccess=' . base64_encode(serialize($user)));
	} else {
		//$smarty->assign('registerError', "Register failed: username exists");
		//$smarty->assign('user', $user);
		header ('Location: index.php?registerError=' . base64_encode(serialize($user)));
	}
	//SmartyIFold::setSmarty($smarty);
	//header('Location: index.php');
}
?>