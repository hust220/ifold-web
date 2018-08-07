<?php /* Smarty version 2.6.11, created on 2017-10-02 13:49:17
         compiled from profileEdit.tpl */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('modifier', 'default', 'profileEdit.tpl', 4, false),)), $this); ?>
<script src="style/js/profileEdit.js" language="javascript" type="text/javascript"></script>
<?php if (isset ( $this->_tpl_vars['user'] )): ?>
	<?php $this->assign('id', ((is_array($_tmp=@$this->_tpl_vars['user']->get('id'))) ? $this->_run_mod_handler('default', true, $_tmp, "") : smarty_modifier_default($_tmp, ""))); ?>
	<?php $this->assign('username', ((is_array($_tmp=@$this->_tpl_vars['user']->get('username'))) ? $this->_run_mod_handler('default', true, $_tmp, "") : smarty_modifier_default($_tmp, ""))); ?>
	<?php $this->assign('namefirst', ((is_array($_tmp=@$this->_tpl_vars['user']->get('namefirst'))) ? $this->_run_mod_handler('default', true, $_tmp, "") : smarty_modifier_default($_tmp, ""))); ?>
	<?php $this->assign('namelast', ((is_array($_tmp=@$this->_tpl_vars['user']->get('namelast'))) ? $this->_run_mod_handler('default', true, $_tmp, "") : smarty_modifier_default($_tmp, ""))); ?>
	<?php $this->assign('email', ((is_array($_tmp=@$this->_tpl_vars['user']->get('email'))) ? $this->_run_mod_handler('default', true, $_tmp, "") : smarty_modifier_default($_tmp, ""))); ?>
	<?php $this->assign('organization', ((is_array($_tmp=@$this->_tpl_vars['user']->get('organization'))) ? $this->_run_mod_handler('default', true, $_tmp, "") : smarty_modifier_default($_tmp, ""))); ?>
	<?php $this->assign('level', ((is_array($_tmp=@$this->_tpl_vars['user']->get('level'))) ? $this->_run_mod_handler('default', true, $_tmp, "") : smarty_modifier_default($_tmp, ""))); ?>
<?php endif; ?>
<div class="indexTitle">&raquo; Your Profile</div><br/>
			<?php if (isset ( $this->_tpl_vars['saveError'] )): ?>
				<div id="errors_profile" class="errors_box" style="display:block">
					<strong><?php echo $this->_tpl_vars['saveError']; ?>
</strong>
				</div>
			<?php endif; ?>
			<?php if (isset ( $this->_tpl_vars['saveSuccess'] )): ?>
				<div id="errors_profile" class="errors_box" style="display:block">
					<strong><?php echo $this->_tpl_vars['saveSuccess']; ?>
</strong>
				</div>
			<?php endif; ?>
			<?php if (isset ( $this->_tpl_vars['passwordError'] )): ?>
				<div id="errors_profile" class="errors_box" style="display:block">
					<strong><?php echo $this->_tpl_vars['passwordError']; ?>
</strong>
				</div>
			<?php endif; ?>
			<?php if (isset ( $this->_tpl_vars['deleteError'] )): ?>
				<div id="errors_profile" class="errors_box" style="display:block">
					<strong><?php echo $this->_tpl_vars['deleteError']; ?>
</strong>
				</div>
			<?php endif; ?>									
			<?php if (isset ( $this->_tpl_vars['profileSuccess'] )): ?>
			<div id="sucProfile">
			User profile successfully updated.
			</div>
			<?php else: ?>
			<div id="menu">
			Enter your current password if you wish to modify any of your account's details.<br/><br/>
				<form id="profileEdit" method="post" action="profileEdit.php">
					<input type="hidden" name="id" value="<?php echo $this->_tpl_vars['id']; ?>
" />
					<table border="0" cellpadding="0" cellspacing="0" style="width:80%" class="ifoldtable">
						<tr>
							<td width="60%">Username:</td>
							<td><input id="username" type="text" name="username" value="<?php echo $this->_tpl_vars['username']; ?>
" style="width:200px" maxlength="10" /></td>
						</tr>
						<tr>
							<td width="60%">User ID:</td>
							<td><input id="userid" type="text" name="userid" value="<?php echo $this->_tpl_vars['id']; ?>
" style="width:200px" maxlength="10" /></td>
						</tr>
						<tr>
							<td>Current Password:</td>
							<td><input id="password" type="password" name="password" style="width:200px" maxlength="15" /></td>
						</tr>
						<tr>
							<td>First Name:</td>
							<td><input id="namefirst" type="text" name="namefirst" value="<?php echo $this->_tpl_vars['namefirst']; ?>
" style="width:200px" maxlength="15" /></td>
						</tr>
						<tr>
							<td>Last Name:</td>
							<td><input id="namelast" type="text" name="namelast" value="<?php echo $this->_tpl_vars['namelast']; ?>
" style="width:200px" maxlength="15" /></td>
						</tr>
						<tr>
							<td>Email:</td>
							<td><input id="email" type="text" name="email" value="<?php echo $this->_tpl_vars['email']; ?>
" style="width:200px" maxlength="60" /></td>
						</tr>
						<tr>
							<td>Organization:</td>
							<td><input id="organization" type="text" name="organization" value="<?php echo $this->_tpl_vars['organization']; ?>
" style="width:200px" maxlength="20" /></td>
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
						<?php if ($this->_tpl_vars['level'] < 3): ?>
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
						<?php endif; ?>
						<tr>
							<td colspan="2" align="center">
							<input type="Submit" onClick="return validateUpdate();" name="update" value="Update" style="width:150px"/>
							<input type="Submit" onClick="return validateDelete();" name="delete" value="Delete Account" style="width:150px"/></td>
						</tr>
					</table>
				</form>
			</div>
			<?php endif; ?>