<?php
/* File: helptest.php
 * Created on Apr 22, 2006 at 12:20:16 PM
 * Author: Adi Unnithan <unnithan@gmail.com>
 *************************************************/
 
require 'config.inc.php';
require 'lib/HelpDAO.class.php';

print "change content:";

if (isset($_POST['add'])) {
	$help = new HelpDAO();
	$help->set('content', $_POST['content']);
	$help->add();
	echo "added!";
} else if (isset($_POST['save'])) {
	$help = new HelpDAO();
	$help->fetch($_POST['id']);
	$help->set('content', $_POST['content']);
	$help->save();
	echo "saved!";
} else {

?>

what id to change:
<form method="post" action="helptest.php">
<input name="id" type="text" /><br/>
<textarea name="content">put content here</textarea>
<input type="submit" name="save" value="save"/> <input type="submit" name="add" value="add"/>
</form>
<?php } ?>