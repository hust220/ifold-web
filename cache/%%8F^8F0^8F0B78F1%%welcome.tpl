133
a:4:{s:8:"template";a:1:{s:11:"welcome.tpl";b:1;}s:9:"timestamp";i:1140538487;s:7:"expires";i:1140542087;s:13:"cache_serials";a:0:{}}<html>
<head>
	<title>iFold: Proteins on Demand</title>
	<style type="text/css">
      <!--
        @import url(style/welcome.css);
      -->
    </style>
    <script src="style/js/prototype.js" language="javascript" type="text/javascript"></script>
    <script src="style/js/moo.fx.js" language="javascript" type="text/javascript"></script>
    <script src="style/js/moo.fx.pack.js" language="javascript" type="text/javascript"></script>
    <script src="style/js/ifolderrors.js" language="javascript" type="text/javascript"></script>
    <script src="style/js/welcome.js" language="javascript" type="text/javascript"></script>
</head>
<body>
	<div id="main">
		<div id="header">
			<img src="style/img/head.jpg" alt="iFold: Proteins on Demand" />
		</div>
		<div id="content">
			<div id="main_content">Hi</div>
			<div id="menu">
				<form id="frmLogin" method="post" action="index.php">
					<div id="errors_login" style="display:block">
										</div>
					<table border="0" cellpadding="0" cellspacing="0" width="100%">
						<tr>
							<td>Username:</td>
							<td><input id="user" type="text" name="user" /></td>
							<td rowspan="2"><input type="Submit" value="Login" onClick="return validateLogin();" style="width:40px;height:36px;font-weight:bold;background:#9BC0CF;border:0px" /></td>
						</tr>
						<tr>
							<td>Password:</td>
							<td><input id="pass" type="password" name="pass" /></td>
						</tr>
					</table>
				</form>
				<br/>
				<form id="frmRegister" method="post" action="register.php">
					<div id="errors_register" style="display:block"></div>
					Username: <input id="username" type="text" name="username" /><br/><br/>
					Password: <input id="password" type="password" name="password" /><br/><br/>
					Confirm Pass: <input id="confirm_pass" type="password" name="confirm_pass" /><br/><br/>
					First Name: <input id="namefirst" type="text" name="namefirst" /><br/><br/>
					Last Name: <input id="namelast" type="text" name="namelast" /><br/><br/>
					Email: <input id="email" type="text" name="email" /><br/><br/>
					Organization: <input id="organization" type="text" name="organization" /><br/><br/>
					Simple:<input id="level" type="radio" name="level" value="0" onClick="hideReason();" /> 
					Advanced: <input id="level" type="radio" name="level" value="1" onClick="showReason();" /><br/><br/>
					<div id="advReason">Reason: <textarea id="advReasonText" name="advanced_reason"></textarea></div>
					<input type="Submit" onClick="return validateRegister();">
				</form>
			</div>	
		</div>
	</div>
</body>
</html>