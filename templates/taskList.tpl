<script src="style/js/queue.js" language="javascript" type="text/javascript"></script>
<script src="style/js/rico.js" language="javascript" type="text/javascript"></script>
<div class="indexTitle">&raquo; The Queue</div><br/>
<input type="hidden" id="userLevel" name="userLevel" value="{$user->get('level')}" />
{counter assign=myTasksCount start=0}
{foreach from=$queue key=key item=queueItem}
	{if $queueItem.user->get('id') == $user->get('id')}
		{counter print=false}
	{/if}
{/foreach}
There are <strong>{php} echo count($this->_tpl_vars['queue']);{/php}</strong> tasks in the queue.
<strong>{$myTasksCount}</strong> of them are yours.
<br/><br/>
{if ($user->get('level') >= 5)}
	<div class="queueButton" id="hideCompleted" onClick="hideShowCompleted(this,'hide',1)">hide completed tasks</div>
{/if}
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
	{foreach from=$queue key=key item=queueItem}
		{if $queueItem.task->get('status') != 5}
		<tr id="{$queueItem.task->get('id')}_{$queueItem.task->get('status')}" class="{cycle values="normal,alt"}">
			<td id="{$queueItem.task->get('id')}_queuenum" align="left" valign="top">
				{if $queueItem.task->get('status') == 1}
					<span class="bigQueueNum">{$queueItem.task->get('queuenum')|default:"&nbsp;"}</span>
				{elseif $queueItem.task->get('status') == 2 || $queueItem.task->get('status') == 3 || $queueItem.task->get('status') == 4}
					<img src="style/img/indicator_white.gif" alt="Running/Processing Task" />
				{else}
					&nbsp;
				{/if}
			</td>
			<td id="{$queueItem.task->get('id')}_name" align="left" valign="top">
				{if ($user->get('level') < 5)}
					{if $queueItem.user->get('id') == $user->get('id')}
							{$queueItem.task->get('name')|truncate:12:"...":true|default:"&nbsp;"}
					{else}
						--
					{/if}
				{else}
					{$queueItem.task->get('name')|truncate:12:"...":true|default:"&nbsp;"}
				{/if}
			</td>
			<td class="taskdescription" id="{$queueItem.task->get('id')}_description" align="left" valign="top">
				{if ($user->get('level') < 5)}
					{if $queueItem.user->get('id') == $user->get('id')}
							{$queueItem.task->get('description')|truncate:20:"...":true|default:"&nbsp;"}
					{else}
						--
					{/if}
				{else}
					{$queueItem.task->get('description')|truncate:20:"...":true|default:"&nbsp;"}
				{/if}
			</td>
			<td id="{$queueItem.task->get('id')}_created_on" align="left" valign="top">
				{$queueItem.task->get('created_on')|date_format:"%B %e, %Y at %I:%M %p"|default:"&nbsp;"}
			</td>
			<td id="{$queueItem.task->get('id')}_user" align="left" valign="top">
				{if ($user->get('level') < 5)}
					{if $queueItem.user->get('id') == $user->get('id')}
							{$queueItem.user->get('id')|default:"&nbsp;"}
					{else}
						--
					{/if}
				{else}
					{$queueItem.user->get('username')}:{$queueItem.user->get('id')|default:"&nbsp;"}
				{/if}
			</td>
			<td id="{$queueItem.task->get('id')}_status" align="left" valign="top">
				{php}
				echo $this->_tpl_vars['foldstatus'][$this->_tpl_vars['queueItem']['task']->get('status')];
				{/php}
			</td>
			<td id="{$queueItem.task->get('id')}_functions" align="left" valign="top" class="alt">
				{if $queueItem.task->get('status') != 2 &&
					$queueItem.task->get('status') != 3 &&
					$queueItem.task->get('status') != 4 &&
					$queueItem.task->get('status') != 8}
					{if ( (($user->get('level') < 5) && ($queueItem.user->get('id') == $user->get('id')))
						|| ($user->get('level') > 5) )}
							<img src="style/img/a_user-idelete.png" alt="Delete {$queueItem.task->get('name')}" title="Delete {$queueItem.task->get('name')}" style="cursor:pointer" onclick="if (confirm('Are you sure you want to delete the task: {$queueItem.task->get('name')}')) {literal}{ deleteRow(this, 'queueMessages', false) }{/literal}"/>
					{else}
						&nbsp;
					{/if}
				{/if}
				{if ( (($user->get('level') < 5) && ($queueItem.user->get('id') == $user->get('id')))
					|| ($user->get('level') > 5) )}
						<img src="style/img/edit-find-small.png" alt="Look at the task parameters for {$queueItem.task->get('name')}" title="Look at the task parameters for {$queueItem.task->get('name')}" style="cursor:pointer" onclick="return GB_show('Task Parameters', 'popTaskInformation.php?type=parameters&id={$queueItem.task->get('id')}', 500, 500)"/>
						<img src="style/img/messages.png" alt="Look at the task messages for {$queueItem.task->get('name')}" title="Look at the task messages for {$queueItem.task->get('name')}" style="cursor:pointer" onclick="return GB_show('Task Messages', 'popTaskInformation.php?type=messages&id={$queueItem.task->get('id')}', 170, 500)"/>
				{/if}
				{if (($queueItem.task->get('status') == 8) && ($user->get('level') > 5))}
					<img src="style/img/task-reset.png" alt="Reset the task {$queueItem.task->get('name')}" title="Reset the task {$queueItem.task->get('name')}" style="cursor:pointer" onclick="resetTask('{$queueItem.task->get('id')}')"/>
				{/if}
				&nbsp;
			</td>
		</tr>
		{/if}
	{/foreach}
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
	{php} $countQueueItems = 0; {/php}
	{foreach from=$queue key=key item=queueItem}
		{if $queueItem.task->get('status') == 5}
			{php} if ($countQueueItems < 9) { {/php}
			<tr id="{$queueItem.task->get('id')}_{$queueItem.task->get('status')}" class="{cycle values="normal,alt"}">
				<td class="cell" id="{$queueItem.task->get('id')}_name" align="left" valign="top" style="width:140px">
					{if ($user->get('level') < 5)}
						{if $queueItem.user->get('id') == $user->get('id')}
								{$queueItem.task->get('name')|truncate:12:"...":true|default:"&nbsp;"}
						{else}
							--
						{/if}
					{else}
						{$queueItem.task->get('name')|truncate:12:"...":true|default:"&nbsp;"}
					{/if}
				</td>
				<td class="cell" class="taskdescription" id="{$queueItem.task->get('id')}_description" align="left" valign="top" style="width:200px">
					{if ($user->get('level') < 5)}
						{if $queueItem.user->get('id') == $user->get('id')}
								{$queueItem.task->get('description')|truncate:20:"...":true|default:"&nbsp;"}
						{else}
							--
						{/if}
					{else}
						{$queueItem.task->get('description')|truncate:20:"...":true|default:"&nbsp;"}
					{/if}
				</td>
				<td class="cell" id="{$queueItem.task->get('id')}_created_on" align="left" valign="top" style="width:115px">
					{$queueItem.task->get('completed_on')|date_format:"%B %e, %Y at %I:%M %p"|default:"&nbsp;"}
				</td>
				<td class="cell" id="{$queueItem.task->get('id')}_user" align="left" valign="top" style="width:70px">
					{if ($user->get('level') < 5)}
						{if $queueItem.user->get('id') == $user->get('id')}
								{$queueItem.user->get('username')|default:"&nbsp;"}
						{else}
							--
						{/if}
					{else}
						{$queueItem.user->get('username')|default:"&nbsp;"}
					{/if}
				</td>
				<td class="cell" id="{$queueItem.task->get('id')}_functions" align="left" valign="top" class="alt" style="width:60px">
					{if $queueItem.task->get('status') != 2 &&
						$queueItem.task->get('status') != 3 &&
						$queueItem.task->get('status') != 4 &&
						$queueItem.task->get('status') != 8}
						{if ( (($user->get('level') < 5) && ($queueItem.user->get('id') == $user->get('id')))
							|| ($user->get('level') > 5) )}
								<img src="style/img/a_user-idelete.png" alt="Delete {$queueItem.task->get('name')}" title="Delete {$queueItem.task->get('name')}" style="cursor:pointer" onclick="if (confirm('Are you sure you want to delete the task: {$queueItem.task->get('name')}')) deleteRow(this, true)"/>
						{else}
							&nbsp;
						{/if}
					{/if}
					{if ( (($user->get('level') < 5) && ($queueItem.user->get('id') == $user->get('id')))
						|| ($user->get('level') > 5) )}
							<img src="style/img/edit-find-small.png" alt="Look at the task parameters for {$queueItem.task->get('name')}" title="Look at the task parameters for {$queueItem.task->get('name')}" style="cursor:pointer" onclick="return GB_show('Task Parameters', 'popTaskInformation.php?type=parameters&id={$queueItem.task->get('id')}', 500, 500)"/>
							<img src="style/img/messages.png" alt="Look at the task messages for {$queueItem.task->get('name')}" title="Look at the task messages for {$queueItem.task->get('name')}" style="cursor:pointer" onclick="return GB_show('Task Messages', 'popTaskInformation.php?type=messages&id={$queueItem.task->get('id')}', 170, 500)"/>
					{else}
						&nbsp;
					{/if}
				</td>
			</tr>
			{php} 
					$countQueueItems++;
				} 
			{/php}
			{/if}
	{/foreach}
	</table>
</div><br/><br/><br/><br/>

{literal}
<script type="text/javascript" language="javascript">
	
	var GB_ANIMATION = true;
    var GB_IMG_DIR = "style/img/";
    var GB_overlay_click_close = true;
    
	var tu = null;
    var opts = 	{	prefetchBuffer: 	true,
    				onscroll :      	updateHeader,
    				sortAscendImg:      'style/img/sort_asc.gif',
               		sortDescendImg:     'style/img/sort_desc.gif'  
   				};
   	
	tu = new Rico.LiveGrid( 'completedQueueTable',
                           8,{/literal}
                           {php} echo count($this->_tpl_vars['queue']);{/php}
                           {literal}
                           ,'ajaxUtilities.php?action=getCompletedTasks', opts );
    
</script>
{/literal}
