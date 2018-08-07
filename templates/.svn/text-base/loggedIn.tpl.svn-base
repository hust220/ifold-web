{* Smarty *}
{php}

function statusToWord($id) {
	return $this->_tpl_vars['daemonstatuses'][$id];
}

{/php}
<html>
<head>
	<title>iFold: Interactive Folding</title>
	<style type="text/css">
      <!--
        @import url(style/ifold.css);
        @import url(style/greybox.css);
      -->
    </style>

	<script src="style/js/prototype.js" language="javascript" type="text/javascript"></script>
	<script src="style/js/scriptaculous/scriptaculous.js" language="javascript" type="text/javascript"></script>
	<script src="style/js/AmiJS.js" language="javascript" type="text/javascript"></script>
    <script src="style/js/greybox.js" language="javascript" type="text/javascript"></script>
    <script src="style/js/ifold.js" language="javascript" type="text/javascript"></script>
    <script src="style/js/ifolderrors.js" language="javascript" type="text/javascript"></script>
</head>
<body>
	<div id="main">
		<div id="header">
			<div style="float:left"><img src="style/img/head.jpg" alt="iFold: Proteins on Demand" border="0" /></div>
			<div style="float:right"><a href="http://dokhlab.unc.edu/main.html"><img src="style/img/dokhlab.jpg" alt="Dokholyan Lab" border="0" /></a></div>
		</div>
		<div id="meta" class="smallfont">
			Logged in as <strong> {$user->get('namefirst')} {$user->get('namelast')} </strong> |
			<a href="logout.php">Logout</a>
		</div>
		<div id="content">
			<div id="nav">
					<a href="index.php"><img src="style/img/nav_home.jpg" alt="Overview/Home" border="0"/></a><br/><br/>
					<a href="submit.php"><img src="style/img/nav_submit.jpg" alt="Submit a Task" border="0"/></a><br/><br/>
					<a href="activity.php"><img src="style/img/nav_activity.jpg" alt="Your Activity" border="0"/></a><br/><br/>
					<a href="profileEdit.php"><img src="style/img/nav_profile.jpg" alt="Edit Profile" border="0" /></a><br/><br/>
					<a href="taskList.php"><img src="style/img/nav_queue.jpg" alt="View Queue" border="0" /></a><br/><br/>
					<a href="help.php"><img src="style/img/nav_help.jpg" alt="Help Center" border="0" /></a>
					{if $user->get('level') >= 5}
						<br/><br/><a href="adminUserList.php"><img src="style/img/nav_manageusers.jpg" alt="Manage Users" border="0" /></a><br/><br/>
						<a href="adminIFold.php"><img src="style/img/nav_manageifold.jpg" alt="Manage iFold" border="0" /></a><br/>
					{/if}
			</div>
			
			<div id="main_content">{include file=$content_template}</div>
			
			<div id="rightbar">
				<div id="ataglance">
					<div id="ataglance-head">Queue At-A-Glance</div>
					<div id="ataglance-content">
						Processing: <strong>
									{if $atg_working > 0}
										{$atg_working} task{if $atg_working > 1}s{/if}
									{else}
										nothing.
									{/if}
									</strong><br/>
						Waiting: 	<strong>
									{if $atg_waiting > 0}
										{$atg_waiting} task{if $atg_waiting > 1}s{/if}
									{else}
										nothing.
									{/if}
									</strong>
					</div>
				</div>
				<div id="ataglance-daemons" style="margin-top:30px">
					<div id="ataglance-daemons-head">Daemons At-A-Glance</div>
					<div id="ataglance-daemons-content">
						<table border="0" cellpadding="0" cellspacing="0">
						{foreach from=$daemonList item=daemon}
							<tr>
								<td align="center" valign="middle">
									{php}
										$status = strtolower($this->_tpl_vars['daemonstatuses'][$this->_tpl_vars['daemon']->get('status')]);
										echo "<img src=\"style/img/a_daemon-i$status.png\" alt=\"$status\" title=\"$status\" />";
									{/php}
								</td>
								<td align="left" valign="top">
									<span style="cursor:default" title="{$daemon->get('address')}:{$daemon->get('port')}">{$daemon->get('address')|truncate:16:"...":true}<br/>
									{$daemon->get('port')|truncate:10:"...":true}</span><br/>
								</td>
							</tr>
						{/foreach}
						</table>
					</div>
				</div>
			</div>
		</div>
	</div>
</body>
</html>