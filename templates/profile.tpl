<script src="style/js/profileEdit.js" language="javascript" type="text/javascript"></script>
<div class="indexTitle">&raquo; Your Profile</div><br/>
<div id="profileEditMessages" class="ajaxMessages">&nbsp;</div><br/><br/>
<table border="0" cellpadding="0" cellspacing="0" class="ifoldTable">
	<tr>
		<th align="left" valign="top">Username</th>
		<td id="{$user->get('id')}_username" align="left" valign="top" onclick="html2input(this)">{$user->get('username')}</td>
	</tr>
	<tr>
		<td id="{$user->get('id')}_password" align="left" valign="top" onclick="html2input(this)">{$user->get('password')}</td>
		<th align="left" valign="top">Password</th>
	</tr>
	<tr>
		<th align="left" valign="top">Password Confirm</th>
		<td id="{$user->get('id')}_password" align="left" valign="top" onclick="html2input(this)">{$user->get('password')}</td>
	</tr>
	<tr>
		<th align="left" valign="top">First Name</th>
		<td id="{$user->get('id')}_namefirst" align="left" valign="top" onclick="html2input(this)">{$user->get('namefirst')}</td>
	</tr>
	<tr>
		<th align="left" valign="top">Last Name</th>
		<td id="{$user->get('id')}_namelast" align="left" valign="top" onclick="html2input(this)">{$user->get('namelast')}</td>
	</tr>
	<tr>
		<th align="left" valign="top">Organization</th>
		<td id="{$user->get('id')}_organization" align="left" valign="top" onclick="html2input(this)">{$user->get('organization')}</td>
	</tr>
	<tr>
		<th align="left" valign="top">Email</th>
		<td id="{$user->get('id')}_email" align="left" valign="top" onclick="html2input(this)">{$user->get('email')}</td>
	</tr>
</table>
