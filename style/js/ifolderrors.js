/********************************************************************
* @name iFold Errors
* @abstract - Allows users to create an account 
* @since Feb 21, 2006
* -------------------------------------------------------------------/
*
* 				Jameson Lopp jameson@unc.edu
* @author		Adi Unnithan adi@unc.edu
*				Daniel Watson dcwatson@email.unc.edu
*********************************************************************/

/*
This file needs some documentation:

iFoldErrors provides a nice javascript wrapper for error-handling. It can
be used to catch errors before hitting the server-side. Here is an example
of a function that uses iFoldErrors:

-------------------------------------------------------------------------
var validateRegister = function() {
	
	var errors = new iFoldErrors('ALERT');
	errors.setErrorAction("ERRORID.style.border='1px solid #9F2727'");
	var fieldsArr = ['username', 'password', 'confirm_pass', 'namefirst', 'namelast', 'email', 
					 'organization'];

	errors.reset(fieldsArr, "fieldNode.style.border='1px solid #C3DADF'");
	
	errors.checkNotNull(fieldsArr);
	errors.checkMinSize('username', 3);
	errors.checkValidPassword('password');
	errors.checkFieldsMatch('password', 'confirm_pass');
	errors.checkIsEmail('email');
	
	if (errors.hasErrors()) {
		errors.show();
		return false;
	}
	return true;
}
-------------------------------------------------------------------------

1. 	The constructor "new iFoldErrors()" accepts either 'ALERT' or a div box
	to display the errors in.

2.	setErrorAction() takes javascript as a parameter -- this JS is called
	on the specific element that has an error (use ERRORID).

3.	reset() takes an array of the field IDs as well as javascript that shows
	what the normal state of those fields are -- this is the opposite of
	setErrorAction().

4.	show() simply displays all of the errors into whatever div box or alert
	was specified in the constructor.

*/

function iFoldError(id, msg) {
	
	this._fieldId = id;
	this._errMsg = msg;
	
	iFoldError.prototype.getId = function() {
		return this._fieldId;
	}
	
	iFoldError.prototype.getMsg = function() {
		return this._errMsg;
	}
}


function iFoldErrors(out) {
	
	this._errors = new Array;
	if (out != 'ALERT')
		this._outId = $(out);
	else
		this._outId = out;
	this._outId.innerHTML = "";
	this._normAct = "";
	this._errAct = "";
	this._internalnullexcept = "";
	
	iFoldErrors.prototype.reset = function(fieldArray, normalAction) {
		// set elements to default state
		for (var i=0;i<fieldArray.length;i++) {
			var fieldNode = $(fieldArray[i]);
			eval(normalAction);
		}
		
		// hide errors dialog
		this.hide();
	}
	
	iFoldErrors.prototype.setErrorAction = function(jsAction) {
		this._errAct = jsAction;
	}
	
	iFoldErrors.prototype.checkNotNull = function(fieldsArr, exceptions) {

		// build exceptions
		var exceptionJS = 'true';
		if (exceptions || this._internalnullexcept != "") {
			var exceptionsArray = Array();
			if (exceptions) exceptionsArray = exceptions.split(",");
			var internalExceptionsArray = this._internalnullexcept.split(",");
			exceptionsArray = exceptionsArray.concat(internalExceptionsArray);
			if (exceptionsArray[0] != null) { exceptionJS = "fieldsArr[i] != '" + exceptionsArray[0] + "'"; }
			for (var i=1;i<exceptionsArray.length;i++) {
				if (exceptionsArray[i] != "") {
					exceptionJS += "&& fieldsArr[i] != '" + exceptionsArray[i] + "'";
				}
			}
		}
		// first let's check everything is not null
		for (var i=0;i<fieldsArr.length;i++) {
			if (($(fieldsArr[i]).value == "") && eval(exceptionJS)) {
				this.add(fieldsArr[i], fieldsArr[i] + ' was not filled out');
			}
		}
	}
	
	iFoldErrors.prototype.checkDependency = function(node, type, relatedTo) {
		if (type == 'xor') {
			if ($(node).value != "") {
				if ($(relatedTo).value != "") {
					this.add(relatedTo, "either " + relatedTo + ' or ' + node + ' should be filled out, but not both');
				}
				this._internalnullexcept += relatedTo + ",";
			}
		} else if (type == 'and') {
			if ($(node).value != "") {
				if ($(relatedTo).value == "") {
					this.add(relatedTo, relatedTo + ' should be filled out, since ' + node + ' was filled out');
				}
			}
		}
	}
	
	iFoldErrors.prototype.checkMinSize = function(fieldId, size) {
		var fieldVal = $F(fieldId);
		if (fieldVal.length < size) {
			var err = new iFoldError(fieldId, fieldId + ' needs to be greater than or ' + size + ' characters.');
			this._errors.push(err);
		}
	}
	
	iFoldErrors.prototype.checkMaxSize = function(fieldId, size) {
		var fieldVal = $F(fieldId);
		if (fieldVal.length > size) {
			var err = new iFoldError(fieldId, fieldId + ' needs to be lesser than ' + size + ' characters.');
			this._errors.push(err);
		}
	}
	
	iFoldErrors.prototype.checkMinValue = function(fieldId, sizeOrNode) {
		var fieldVal = $F(fieldId);
		var value = (isNaN(parseFloat(sizeOrNode))) ? $F(sizeOrNode) : sizeOrNode;
		if (parseFloat(fieldVal) < parseFloat(value)) {
			var err = new iFoldError(fieldId, fieldId + ' needs to be greater than or equal to ' + sizeOrNode);
			this._errors.push(err);
		}
	}
	
	iFoldErrors.prototype.checkMaxValue = function(fieldId, sizeOrNode) {
		var fieldVal = $F(fieldId);
		var value = (isNaN(parseFloat(sizeOrNode))) ? $F(sizeOrNode) : sizeOrNode;
		if (parseFloat(fieldVal) > parseFloat(value)) {
			var err = new iFoldError(fieldId, fieldId + ' needs to be less than or equal to ' + sizeOrNode);
			this._errors.push(err);
		}
	}
	
	iFoldErrors.prototype.checkValidPassword = function(pass) {
		var passVal = $F(pass);
		if (passVal.length < 6) {
			var err = new iFoldError(pass, 'Password should be greater than or equal to 6 characters in length.');
			this._errors.push(err);
		}
	}
	
	iFoldErrors.prototype.checkFieldsNotMatch = function(args) {
		var matchAgainst = $F(arguments[0]);
		for (var i=1;i<arguments.length;i++) {
			if ($F(arguments[i]) == matchAgainst) {
				var err = new iFoldError(arguments[i], arguments[i] + ' should not match ' + arguments[0] + '.');
				this._errors.push(err);
			}
		}
	}
	
	iFoldErrors.prototype.checkFieldsMatch = function(args) {
		var matchAgainst = $F(arguments[0]);
		for (var i=1;i<arguments.length;i++) {
			if ($F(arguments[i]) != matchAgainst) {
				var err = new iFoldError(arguments[i], arguments[i] + ' does not match ' + arguments[0] + '.');
				this._errors.push(err);
			}
		}
	}
	
	iFoldErrors.prototype.checkIsEmail = function(email) {
		if (! ($F(email).search(/^\w+((-\w+)|(\.\w+))*\@[A-Za-z0-9]+((\.|-)[A-Za-z0-9]+)*\.[A-Za-z0-9]+$/) != -1)) {
			var err = new iFoldError(email, 'Not a valid email address!');
			this._errors.push(err);
		}
	}

	iFoldErrors.prototype.checkIsNumber = function(number) {
		var objRegExp = /(^-?\d\d*$)/;

		if (! ($F(number).search(/(^-?\d\d*$)/) != -1)) {
			var err = new iFoldError(number, 'Not a valid integer');
			this._errors.push(err);
		}
	}
		
	iFoldErrors.prototype.add = function(fieldId, errMsg) {
		var error = new iFoldError(fieldId, errMsg);
		this._errors.push(error);
	}
	
	iFoldErrors.prototype.hide = function() {
		if (this._outId != 'ALERT') Element.hide(this._outId);
	}
	
	iFoldErrors.prototype.show = function() {
		var allErrors = "";
		if (this._outId != 'ALERT') Element.show(this._outId);
		var errHandler = this._errAct.replace(/ERRORID/g, "$(this._errors[i].getId())");
		var errHandler = errHandler.replace(/ERRORMSG/g, "$(this._errors[i].getMsg())");
		for (var i=0;i<this._errors.length;i++) {
			eval(errHandler);
			allErrors += this._errors[i].getMsg();
			if (this._outId != 'ALERT') allErrors += "<br/>";
			allErrors += "\n";
		}
		if (this._outId != 'ALERT') this._outId.innerHTML = allErrors;
		else alert(allErrors);
	}
	
	iFoldErrors.prototype.hasErrors = function() {
		return (this._errors.length > 0);
	}
}