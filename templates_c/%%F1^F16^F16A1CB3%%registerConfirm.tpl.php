<?php /* Smarty version 2.6.11, created on 2006-06-02 11:28:21
         compiled from registerConfirm.tpl */ ?>
<?php if (isset ( $this->_tpl_vars['userRegConfirm'] )): ?>

<strong>Thanks, <?php echo $this->_tpl_vars['userRegConfirm']->get('namefirst'); ?>
!</strong> You have just completed <strong>Step 2 of 3</strong> in the Registration process.
The final step doesn't require anything on your end. An iFold administrator has been sent a notice
and will complete the final step, which is your approval.<br/><br/>

At that point, you will be sent a confirmation email and you will be able to login to iFold. Thanks
again for your patience and ensuring the security of this process as well as your reliability and
safety in using iFold.
<br/><br/>
iFold Administrators

<?php endif; ?>

<?php if (isset ( $this->_tpl_vars['emailReconfirm'] )): ?>

<strong>Thanks, <?php echo $this->_tpl_vars['emailReconfirm']->get('namefirst'); ?>
!</strong> You have just confirmed your new email address.
You can now submit new jobs once again.
<br/><br/>
iFold Administrators

<?php endif; ?>

<?php if (isset ( $this->_tpl_vars['confirmRegisterError'] )): ?>
<?php echo $this->_tpl_vars['confirmRegisterError']; ?>

<?php endif; ?>