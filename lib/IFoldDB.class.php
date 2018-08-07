<?php
/********************************************************************
* @name IFoldDB
* @abstract Database class -- abstracts connection mechanism, SQL
* 			handling.
* @since Feb 12, 2006
* -------------------------------------------------------------------/
*
* 				Jameson Lopp jameson@unc.edu
* @author		Adi Unnithan adi@unc.edu
*				Daniel Watson dcwatson@email.unc.edu
*********************************************************************/

require "except/DBDuplicateRowException.class.php";
require "except/DBRecordNotFoundException.class.php";

class IFoldDB {

    private function __construct() {
    }
    
    public static function& getConn() {
    	static $conn;
    	if (!$conn) {
    		$props = new IFoldProps();
    		try {
	    		$conn = &ADONewConnection('mysql');
				$conn->connect(	$props->getDatabaseHost(), 
								$props->getDatabaseUser(), 
								$props->getDatabasePassword(), 
								$props->getDatabaseName()) or die('could not connect');
				$conn->SetFetchMode(ADODB_FETCH_ASSOC);	
    		} catch (exception $e) {
    			var_dump($e);
    			adodb_backtrace($e->gettrace());
    		}
    	}
    	return $conn;
    }
    
}
?>