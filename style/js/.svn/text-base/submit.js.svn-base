
var currContent = null;

var showHideButtons = function(whatToDo) {
	for (var i=0;i<$('accordion').childNodes.length;i++) {
		if ($('accordion').childNodes[i].nodeType != 1) continue;
		var currentPanelId = $('accordion').childNodes[i].id;
		var currentPanelNum = currentPanelId.substring(0,currentPanelId.indexOf('_'));
		//eval("new Effect." + whatToDo + "($(currentPanelNum+'_btn_chooseTask'), {duration:0.5});");
		$(currentPanelNum+'_btn_chooseTask').style.display = whatToDo;
	}
}

var selectMolecule = function(id) {
	if (id == 1) { secondId = 2; thirdId = 3; }
	else if (id == 2) { secondId = 1; thirdId = 3; }
	else if (id == 3) { secondId = 1; thirdId = 2; }
	new Effect.Opacity($('molecule' + id), {from: 1.0, to: 1.0, duration: 0.1});
	new Effect.Opacity($('molecule' + secondId), {from: 1.0, to: 0.3, duration: 0.3});
	new Effect.Opacity($('molecule' + thirdId), {from: 1.0, to: 0.3, duration: 0.3});
}

var toggleCheckbox = function(el) {
	if (el.value == 0) {
		el.value = 1;
	} else {
		el.value = 0;
	}
}

var loadForm = function(id) {
	$(id+'_btn_chooseTask').style.display = 'none';
	$('foldtype').value = id;
	showHideButtons('none');
	$('foldtype').value = id;
	$('formToBeLoaded').innerHTML = $('foldContent_' + id).innerHTML;
	for (var i=0;i<$('accordion').childNodes.length;i++) {
		if ($('accordion').childNodes[i].nodeType != 1) continue;
		var currentPanelId = $('accordion').childNodes[i].id;
		var currentPanelNum = currentPanelId.substring(0,currentPanelId.indexOf('_'));
		if (currentPanelNum != id) {
			new Effect.BlindUp(currentPanelId, {duration: 1});
		}
	}
	new Effect.BlindDown('formToBeLoaded', {duration: 1, onComplete: 
		new function() {
			$(id+'_btn_chooseTask').style.width = '155px';
			$(id+'_btn_chooseTask').innerHTML = "choose a different task";
			$(id+'_btn_chooseTask').onclick = function() {
				loadFoldPicker();
			}
			setTimeout("showHideButtons('block')", 1000);
		}
	});
	currContent = id;
}

var loadFoldPicker = function() {
	$(currContent+'_btn_chooseTask').style.display = 'none';
	showHideButtons('none');
	for (var i=0;i<$('accordion').childNodes.length;i++) {
		if ($('accordion').childNodes[i].nodeType != 1) continue;
		var currentPanelId = $('accordion').childNodes[i].id;
		var currentPanelNum = currentPanelId.substring(0,currentPanelId.indexOf('_'));
		if (currentPanelNum != currContent) {
			new Effect.BlindDown(currentPanelId, {duration: 1});
		}
	}
	var tempCurrContent = currContent;
	new Effect.BlindUp('formToBeLoaded', {duration: 1, onComplete:
		new function() {
			$(currContent+'_btn_chooseTask').style.width = '120px';
			$(currContent+'_btn_chooseTask').innerHTML = "choose this task";
			$(currContent+'_btn_chooseTask').onclick = function() {
				loadForm(tempCurrContent);
			}
			setTimeout("showHideButtons('block')", 1000);
		}
	});
}

foldtypeValidateId = null;
thisForm = null;
	
var validateForm = function(form) {
	
	//alert ('validating...');
	foldtypeValidateId = $F('foldtype');
	thisForm = form;
	
	var ajax = new Ajax.Request(
		'config/properties.xml',
		{	method: 'post', 
			onSuccess: processValidateSuccess, 
			onFailure: processValidateFailure	}
	);
	return false;
}

var validateDependencies = function(errorsClass, parentNode) {
	// checking for dependencies
	var dependencies = parentNode.getElementsByTagName('dependency');
	if (dependencies.length > 0) {
		for (var d=0;d<dependencies.length;d++) {
			errorsClass.checkDependency( 	
				parentNode.getElementsByTagName('name')[0].firstChild.data,
				dependencies[d].getAttribute('type'),					
				dependencies[d].firstChild.getAttribute('name')	
			);
		}
	}
}

var processValidateSuccess = function(origRequest) {
	
	this.xml = origRequest.responseXML;
	var errors = new iFoldErrors('ALERT');
	var generalArr = ['username', 'name'];
	errors.setErrorAction("ERRORID.style.border='1px solid #FF0000'");
	var taskparams = new Array;
	var paramsArr = new Array;
	var fullArr = new Array;
	var taskAttributes = new Array;
	
	this.getRefNode = function(node) {
		return node.getAttribute('name');
	}
	
	var taskparams = this.xml.getElementsByTagName('taskparam');
	var taskoutputs = this.xml.getElementsByTagName('taskoutput');
	
	// create task parameters array
	for (var p=0;p<taskparams.length;p++) {
	
		// pushing parameters into array that will eventually be checked
		if (taskparams[p].getElementsByTagName('viewableAllFolds').length > 0) {
			paramsArr.push(taskparams[p].getElementsByTagName('name')[0].firstChild.data);
		} else {
			var defaults = taskparams[p].getElementsByTagName('default');
			for (var d=0;d<defaults.length;d++) {
				if (defaults[d].getAttribute('foldtype') == foldtypeValidateId) {
					paramsArr.push(taskparams[p].getElementsByTagName('name')[0].firstChild.data);
				}
			}
		}
		// check dependencies
		validateDependencies(errors, taskparams[p]);
		
	}
	
	// validate the task outputs
	for (var out=0;out<taskoutputs.length;out++) {
		validateDependencies(errors, taskoutputs[out]);
	}
	
	fullArr = generalArr.concat(paramsArr);
	errors.reset(fullArr, "fieldNode.style.border='1px solid #C3DADF'");
	errors.checkNotNull(fullArr);
	
	// after we have checked for null, add the taskoutputs to the parameters
	for (var p=0;p<taskparams.length;p++) taskAttributes.push(taskparams[p]);
	for (var out=0;out<taskoutputs.length;out++) {
		var defaults = taskoutputs[out].getElementsByTagName('default');
		for (var d=0;d<defaults.length;d++) {
			if (defaults[d].getAttribute('foldtype') == foldtypeValidateId) {
				taskAttributes.push(taskoutputs[out]);
			}
		}
	}
	
	// validate task parameters
	for (var p=0;p<taskAttributes.length;p++) {
		var ranges = taskAttributes[p].getElementsByTagName('range');
		for (var r=0;r<ranges.length;r++) {
			if ((ranges[r].getAttribute('foldtype') == null) ||
				(ranges[r].getAttribute('foldtype') == foldtypeValidateId)) {
				var min = ranges[r].getElementsByTagName('min')[0];
				var max = ranges[r].getElementsByTagName('max')[0];
				if (min) {
					if (min.getElementsByTagName('ref').length > 0) minNode = this.getRefNode(min.firstChild);
					else minNode = min.firstChild.data;
					errors.checkMinValue(taskAttributes[p].getElementsByTagName('name')[0].firstChild.data, minNode);
				}
				if (max) {
					if (max.getElementsByTagName('ref').length > 0) maxNode = this.getRefNode(max.firstChild);
					else maxNode = max.firstChild.data;
					errors.checkMaxValue(taskAttributes[p].getElementsByTagName('name')[0].firstChild.data, maxNode);
				}
			}
		}
	}
	
	if (errors.hasErrors()) {
		errors.show();
	} else {
		thisForm.submit();
	}
}
	
var processValidateFailure = function(origRequest) {
	alert('Error in Validating your Submission. Please Try Again Later.');
}