<div class="indexTitle">&raquo; Help Center</div><br/>
<div id="help">
{if isset($saveError)}
<div class="errors_box" style="width:90%">
		{$saveError}
</div>
{/if}
{if isset($saveSuccess)}
<div class="errors_box" style="width:90%">
		{$saveSuccess}
</div>
{/if}
{if isset($deleteError)}
<div class="errors_box" style="width:90%">
		{$deleteError}
</div>
{/if}
{if isset($deleteSuccess)}
<div class="errors_box" style="width:90%">
		{$deleteSuccess}
</div>
{/if}
	<table id="helpTable" border="0" cellpadding="0" cellspacing="0" class="ifoldTable">
	{foreach from=$helpdata item=helpItem}
		{if ($user->get('level') > $helpItem->get('level'))}
			{if ( $user->get('level') > 4)}
				<form id="helpEditButton" method="post" action="help.php">
				<input type="hidden" name="id" value="{$helpItem->get('id')}" />
				<input type="Submit" name="action" value="edit" />
				</form>
			{/if}
			<a href="help.php?action=view&id={$helpItem->get('id')}">{$helpItem->get('name')}</a>
			<br/><br/>
		{/if}
	{/foreach}
	{if ( $user->get('level') > 4)}
		<form name="help" action="help.php" method="POST">
		<input type="submit" name="action" value="add" />
		</form> 
	{/if}
	</table>
</div>
