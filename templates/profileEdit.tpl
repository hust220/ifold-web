<script src="style/js/profileEdit.js" language="javascript" type="text/javascript"></script>
{* Smarty *}
{if isset($user)}
	{assign var="id" value=$user->get('id')|default:""}
	{assign var="username" value=$user->get('username')|default:""}
	{assign var="namefirst" value=$user->get('namefirst')|default:""}
	{assign var="namelast" value=$user->get('namelast')|default:""}
	{assign var="email" value=$user->get('email')|default:""}
	{assign var="organization" value=$user->get('organization')|default:""}
	{assign var="level" value=$user->get('level')|default:""}
{/if}
<div class="indexTitle">&raquo; Your Profile</div><br/>
			{if isset($saveError)}
				<div id="errors_profile" class="errors_box" style="display:block">
					<strong>{$saveError}</strong>
				</div>
			{/if}
			{if isset($saveSuccess)}
				<div id="errors_profile" class="errors_box" style="display:block">
					<strong>{$saveSuccess}</strong>
				</div>
			{/if}
			{if isset($passwordError)}
				<div id="errors_profile" class="errors_box" style="display:block">
					<strong>{$passwordError}</strong>
				</div>
			{/if}
			{if isset($deleteError)}
				<div id="errors_profile" class="errors_box" style="display:block">
					<strong>{$deleteError}</strong>
				</div>
			{/if}									
			{if isset($profileSuccess)}
			<div id="sucProfile">
			User profile successfully updated.
			</div>
			{else}
			<div id="menu">
			Enter your current password if you wish to modify any of your account's details.<br/><br/>
				<form id="profileEdit" method="post" action="profileEdit.php">
					<input type="hidden" name="id" value="{$id}" />
					<table border="0" cellpadding="0" cellspacing="0" style="width:80%" class="ifoldtable">
						<tr>
							<td width="60%">Username:</td>
							<td><input id="username" type="text" name="username" value="{$username}" style="width:200px" maxlength="10" /></td>
						</tr>
						<tr>
							<td width="60%">User ID:</td>
							<td><input id="userid" type="text" name="userid" value="{$id}" style="width:200px" maxlength="10" /></td>
						</tr>
						<tr>
							<td>Current Password:</td>
							<td><input id="password" type="password" name="password" style="width:200px" maxlength="15" /></td>
						</tr>
						<tr>
							<td>First Name:</td>
							<td><input id="namefirst" type="text" name="namefirst" value="{$namefirst}" style="width:200px" maxlength="15" /></td>
						</tr>
						<tr>
							<td>Last Name:</td>
							<td><input id="namelast" type="text" name="namelast" value="{$namelast}" style="width:200px" maxlength="15" /></td>
						</tr>
						<tr>
							<td>Email:</td>
							<td><input id="email" type="text" name="email" value="{$email}" style="width:200px" maxlength="60" /></td>
						</tr>
						<tr>
							<td>Organization:</td>
							<td><input id="organization" type="text" name="organization" value="{$organization}" style="width:200px" maxlength="20" /></td>
						</tr>
						<tr>
							<td colspan="2" align="center">To change your password, enter your desired new password here:</td>
						</tr>
						<tr>
							<td>New Password:</td>
							<td><input id="newpassword" type="password" name="newpassword" style="width:200px" maxlength="15" /></td>
						</tr>
						<tr>
							<td>Confirm New Password:</td>
							<td><input id="newpasswordconfirm" type="password" name="newpasswordconfirm" style="width:200px" maxlength="15" /></td>
						</tr>
						{if $level < 3}
						<tr>
							<td colspan="2" align="center">If you collaborate with Dokholyan Lab and wish to become an advanced user, check below:</td>
						</tr>
						<tr>
							<td>Request account upgrade:</td>
							<td><input id="upgrade" type="checkbox" name="upgrade" style="width:200px" value="true" /></td>
						</tr>
						<tr>
							<td>Reason for account upgrade request:</td>
							<td><input id="upgradereason" type="text" name="upgradereason" style="width:200px" maxlength="60" /></td>
						</tr>						
						{/if}
						<tr>
							<td colspan="2" align="center">
							<input type="Submit" onClick="return validateUpdate();" name="update" value="Update" style="width:150px"/>
							<input type="Submit" onClick="return validateDelete();" name="delete" value="Delete Account" style="width:150px"/></td>
						</tr>
					</table>
				</form>
			</div>
			{/if}
