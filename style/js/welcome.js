var validateLogin = function() {
	
	var errors = new iFoldErrors('ALERT');
	errors.setErrorAction("ERRORID.style.border='1px solid #9F2727'");
	var fieldsArr = ['user', 'pass'];
	errors.reset(fieldsArr, "fieldNode.style.border='1px solid #C3DADF'");
	
	errors.checkNotNull(fieldsArr);
	if (errors.hasErrors()) {
		errors.show();
		return false;
	}
	
	return true;
}

var validateRegister = function() {
	
	/**
	 * TODO allow action handlers so that we can pass in normal states and error states
	 */
	var errors = new iFoldErrors('ALERT');
	errors.setErrorAction("ERRORID.style.border='1px solid #9F2727'");
	var fieldsArr = ['username', 'password', 'confirm_pass', 'namefirst', 'namelast', 'email', 
					 'organization'];

	errors.reset(fieldsArr, "fieldNode.style.border='1px solid #C3DADF'");
	
	errors.checkNotNull(fieldsArr);
	errors.checkMinSize('username', 3);
	errors.checkValidPassword('password');
	errors.checkFieldsNotMatch('username', 'password');
	errors.checkFieldsMatch('password', 'confirm_pass');
	errors.checkIsEmail('email');
	
	if (errors.hasErrors()) {
		errors.show();
		return false;
	}
	return true;
}

