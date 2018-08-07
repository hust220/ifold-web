<?php /* Smarty version 2.6.11, created on 2017-10-02 13:59:47
         compiled from activity.tpl */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('function', 'counter', 'activity.tpl', 2, false),array('function', 'cycle', 'activity.tpl', 64, false),array('modifier', 'default', 'activity.tpl', 25, false),)), $this); ?>
<script src="style/js/queue.js" language="javascript" type="text/javascript"></script>
<?php echo smarty_function_counter(array('assign' => 'myCompletedCount','start' => 0), $this);?>

<?php $_from = $this->_tpl_vars['outputList']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['output']):
?>
	<?php echo smarty_function_counter(array('print' => false), $this);?>

<?php endforeach; endif; unset($_from); ?>
<?php if ($this->_tpl_vars['myCompletedCount'] > 0): ?>
<div class="indexTitle">&raquo; Your Activity</div><br/>
<?php echo $this->_tpl_vars['user']->get('username'); ?>
(userid: <?php echo $this->_tpl_vars['user']->get('id'); ?>
)
You have <strong><?php echo $this->_tpl_vars['myCompletedCount']; ?>
 outputs</strong> that have completed and ready for download!<br/><br/>

<div id="outputMessages" class="ajaxMessages"></div><br/>
<div id="queue">
	<table id="completedTable" border="0" cellpadding="0" cellspacing="0" class="ifoldTable">
		<tr>
			<th align="left" valign="top">Task Name</th>
			<th align="left" valign="top">Task Desc.</th>
			<th align="left" valign="top">Submitted On</th>
			<th align="left" valign="top">Output Type</th>
			<th align="left" valign="top">Filename</th>
			<th align="left" valign="top" class="alt">&nbsp;</th>
		</tr>
	<?php $_from = $this->_tpl_vars['outputList']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['output']):
?>
		<tr>
			<td id="<?php echo $this->_tpl_vars['output']->get('id'); ?>
_name" align="left" valign="top">
				<?php echo ((is_array($_tmp=@$this->_tpl_vars['output']->get('name'))) ? $this->_run_mod_handler('default', true, $_tmp, "&nbsp;") : smarty_modifier_default($_tmp, "&nbsp;")); ?>

			</td>
			<td id="<?php echo $this->_tpl_vars['output']->get('id'); ?>
_description" align="left" valign="top">
				<?php echo ((is_array($_tmp=@$this->_tpl_vars['output']->get('description'))) ? $this->_run_mod_handler('default', true, $_tmp, "&nbsp;") : smarty_modifier_default($_tmp, "&nbsp;")); ?>

			</td>
			<td id="<?php echo $this->_tpl_vars['output']->get('id'); ?>
_created_on" align="left" valign="top">
				<?php echo ((is_array($_tmp=@$this->_tpl_vars['output']->get('created_on'))) ? $this->_run_mod_handler('default', true, $_tmp, "&nbsp;") : smarty_modifier_default($_tmp, "&nbsp;")); ?>

			</td>
			<td id="<?php echo $this->_tpl_vars['output']->get('id'); ?>
_outputType" align="left" valign="top">
				<?php 
				echo $this->_tpl_vars['outputtypes'][$this->_tpl_vars['output']->get('outputType')];
				 ?>
			</td>
			<td id="<?php echo $this->_tpl_vars['output']->get('id'); ?>
_fileName" align="left" valign="top">
				<a href="<?php echo DOWNLOAD_DIR ?>/<?php echo $this->_tpl_vars['output']->get('fileName'); ?>
">
					<?php echo $this->_tpl_vars['output']->get('fileName'); ?>

				</a>
			</td>
			<td id="<?php echo $this->_tpl_vars['output']->get('id'); ?>
_functions" align="left" valign="top" class="alt">
				<img src="style/img/a_user-idelete.png" alt="Delete This Output" style="cursor:pointer" onclick="if (confirm('Are you sure you want to delete this output associated with the task: <?php echo $this->_tpl_vars['output']->get('name'); ?>
')) deleteOutputRow(this)"/>
			</td>
		</tr>
	<?php endforeach; endif; unset($_from); ?>
	</table>
</div><br/><br/>
<?php endif; ?>
You have previously submitted <strong><?php  echo count($this->_tpl_vars['taskList']); ?></strong> tasks.<br/><br/>
<div id="queueMessages" class="ajaxMessages"></div><br/>
<div id="queue">
	<table id="queueTable" border="0" cellpadding="0" cellspacing="0" class="ifoldTable">
		<tr>
			<th align="left" valign="top">Queue #</th>
			<th align="left" valign="top">Name</th>
			<th align="left" valign="top">Description</th>
			<th align="left" valign="top">Created On</th>
			<th align="left" valign="top">Status</th>
			<th align="left" valign="top" class="alt">Functions</th>
		</tr>
	<?php $_from = $this->_tpl_vars['taskList']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['task']):
?>
		<tr class="<?php echo smarty_function_cycle(array('values' => "normal,alt"), $this);?>
" >
			<td id="<?php echo $this->_tpl_vars['task']->get('id'); ?>
_queuenum" align="left" valign="top">
				<?php if ($this->_tpl_vars['task']->get('status') != 5): ?>
					<?php echo $this->_tpl_vars['task']->get('queuenum'); ?>

				<?php else: ?>
					--
				<?php endif; ?>
			</td>
			<td id="<?php echo $this->_tpl_vars['task']->get('id'); ?>
_name" align="left" valign="top">
				<?php echo ((is_array($_tmp=@$this->_tpl_vars['task']->get('name'))) ? $this->_run_mod_handler('default', true, $_tmp, "&nbsp;") : smarty_modifier_default($_tmp, "&nbsp;")); ?>

			</td>
			<td id="<?php echo $this->_tpl_vars['task']->get('id'); ?>
_description" align="left" valign="top">
				<?php echo ((is_array($_tmp=@$this->_tpl_vars['task']->get('description'))) ? $this->_run_mod_handler('default', true, $_tmp, "&nbsp;") : smarty_modifier_default($_tmp, "&nbsp;")); ?>

			</td>
			<td id="<?php echo $this->_tpl_vars['task']->get('id'); ?>
_created_on" align="left" valign="top">
				<?php echo ((is_array($_tmp=@$this->_tpl_vars['task']->get('created_on'))) ? $this->_run_mod_handler('default', true, $_tmp, "&nbsp;") : smarty_modifier_default($_tmp, "&nbsp;")); ?>

			</td>
			<td id="<?php echo $this->_tpl_vars['task']->get('id'); ?>
_status" align="left" valign="top">
				<?php 
				echo $this->_tpl_vars['foldstatus'][$this->_tpl_vars['task']->get('status')];
				 ?>
			</td>
			<td id="<?php echo $this->_tpl_vars['task']->get('id'); ?>
_functions" align="left" valign="top" class="alt">
				<?php if ($this->_tpl_vars['task']->get('status') != 2 && $this->_tpl_vars['task']->get('status') != 3 && $this->_tpl_vars['task']->get('status') != 4 && $this->_tpl_vars['task']->get('status') != 8): ?>
					<?php if (( ( ( $this->_tpl_vars['user']->get('level') < 5 ) && ( $this->_tpl_vars['task']->get('created_by') == $this->_tpl_vars['user']->get('id') ) ) || ( $this->_tpl_vars['user']->get('level') > 5 ) )): ?>
							<img src="style/img/a_user-idelete.png" alt="Delete <?php echo $this->_tpl_vars['task']->get('name'); ?>
" title="Delete <?php echo $this->_tpl_vars['task']->get('name'); ?>
" style="cursor:pointer" onclick="if (confirm('Are you sure you want to delete the task: <?php echo $this->_tpl_vars['task']->get('name'); ?>
')) deleteRow(this)"/>
					<?php else: ?>
						&nbsp;
					<?php endif; ?>
				<?php endif; ?>
				<?php if (( ( ( $this->_tpl_vars['user']->get('level') < 5 ) && ( $this->_tpl_vars['task']->get('created_by') == $this->_tpl_vars['user']->get('id') ) ) || ( $this->_tpl_vars['user']->get('level') > 5 ) )): ?>
						<img src="style/img/edit-find-small.png" alt="Look at the task parameters for <?php echo $this->_tpl_vars['task']->get('name'); ?>
" title="Look at the task parameters for <?php echo $this->_tpl_vars['task']->get('name'); ?>
" style="cursor:pointer" onclick="return GB_show('Task Parameters', 'popTaskInformation.php?type=parameters&id=<?php echo $this->_tpl_vars['task']->get('id'); ?>
', 500, 500)"/>
						<img src="style/img/messages.png" alt="Look at the task messages for <?php echo $this->_tpl_vars['task']->get('name'); ?>
" title="Look at the task messages for <?php echo $this->_tpl_vars['task']->get('name'); ?>
" style="cursor:pointer" onclick="return GB_show('Task Messages', 'popTaskInformation.php?type=messages&id=<?php echo $this->_tpl_vars['task']->get('id'); ?>
', 170, 500)"/>
				<?php else: ?>
					&nbsp;
				<?php endif; ?>
			</td>
		</tr>
	<?php endforeach; endif; unset($_from); ?>
	</table>
</div>

<script type="text/javascript" language="javascript">
	
	var GB_ANIMATION = true;
    var GB_IMG_DIR = "style/img/";
    var GB_overlay_click_close = true;
    
</script>
			