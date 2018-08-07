if (document.images)
{
  pic1 = new Image(32,32); 
  pic1.src = "style/img/indicator_medium.gif"; 
}

/*Element.prototype.saveBgColor = function() {
	var node;
	if (this.childNodes[0].nodeType == 1) node = this.childNodes[0];
	else node = this.childNodes[1];
	this.savedColor = node.style.background;
}

Element.prototype.highlightRow = function() {
	//this.saveBgColor();
	for (var i=1;i<this.childNodes.length;i=i+2) {
		if (this.childNodes[i].nodeType == 1) {
			this.childNodes[i].style.background = '#FBFFAF';
		}
	}
}

Element.prototype.unhighlightRow = function() {
	for (var i=1;i<this.childNodes.length;i=i+2) {
		if (this.childNodes[i].nodeType == 1) {
			this.childNodes[i].style.background = this.savedColor;
		}
	}
}
*/
var hideShowCompleted = function(el,dowhat,d) {
	var table = $('completedQueue');
	if (dowhat == 'hide') {
		el.innerHTML = 'show completed tasks';
		new Effect.BlindUp(table, {duration: d});
		el.onclick = function() { hideShowCompleted(el,'show',1); }
	} else if (dowhat == 'show') {
		el.innerHTML = 'hide completed tasks';
		new Effect.BlindDown(table, {duration: d});
		el.onclick = function() { hideShowCompleted(el,'hide',1); }
	}
}

var hideParameters = function() {
	$('overlayParams').style.display = 'none';
}

var loadParameters = function(id) {
	var url = 'taskListEdit.php';
	var params = 'action=loadParams&id=' + id;
	var ajax = new Ajax.Request(
		url,
		{	method: 	'post', 
			parameters:	params,
			onSuccess: 	processParamLoadSuccess, 
			onFailure: 	processParamLoadFailure	}
	);
}

var loadMessages = function(id) {
	var url = 'taskListEdit.php';
	var params = 'action=loadMessages&id=' + id;
	var ajax = new Ajax.Request(
		url,
		{	method: 	'post', 
			parameters:	params,
			onSuccess: 	processParamLoadSuccess, 
			onFailure: 	processParamLoadFailure	}
	);
}

var resetTask = function(id) {

	var anonProcessResetTaskSuccess = function(req){ processResetTaskSuccess(req, 'queueMessages') };
	var anonProcessResetTaskFailure = function(req){ processResetTaskFailure(req, 'queueMessages') };

	var url = 'taskListEdit.php';
	var params = 'action=resetTask&id=' + id;
	var ajax = new Ajax.Request(
		url,
		{	method: 	'post', 
			parameters:	params,
			onSuccess: 	anonProcessResetTaskSuccess, 
			onFailure: 	anonProcessResetTaskFailure	}
	);
}

var deleteRow = function(el, messageNode, isLiveGrid) {

	var anonProcessDelSuccess = function(req){ processDelSuccess(req, el, messageNode, isLiveGrid) };
	var anonProcessDelFailure = function(req){ processDelFailure(req, el, messageNode) };

	var underInd = el.parentNode.id.indexOf('_');
	var url = 'taskListEdit.php';
	var params = 'action=delete&id=' + el.parentNode.id.substring(0,underInd);
	var ajax = new Ajax.Request(
		url,
		{method: 'post', parameters: params, onSuccess: anonProcessDelSuccess, onFailure: anonProcessDelFailure}
	);
}

var deleteOutputRow = function(el) {

	var anonProcessDelSuccess = function(req){ processDelSuccess(req, el, 'outputMessages', false) };
	var anonProcessDelFailure = function(req){ processDelFailure(req, el, 'outputMessages', false) };

	var underInd = el.parentNode.id.indexOf('_');
	var url = 'activityEdit.php';
	var params = 'action=deleteOutput&id=' + el.parentNode.id.substring(0,underInd);
	var ajax = new Ajax.Request(
		url,
		{method: 'post', parameters: params, onSuccess: anonProcessDelSuccess, onFailure: anonProcessDelFailure}
	);
}

var processResetTaskSuccess = function(origRequest, messageNode) {
	$(messageNode).innerHTML = origRequest.responseText;
	window.history.go(0);
}

var processResetTaskFailure = function(origRequest, messageNode) {
	$(messageNode).innerHTML = "Could not reset task. Please try again later.";
}

var processDelSuccess = function(origRequest, el, messageNode, isLiveGrid) {

	if (origRequest.responseText.toLowerCase().indexOf("error") == -1) {
		if (isLiveGrid) {
			window.history.go(0);
			//tu.requestContentRefresh(1);
			//tu.viewPort.refreshContents();
		} else {
			new Effect.Fade(el.parentNode.parentNode, {duration: 0.5});
		}
	}
	$(messageNode).innerHTML = origRequest.responseText;
}

var processDelFailure = function(origRequest, el, messageNode) {
	$(messageNode).innerHTML = 'Error in Deletion. Try Again Later...';
}

var processParamLoadSuccess = function(origRequest) {
	var errorMsg = "Sorry, cannot load parameters at this time";
	var xml = origRequest.responseXML;
	var objectList = xml.getElementsByTagName('objects')[0];
	var objects = objectList.getElementsByTagName('object');
	if (objects.length == 0) {
		$('paramsBox').innerHTML = errorMsg + closeMsg;
		return;
	}
	var paramsHTML= "<html>";
	paramsHTML += 	"	<head>";
	paramsHTML += 	"		<title>iFold: Interactive Folding</title>";
	paramsHTML += 	"		<link rel=\"stylesheet\" type=\"text/css\" href=\"style/ifold.css\" />";
	paramsHTML += 	"		<script src=\"style/js/prototype.js\" language=\"javascript\" type=\"text/javascript\"></script>";
	paramsHTML += 	"		<script src=\"style/js/queue.js\" language=\"javascript\" type=\"text/javascript\"></script>";
	paramsHTML += 	"	</head>";
	paramsHTML += 	"	<body style=\"background:#FFFBEF\">";
	paramsHTML += "<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"100%\">";
	paramsHTML += "<tr>";
	for (var o=0;o<objects.length;o++) {
		var props = objects[o].getElementsByTagName('property');
		if ((props == null) || (props.length == 0)) {
			paramsHTML += "<td>"+errorMsg+"</td></tr></table></body></html";
			document.writeln(paramsHTML);
			return;
		}
		paramsHTML += '<td align="left" valign="top">';
		paramsHTML += '<strong>' + objects[o].getElementsByTagName('table')[0].firstChild.data + '</strong>';
		paramsHTML += '<table id="queueTable" border="0" cellpadding="0" cellspacing="0" class="ifoldTable">';
		for (var i=0;i<props.length;i++) {
			paramsHTML += '<tr>';
			paramsHTML += '<td align="left" valign="top">' + props[i].getElementsByTagName('name')[0].firstChild.data + '</td>';
			paramsHTML += '<td align="left" valign="top">';
			if (props[i].getElementsByTagName('value')[0].firstChild != null) {
				if (props[i].getElementsByTagName('name')[0].firstChild.data == "messages") {
					var messages = props[i].getElementsByTagName('value')[0].firstChild.data.replace(/Message:/g,"");
					paramsHTML += '<pre>';
					paramsHTML += messages;
					paramsHTML += '</pre>';
				} else {
					paramsHTML += props[i].getElementsByTagName('value')[0].firstChild.data;
				}
			} else {
				paramsHTML += '&nbsp;';
			}
			paramsHTML += '</td>';
			paramsHTML += '</tr>';
		}
		paramsHTML += '</table>';
	}
	paramsHTML += "</td></tr>";
	paramsHTML += "</table>";
	paramsHTML += "</body>";
	paramsHTML += "</html>";
	document.writeln(paramsHTML);
}

var processParamLoadFailure = function(origRequest) {
	$('paramsBox').innerHTML = "Error: Could not load parameters at this time. Please try again later.";
}

function updateHeader( liveGrid, offset ) {
    $('bookmark').innerHTML = "Listing tasks <strong>" + (offset+1) + " - " + (offset+liveGrid.metaData.getPageSize()) + "</strong> of <strong>" + 
    liveGrid.metaData.getTotalRows() + "</strong>";
    var sortInfo = "";
    if (liveGrid.sortCol) {
    	sortInfo = "&data_grid_sort_col=" + liveGrid.sortCol + "&data_grid_sort_dir=" + liveGrid.sortDir;
    }
	$('bookmark').href="ajaxUtilities.php?action=getCompletedTasks" + "&data_grid_index=" + offset + sortInfo;
}