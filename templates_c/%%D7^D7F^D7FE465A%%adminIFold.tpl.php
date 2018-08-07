<?php /* Smarty version 2.6.11, created on 2006-05-11 15:27:47
         compiled from adminIFold.tpl */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('function', 'cycle', 'adminIFold.tpl', 14, false),)), $this); ?>
<script src="style/js/queue.js" language="javascript" type="text/javascript"></script>
<script src="style/js/adminifold.js" language="javascript" type="text/javascript"></script>
<div class="indexTitle">&raquo; Manage iFold:</div><br/>
<div id="ifoldMessages" class="ajaxMessages">&nbsp;</div><br/><br/>
<table border="0" cellpadding="0" cellspacing="0" class="ifoldTable">
	<tr>
		<th align="left" valign="top" width="20">&nbsp;</th>
		<th align="left" valign="top" width="150">Address</th>
		<th align="left" valign="top" width="50">Port</th>
		<th align="left" valign="top">Last Received Task</th>
		<th align="left" valign="top" class="alt" width="50">Functions</th>
	</tr>
	<?php $_from = $this->_tpl_vars['daemonList']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['daemon']):
?>
		<tr class="<?php echo smarty_function_cycle(array('values' => "normal,alt"), $this);?>
">
			<td align="center" valign="top">
				<?php 
					$status = strtolower($this->_tpl_vars['daemonstatuses'][$this->_tpl_vars['daemon']->get('status')]);
					echo "<img src=\"style/img/a_daemon-i$status.png\" alt=\"$status\" title=\"$status\"/>";
				 ?>
			</td>
			<td align="left" valign="top"><?php echo $this->_tpl_vars['daemon']->get('address'); ?>
</td>
			<td align="left" valign="top"><?php echo $this->_tpl_vars['daemon']->get('port'); ?>
</td>
			<td align="left" valign="top">
				<?php if ($this->_tpl_vars['daemon']->get('taskId') != '0'): ?>
					<img src="style/img/edit-find-small.png" alt="what task" title="Look at what task is running on this daemon" style="cursor:pointer" onclick="return GB_show('Task Parameters', 'popTaskInformation.php?type=parameters&id=<?php echo $this->_tpl_vars['daemon']->get('taskId'); ?>
', 500, 500)"/>
				<?php else: ?>
					&nbsp;
				<?php endif; ?>
			</td>
			<td align="left" valign="top">
				<?php if ($this->_tpl_vars['daemon']->get('action') == '1'): ?>
					<img src="style/img/a_daemon-ipause.png" alt="pause" title="Pause the daemon and deny any incoming tasks to this daemon" style="cursor:pointer" onclick="daemonPause(this, <?php echo $this->_tpl_vars['daemon']->get('id'); ?>
)"/>
				<?php elseif ($this->_tpl_vars['daemon']->get('action') == '2'): ?>
					<img src="style/img/a_daemon-iactivate.png" alt="wake" title="Wake the daemon and accept any incoming tasks to this daemon" style="cursor:pointer" onclick="daemonWake(this, <?php echo $this->_tpl_vars['daemon']->get('id'); ?>
)" />
				<?php endif; ?>
			</td>
		</tr>
	<?php endforeach; endif; unset($_from); ?>
</table>

<script type="text/javascript" language="javascript">
	
	var GB_ANIMATION = true;
    var GB_IMG_DIR = "style/img/";
    var GB_overlay_click_close = true;
</script>