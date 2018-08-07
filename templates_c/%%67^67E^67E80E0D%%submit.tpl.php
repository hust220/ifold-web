<?php /* Smarty version 2.6.11, created on 2007-11-28 17:10:36
         compiled from submit.tpl */ ?>
<script src="style/js/rico.js"></script>
<script src="style/js/ifolderrors.js" language="javascript" type="text/javascript"></script>
<script src="style/js/submit.js" language="javascript" type="text/javascript"></script>

<div class="indexTitle">&raquo; Submit a Task</div><br/>

<?php if (isset ( $this->_tpl_vars['submitError'] )): ?>
<div class="errors_box" style="width:90%">
		<?php echo $this->_tpl_vars['submitError']; ?>

</div>
<?php endif; ?>

<?php if (isset ( $this->_tpl_vars['submitSuccess'] )): ?>
	Job has been submitted!
<?php endif; ?>

<h2 class="submitSteps">Step 1: Fill in the General Information</h2>

<!-- Start the Form -->

<form enctype="multipart/form-data" method="post" action="submit.php" onSubmit="return validateForm(this);">
<table id="submitTable" border="0" cellpadding="0" cellspacing="0" class="ifoldTable" style="width:400px">
	<tr>
		<td width="90%">Username:</td>
		<td><input id="username" type="text" disabled="true" value="<?php echo $this->_tpl_vars['user']->get('username'); ?>
" /></td>
	</tr>
	<tr>
		<td>Name of Task:</td>
		<td><input id="name" type="text" name="name" value="<?php echo $this->_tpl_vars['user']->get('username'); ?>
.<?php echo date("m\.d\.y\-G\:i") ?>"/></td>
	</tr>
	<tr>
		<td>Description of Task:</td>
		<td><input id="description" type="text" name="description" value="<?php echo $this->_tpl_vars['user']->get('username'); ?>
.<?php echo date("m\.d\.y\-G\:i") ?>" /></td>
	</tr>
</table><br/>
<input id="foldtype" type="hidden" name="foldtype" />
<h2 class="submitSteps">Step 2: Select the Type of Task</h2>

<!-- Continue with the Second Part of the Form -->

<div id="accordion" style="width:95%">
	<?php $_from = $this->_tpl_vars['foldtypes']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['foldtype']):
?>
	<?php 

		$this->_tpl_vars['foldtypeId'] = $this->_tpl_vars['foldtype']['id'];
	 ?>
		<div id="<?php echo $this->_tpl_vars['foldtypeId']; ?>
_FoldTypePanel">
			<div class="foldtype_panel_head" id="<?php echo $this->_tpl_vars['foldtype']->name; ?>
Header">
				<div class="lbl_chooseTask"><?php echo $this->_tpl_vars['foldtype']->description; ?>
</div>
				<div id="<?php echo $this->_tpl_vars['foldtypeId']; ?>
_btn_chooseTask" class="btn_chooseTask" onmouseover="this.style.border='1px inset black'" onmouseout="this.style.border='1px outset black'" onclick="loadForm('<?php echo $this->_tpl_vars['foldtype']['id']; ?>')">choose this task</div>
			</div>
			<div id="<?php echo $this->_tpl_vars['foldtype']->name; ?>
Content">
				<div class="foldtype_content_sub">
				<?php 
					$result = $this->_tpl_vars['foldtype']->xpath('descendant::detailed');
					while (list(, $node) = each($result)) {
						echo $node->asXML();
					}
				 ?>
				</div>
			</div>
		</div>
	<?php endforeach; endif; unset($_from); ?>
</div>

<div id="formToBeLoaded"></div>
</form>
<?php 

function foldHasParam($param, $id) {
 $foutput = false;
  if (!isset($param->defaults)) return false;
  foreach ($param->defaults->default as $defaultVal) {
   $ftype=$defaultVal['foldtype'];
    if ("$ftype" == "$id"){ 
      $foutput=true;
    }
  }
  
  return $foutput;

}

function foldHasOutput($output, $id) {
	return foldHasParam($output, $id);
}

function getDefault($param, $id) {
	if (!isset($param->defaults)) return "";
	foreach ($param->defaults->default as $defaultVal) {
   $ftype=$defaultVal['foldtype'];
		if ("$ftype" == "$id") return $defaultVal;
	}
  
	return "";
}

function printDropDownVals($param) {
	foreach ($param->ranges->range->value as $value) {
		 ?><option value="<?php echo $value['id']; ?>"><?php echo $value; ?></option><?php 
	}
}

 ?>

<?php $_from = $this->_tpl_vars['foldtypes']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['foldtype']):
?>
<?php 
	$this->_tpl_vars['foldtypeId'] = $this->_tpl_vars['foldtype']['id'];
 ?>
<div id="foldContent_<?php echo $this->_tpl_vars['foldtypeId']; ?>
" class="ifoldTabContent">
	<h2 class="submitSteps">Step 3: Choose Type of Molecule:</h2>
	<h5 class="submitSteps">Please note: Simulations of DNA/RNA biomolecules are under development and will be added to iFold in due course.</h5>
	<table border="0" cellpadding="0" cellspacing="0" width="70%" height="50" class="ifoldTable submitParamsTable">
		<tr>
			<td id="molecule1" style="background:url(style/img/submit_protein.png) no-repeat top right;font-weight:bold"><input type="radio" name="molecule" value="1" onclick="selectMolecule('1')" style="width:30px"/> Protein</td>
			<td id="molecule2" style="background:url(style/img/submit_dna.png) no-repeat top right;font-weight:bold"><input type="radio" name="molecule" value="2" onclick="selectMolecule('2')" style="width:30px"/> DNA</td>
			<td id="molecule3" style="background:url(style/img/submit_rna.png) no-repeat top right;font-weight:bold"><input type="radio" name="molecule" value="3" onclick="selectMolecule('3')" style="width:30px"/> RNA</td>
		</tr>
	</table><br/>
  <script type="text/javascript">	selectMolecule('1'); </script>
	<h2 class="submitSteps">Step 4: Please Fill in the these Inputs:</h2>
	<table border="0" cellpadding="0" cellspacing="0" class="ifoldTable submitParamsTable">
	<?php $_from = $this->_tpl_vars['taskparams']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['taskparam']):
?>
		<?php if (isset ( $this->_tpl_vars['taskparam']->viewableAllFolds ) || foldHasParam ( $this->_tpl_vars['taskparam'] , $this->_tpl_vars['foldtypeId'] )): ?>
		<tr>
			<td width="70%"><?php echo $this->_tpl_vars['taskparam']->description; ?>
:</td>
			<td>
			<?php if ($this->_tpl_vars['taskparam']->type == 'upload'): ?>
				<input type="file" size="15" id="<?php echo $this->_tpl_vars['taskparam']->name; ?>
" name="<?php echo $this->_tpl_vars['taskparam']->name; ?>
" />
			<?php elseif ($this->_tpl_vars['taskparam']->type == 'dropdown'): ?>
				<select id="<?php echo $this->_tpl_vars['taskparam']->name; ?>
" name="<?php echo $this->_tpl_vars['taskparam']->name; ?>
">
					<?php  printDropDownVals($this->_tpl_vars['taskparam']);  ?>
				</select>
			<?php else: ?>
				<input type="text" id="<?php echo $this->_tpl_vars['taskparam']->name; ?>
" name="<?php echo $this->_tpl_vars['taskparam']->name; ?>
" value="<?php echo getDefault($this->_tpl_vars['taskparam'], $this->_tpl_vars['foldtypeId']); ?>"/>
			<?php endif; ?>
			</td>
		</tr>
		<?php endif; ?>
	<?php endforeach; endif; unset($_from); ?>
	</table><br/>
	<?php if (! isset ( $this->_tpl_vars['foldtype']->nooutputparams )): ?>
		<h2 class="submitSteps">Step 5: Select Your Outputs:</h2>
		<table border="0" cellpadding="0" cellspacing="0" class="ifoldTable submitParamsTable">
		<?php $_from = $this->_tpl_vars['taskoutputs']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['taskoutput']):
?>
			<?php if (foldHasOutput ( $this->_tpl_vars['taskoutput'] , $this->_tpl_vars['foldtypeId'] )): ?>
			<tr>
				<td width="70%"><?php echo $this->_tpl_vars['taskoutput']->description; ?>
:</td>
				<td><input
					<?php if ($this->_tpl_vars['taskoutput']->displaytype == 'text'): ?> 
						type="text" 
					<?php elseif ($this->_tpl_vars['taskoutput']->displaytype == 'checkbox'): ?>
						type="checkbox" onclick="toggleCheckbox(this)"
					<?php endif; ?>
					id="<?php echo $this->_tpl_vars['taskoutput']->name; ?>
" name="<?php echo $this->_tpl_vars['taskoutput']->name; ?>
" value="<?php echo getDefault($this->_tpl_vars['taskoutput'], $this->_tpl_vars['foldtypeId']); ?>"/></td>
			</tr>
			<?php endif; ?>
		<?php endforeach; endif; unset($_from); ?>
		</table><br/>
	<?php endif; ?>
  
	<input type="hidden" name="action" value="Submit Task" />
	<input type="submit" value="Submit Task" />
</div>
<?php endforeach; endif; unset($_from); ?>

<?php echo '
<script type="text/javascript">
	new Rico.Accordion( $(\'accordion\'), {panelHeight:110,borderColor:\'#639ACE\',collapsedBg:\'#E0ECEF\',expandedBg:\'#9BC1CF\',hoverBg:\'#D1E9EF\',hoverTextColor:\'#333366\',collapsedTextColor:\'#598D9F\',expandedTextColor:\'#333366\'});
</script>
'; ?>
