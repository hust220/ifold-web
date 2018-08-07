<?php
/********************************************************************
* @name AdminUserEdit
* @abstract - Provides user account editing functionality for admins
* @since Feb 22, 2006
* -------------------------------------------------------------------/
*
* @author		Jameson Lopp jameson@unc.edu
* @author		Adi Unnithan adi@unc.edu
*				Daniel Watson dcwatson@email.unc.edu
*********************************************************************/

require('config.inc.php');

// if not logged in, redirect to main page
if(!isset($_SESSION['user'])) 
{
	header('Location: index.php');
	return;
}
$user = unserialize($_SESSION['user']);

// user is not admin, thus redirect to main page
if ($user->get('level') < 5) 
	header('Location: index.php');

// user is admin, thus allow editing
else if ($user->get('level') >= 5) 
{
	if (isset($_POST['action'])) {
		if (($_POST['action'] == 'update')) {
			$userToEdit = new UserDAO();
			$userToEdit->set("id", $_POST['id']);
			$userToEdit->set($_POST['name'], $_POST['value']);
			
			// user edited successfully, return to user list
			if (! $userToEdit->save()) {
				print "Error in updating the '" . $_POST['name'] . "' field. Please try again later.";
				exit;
			} else {
				print "Saved the '" . $_POST['name'] . "' field'!";
			}
		}
		else if (($_POST['action'] == 'delete')) {
			$userToDel = new UserDAO();
			$userToDel->set("id", $_POST['id']);
	
			// user deleted, return to user list
			if (! $userToDel->delete()) {
				print "Error in deletion. Please try again later.";
				exit;
			} else {
				print "Deletion successful!";
			}
			exit;
		}
		
		else if (($_POST['action'] == 'email')) {
			$userToFetch = new UserDAO();
			$userToFetch->fetch($_POST['id']);
			
			$mail_subject = "iFold Registration (Approval): " . ucwords ($userToFetch->get('namefirst')) . " " . ucwords ($userToFetch->get('namelast')) . "!";
		    $mail_message = "You have been approved for using iFold. Please feel free to use iFold at: http://ifold.dokhlab.org\n\n" .
		    				"Thanks for your cooperation, and welcome to iFold!\n\n" . 
							"Thanks!\niFold Administrators\n\n==============================================\n" . 
							"Nikolay V. Dokholyan\n" . 
							"Assistant Professor\nDepartment of Biochemistry and Biophysics\nUniversity of North Carolina at Chapel Hill\nSchool of Medicine\n" . 
							"Campus Box 7260\nChapel Hill, NC 27599\nOffice: (919) 843-2513\nFax: (919) 966-2852\nEmail: dokh@med.unc.edu\nWeb: http://dokhlab.unc.edu/\n" . 
							"==============================================\n\n\n" . 
							"PS: This is an automated message. Please don't reply to this email. To contact iFold administrators, please send an email to: ifold@listserv.unc.edu\n";
				
		    $mail_headers = "From: iFold: Interactive Folding\r\nReply-To:\r\nX-Mailer: iFold Registration PHP Script" . phpversion ();
		    if (! mail ($userToFetch->get('email'), $mail_subject, $mail_message, $mail_headers)) {
		    	print "Error in emailing. Please try again later.";
		    	exit;
		    } else {
		    	print "Email successful!";	
		    }
			
		}
		else {
			print "Error: Unknown Action...";
		}
	}
	
}

?>
