/********************************************************************
* @name iFold Tabs
* @abstract - Sweet tab control mechanism
* @since Feb 21, 2006
* -------------------------------------------------------------------/
*
* 				Jameson Lopp jameson@unc.edu
* @author		Adi Unnithan adi@unc.edu
*				Daniel Watson dcwatson@email.unc.edu
*********************************************************************/

//var tabNames = new Array;
var currShown = null;

var tabRegister = function() {
	//for (var i=0;i<arguments.length;i++) {
	//	tabNames.push(arguments[i]);
	//}
	//tabHideAll();
	tabOpen(arguments[0]);
}

/*
var tabHideAll = function() {
	for (var i=0;i<tabNames.length;i++) {
		$('tab'+tabNames[i]).style.display = 'none';
	}
}

var tabOpen = function(tabName) {
	if (currShown) {
		$('tab' + currShown).style.display = 'none';
		$('but' + currShown).style.color = '#8EBBCF';
		$('but' + currShown).style.backgroundImage = 'url(style/img/button_back.jpg)';
		$('but' + currShown).style.borderWidth = '1px 2px 1px 1px';
		$('but' + currShown).style.borderColor = '#C6E7EF';
	}
	$('tab' + tabName).style.display = 'block';
	$('but' + tabName).style.color = '#356B84';
	$('but' + tabName).style.background = '#F4F9F9';
	$('but' + tabName).style.borderWidth = '1px 2px 0 1px';
	$('but' + tabName).style.borderColor = '#9BC5CF';
	$('foldtype').value = tabName;
	currShown = tabName;
}*/

var tabOpen = function(tabName) {
	if (currShown) {
		$('but' + currShown).style.color = '#8EBBCF';
		$('but' + currShown).style.backgroundImage = 'url(style/img/button_back.jpg)';
		$('but' + currShown).style.borderWidth = '1px 2px 1px 1px';
		$('but' + currShown).style.borderColor = '#C6E7EF';
	}
	$('ifoldTabBody').innerHTML = $('tab' + tabName).innerHTML;
	$('but' + tabName).style.color = '#356B84';
	$('but' + tabName).style.background = '#F4F9F9';
	$('but' + tabName).style.borderWidth = '1px 2px 0 1px';
	$('but' + tabName).style.borderColor = '#9BC5CF';
	$('foldtype').value = tabName;
	currShown = tabName;
}