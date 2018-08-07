var pauseWakeIcon;
var pauseWakeId;

var daemonPause = function(img, id) {
	pauseWakeIcon = img;
	pauseWakeId = id;
	pauseWakeIcon.src = "style/img/indicator.gif";
	pauseWakeIcon.onclick = null;
	var url = 'adminIfoldEdit.php';
	var params = 'action=pauseDaemon&id=' + id;
	var ajax = new Ajax.Request(
		url,
		{	method: 'post', 
			parameters: params, 
			onSuccess: processDPauseSuccess, 
			onFailure: processDPauseFailure	}
	);
}

var processDPauseSuccess = function(origRequest) {
	if (origRequest.responseText == "success") {
		pauseWakeIcon.src = "style/img/a_daemon-iactivate.png";
		pauseWakeIcon.onclick = function() {
			daemonWake(this, pauseWakeId);
		}
		$('ifoldMessages').innerHTML = 	"Successfully paused this daemon. It will process any currently running task " +
										"and deny any future ones.";
	} else {
		processDPauseFailure(origRequest);
	}
}

var processDPauseFailure = function(origRequest) {
	pauseWakeIcon.src = "style/img/a_daemon-ipause.png";
	$('ifoldMessages').innerHTML = 	"Failed to pause this daemon. This could be a connection problem. " +
									"Please try again later.";
}

var daemonWake = function(img, id) {
	pauseWakeIcon = img;
	pauseWakeId = id;
	pauseWakeIcon.src = "style/img/indicator.gif";
	pauseWakeIcon.onclick = null;
	var url = 'adminIfoldEdit.php';
	var params = 'action=wakeDaemon&id=' + id;
	var ajax = new Ajax.Request(
		url,
		{	method: 'post', 
			parameters: params, 
			onSuccess: processDWakeSuccess, 
			onFailure: processDWakeFailure	}
	);
}

var processDWakeSuccess = function(origRequest) {
	if (origRequest.responseText == "success") {
		pauseWakeIcon.src = "style/img/a_daemon-ipause.png";
		pauseWakeIcon.onclick = function() {
			daemonPause(this, pauseWakeId);
		}
		$('ifoldMessages').innerHTML = 	"Successfully woke up this daemon. It will process any currently running task " +
										"and accept any future ones.";
	} else {
		processDWakeFailure(origRequest);
	}
}

var processDWakeFailure = function(origRequest) {
	pauseWakeIcon.src = "style/img/a_daemon-ipause.png";
	$('ifoldMessages').innerHTML = 	"Failed to wake this daemon. This could be a connection problem. " +
									"Please try again later.";
}