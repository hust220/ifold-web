<?php /* Smarty version 2.6.11, created on 2017-11-13 13:29:07
         compiled from taskList.tpl */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('function', 'counter', 'taskList.tpl', 5, false),array('function', 'cycle', 'taskList.tpl', 33, false),array('modifier', 'default', 'taskList.tpl', 36, false),array('modifier', 'truncate', 'taskList.tpl', 46, false),array('modifier', 'date_format', 'taskList.tpl', 66, false),)), $this); ?>
<script src="style/js/queue.js" language="javascript" type="text/javascript"></script>
<script src="style/js/rico.js" language="javascript" type="text/javascript"></script>
<div class="indexTitle">&raquo; The Queue</div><br/>
<input type="hidden" id="userLevel" name="userLevel" value="<?php echo $this->_tpl_vars['user']->get('level'); ?>
" />
<?php echo smarty_function_counter(array('assign' => 'myTasksCount','start' => 0), $this);?>

<?php $_from = $this->_tpl_vars['queue']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['key'] => $this->_tpl_vars['queueItem']):
?>
	<?php if ($this->_tpl_vars['queueItem']['user']->get('id') == $this->_tpl_vars['user']->get('id')): ?>
		<?php echo smarty_function_counter(array('print' => false), $this);?>

	<?php endif; ?>
<?php endforeach; endif; unset($_from); ?>
There are <strong><?php  echo count($this->_tpl_vars['queue']); ?></strong> tasks in the queue.
<strong><?php echo $this->_tpl_vars['myTasksCount']; ?>
</strong> of them are yours.
<br/><br/>
<?php if (( $this->_tpl_vars['user']->get('level') >= 5 )): ?>
	<div class="queueButton" id="hideCompleted" onClick="hideShowCompleted(this,'hide',1)">hide completed tasks</div>
<?php endif; ?>
<br/><br/>
<div id="queue">
	<h2 class="submitSteps">Non-Completed Tasks</h2>
	<div id="queueMessages" class="ajaxMessages"></div><br/>
	<table id="queueTable" border="0" cellpadding="0" cellspacing="0" class="ifoldTable">
		<tr>
			<th align="left" valign="top" width="30">Q #</th>
			<th align="left" valign="top">Name</th>
			<th align="left" valign="top">Description</th>
			<th align="left" valign="top">Created</th>
			<th align="left" valign="top">Created By</th>
			<th align="left" valign="top">Status</th>
			<th align="left" valign="top" class="alt">Functions</th>
		</tr>
	<?php $_from = $this->_tpl_vars['queue']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['key'] => $this->_tpl_vars['queueItem']):
?>
		<?php if ($this->_tpl_vars['queueItem']['task']->get('status') != 5): ?>
		<tr id="<?php echo $this->_tpl_vars['queueItem']['task']->get('id'); ?>
_<?php echo $this->_tpl_vars['queueItem']['task']->get('status'); ?>
" class="<?php echo smarty_function_cycle(array('values' => "normal,alt"), $this);?>
">
			<td id="<?php echo $this->_tpl_vars['queueItem']['task']->get('id'); ?>
_queuenum" align="left" valign="top">
				<?php if ($this->_tpl_vars['queueItem']['task']->get('status') == 1): ?>
					<span class="bigQueueNum"><?php echo ((is_array($_tmp=@$this->_tpl_vars['queueItem']['task']->get('queuenum'))) ? $this->_run_mod_handler('default', true, $_tmp, "&nbsp;") : smarty_modifier_default($_tmp, "&nbsp;")); ?>
</span>
				<?php elseif ($this->_tpl_vars['queueItem']['task']->get('status') == 2 || $this->_tpl_vars['queueItem']['task']->get('status') == 3 || $this->_tpl_vars['queueItem']['task']->get('status') == 4): ?>
					<img src="style/img/indicator_white.gif" alt="Running/Processing Task" />
				<?php else: ?>
					&nbsp;
				<?php endif; ?>
			</td>
			<td id="<?php echo $this->_tpl_vars['queueItem']['task']->get('id'); ?>
_name" align="left" valign="top">
				<?php if (( $this->_tpl_vars['user']->get('level') < 5 )): ?>
					<?php if ($this->_tpl_vars['queueItem']['user']->get('id') == $this->_tpl_vars['user']->get('id')): ?>
							<?php echo ((is_array($_tmp=((is_array($_tmp=$this->_tpl_vars['queueItem']['task']->get('name'))) ? $this->_run_mod_handler('truncate', true, $_tmp, 12, "...", true) : smarty_modifier_truncate($_tmp, 12, "...", true)))) ? $this->_run_mod_handler('default', true, $_tmp, "&nbsp;") : smarty_modifier_default($_tmp, "&nbsp;")); ?>

					<?php else: ?>
						--
					<?php endif; ?>
				<?php else: ?>
					<?php echo ((is_array($_tmp=((is_array($_tmp=$this->_tpl_vars['queueItem']['task']->get('name'))) ? $this->_run_mod_handler('truncate', true, $_tmp, 12, "...", true) : smarty_modifier_truncate($_tmp, 12, "...", true)))) ? $this->_run_mod_handler('default', true, $_tmp, "&nbsp;") : smarty_modifier_default($_tmp, "&nbsp;")); ?>

				<?php endif; ?>
			</td>
			<td class="taskdescription" id="<?php echo $this->_tpl_vars['queueItem']['task']->get('id'); ?>
_description" align="left" valign="top">
				<?php if (( $this->_tpl_vars['user']->get('level') < 5 )): ?>
					<?php if ($this->_tpl_vars['queueItem']['user']->get('id') == $this->_tpl_vars['user']->get('id')): ?>
							<?php echo ((is_array($_tmp=((is_array($_tmp=$this->_tpl_vars['queueItem']['task']->get('description'))) ? $this->_run_mod_handler('truncate', true, $_tmp, 20, "...", true) : smarty_modifier_truncate($_tmp, 20, "...", true)))) ? $this->_run_mod_handler('default', true, $_tmp, "&nbsp;") : smarty_modifier_default($_tmp, "&nbsp;")); ?>

					<?php else: ?>
						--
					<?php endif; ?>
				<?php else: ?>
					<?php echo ((is_array($_tmp=((is_array($_tmp=$this->_tpl_vars['queueItem']['task']->get('description'))) ? $this->_run_mod_handler('truncate', true, $_tmp, 20, "...", true) : smarty_modifier_truncate($_tmp, 20, "...", true)))) ? $this->_run_mod_handler('default', true, $_tmp, "&nbsp;") : smarty_modifier_default($_tmp, "&nbsp;")); ?>

				<?php endif; ?>
			</td>
			<td id="<?php echo $this->_tpl_vars['queueItem']['task']->get('id'); ?>
_created_on" align="left" valign="top">
				<?php echo ((is_array($_tmp=((is_array($_tmp=$this->_tpl_vars['queueItem']['task']->get('created_on'))) ? $this->_run_mod_handler('date_format', true, $_tmp, "%B %e, %Y at %I:%M %p") : smarty_modifier_date_format($_tmp, "%B %e, %Y at %I:%M %p")))) ? $this->_run_mod_handler('default', true, $_tmp, "&nbsp;") : smarty_modifier_default($_tmp, "&nbsp;")); ?>

			</td>
			<td id="<?php echo $this->_tpl_vars['queueItem']['task']->get('id'); ?>
_user" align="left" valign="top">
				<?php if (( $this->_tpl_vars['user']->get('level') < 5 )): ?>
					<?php if ($this->_tpl_vars['queueItem']['user']->get('id') == $this->_tpl_vars['user']->get('id')): ?>
							<?php echo ((is_array($_tmp=@$this->_tpl_vars['queueItem']['user']->get('id'))) ? $this->_run_mod_handler('default', true, $_tmp, "&nbsp;") : smarty_modifier_default($_tmp, "&nbsp;")); ?>

					<?php else: ?>
						--
					<?php endif; ?>
				<?php else: ?>
					<?php echo $this->_tpl_vars['queueItem']['user']->get('username'); ?>
:<?php echo ((is_array($_tmp=@$this->_tpl_vars['queueItem']['user']->get('id'))) ? $this->_run_mod_handler('default', true, $_tmp, "&nbsp;") : smarty_modifier_default($_tmp, "&nbsp;")); ?>

				<?php endif; ?>
			</td>
			<td id="<?php echo $this->_tpl_vars['queueItem']['task']->get('id'); ?>
_status" align="left" valign="top">
				<?php 
				echo $this->_tpl_vars['foldstatus'][$this->_tpl_vars['queueItem']['task']->get('status')];
				 ?>
			</td>
			<td id="<?php echo $this->_tpl_vars['queueItem']['task']->get('id'); ?>
_functions" align="left" valign="top" class="alt">
				<?php if ($this->_tpl_vars['queueItem']['task']->get('status') != 2 && $this->_tpl_vars['queueItem']['task']->get('status') != 3 && $this->_tpl_vars['queueItem']['task']->get('status') != 4 && $this->_tpl_vars['queueItem']['task']->get('status') != 8): ?>
					<?php if (( ( ( $this->_tpl_vars['user']->get('level') < 5 ) && ( $this->_tpl_vars['queueItem']['user']->get('id') == $this->_tpl_vars['user']->get('id') ) ) || ( $this->_tpl_vars['user']->get('level') > 5 ) )): ?>
							<img src="style/img/a_user-idelete.png" alt="Delete <?php echo $this->_tpl_vars['queueItem']['task']->get('name'); ?>
" title="Delete <?php echo $this->_tpl_vars['queueItem']['task']->get('name'); ?>
" style="cursor:pointer" onclick="if (confirm('Are you sure you want to delete the task: <?php echo $this->_tpl_vars['queueItem']['task']->get('name'); ?>
')) <?php echo '{ deleteRow(this, \'queueMessages\', false) }'; ?>
"/>
					<?php else: ?>
						&nbsp;
					<?php endif; ?>
				<?php endif; ?>
				<?php if (( ( ( $this->_tpl_vars['user']->get('level') < 5 ) && ( $this->_tpl_vars['queueItem']['user']->get('id') == $this->_tpl_vars['user']->get('id') ) ) || ( $this->_tpl_vars['user']->get('level') > 5 ) )): ?>
						<img src="style/img/edit-find-small.png" alt="Look at the task parameters for <?php echo $this->_tpl_vars['queueItem']['task']->get('name'); ?>
" title="Look at the task parameters for <?php echo $this->_tpl_vars['queueItem']['task']->get('name'); ?>
" style="cursor:pointer" onclick="return GB_show('Task Parameters', 'popTaskInformation.php?type=parameters&id=<?php echo $this->_tpl_vars['queueItem']['task']->get('id'); ?>
', 500, 500)"/>
						<img src="style/img/messages.png" alt="Look at the task messages for <?php echo $this->_tpl_vars['queueItem']['task']->get('name'); ?>
" title="Look at the task messages for <?php echo $this->_tpl_vars['queueItem']['task']->get('name'); ?>
" style="cursor:pointer" onclick="return GB_show('Task Messages', 'popTaskInformation.php?type=messages&id=<?php echo $this->_tpl_vars['queueItem']['task']->get('id'); ?>
', 170, 500)"/>
				<?php endif; ?>
				<?php if (( ( $this->_tpl_vars['queueItem']['task']->get('status') == 8 ) && ( $this->_tpl_vars['user']->get('level') > 5 ) )): ?>
					<img src="style/img/task-reset.png" alt="Reset the task <?php echo $this->_tpl_vars['queueItem']['task']->get('name'); ?>
" title="Reset the task <?php echo $this->_tpl_vars['queueItem']['task']->get('name'); ?>
" style="cursor:pointer" onclick="resetTask('<?php echo $this->_tpl_vars['queueItem']['task']->get('id'); ?>
')"/>
				<?php endif; ?>
				&nbsp;
			</td>
		</tr>
		<?php endif; ?>
	<?php endforeach; endif; unset($_from); ?>
	</table>
</div><br/><br/>

<div id="completedQueue">
	<h2 class="submitSteps">Completed Tasks (Live Grid)</h2>
	<div id="completedQueueMessages" class="ajaxMessages"></div><br/>
	<div id="bookmark" class="liveGridBookmark"></div><br/>
	<table id="completedQueueTable_header" border="0" cellpadding="0" cellspacing="0" class="fixedTable ifoldtable" style="width:585px">
		<tr>
			<th align="left" valign="top" style="width:140px">Name</th>
			<th align="left" valign="top" style="width:200px">Description</th>
			<th align="left" valign="top" style="width:115px">Completed</th>
			<th align="left" valign="top" style="width:70px">Owner</th>
			<th align="left" valign="top" class="alt" style="width:60px">&nbsp;</th>
		</tr>
	</table>
	<table id="completedQueueTable" border="0" cellpadding="0" cellspacing="0" class="fixedTable ifoldtable" style="width:585px;float:left">
	<?php  $countQueueItems = 0;  ?>
	<?php $_from = $this->_tpl_vars['queue']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['key'] => $this->_tpl_vars['queueItem']):
?>
		<?php if ($this->_tpl_vars['queueItem']['task']->get('status') == 5): ?>
			<?php  if ($countQueueItems < 9) {  ?>
			<tr id="<?php echo $this->_tpl_vars['queueItem']['task']->get('id'); ?>
_<?php echo $this->_tpl_vars['queueItem']['task']->get('status'); ?>
" class="<?php echo smarty_function_cycle(array('values' => "normal,alt"), $this);?>
">
				<td class="cell" id="<?php echo $this->_tpl_vars['queueItem']['task']->get('id'); ?>
_name" align="left" valign="top" style="width:140px">
					<?php if (( $this->_tpl_vars['user']->get('level') < 5 )): ?>
						<?php if ($this->_tpl_vars['queueItem']['user']->get('id') == $this->_tpl_vars['user']->get('id')): ?>
								<?php echo ((is_array($_tmp=((is_array($_tmp=$this->_tpl_vars['queueItem']['task']->get('name'))) ? $this->_run_mod_handler('truncate', true, $_tmp, 12, "...", true) : smarty_modifier_truncate($_tmp, 12, "...", true)))) ? $this->_run_mod_handler('default', true, $_tmp, "&nbsp;") : smarty_modifier_default($_tmp, "&nbsp;")); ?>

						<?php else: ?>
							--
						<?php endif; ?>
					<?php else: ?>
						<?php echo ((is_array($_tmp=((is_array($_tmp=$this->_tpl_vars['queueItem']['task']->get('name'))) ? $this->_run_mod_handler('truncate', true, $_tmp, 12, "...", true) : smarty_modifier_truncate($_tmp, 12, "...", true)))) ? $this->_run_mod_handler('default', true, $_tmp, "&nbsp;") : smarty_modifier_default($_tmp, "&nbsp;")); ?>

					<?php endif; ?>
				</td>
				<td class="cell" class="taskdescription" id="<?php echo $this->_tpl_vars['queueItem']['task']->get('id'); ?>
_description" align="left" valign="top" style="width:200px">
					<?php if (( $this->_tpl_vars['user']->get('level') < 5 )): ?>
						<?php if ($this->_tpl_vars['queueItem']['user']->get('id') == $this->_tpl_vars['user']->get('id')): ?>
								<?php echo ((is_array($_tmp=((is_array($_tmp=$this->_tpl_vars['queueItem']['task']->get('description'))) ? $this->_run_mod_handler('truncate', true, $_tmp, 20, "...", true) : smarty_modifier_truncate($_tmp, 20, "...", true)))) ? $this->_run_mod_handler('default', true, $_tmp, "&nbsp;") : smarty_modifier_default($_tmp, "&nbsp;")); ?>

						<?php else: ?>
							--
						<?php endif; ?>
					<?php else: ?>
						<?php echo ((is_array($_tmp=((is_array($_tmp=$this->_tpl_vars['queueItem']['task']->get('description'))) ? $this->_run_mod_handler('truncate', true, $_tmp, 20, "...", true) : smarty_modifier_truncate($_tmp, 20, "...", true)))) ? $this->_run_mod_handler('default', true, $_tmp, "&nbsp;") : smarty_modifier_default($_tmp, "&nbsp;")); ?>

					<?php endif; ?>
				</td>
				<td class="cell" id="<?php echo $this->_tpl_vars['queueItem']['task']->get('id'); ?>
_created_on" align="left" valign="top" style="width:115px">
					<?php echo ((is_array($_tmp=((is_array($_tmp=$this->_tpl_vars['queueItem']['task']->get('completed_on'))) ? $this->_run_mod_handler('date_format', true, $_tmp, "%B %e, %Y at %I:%M %p") : smarty_modifier_date_format($_tmp, "%B %e, %Y at %I:%M %p")))) ? $this->_run_mod_handler('default', true, $_tmp, "&nbsp;") : smarty_modifier_default($_tmp, "&nbsp;")); ?>

				</td>
				<td class="cell" id="<?php echo $this->_tpl_vars['queueItem']['task']->get('id'); ?>
_user" align="left" valign="top" style="width:70px">
					<?php if (( $this->_tpl_vars['user']->get('level') < 5 )): ?>
						<?php if ($this->_tpl_vars['queueItem']['user']->get('id') == $this->_tpl_vars['user']->get('id')): ?>
								<?php echo ((is_array($_tmp=@$this->_tpl_vars['queueItem']['user']->get('username'))) ? $this->_run_mod_handler('default', true, $_tmp, "&nbsp;") : smarty_modifier_default($_tmp, "&nbsp;")); ?>

						<?php else: ?>
							--
						<?php endif; ?>
					<?php else: ?>
						<?php echo ((is_array($_tmp=@$this->_tpl_vars['queueItem']['user']->get('username'))) ? $this->_run_mod_handler('default', true, $_tmp, "&nbsp;") : smarty_modifier_default($_tmp, "&nbsp;")); ?>

					<?php endif; ?>
				</td>
				<td class="cell" id="<?php echo $this->_tpl_vars['queueItem']['task']->get('id'); ?>
_functions" align="left" valign="top" class="alt" style="width:60px">
					<?php if ($this->_tpl_vars['queueItem']['task']->get('status') != 2 && $this->_tpl_vars['queueItem']['task']->get('status') != 3 && $this->_tpl_vars['queueItem']['task']->get('status') != 4 && $this->_tpl_vars['queueItem']['task']->get('status') != 8): ?>
						<?php if (( ( ( $this->_tpl_vars['user']->get('level') < 5 ) && ( $this->_tpl_vars['queueItem']['user']->get('id') == $this->_tpl_vars['user']->get('id') ) ) || ( $this->_tpl_vars['user']->get('level') > 5 ) )): ?>
								<img src="style/img/a_user-idelete.png" alt="Delete <?php echo $this->_tpl_vars['queueItem']['task']->get('name'); ?>
" title="Delete <?php echo $this->_tpl_vars['queueItem']['task']->get('name'); ?>
" style="cursor:pointer" onclick="if (confirm('Are you sure you want to delete the task: <?php echo $this->_tpl_vars['queueItem']['task']->get('name'); ?>
')) deleteRow(this, true)"/>
						<?php else: ?>
							&nbsp;
						<?php endif; ?>
					<?php endif; ?>
					<?php if (( ( ( $this->_tpl_vars['user']->get('level') < 5 ) && ( $this->_tpl_vars['queueItem']['user']->get('id') == $this->_tpl_vars['user']->get('id') ) ) || ( $this->_tpl_vars['user']->get('level') > 5 ) )): ?>
							<img src="style/img/edit-find-small.png" alt="Look at the task parameters for <?php echo $this->_tpl_vars['queueItem']['task']->get('name'); ?>
" title="Look at the task parameters for <?php echo $this->_tpl_vars['queueItem']['task']->get('name'); ?>
" style="cursor:pointer" onclick="return GB_show('Task Parameters', 'popTaskInformation.php?type=parameters&id=<?php echo $this->_tpl_vars['queueItem']['task']->get('id'); ?>
', 500, 500)"/>
							<img src="style/img/messages.png" alt="Look at the task messages for <?php echo $this->_tpl_vars['queueItem']['task']->get('name'); ?>
" title="Look at the task messages for <?php echo $this->_tpl_vars['queueItem']['task']->get('name'); ?>
" style="cursor:pointer" onclick="return GB_show('Task Messages', 'popTaskInformation.php?type=messages&id=<?php echo $this->_tpl_vars['queueItem']['task']->get('id'); ?>
', 170, 500)"/>
					<?php else: ?>
						&nbsp;
					<?php endif; ?>
				</td>
			</tr>
			<?php  
					$countQueueItems++;
				} 
			 ?>
			<?php endif; ?>
	<?php endforeach; endif; unset($_from); ?>
	</table>
</div><br/><br/><br/><br/>

<?php echo '
<script type="text/javascript" language="javascript">
	
	var GB_ANIMATION = true;
    var GB_IMG_DIR = "style/img/";
    var GB_overlay_click_close = true;
    
	var tu = null;
    var opts = 	{	prefetchBuffer: 	true,
    				onscroll :      	updateHeader,
    				sortAscendImg:      \'style/img/sort_asc.gif\',
               		sortDescendImg:     \'style/img/sort_desc.gif\'  
   				};
   	
	tu = new Rico.LiveGrid( \'completedQueueTable\',
                           8,'; ?>

                           <?php  echo count($this->_tpl_vars['queue']); ?>
                           <?php echo '
                           ,\'ajaxUtilities.php?action=getCompletedTasks\', opts );
    
</script>
'; ?>
