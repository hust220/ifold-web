var currentNodeVal = "";

var html2input = function(el) {
	var inputWidth = el.offsetWidth-10;
	var inputHeight = el.offsetHeight - 10;
	currentNodeVal = el.innerHTML;
	el.onclick = "";
	el.innerHTML = "<textarea onblur=\"savefield(this, this.parentNode)\" " + 
					"style=\"width:" + inputWidth + "px;height:" + inputHeight + "\">" + el.innerHTML + "</textarea>";
	el.firstChild.focus();
}

var approve = function(el, email) {
	savefield (el, el.parentNode);
	if (email) sendEmail(el, el.parentNode);
}

var deapprove = function (el) {
	savefield(el, el.parentNode);
}

var deleteRow = function(el) {
	
	var anonProcessDelSuccess = function(req){ processDelSuccess(req, el, 'adminUserMessages') };
	var anonProcessDelFailure = function(req){ processDelFailure(req, el, 'adminUserMessages') };

	var underInd = el.parentNode.id.indexOf('_');
	var url = 'adminUserEdit.php';
	var params = 'action=delete&id=' + el.parentNode.id.substring(0,underInd);
	var ajax = new Ajax.Request(
		url,
		{method: 'post', parameters: params, onSuccess: anonProcessDelSuccess, onFailure: anonProcessDelFailure}
	);
}

var savefield = function(el, par) {

	var anonProcessSaveSuccess = function(req){ processSaveSuccess(req, el, 'adminUserMessages') };
	var anonProcessSaveFailure = function(req){ processSaveFailure(req, el, 'adminUserMessages') };

	var underInd = par.id.indexOf('_');
	$('adminUserMessages').innerHTML = 'Saving \'' + par.id.substring(underInd+1) + '\'...';
	var url = 'adminUserEdit.php';
	var params = 'action=update&id=' + par.id.substring(0,underInd) + 
					'&name=' + par.id.substring(underInd+1);
	if (par.id.substring(underInd+1) != "approved") {
		params += '&value=' + el.value;
	} else {
		params += '&value=' + (el.alt == "denied!" ? '1' : '0');
	}
	var ajax = new Ajax.Request(
		url,
		{method: 'post', parameters: params, onSuccess: anonProcessSaveSuccess, onFailure: anonProcessSaveFailure}
	);
}

var sendEmail = function(el, par) {

	var anonProcessEmailSuccess = function(req){ processEmailSuccess(req, el, 'adminUserMessages') };
	var anonProcessEmailFailure = function(req){ processEmailFailure(req, el, 'adminUserMessages') };

	var underInd = par.id.indexOf('_');
	var url = 'adminUserEdit.php';
	var params = 'action=email&id=' + par.id.substring(0,underInd); 
	var ajax = new Ajax.Request(
		url,
		{method: 'post', parameters: params, onSuccess: anonProcessEmailSuccess, onFailure: anonProcessEmailFailure}
	);
}

var processSaveSuccess = function(origRequest, el, messageNode) {
	var underInd = el.parentNode.id.indexOf('_');
	var par = el.parentNode;
	if (origRequest.responseText.toLowerCase().indexOf("error") != -1) {
		if (el.parentNode.id.substring(underInd+1) != "approved") {
			el.parentNode.innerHTML = currentNodeVal;
		}
	} else {
		if (el.parentNode.id.substring(underInd+1) != "approved") {
			el.parentNode.innerHTML = el.value;
		} else {
			if (el.alt == "denied!") {
				el.src = "style/img/a_user-iapproved.png";
				el.alt = "approved!";
				el.onclick = function() { deapprove(el); }
				el.value = "1";
			} else {
				el.src = "style/img/a_user-idenied.png";
				el.alt = "denied!";
				el.onclick = function() { 
					if (confirm('Send an Approval Confirmation email?')) { 
						approve(el, true); 
					} else {
						approve(this, false);
					}
				}
				el.value = "0";
			}
		}
	}
	par.onclick = function() { html2input(par); }
	$(messageNode).innerHTML = origRequest.responseText;
}

var processSaveFailure = function(origRequest, el, messageNode) {
	$(messageNode).innerHTML = 'Error in Saving. Try Again Later...';
}

var processEmailSuccess = function(origRequest, el, messageNode) {
	$(messageNode).innerHTML = origRequest.responseText;
}

var processEmailFailure = function(origRequest, el, messageNode) {
	$(messageNode).innerHTML = ' Error in Emailing!';
}

var processDelSuccess = function(origRequest, el, messageNode) {
	if (origRequest.responseText.toLowerCase().indexOf("error") == -1) {
		var parpar = el.parentNode.parentNode;
		new Effect.Fade(parpar, {duration: 1});
	}
	$(messageNode).innerHTML = origRequest.responseText;
}

var processDelFailure = function(origRequest, el, messageNode) {
	$(messageNode).innerHTML = 'Error in Deletion. Try Again Later...';
}

