<?php

class DBRecordNotFoundException extends Exception {

	function __construct() {
    	super("Record not found in the database");
    }
}
?>