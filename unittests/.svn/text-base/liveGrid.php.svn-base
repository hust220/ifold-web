<?php
/* File: liveGrid.php
 * Created on Apr 13, 2006 at 5:50:09 AM
 * Author: Adi Unnithan <unnithan@gmail.com>
 *************************************************/
?>
<html>
<head>
	<title>iFold: Interactive Folding</title>
	<style type="text/css">
      <!--
        @import url(../style/ifold.css);
      -->
    </style>
    <script src="../style/js/prototype.js" language="javascript" type="text/javascript"></script>
	<script src="../style/js/rico.js" language="javascript" type="text/javascript"></script>
</head>
<body>
<div id="completedQueue">
	<h2 class="submitSteps">Completed Tasks</h2>
	<div id="completedQueueMessages" class="ajaxMessages"></div><br/>
	<table id="completedQueueTable_header" border="0" cellpadding="0" cellspacing="0" class="ifoldtable fixedTable" style="width:585px">
		<tr>
			<th align="left" valign="top" style="width:140px">Name</th>
			<th align="left" valign="top" style="width:200px">Description</th>
			<th align="left" valign="top" style="width:115px">Created</th>
			<th align="left" valign="top" style="width:80px">Owner</th>
			<th align="left" valign="top" class="alt" style="width:50px">&nbsp;</th>
		</tr>
	</table>
	<table id="completedQueueTable" border="0" cellpadding="0" cellspacing="0" class="ifoldtable fixedTable" style="width:585px;float:left">
		<tr>
			<td align="left" valign="top" style="width:140px">test</td>
			<td align="left" valign="top" style="width:200px">test</td>
			<td align="left" valign="top" style="width:115px">test</td>
			<td align="left" valign="top" style="width:80px">etst</td>
			<td align="left" valign="top" style="width:50px">lksad</td>
		</tr>
		<tr>
			<td align="left" valign="top" style="width:140px">test</td>
			<td align="left" valign="top" style="width:200px">test</td>
			<td align="left" valign="top" style="width:115px">test</td>
			<td align="left" valign="top" style="width:80px">etst</td>
			<td align="left" valign="top" style="width:50px">lksad</td>
		</tr>
		<tr>
			<td align="left" valign="top" style="width:140px">test</td>
			<td align="left" valign="top" style="width:200px">test</td>
			<td align="left" valign="top" style="width:115px">test</td>
			<td align="left" valign="top" style="width:80px">etst</td>
			<td align="left" valign="top" style="width:50px">lksad</td>
		</tr>
		<tr>
			<td align="left" valign="top" style="width:140px">test</td>
			<td align="left" valign="top" style="width:200px">test</td>
			<td align="left" valign="top" style="width:115px">test</td>
			<td align="left" valign="top" style="width:80px">etst</td>
			<td align="left" valign="top" style="width:50px">lksad</td>
		</tr>
		<tr>
			<td align="left" valign="top" style="width:140px">test</td>
			<td align="left" valign="top" style="width:200px">test</td>
			<td align="left" valign="top" style="width:115px">test</td>
			<td align="left" valign="top" style="width:80px">etst</td>
			<td align="left" valign="top" style="width:50px">lksad</td>
		</tr>
		<tr>
			<td align="left" valign="top" style="width:140px">test</td>
			<td align="left" valign="top" style="width:200px">test</td>
			<td align="left" valign="top" style="width:115px">test</td>
			<td align="left" valign="top" style="width:80px">etst</td>
			<td align="left" valign="top" style="width:50px">lksad</td>
		</tr>
		<tr>
			<td align="left" valign="top" style="width:140px">test</td>
			<td align="left" valign="top" style="width:200px">test</td>
			<td align="left" valign="top" style="width:115px">test</td>
			<td align="left" valign="top" style="width:80px">etst</td>
			<td align="left" valign="top" style="width:50px">lksad</td>
		</tr>
		<tr>
			<td align="left" valign="top" style="width:140px">test</td>
			<td align="left" valign="top" style="width:200px">test</td>
			<td align="left" valign="top" style="width:115px">test</td>
			<td align="left" valign="top" style="width:80px">etst</td>
			<td align="left" valign="top" style="width:50px">lksad</td>
		</tr>
		<tr>
			<td align="left" valign="top" style="width:140px">test</td>
			<td align="left" valign="top" style="width:200px">test</td>
			<td align="left" valign="top" style="width:115px">test</td>
			<td align="left" valign="top" style="width:80px">etst</td>
			<td align="left" valign="top" style="width:50px">lksad</td>
		</tr>
		<tr>
			<td align="left" valign="top" style="width:140px">test</td>
			<td align="left" valign="top" style="width:200px">test</td>
			<td align="left" valign="top" style="width:115px">test</td>
			<td align="left" valign="top" style="width:80px">etst</td>
			<td align="left" valign="top" style="width:50px">lksad</td>
		</tr>
	</table>
</div>

<script type="text/javascript" language="javascript">
	tu = null;
    var opts = 	{	prefetchBuffer: 	true,
   				};
   	
	tu = new Rico.LiveGrid( 'completedQueueTable',
                           5,
                           40,
                           '../ajaxUtilities.php?action=getCompletedTasks', opts );
</script>
</body>
</html>