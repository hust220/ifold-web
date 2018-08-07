{if isset($userRegConfirm)}

<strong>Thanks, {$userRegConfirm->get('namefirst')}!</strong> You have just completed <strong>Step 2 of 3</strong> in the Registration process.
The final step doesn't require anything on your end. An iFold administrator has been sent a notice
and will complete the final step, which is your approval.<br/><br/>

At that point, you will be sent a confirmation email and you will be able to login to iFold. Thanks
again for your patience and ensuring the security of this process as well as your reliability and
safety in using iFold.
<br/><br/>
iFold Administrators

{/if}

{if isset($emailReconfirm)}

<strong>Thanks, {$emailReconfirm->get('namefirst')}!</strong> You have just confirmed your new email address.
You can now submit new jobs once again.
<br/><br/>
iFold Administrators

{/if}

{if isset($confirmRegisterError)}
{$confirmRegisterError}
{/if}