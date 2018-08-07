<?php /* Smarty version 2.6.11, created on 2006-05-11 12:37:23
         compiled from loggedIn.tpl */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('modifier', 'truncate', 'loggedIn.tpl', 85, false),)), $this); ?>
<?php 

function statusToWord($id) {
	return $this->_tpl_vars['daemonstatuses'][$id];
}

 ?>
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
			Logged in as <strong> <?php echo $this->_tpl_vars['user']->get('namefirst'); ?>
 <?php echo $this->_tpl_vars['user']->get('namelast'); ?>
 </strong> |
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
					<?php if ($this->_tpl_vars['user']->get('level') >= 5): ?>
						<br/><br/><a href="adminUserList.php"><img src="style/img/nav_manageusers.jpg" alt="Manage Users" border="0" /></a><br/><br/>
						<a href="adminIFold.php"><img src="style/img/nav_manageifold.jpg" alt="Manage iFold" border="0" /></a><br/>
					<?php endif; ?>
			</div>
			
			<div id="main_content"><?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => $this->_tpl_vars['content_template'], 'smarty_include_vars' => array()));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?></div>
			
			<div id="rightbar">
				<div id="ataglance">
					<div id="ataglance-head">Queue At-A-Glance</div>
					<div id="ataglance-content">
						Processing: <strong>
									<?php if ($this->_tpl_vars['atg_working'] > 0): ?>
										<?php echo $this->_tpl_vars['atg_working']; ?>
 task<?php if ($this->_tpl_vars['atg_working'] > 1): ?>s<?php endif; ?>
									<?php else: ?>
										nothing.
									<?php endif; ?>
									</strong><br/>
						Waiting: 	<strong>
									<?php if ($this->_tpl_vars['atg_waiting'] > 0): ?>
										<?php echo $this->_tpl_vars['atg_waiting']; ?>
 task<?php if ($this->_tpl_vars['atg_waiting'] > 1): ?>s<?php endif; ?>
									<?php else: ?>
										nothing.
									<?php endif; ?>
									</strong>
					</div>
				</div>
				<div id="ataglance-daemons" style="margin-top:30px">
					<div id="ataglance-daemons-head">Daemons At-A-Glance</div>
					<div id="ataglance-daemons-content">
						<table border="0" cellpadding="0" cellspacing="0">
						<?php $_from = $this->_tpl_vars['daemonList']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['daemon']):
?>
							<tr>
								<td align="center" valign="middle">
									<?php 
										$status = strtolower($this->_tpl_vars['daemonstatuses'][$this->_tpl_vars['daemon']->get('status')]);
										echo "<img src=\"style/img/a_daemon-i$status.png\" alt=\"$status\" title=\"$status\" />";
									 ?>
								</td>
								<td align="left" valign="top">
									<span style="cursor:default" title="<?php echo $this->_tpl_vars['daemon']->get('address'); ?>
:<?php echo $this->_tpl_vars['daemon']->get('port'); ?>
"><?php echo ((is_array($_tmp=$this->_tpl_vars['daemon']->get('address'))) ? $this->_run_mod_handler('truncate', true, $_tmp, 16, "...", true) : smarty_modifier_truncate($_tmp, 16, "...", true)); ?>
<br/>
									<?php echo ((is_array($_tmp=$this->_tpl_vars['daemon']->get('port'))) ? $this->_run_mod_handler('truncate', true, $_tmp, 10, "...", true) : smarty_modifier_truncate($_tmp, 10, "...", true)); ?>
</span><br/>
								</td>
							</tr>
						<?php endforeach; endif; unset($_from); ?>
						</table>
					</div>
				</div>
			</div>
		</div>
	</div>
</body>
</html>