<?php /* Smarty version 2.6.11, created on 2006-05-11 19:53:11
         compiled from helpView.tpl */ ?>
<div class="indexTitle">&raquo; <a href="help.php">Help Center:</a> <?php echo $this->_tpl_vars['helpdata']->get('name'); ?>
</div><br/>
<div id="help">
<table id="helpTable" border="0" cellpadding="0" cellspacing="0" class="ifoldTable">
<h2><?php echo $this->_tpl_vars['helpdata']->get('description'); ?>
</h2>
<?php echo $this->_tpl_vars['helpdata']->get('content'); ?>

</table>
</div>