<script src="style/js/queue.js" language="javascript" type="text/javascript"></script>
{counter assign=myCompletedCount start=0}
{foreach from=$outputList item=output}
	{counter print=false}
{/foreach}
{if $myCompletedCount > 0}
<div class="indexTitle">&raquo; Your Activity</div><br/>
{$user->get('username')}(userid: {$user->get('id')})
You have <strong>{$myCompletedCount} outputs</strong> that have completed and ready for download!<br/><br/>

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
	{foreach from=$outputList item=output}
		<tr>
			<td id="{$output->get('id')}_name" align="left" valign="top">
				{$output->get('name')|default:"&nbsp;"}
			</td>
			<td id="{$output->get('id')}_description" align="left" valign="top">
				{$output->get('description')|default:"&nbsp;"}
			</td>
			<td id="{$output->get('id')}_created_on" align="left" valign="top">
				{$output->get('created_on')|default:"&nbsp;"}
			</td>
			<td id="{$output->get('id')}_outputType" align="left" valign="top">
				{php}
				echo $this->_tpl_vars['outputtypes'][$this->_tpl_vars['output']->get('outputType')];
				{/php}
			</td>
			<td id="{$output->get('id')}_fileName" align="left" valign="top">
				<a href="{php}echo DOWNLOAD_DIR{/php}/{$output->get('fileName')}">
					{$output->get('fileName')}
				</a>
			</td>
			<td id="{$output->get('id')}_functions" align="left" valign="top" class="alt">
				<img src="style/img/a_user-idelete.png" alt="Delete This Output" style="cursor:pointer" onclick="if (confirm('Are you sure you want to delete this output associated with the task: {$output->get('name')}')) deleteOutputRow(this)"/>
			</td>
		</tr>
	{/foreach}
	</table>
</div><br/><br/>
{/if}
You have previously submitted <strong>{php} echo count($this->_tpl_vars['taskList']);{/php}</strong> tasks.<br/><br/>
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
	{foreach from=$taskList item=task}
		<tr class="{cycle values="normal,alt"}" >
			<td id="{$task->get('id')}_queuenum" align="left" valign="top">
				{if $task->get('status') != 5}
					{$task->get('queuenum')}
				{else}
					--
				{/if}
			</td>
			<td id="{$task->get('id')}_name" align="left" valign="top">
				{$task->get('name')|default:"&nbsp;"}
			</td>
			<td id="{$task->get('id')}_description" align="left" valign="top">
				{$task->get('description')|default:"&nbsp;"}
			</td>
			<td id="{$task->get('id')}_created_on" align="left" valign="top">
				{$task->get('created_on')|default:"&nbsp;"}
			</td>
			<td id="{$task->get('id')}_status" align="left" valign="top">
				{php}
				echo $this->_tpl_vars['foldstatus'][$this->_tpl_vars['task']->get('status')];
				{/php}
			</td>
			<td id="{$task->get('id')}_functions" align="left" valign="top" class="alt">
				{if $task->get('status') != 2 &&
					$task->get('status') != 3 &&
					$task->get('status') != 4 &&
					$task->get('status') != 8}
					{if ( (($user->get('level') < 5) && ($task->get('created_by') == $user->get('id')))
						|| ($user->get('level') > 5) )}
							<img src="style/img/a_user-idelete.png" alt="Delete {$task->get('name')}" title="Delete {$task->get('name')}" style="cursor:pointer" onclick="if (confirm('Are you sure you want to delete the task: {$task->get('name')}')) deleteRow(this)"/>
					{else}
						&nbsp;
					{/if}
				{/if}
				{if ( (($user->get('level') < 5) && ($task->get('created_by') == $user->get('id')))
					|| ($user->get('level') > 5) )}
						<img src="style/img/edit-find-small.png" alt="Look at the task parameters for {$task->get('name')}" title="Look at the task parameters for {$task->get('name')}" style="cursor:pointer" onclick="return GB_show('Task Parameters', 'popTaskInformation.php?type=parameters&id={$task->get('id')}', 500, 500)"/>
						<img src="style/img/messages.png" alt="Look at the task messages for {$task->get('name')}" title="Look at the task messages for {$task->get('name')}" style="cursor:pointer" onclick="return GB_show('Task Messages', 'popTaskInformation.php?type=messages&id={$task->get('id')}', 170, 500)"/>
				{else}
					&nbsp;
				{/if}
			</td>
		</tr>
	{/foreach}
	</table>
</div>

<script type="text/javascript" language="javascript">
	
	var GB_ANIMATION = true;
    var GB_IMG_DIR = "style/img/";
    var GB_overlay_click_close = true;
    
</script>
			
