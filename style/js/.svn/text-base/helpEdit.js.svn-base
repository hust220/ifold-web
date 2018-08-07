var validateDelete = function() {
	if (confirm('Do you wish to delete this help page? It cannot be undeleted.')) { 
		return true; 
	}
	return false;
}

var validateUpdate = function() {
	var errors = new iFoldErrors('ALERT');
	errors.setErrorAction("ERRORID.style.border='1px solid #9F2727'");
	var fieldsArr = ['name', 'level'];
	
	errors.reset(fieldsArr, "fieldNode.style.border='1px solid #C3DADF'");
	
	errors.checkNotNull(fieldsArr);

	if($('level').value != null)
	{
		errors.checkIsNumber('level');
	}
	
	if (errors.hasErrors()) {
		errors.show();
		return false;
	}
	return true;
}

