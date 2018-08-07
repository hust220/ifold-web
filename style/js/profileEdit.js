var validateDelete = function() {
	if (confirm('Do you wish to delete your ifold account? It cannot be undeleted.')) { 
		return true; 
	}
	return false;
}

var validateUpdate = function() {
	var errors = new iFoldErrors('ALERT');
	errors.setErrorAction("ERRORID.style.border='1px solid #9F2727'");
	var fieldsArr = ['username', 'password', 'namefirst', 'namelast', 'email', 'organization'];
	var passFieldsArr = ['newpassword', 'newpasswordconfirm'];
	
	errors.reset(fieldsArr, "fieldNode.style.border='1px solid #C3DADF'");
	errors.reset(passFieldsArr, "fieldNode.style.border='1px solid #C3DADF'");
	
	errors.checkNotNull(fieldsArr);
	errors.checkMinSize('username', 3);
	errors.checkFieldsNotMatch('username', 'password');
	errors.checkIsEmail('email');

	if($('newpassword').value != "")
	{
		errors.checkFieldsNotMatch('username', 'newpassword');
		errors.checkValidPassword('newpassword');
		errors.checkFieldsMatch('newpassword', 'newpasswordconfirm');
	}
	
	if (errors.hasErrors()) {
		errors.show();
		return false;
	}
	return true;
}

