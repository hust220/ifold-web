<script src="style/js/adminuserlist.js" language="javascript" type="text/javascript"></script>
<div class="indexTitle">&raquo; Admin User List</div><br/>
<div id="adminUserMessages" class="ajaxMessages">&nbsp;</div><br/><br/>
<table border="0" cellpadding="0" cellspacing="0" class="ifoldTable">
	<tr>
		<th align="left" valign="top">Aprvd?</th>
		<th align="left" valign="top">Username</th>
		<th align="left" valign="top">First Name</th>
		<th align="left" valign="top">Last Name</th>
		<th align="left" valign="top">Lv.</th>
		<th align="left" valign="top">Organization</th>
		<th align="left" valign="top">Num Tasks</th>
		<th align="left" valign="top">CPU Hours</th>
		<th align="left" valign="top" class="alt">Admin Functions</th>
	</tr>
	{foreach from=$userList item=userIter}
		<tr class="{cycle values="normal,alt"}">
			<td id="{$userIter->get('id')}_approved" align="left" valign="top">
				{if ($userIter->get('approved') == 0)} <img src="style/img/a_user-idenied.png" value="0" alt="denied!" style="cursor:pointer" onclick="if (confirm('Send an Approval Confirmation email to {$userIter->get('username')}?')) approve(this, true); else approve(this, false);"/>
				{else} <img src="style/img/a_user-iapproved.png" value="0" alt="approved!" style="cursor:pointer" onclick="deapprove(this)"/>
				{/if}
			</td>
			<td id="{$userIter->get('id')}_username" align="left" valign="top" onclick="html2input(this)">{$userIter->get('username')}</td>
			<td id="{$userIter->get('id')}_namefirst" align="left" valign="top" onclick="html2input(this)">{$userIter->get('namefirst')}</td>
			<td id="{$userIter->get('id')}_namelast" align="left" valign="top" onclick="html2input(this)">{$userIter->get('namelast')}</td>
			<td id="{$userIter->get('id')}_level" align="left" valign="top" onclick="html2input(this)" 
				{if ($userIter->get('level') < 3)}
					style="color:#C0C0C0">{$userIter->get('level')}
				{elseif ($userIter->get('level') < 5) }
					style="color:#808080">{$userIter->get('level')}
				{else}
					style="color:#000000;font-weight:bold">{$userIter->get('level')}
				{/if}
			</td>
			<td id="{$userIter->get('id')}_organization" align="left" valign="top" onclick="html2input(this)">{$userIter->get('organization')}</td>
			<td id="{$userIter->get('id')}_numtasks" align="left" valign="top" onclick="html2input(this)">{$userIter->get('numtasks')}</td>
			<td id="{$userIter->get('id')}_cpuHours" align="left" valign="top" onclick="html2input(this)">{$userIter->get('cpuHours')}</td>
			<td id="{$userIter->get('id')}_functions" align="left" valign="top">
				<img src="style/img/a_user-idelete.png" alt="Delete {$userIter->get('username')}" style="cursor:pointer" onclick="if (confirm('Are you sure you want to delete?')) deleteRow(this)"/>
				<a href="mailto:{$userIter->get('email')}" border="0" ><img src="style/img/a_user-iemail.png" border=0></a>
			</td>
		</tr>
	{/foreach}
</table>
