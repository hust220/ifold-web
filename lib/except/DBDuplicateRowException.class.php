<?php

class DBDuplicateRowException extends Exception {

	function __construct() {
    	super("Duplicate entry found in the database");
    }
}
?>