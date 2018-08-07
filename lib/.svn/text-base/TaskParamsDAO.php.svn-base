<?php
/********************************************************************
* @name Task Parameters Data Access Object
* @abstract contains properties of inputs for a single task
* 
* @since Mar 1, 2006
* -------------------------------------------------------------------/
*
* @author		Jameson Lopp jameson@unc.edu
* @author		Adi Unnithan adi@unc.edu
*				Daniel Watson dcwatson@email.unc.edu
*********************************************************************/

require_once 'DAO.class.php';
 
class TaskParamsDAO extends DAO {

	// the properties of the params DAO
	// can change at various points
	// please see /config/properties.xml
	// for the parameters.
		
    public function __construct() {
    	$this->table = "taskparams";
    }

	public function fetchByTask($id) {
    	$conn =& IFoldDB::getConn();
    	$query = "SELECT " . $this->table . ".* FROM tasks " . 
					"INNER JOIN " . $this->table . " " .
					"ON tasks.id = " . $conn->qstr($id, get_magic_quotes_gpc()) . " " .
					"AND tasks.param_id = " . $this->table . ".id LIMIT 1";
    	$rs = $conn->execute($query);
    	if ($rs->RecordCount() > 0) {
    		$rs->MoveFirst();
    		$this->digest($rs->fields);
    		return true;
    	} else {
    		return false;
    	}
	}
}
?>