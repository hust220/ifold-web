<script language="JavaScript" type="text/javascript" src="style/js/rte/html2xhtml.js"></script>
<script language="JavaScript" type="text/javascript" src="style/js/rte/richtext.js"></script>
<script language="JavaScript" type="text/javascript" src="richtext_compressed.js"></script>
<script src="style/js/helpEdit.js" language="javascript" type="text/javascript"></script>
<div class="indexTitle">&raquo; Help Center</div><br/>
<div>
<form name="helpEdit" action="help.php" method="POST" onsubmit="return submitForm();">
<input type="hidden" id="id" name="id" value="{$helpdata->get('id')}" />
Name: <input id="name" type="text" name="name" value="{$helpdata->get('name')}" style="width:200px" maxlength="40" /><br/>
Description: <input id="description" type="text" name="description" value="{$helpdata->get('description')}" style="width:200px" maxlength="40" /><br/>
Security level required to view page: <input id="level" type="text" name="level" value="{$helpdata->get('level')}" style="width:20px" maxlength="2" /><br/>
{literal}
<script language="JavaScript" type="text/javascript">
<!--
function submitForm() {
	//make sure hidden and iframe values are in sync before submitting form
	//to sync only 1 rte, use updateRTE(rte)
	//to sync all rtes, use updateRTEs
	updateRTE('rte1');
	//updateRTEs();
	//alert("rte1 = " + document.helpEdit.rte1.value);
	
	//change the following line to true to submit form
	return true;
}

//Usage: initRTE(imagesPath, includesPath, cssFile, genXHTML)
initRTE("style/js/rte/images/", "style/js/rte/", "", true);
//-->
</script>

<script language="JavaScript" type="text/javascript">
<!--
//Usage: writeRichText(fieldname, html, width, height, buttons, readOnly)
writeRichText('rte1', {/literal}'{$helpdata->get('content')}'{literal}, 500, 500, true, false);
//-->
</script>
{/literal}
<p><input type="submit" name="action" value="update" onClick="return validateUpdate();"><input type="submit" name="action" value="delete" onClick="return validateDelete();"></p>
</form>
</div>



