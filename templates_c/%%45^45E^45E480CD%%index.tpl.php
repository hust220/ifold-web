<?php /* Smarty version 2.6.11, created on 2007-11-06 13:16:37
         compiled from index.tpl */ ?>
<div class="indexTitle">&raquo; <?php echo $this->_tpl_vars['user']->get('namefirst'); ?>
 <?php echo $this->_tpl_vars['user']->get('namelast'); ?>
's Fold Status</div>
<br/>
<?php if ($this->_tpl_vars['user']->get('emailConfirmed') == 0): ?>
<strong>
WARNING - Your current registered email address has not been confirmed with iFold. 
Until you confirm your address, you will not be allowed to submit new jobs. 
Check your email for a message from iFold and click the enclosed link to confirm your address.
</strong><br/><br/>
<?php endif; ?>
<div class="indexStatus">
<?php if ($this->_tpl_vars['numCompleted'] == 0 && $this->_tpl_vars['numProcessing'] == 0 && $this->_tpl_vars['numQueued'] == 0): ?>
	You haven't submitted any tasks recently, and there's nothing to pick up.
<?php else: ?>
	<?php if ($this->_tpl_vars['numCompleted'] != 0): ?>
		<a href="activity.php"><span class="frontIndicator"><?php echo $this->_tpl_vars['numCompleted']; ?>
 task<?php if ($this->_tpl_vars['numCompleted'] > 1): ?>s are <?php else: ?> is <?php endif; ?>ready to be picked up!</span></a><br/>
	<?php endif; ?>
	<?php if ($this->_tpl_vars['numProcessing'] != 0): ?>
		<a href="taskList.php"><span class="frontIndicator" style="color:#6E96A2"><?php echo $this->_tpl_vars['numProcessing']; ?>
 task<?php if ($this->_tpl_vars['numProcessing'] > 1): ?>s are <?php else: ?> is <?php endif; ?> processing...</span></a><br/>
	<?php endif; ?>
	<?php if ($this->_tpl_vars['numQueued'] != 0): ?>
		<a href="taskList.php"><span class="frontIndicator" style="color:#A8C3CF"><?php echo $this->_tpl_vars['numQueued']; ?>
 task<?php if ($this->_tpl_vars['numQueued'] > 1): ?>s are <?php else: ?> is <?php endif; ?> queued.</span></a><br/>
	<?php endif; ?>
<?php endif; ?>
</div>
<p>
Please use the left menu to submit a new task to iFold. <p>To contact iFold administrators, send email to: <a href="mailto:ifold@listserv.unc.edu" alt="iFold Administrators">ifold@listserv.unc.edu</a>.