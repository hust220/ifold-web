<?php /* Smarty version 2.6.11, created on 2006-05-11 15:27:30
         compiled from help.tpl */ ?>
<div class="indexTitle">&raquo; Help Center</div><br/>
<div id="help">
<?php if (isset ( $this->_tpl_vars['saveError'] )): ?>
<div class="errors_box" style="width:90%">
		<?php echo $this->_tpl_vars['saveError']; ?>

</div>
<?php endif; ?>
<?php if (isset ( $this->_tpl_vars['saveSuccess'] )): ?>
<div class="errors_box" style="width:90%">
		<?php echo $this->_tpl_vars['saveSuccess']; ?>

</div>
<?php endif; ?>
<?php if (isset ( $this->_tpl_vars['deleteError'] )): ?>
<div class="errors_box" style="width:90%">
		<?php echo $this->_tpl_vars['deleteError']; ?>

</div>
<?php endif; ?>
<?php if (isset ( $this->_tpl_vars['deleteSuccess'] )): ?>
<div class="errors_box" style="width:90%">
		<?php echo $this->_tpl_vars['deleteSuccess']; ?>

</div>
<?php endif; ?>
	<table id="helpTable" border="0" cellpadding="0" cellspacing="0" class="ifoldTable">
	<?php $_from = $this->_tpl_vars['helpdata']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['helpItem']):
?>
		<?php if (( $this->_tpl_vars['user']->get('level') > $this->_tpl_vars['helpItem']->get('level') )): ?>
			<?php if (( $this->_tpl_vars['user']->get('level') > 4 )): ?>
				<form id="helpEditButton" method="post" action="help.php">
				<input type="hidden" name="id" value="<?php echo $this->_tpl_vars['helpItem']->get('id'); ?>
" />
				<input type="Submit" name="action" value="edit" />
				</form>
			<?php endif; ?>
			<a href="help.php?action=view&id=<?php echo $this->_tpl_vars['helpItem']->get('id'); ?>
"><?php echo $this->_tpl_vars['helpItem']->get('name'); ?>
</a>
			<br/><br/>
		<?php endif; ?>
	<?php endforeach; endif; unset($_from); ?>
	<?php if (( $this->_tpl_vars['user']->get('level') > 4 )): ?>
		<form name="help" action="help.php" method="POST">
		<input type="submit" name="action" value="add" />
		</form> 
	<?php endif; ?>
	</table>
</div>