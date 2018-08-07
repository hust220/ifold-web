<script src="style/js/prototype.js" language="javascript" type="text/javascript"></script>
<script src="style/js/queue.js" language="javascript" type="text/javascript"></script>
<img src="style/img/indicator_medium.gif" alt="loading" title="loading" />
<script language="javascript" type="text/javascript">
	<?php if ($_GET['type'] == 'messages') { ?>
		loadMessages('<?php echo $_GET['id'] ?>');
	<?php } else { ?>
		loadParameters('<?php echo $_GET['id'] ?>');
	<?php } ?>
</script>