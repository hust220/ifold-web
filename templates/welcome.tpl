{* Smarty *}
{if isset($user)}
	{assign var="namefirst" value=$user->get('namefirst')|default:""}
	{assign var="namelast" value=$user->get('namelast')|default:""}
	{assign var="email" value=$user->get('email')|default:""}
	{assign var="organization" value=$user->get('organization')|default:""}
{/if}
<html>
<head>
	<title>iFold: Interactive Folding</title>
	<style type="text/css">
      <!--
        @import url(style/welcome.css);
        @import url(style/greybox.css);
      -->
    </style>
    <script src="style/js/prototype.js" language="javascript" type="text/javascript"></script>
    <script src="style/js/moo.fx.js" language="javascript" type="text/javascript"></script>
    <script src="style/js/moo.fx.pack.js" language="javascript" type="text/javascript"></script>
    <script src="style/js/ifolderrors.js" language="javascript" type="text/javascript"></script>
    <script src="style/js/welcome.js" language="javascript" type="text/javascript"></script>
    <script src="style/js/greybox.js" language="javascript" type="text/javascript"></script>
    <script src="style/js/AmiJS.js" language="javascript" type="text/javascript"></script>
</head>
<body>
	<div id="main">
		<div id="header">
			<div style="float:left"><img src="style/img/head.jpg" alt="iFold: Proteins on Demand" border="0" /></div>
			<div style="float:right"><a href="http://dokhlab.unc.edu/main.html"><img src="style/img/dokhlab.jpg" alt="Dokholyan Lab" border="0" /></a></div>
		</div>
		<div id="content">
			<div id="main_content">
				{if isset($content_template)}
					{include file=$content_template}
				{/if}
			</div>
			<div id="menu">
				{if isset($loginError)}
					<div id="errors_login" class="errors_box" style="display:block">
							<strong>Error: {$loginError}</strong>
					</div>
				{/if}
				<noscript>
				If you see this message, your browser is not running JavaScript. You must have JavaScript enabled for your browser in order to use iFold.
				</noscript>
				<script language="javascript" type="text/javascript">
					document.writeln('<form id="frmLogin" method="post" action="index.php">\n\n');
					document.writeln('<table border="0" cellpadding="0" cellspacing="0" width="75%" style="float:left">\n');
					document.writeln('<tr>\n<td>Username:<\/td>\n<td><input id="user" type="text" name="user" \/><\/td>\n<\/tr>\n');
					document.writeln('<tr>\n<td>Password:<\/td>\n<td><input id="pass" type="password" name="pass" \/><\/td>\n<\/tr>\n<\/table>\n');
					document.writeln('<div style="float:left;margin:2px 0 0 2px">\n');
					document.writeln('<input type="Submit" value="Login" onClick="return validateLogin();" style="width:40px;height:36px;font-weight:bold;background:#9BC0CF;border:0px" \/>\n');
					document.writeln('<\/div>\n<\/form>\n<a href="lostPassword.php">Lost Password?<\/a>');
				</script><br/>
				{if isset($registerError)}
					<div id="errors_register" class="errors_box" style="display:block">
						<strong>{$registerError}</strong>
					</div>
				{/if}
				{if isset($registerSuccess)}
				<div id="sucRegister">
				Thanks for completing the first part of our iFold registration, <strong>{$registerSuccess->get('namefirst')}!</strong> An email was forwarded to <strong>{$registerSuccess->get('email')}</strong> -- please click on the
				autogenerated link in the email to complete the second part of your registration. Thanks again!
				</div>
				{else}
          <br><br> <b> News: The migration of iFold computiong notes have been finished. You are welcome to submit your iFold jobs.  </b> <br><br>
					<br><br><b><u>	Please provide your affiliated institute's email address for registration to iFold.</u></b><br><br>
				<form id="frmRegister" method="post" action="register.php">
					<table border="0" cellpadding="0" cellspacing="0" width="100%">
						<tr>
							<td>Username:</td>
							<td><input id="username" type="text" name="username" maxlength="10" /></td>
						</tr>
						<tr>
							<td>Password:</td>
							<td><input id="password" type="password" name="password" maxlength="15" /></td>
						</tr>
						<tr>
							<td>Confirm Pass:</td>
							<td><input id="confirm_pass" type="password" name="confirm_pass" maxlength="15" /></td>
						</tr>
						<tr>
							<td>First Name:</td>
							<td><input id="namefirst" type="text" name="namefirst" value="{$namefirst}" maxlength="15" /></td>
						</tr>
						<tr>
							<td>Last Name:</td>
							<td><input id="namelast" type="text" name="namelast" value="{$namelast}" maxlength="15" /></td>
						</tr>
						<tr>
							<td>Instt. Email:</td>
							<td><input id="email" type="text" name="email" value="{$email}" maxlength="100" /></td>
						</tr>
						<tr>
							<td>Organization:</td>
							<td><input id="organization" type="text" name="organization" value="{$organization}" maxlength="20" /></td>
						</tr>

													<td colspan="2" align="center"><input type="Submit" onClick="return validateRegister();" value="Register an Account" style="width:150px"/></td>
						</tr>
					</table>
				</form>
				{/if}
			</div>	
		</div>
	</div>
</body>
</html>
