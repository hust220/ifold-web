
To have your password emailed to you, enter the email address that is currently registered with your account.<br/><br/>
<form id="profileEdit" method="post" action="lostPassword.php">
	Email Address:
	<input id="email" type="text" name="email" maxlength="40" /><br/>
	<input type="Submit" name="Submit" value="Submit" style="width:150px"/>
</form>
If you are unable to retrieve your password or have other technical difficulties, send us an email.
<br/><br/>
iFold Administrators
<br/><br/>
{if isset($lostPasswordError)}
<strong>{$lostPasswordError}</strong>
{/if}